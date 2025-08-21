#include "SourceSolution.h"
#include <QDebug>
#include <filesystem>

SourceSolution& SourceSolution::instance()
{
    static SourceSolution solution;
    return solution;
}

bool SourceSolution::registrate(const std::string& ext, CreateSourceMaker createfun)
{
    return callbacks.insert({ext, createfun}).second;
}

bool SourceSolution::has(const std::string& ext) const
{
    return callbacks.find(ext) != callbacks.end();
}

std::shared_ptr<ModelSource> SourceSolution::create(const std::string& path)
{
    std::filesystem::path fs_path(path);
    std::string ext = fs_path.extension().string();

    auto it = callbacks.find(ext);
    if (it != callbacks.end())
    {
        auto factory = it->second();
        return factory->create(path);
    }

    return nullptr;
}

