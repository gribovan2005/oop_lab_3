#ifndef SOURCESOLUTION_H
#define SOURCESOLUTION_H

#include <map>
#include <memory>
#include <string>
#include <functional>

#include "ModelSourceFactory.h"
#include "ModelSource.h"

class SourceSolution
{
public:
    using CreateSourceMaker = std::function<std::unique_ptr<ModelSourceFactory>()>;
    using CallBackMap = std::map<std::string, CreateSourceMaker>;

    static SourceSolution& instance();

    bool registrate(const std::string& ext, CreateSourceMaker createfun);
    bool has(const std::string& ext) const;
    std::shared_ptr<ModelSource> create(const std::string &path);

private:
    CallBackMap callbacks;

    SourceSolution() = default;
    ~SourceSolution() = default;

    SourceSolution(const SourceSolution&) = delete;
    SourceSolution& operator=(const SourceSolution&) = delete;
};

#endif 
