#ifndef VERTEXARRAYOBJECT_HPP
#define VERTEXARRAYOBJECT_HPP
#include "vertexTypes.hpp"
#include <vector>
class VertexArrayObject
{
private:
    unsigned int m_Vao;
    unsigned int m_Vbo;
    unsigned int m_Veo;
    std::vector<unsigned int> m_AttribList;
    unsigned int m_verticesCount;
    unsigned int m_indicesCount;
public:
    VertexArrayObject();
    ~VertexArrayObject();
    void Build(const std::vector<vertex3Tex>& vertices,
    const std::vector<unsigned int>& indices);
    void activate();
    void deactivate();
    unsigned int getVerticesCount();
    unsigned int getIndicesCount();
};
#endif