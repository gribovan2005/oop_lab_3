#ifndef CSVADJENCYSOURCE_H
#define CSVADJENCYSOURCE_H

#include "ModelSource.h"

#include <queue>
#include <fstream>
#include <sstream>

#include "AdjacencyList.h"

class CSVAdjencySource : public ModelSource
{
public:
    explicit CSVAdjencySource(const std::string& path);

    virtual std::optional<Vertex> nextVertex() override;
    virtual std::optional<Edge> nextEdge() override;

private:
    std::ifstream sourceFile{};
    std::queue<Vertex> vertexQueue{};
    std::queue<Edge> edgeQueue{};

    void readVertex(std::stringstream &ss);
    void readEdge(std::stringstream &ss);
    bool vertexEnd = false;

    void fileLineIter();
};

#endif 
