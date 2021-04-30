#include "square.hpp"
#include<cstdlib>
#include <iostream>
Square::Square(float x,float y)
{
    m_Position=glm::vec3(x,y,0.0f);
}
glm::vec3 Square::getPosition()
{
    return m_Position;
}
void Square::assagiGit()
{
    m_Position.y-=0.5f;
}
void Square::sagGit()
{
    m_Position.x+=0.5f;
}
void Square::solGit()
{
    m_Position.x-=0.5f;
}
void Square::setHareketImkani(bool HareketImkani)
{
    m_HareketImkani=HareketImkani;
}
bool Square::getHareketImkani()
{
    return m_HareketImkani;
}
void Square::Cevir(glm::vec3 orj)
{
    float x=m_Position.x-orj.x;
    float y=m_Position.y-orj.y;
    m_Position=glm::vec3(orj.x+(y*-1),orj.y+x,0.0f);
}
glm::vec3 Square::cevirsekNeOlur(glm::vec3 orj)
{
    float x=m_Position.x-orj.x;
    float y=m_Position.y-orj.y;
    return glm::vec3(orj.x+(y*-1),orj.y+x,0.0f);
}