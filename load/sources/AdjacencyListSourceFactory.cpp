#include "AdjacencyListSourceFactory.h"

#include <QDebug>
#include "AdjacencyListSource.h"

std::shared_ptr<ModelSource> AdjacencyListSourceFactory::create(const std::string &path)
{
    return std::make_shared<AdjacencyListSource>(path);
}
