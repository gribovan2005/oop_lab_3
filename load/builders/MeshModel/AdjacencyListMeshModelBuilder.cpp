#include "AdjacencyListMeshModelBuilder.h"

#include <map>
#include <set>
#include <QDebug>

AdjacencyListMeshModelBuilder::AdjacencyListMeshModelBuilder(std::shared_ptr<ModelSource> source)
{
    source_ = source;
}

bool AdjacencyListMeshModelBuilder::buildVertex()
{
    
    if (!part)
        ++part;

    if (part != 1) return false;
    
    std::optional<Vertex> maybeVertex{};
    maybeVertex = source_->nextVertex();
    while (maybeVertex.has_value())
    {
        vertices.push_back(maybeVertex.value());
        maybeVertex = source_->nextVertex();
    }
    
    return true;
}

bool AdjacencyListMeshModelBuilder::buildEdge()
{
    qDebug() << "start build edge";
    if (part == 1)
        ++part;

    if (part != 2) return false;

    std::optional<Edge> maybeEdge{};
    maybeEdge = source_->nextEdge();
    while (maybeEdge.has_value())
    {
        adjacencyList.add(maybeEdge.value().getFirstInd(), maybeEdge.value().getSecondInd());
        maybeEdge = source_->nextEdge();
    }

    return true;
}

bool AdjacencyListMeshModelBuilder::buildFaces()
{   
    
    if (part == 2)
        ++part;

    if (part != 3)
        return false;

    int count = 0;
    for (const auto& v1 : vertices)
    {
        int v1_index = count;

        if (!adjacencyList.contains(v1_index))
        {
            ++count;
            continue;
        }

        const auto& neighbours = adjacencyList.get(v1_index);

        qDebug() << "hello 1";
        if (neighbours.size() < 2)
        {  
            ++count;
            continue;
        }

        auto it1 = neighbours.begin();
        for (; it1 != neighbours.end(); ++it1)
        {
            auto it2 = std::next(it1);
            for (; it2 != neighbours.end(); ++it2)
            {
                int v2_index = *it1;
                int v3_index = *it2;
                qDebug() << "hello 2";
                Vertex vertex1 = vertices[v2_index];
                Vertex vertex2 = vertices[v3_index];
                qDebug() << "hello 3";
                if (v1.isOnPlane(vertex1, vertex2, v1))
                {
                    qDebug() << "hello 4";
                    bool added = false;
                    for (auto& surface : surfaces)
                    {
                        if (surface.count(v2_index) > 0 && surface.count(v3_index) > 0 && surface.count(v1_index) > 0)
                        {
                            surface.insert(v1_index);
                            added = true;
                            break;
                        }
                    }
                    qDebug() << "hello 5";
                    if (!added)
                    {
                        std::set<int> newSurface = { v1_index, v2_index, v3_index };
                        surfaces.push_back(newSurface);
                    }
                }
            }
        }
        ++count;
    }
    qDebug() << "hello6";
    remove_duplicate_surfaces(surfaces);
    return true;
}

void AdjacencyListMeshModelBuilder::remove_duplicate_surfaces(std::vector<std::set<int>>& surfaces)
{
    std::set<std::set<int>> unique_surfaces;
    std::vector<std::set<int>> filtered;

    for (const auto& surf : surfaces)
    {
        if (unique_surfaces.insert(surf).second)
            filtered.push_back(surf);
    }

    surfaces = std::move(filtered);
}


std::shared_ptr<BaseModel> AdjacencyListMeshModelBuilder::get()
{
    if (!model_) { model_ = create(); }

    return model_;
}

std::shared_ptr<BaseModel> AdjacencyListMeshModelBuilder::create()
{
    if (part == 3)
    {
        auto modelData = std::make_shared<AdjacencyListData>(vertices, adjacencyList, surfaces);

        model_ = std::make_shared<MeshModel>(modelData);
    }

    return model_;
}

