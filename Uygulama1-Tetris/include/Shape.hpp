#ifndef SHAPE_HPP
#define SHAPE_HPP
#include<square.hpp>
#include<vector>
#include<glm/vec3.hpp>
class Shape
{
public:
    enum DIR { Left, Right,Down,NoDir};
    Shape();
    std::vector<Square> Sekil;
    void setYon(DIR Yon);
    void Hareket();
    DIR getYon();
private:
    DIR m_Yon;
    void SagHareket();
    void SolHareket();
    void AssagiHareket();
};
#endif