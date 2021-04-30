#ifndef SQUARE_HPP
#define SQUARE_HPP
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>
class Square
{
public:
    enum DIRECTION
    {
        DIR_RIGHT =1,
        DIR_LEFT =-1,
        DIR_UP =2,
        DIR_DOWN =-2
    };

    Square(float x,float y,float length);


    glm::vec3 getPosition();
    glm::vec4 getColor();
    void setDirection(DIRECTION dir);
    Square::DIRECTION getDirection();
    void move();
private:
    glm::vec3 m_Position;
    glm::vec4 m_Color;
    DIRECTION m_Direction;
    float m_lenght;
};

#endif