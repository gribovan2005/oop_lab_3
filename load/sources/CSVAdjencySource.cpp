#include "CSVAdjencySource.h"
#include "LoadException.h"

CSVAdjencySource::CSVAdjencySource(const std::string& path)
{
    sourceFile = std::ifstream(path);
    if (sourceFile.fail())
        throw FileError(__FILE__, __LINE__, "Could not open file");
}

std::optional<Vertex> CSVAdjencySource::nextVertex()
{
    while (vertexQueue.empty() && !sourceFile.eof())
        fileLineIter();

    if (vertexQueue.empty())
        return std::nullopt;

    auto curVertex = vertexQueue.front();
    vertexQueue.pop();
    return curVertex;
}

std::optional<Edge> CSVAdjencySource::nextEdge()
{
    while (edgeQueue.empty() && !sourceFile.eof())
        fileLineIter();

    if (edgeQueue.empty())
        return std::nullopt;

    auto curEdge = edgeQueue.front();
    edgeQueue.pop();
    return curEdge;
}

void CSVAdjencySource::readVertex(std::stringstream &ss)
{
    std::string token;
    double coords[3];
    int i = 0;

    while (std::getline(ss, token, ',') && i < 3)
    {
        std::stringstream valStream(token);
        valStream >> coords[i++];
        if (valStream.fail())
            throw FileError(__FILE__, __LINE__, "Invalid vertex coordinate");
    }

    if (i != 3)
        throw FileError(__FILE__, __LINE__, "Vertex must have 3 coordinates");

    vertexQueue.push(Vertex(coords[0], coords[1], coords[2]));
}

void CSVAdjencySource::readEdge(std::stringstream &ss)
{
    std::string token;
    int firstInd = -1;

    if (!std::getline(ss, token, ','))
        throw FileError(__FILE__, __LINE__, "Missing first index");

    std::stringstream firstStream(token);
    firstStream >> firstInd;

    if (firstStream.fail())
        throw FileError(__FILE__, __LINE__, "Invalid first index");

    while (std::getline(ss, token, ','))
    {
        std::stringstream secondStream(token);
        int secondInd;
        secondStream >> secondInd;

        if (secondStream.fail())
            throw FileError(__FILE__, __LINE__, "Invalid second index");

        edgeQueue.push(Edge(firstInd, secondInd));
    }
}

void CSVAdjencySource::fileLineIter()
{
    std::string buffer;

    if (!std::getline(sourceFile, buffer))
        return;

    buffer.erase(0, buffer.find_first_not_of(" \t\r\n"));
    buffer.erase(buffer.find_last_not_of(" \t\r\n") + 1);

    if (buffer == "vertex_end")
    {
        vertexEnd = true;
        return;
    }

    std::stringstream ss(buffer);

    if (vertexEnd)
        readEdge(ss);
    else
        readVertex(ss);
}
