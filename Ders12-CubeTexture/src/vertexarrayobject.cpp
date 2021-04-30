#include "vertexarrayobject.hpp"
#include <glad/glad.h>
#include "vertexTypes.hpp"
VertexArrayObject::VertexArrayObject()
{
    m_Vao=0;
    m_Vbo=0;
    m_Veo=0;
}
VertexArrayObject::~VertexArrayObject()
{
    if (m_Vao)
    {
        glDeleteBuffers(1,&m_Vao);
        glDeleteBuffers(1,&m_Vbo);
        glDeleteBuffers(1,&m_Veo);
    }

}
void VertexArrayObject::Build(const std::vector<vertex3Tex>& vertices,
    const std::vector<unsigned int>& indices)
{
    glGenVertexArrays(1,&m_Vao);
    glGenBuffers(1,&m_Vbo);

    glGenBuffers(1,&m_Veo);
    
    glBindVertexArray(m_Vao);

    glBindBuffer(GL_ARRAY_BUFFER,m_Vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertex3Tex)*vertices.size(),&vertices[0],GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(float)*5,(void*)0);
    glEnableVertexAttribArray(0);
    //kaplama
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,sizeof(float)*5,(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_Veo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*indices.size(),&indices[0],GL_STATIC_DRAW);

    m_AttribList.push_back(0);
    m_AttribList.push_back(1);
}
void VertexArrayObject::activate()
{
    glBindVertexArray(m_Vao);
    for(auto siradaki:m_AttribList)
    {
        glEnableVertexAttribArray(siradaki);
    }
}
void VertexArrayObject::deativate()
{
    for(auto siradaki:m_AttribList)
    {
        glDisableVertexAttribArray(siradaki);
    }
    glBindVertexArray(0);
}