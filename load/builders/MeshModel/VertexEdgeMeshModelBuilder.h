#ifndef VERTEXEDGEMESHMODELBUILDER_H
#define VERTEXEDGEMESHMODELBUILDER_H

#include "MeshModelBuilder.h"

#include "Edge.h"
#include <set>
#include <map>

#include "MeshModel.h"
#include "VertexEdgeData.h"

class VertexEdgeMeshModelBuilder : public MeshModelBuilder
{
public:
    explicit VertexEdgeMeshModelBuilder(std::shared_ptr<ModelSource> source);

    virtual bool buildVertex() override;
    virtual bool buildEdge() override;
    virtual bool buildFaces() override;

    virtual std::shared_ptr<BaseModel> get() override;
    void remove_duplicate_surfaces(std::vector<std::set<int>>& surfaces);

protected:
    virtual std::shared_ptr<BaseModel> create() override;

private:
    std::vector<Vertex> vertices{};
    std::vector<Edge> edges{};
    std::vector<std::set<int>> surfaces{};
};

#endif 
