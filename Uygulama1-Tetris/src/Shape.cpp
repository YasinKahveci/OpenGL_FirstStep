#include<Shape.hpp>
#include <ctime>
Shape::Shape()
{
    int ilkKonum;
    float ilkKonumFloat;
    srand((unsigned int)time(NULL));
    int Tip=std::rand()%3;
    if (Tip==0)//T sekli
    {
        ilkKonum=3-(std::rand()%7);
        ilkKonumFloat=float(ilkKonum);
        Sekil.push_back(Square(ilkKonumFloat,4.0f));
        Sekil.push_back(Square(ilkKonumFloat-0.5f,4.0f));
        Sekil.push_back(Square(ilkKonumFloat,3.5f));
        Sekil.push_back(Square(ilkKonumFloat+0.5f,4.0f));
    }
    if (Tip==1)//Z sekli
    {
        ilkKonum=3-(std::rand()%7);
        ilkKonumFloat=float(ilkKonum);
        Sekil.push_back(Square(ilkKonumFloat,4.0f));
        Sekil.push_back(Square(ilkKonumFloat-0.5f,4.0f));
        Sekil.push_back(Square(ilkKonumFloat,3.5f));
        Sekil.push_back(Square(ilkKonumFloat+0.5f,3.5f));
    }
    if (Tip==2)//I sekli
    {
        ilkKonum=4-(std::rand()%5);
        ilkKonumFloat=float(ilkKonum);
        Sekil.push_back(Square(ilkKonumFloat,3.5f));
        Sekil.push_back(Square(ilkKonumFloat,4.0f));
        Sekil.push_back(Square(ilkKonumFloat,3.0f));
        Sekil.push_back(Square(ilkKonumFloat,2.5f));
    }
}
void Shape::SagHareket()
{
    for (int i=0;i<4;i++)
        Sekil.at(i).sagGit();
}
void Shape::SolHareket()
{
    for (int i=0;i<4;i++)
        Sekil.at(i).solGit();
}
void Shape::AssagiHareket()
{
    for (int i=0;i<4;i++)
        Sekil.at(i).assagiGit();
}
void Shape::setYon(DIR Yon)
{
    m_Yon=Yon;
}
void Shape::Hareket()
{
    if (m_Yon==Left)
    {
        SolHareket();
    }
    else if (m_Yon==Right)
    {
        SagHareket();
    }
    else if (m_Yon==Down)
    {
        AssagiHareket();
    }
    m_Yon=NoDir;
}
Shape::DIR Shape::getYon()
{
    return m_Yon;
}