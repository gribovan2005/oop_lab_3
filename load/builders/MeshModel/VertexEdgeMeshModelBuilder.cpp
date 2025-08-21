#include "VertexEdgeMeshModelBuilder.h"

#include <set>
#include <map> 
#include <QDebug>

VertexEdgeMeshModelBuilder::VertexEdgeMeshModelBuilder(std::shared_ptr<ModelSource> source)
{
    source_ = source;
}

bool VertexEdgeMeshModelBuilder::buildVertex()
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

bool VertexEdgeMeshModelBuilder::buildEdge()
{
    if (part == 1)
        ++part;

    if (part != 2) return false;

    std::optional<Edge> maybeEdge{};
    maybeEdge = source_->nextEdge();
    while (maybeEdge.has_value())
    {
        edges.push_back(maybeEdge.value());
        maybeEdge = source_->nextEdge();
    }

    return true;
}

bool VertexEdgeMeshModelBuilder::buildFaces() 
{
    if (part == 2) 
        ++part;

    if (part != 3) 
        return false;

    std::map<int, std::set<int>> adjacencyList;

    for (const auto& edge : edges) 
    {
        int u = edge.getFirstInd();
        int v = edge.getSecondInd();
        adjacencyList[u].insert(v);
        adjacencyList[v].insert(u);
    }
    
    int count = 0;
    for (const auto& v1 : vertices) 
    {
        for (const auto& [v2, neighbours] : adjacencyList) 
        {
            if (neighbours.size() < 2) 
                continue;  

            Vertex vertex1 = vertices[v2]; 

            auto it1 = neighbours.begin();
            for (; it1 != neighbours.end(); ++it1) 
            {
                auto it2 = std::next(it1); 
                for (; it2 != neighbours.end(); ++it2) 
                {
                    int element_1 = *it1;
                    int element_2 = *it2;

                    Vertex vertex2 = vertices[element_1];
                    Vertex vertex3 = vertices[element_2];

                    if (v1.isOnPlane(vertex1, vertex2, vertex3)) 
                    { 
                        bool added = false;
                        for (auto& surface : surfaces) 
                        {
                            if (surface.count(element_1) > 0 && surface.count(element_2) > 0 && surface.count(v2) > 0) 
                            {
                                surface.insert(count); 
                                added = true;
                                break;
                            }
                        }

                        if (!added) 
                        {
                            std::set<int> newSurface = {element_1, element_2, v2, count};
                            surfaces.push_back(newSurface);
                        }
                    }
                }
            }
        }
        count++;
    }

    remove_duplicate_surfaces(surfaces);
    return true;
}


void VertexEdgeMeshModelBuilder::remove_duplicate_surfaces(std::vector<std::set<int>>& surfaces)
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


std::shared_ptr<BaseModel> VertexEdgeMeshModelBuilder::get()
{
    if (!model_) { model_ = create(); }

    return model_;
}

std::shared_ptr<BaseModel> VertexEdgeMeshModelBuilder::create()
{
    if (part == 3)
    {
        auto modelData = std::make_shared<VertexEdgeData>(vertices, edges, surfaces);
        
        model_ = std::make_shared<MeshModel>(modelData);
    }

    return model_;
}
