#include "CSVEdgeSource.h"
#include "LoadException.h"

#include <sstream>
#include <algorithm>

CSVEdgeSource::CSVEdgeSource(const std::string& path)
{
    sourceFile = std::ifstream(path);
    if (sourceFile.fail())
        throw FileError(__FILE__, __LINE__, "Could not open file");
}

std::optional<Vertex> CSVEdgeSource::nextVertex()
{
    while (vertexQueue.empty() && !sourceFile.eof())
        fileLineIter();

    if (vertexQueue.empty())
        return std::nullopt;

    auto curVertex = vertexQueue.front();
    vertexQueue.pop();

    return curVertex;
}

std::optional<Edge> CSVEdgeSource::nextEdge()
{
    while (edgeQueue.empty() && !sourceFile.eof())
        fileLineIter();

    if (edgeQueue.empty())
        return std::nullopt;

    auto curEdge = edgeQueue.front();
    edgeQueue.pop();

    return curEdge;
}

void CSVEdgeSource::readVertex(std::stringstream &ss)
{
    std::string token;
    double coords[3];
    int i = 0;

    while (std::getline(ss, token, ',') && i < 3)
    {
        token.erase(std::remove_if(token.begin(), token.end(), ::isspace), token.end());
        std::stringstream valStream(token);
        valStream >> coords[i++];
        if (valStream.fail())
            throw FileError(__FILE__, __LINE__, "Invalid vertex coordinate");
    }

    if (i != 3)
        throw FileError(__FILE__, __LINE__, "Vertex must have 3 coordinates");

    vertexQueue.push(Vertex(coords[0], coords[1], coords[2]));
}

void CSVEdgeSource::readEdge(std::stringstream &ss)
{
    std::string token;
    int values[2];
    int i = 0;

    while (std::getline(ss, token, ',') && i < 2)
    {
        token.erase(std::remove_if(token.begin(), token.end(), ::isspace), token.end());
        std::stringstream valStream(token);
        valStream >> values[i++];
        if (valStream.fail())
            throw FileError(__FILE__, __LINE__, "Invalid edge index");
    }

    if (i != 2)
        throw FileError(__FILE__, __LINE__, "Edge must have 2 indices");

    edgeQueue.push(Edge(values[0], values[1]));
}

void CSVEdgeSource::fileLineIter()
{
    std::string buffer;
    std::getline(sourceFile, buffer);

    if (buffer.empty())
        return;

    std::stringstream ss(buffer);
    std::string prefix;
    std::getline(ss, prefix, ',');

    prefix.erase(std::remove_if(prefix.begin(), prefix.end(), ::isspace), prefix.end());

    if (prefix == "v")
        readVertex(ss);
    else if (prefix == "e")
        readEdge(ss);
}
