#include "DrawVisitor.h"

#include "glm_wrapper.h"
#include <QDebug>
#include "VertexEdgeData.h"
#include "AdjacencyListData.h"

DrawVisitor::DrawVisitor(std::shared_ptr<BaseDrawer> drawer, std::shared_ptr<BaseCamera> camera)
{
    drawer_ = std::move(drawer);
    camera_ = std::move(camera);
}

void DrawVisitor::visit(Scene &scene)
{
    for (auto& [_, i]: scene)
        if (i->isVisible())
            i->accept(*this);
}




void DrawVisitor::visit(MeshModel &model) 
{
    const auto modelData = model.data_;
    const auto model_matrix = model.getTransformMatrix();

    Matrix4 view_matrix = camera_->getViewMatrix();
    Matrix4 projection_matrix = camera_->getProjectionMatrix();
    Matrix4 matr = projection_matrix * view_matrix * context * model_matrix;

    const auto& vertices = modelData->getVertices();
    const auto& surfaces = modelData->getSurfaces();
    const auto& edges = modelData->getEdges();
    Vector3 camera_position = camera_->getPosition();
    
    for (const auto& face : surfaces)
    {
        QString indices_str = "Face indices: ";
        for (int idx : face)
        {
            indices_str += QString::number(idx) + " ";
        }
        qDebug() << indices_str;
        
    }
    
    Vector3 center(0, 0, 0);
    for (const auto& vertex : vertices) 
    {
        Vector3 world_pos = model_matrix * Vector3(vertex.getX(), vertex.getY(), vertex.getZ());
        center += world_pos;
    }
    if (!vertices.empty()) 
    {
        center /= static_cast<float>(vertices.size());
    }

    for (const auto& face : surfaces) 
    {
        if (face.size() < 3) continue;

        auto it = face.begin();
        int v1 = *it; it++;
        int v2 = *it; it++;
        int v3 = *it;

        Vertex vert_1 = vertices[v1];
        Vertex vert_2 = vertices[v2];
        Vertex vert_3 = vertices[v3];

        Vector3 world_p0 = model_matrix * Vector3(vert_1.getX(), vert_1.getY(), vert_1.getZ());
        Vector3 world_p1 = model_matrix * Vector3(vert_2.getX(), vert_2.getY(), vert_2.getZ());
        Vector3 world_p2 = model_matrix * Vector3(vert_3.getX(), vert_3.getY(), vert_3.getZ());

        Vector3 edge1 = world_p1 - world_p0;
        Vector3 edge2 = world_p2 - world_p0;
        Vector3 normal = normalize(cross(edge1, edge2));

        Vector3 to_face = world_p0 - center;
        if (dot(normal, to_face) < 0) 
        {
            normal = -normal;
        }

        Vector3 camera_vec = camera_position - world_p0;
        if (dot(normal, camera_vec) > 0) 
        {
            for (auto it_1 = face.begin(); it_1 != face.end(); it_1++) 
            {
                for (auto it_2 = face.begin(); it_2 != face.end(); it_2++) 
                {
                    bool is_edge = false;
                    for (const auto &edge : edges) 
                    {
                        if ((edge.getFirstInd() == *it_1 && edge.getSecondInd() == *it_2) || 
                            (edge.getFirstInd() == *it_2 && edge.getSecondInd() == *it_1)) 
                        {
                            is_edge = true;
                            break;
                        }
                    }
                    if (is_edge) 
                    {
                        Vertex vert = vertices[*it_1];
                        Vertex vert_an = vertices[*it_2];
                        Vector3 v_start = matr * Vector3(vert.getX(), vert.getY(), vert.getZ());
                        Vector3 v_end = matr * Vector3(vert_an.getX(), vert_an.getY(), vert_an.getZ());
                        drawer_->drawLine(v_start[0], v_start[1], v_end[0], v_end[1]);
                    }
                }
            }
        }
    }
}



void DrawVisitor::visit(LightSource &light)
{

}


void DrawVisitor::visit(BaseCamera &camera)
{

}


void DrawVisitor::clearTransformContext()
{
    context = Matrix4(1.0);
}
void DrawVisitor::addTransformContext(const Matrix4 &ctx)
{
    context = context * ctx;
}
