#ifndef SQUARE_HPP
#define SQUARE_HPP
#include<glm/vec3.hpp>
class Square
{
public:
    Square(float x,float y);
    glm::vec3 getPosition();
    void assagiGit();
    void sagGit();
    void solGit();
    void setHareketImkani(bool HareketImkani);
    bool getHareketImkani();
    void Cevir(glm::vec3 orj);
    glm::vec3 cevirsekNeOlur(glm::vec3 orj);
private:
    glm::vec3 m_Position;
    bool m_HareketImkani=true;
};

#endif