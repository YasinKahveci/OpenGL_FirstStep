#ifndef MESH_HPP
#define MESH_HPP

class VertexArrayObject;
class MeshManager;
class Mesh
{
private:
    VertexArrayObject* m_VAO;
    unsigned int m_IndexCount;
    unsigned int m_VertexCount;
public:
    Mesh();
    void Draw();
    friend MeshManager;
};

#endif