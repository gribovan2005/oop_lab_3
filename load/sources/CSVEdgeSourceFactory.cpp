#include "CSVEdgeSource.h"
#include "CSVEdgeSourceFactory.h"

std::shared_ptr<ModelSource> CSVEdgeSourceFactory::create(const std::string &path)
{
    return std::make_shared<CSVEdgeSource>(path);
}
