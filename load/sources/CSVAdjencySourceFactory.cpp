#include "CSVAdjencySource.h"

#include "CSVAdjencySourceFactory.h"

std::shared_ptr<ModelSource> CSVAdjencySourceFactory::create(const std::string &path)
{
    return std::make_shared<CSVAdjencySource>(path);
}
