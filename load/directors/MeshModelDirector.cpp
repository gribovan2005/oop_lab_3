#include "MeshModelDirector.h"

#include <QDebug>

std::shared_ptr<BaseModel> MeshModelDirector::create(std::shared_ptr<ModelBuilder> builder)
{
    
    if (builder->buildVertex() && builder->buildEdge() && builder->buildFaces())
        qDebug() << "builded";
        return builder->get();

    return nullptr;
}
