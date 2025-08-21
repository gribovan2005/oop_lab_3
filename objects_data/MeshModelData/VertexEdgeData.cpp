#include "VertexEdgeData.h"

#include <QDebug>
#include <map>
#include <set>
#include <tuple>
#include <algorithm>

VertexEdgeData::VertexEdgeData(std::vector<Vertex> vertices, std::vector<Edge> edges, std::vector<std::set<int>> faces) :
    vertices_(std::move(vertices)), edges_(std::move(edges)), surfaces_(std::move(faces))
{

}

const std::vector<Vertex>& VertexEdgeData::getVertices() const
{
    return vertices_;
}

const std::vector<Edge>& VertexEdgeData::getEdges() const
{
    return edges_;
}

void VertexEdgeData::addVertex(const Vertex& vertex)
{
    vertices_.push_back(vertex);
}

void VertexEdgeData::addEdge(const Edge& edge)
{
    edges_.push_back(edge);
}


std::vector<std::set<int>> VertexEdgeData::getSurfaces()
{
    return surfaces_;
}