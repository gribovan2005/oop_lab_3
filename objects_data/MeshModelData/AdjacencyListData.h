#ifndef ADJACENCYLISTDATA_H
#define ADJACENCYLISTDATA_H

#include "MeshModelData.h"

#include <vector>
#include <set>
#include "Vertex.h"
#include "Edge.h"
#include "AdjacencyList.h"

class AdjacencyListData : public MeshModelData
{
public:
    AdjacencyListData(std::vector<Vertex> vertices, AdjacencyList adjacencyList, std::vector<std::set<int>> faces);
    const std::vector<Vertex>& getVertices() const override;
    const std::vector<Edge>& getEdges() const override;

    void addVertex(const Vertex& vertex) override;
    void addEdge(const Edge& edge) override;

    std::vector<std::set<int>> getSurfaces() override;

private:
    std::vector<Vertex> vertices_;
    AdjacencyList adjacencyList_;
    std::vector<std::set<int>> surfaces_;
};

#endif 
