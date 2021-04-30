#include "Mesh.hpp"
#include "vertexarrayobject.hpp"
#include "glad/glad.h"
Mesh::Mesh()
{

}
void Mesh::Draw()
{
    m_VAO->activate();
    glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, 0);
    m_VAO->deactivate();
}
