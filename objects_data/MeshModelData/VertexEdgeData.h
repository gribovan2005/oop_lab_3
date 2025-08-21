#ifndef VERTEXEDGEDATA_H
#define VERTEXEDGEDATA_H

#include "MeshModelData.h"

#include <vector>

#include "Edge.h"

#include <array>
#include <set>

class VertexEdgeData : public MeshModelData
{
public:
    VertexEdgeData(std::vector<Vertex> vertices, std::vector<Edge> edges, std::vector<std::set<int>> faces);

    virtual const std::vector<Vertex>& getVertices() const override;
    virtual const std::vector<Edge>& getEdges() const override;

    virtual void addVertex(const Vertex& vertex) override;
    virtual void addEdge(const Edge& edge) override;

    std::vector<std::set<int>> getSurfaces() override;
private:
    std::vector<Vertex> vertices_;
    std::vector<Edge> edges_;
    std::vector<std::set<int>> surfaces_;
};

#endif 
