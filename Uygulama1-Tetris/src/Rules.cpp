#include "Rules.hpp"
#include <iostream>
Rules* Rules::Point =nullptr;
Rules::Rules()
{
    begin=clock();
    Shapes.push_back(Shape());
}
Rules* Rules::getInstance()
{
    if (Point==nullptr)
    {
        Point=new Rules();
    }
    return Point;
}
void Rules::OyunDongusu()
{
    SetMoves();//Butun cisimlerin hareketini baslangicta true yapiyor.
    YerCekimi();//Cisimlerin yer cekiminden etkilenip dusmesi gereken cisimlere bool atiyor.(false atiyor hareket edemeyenlere)
    HareketEttir();//Yer cekiminden etkilenen cisimleri hareket ettiriyor.
    SatiriSil();//Eger Satirda Kareler yerlesmisse satiri siler.
    Olustur();//Tum cisimler hareket etmez durumdaysa yeni cisim olusturuyor.
    KlavyeHareketiKontrol();//Dusen cismin sag sola ve assagi hareketini sagliyor.
}
void Rules::Olustur()
{
    if(CisimlerDurduMu())
        Shapes.push_back(Shape());
}
void Rules::YerCekimi()
{
    for (int i = 0; i < Shapes.size(); i++)
    {
        int j=0;
        for (; j < Shapes.at(i).Sekil.size(); j++)
        {               
            for (int x = 0; x < Shapes.size(); x++)
            {
                for (int y=0; y < Shapes.at(x).Sekil.size(); y++)
                {
                    if(!AssagiHareketEdebilirMi(Shapes.at(i).Sekil.at(j).getPosition(),Shapes.at(x).Sekil.at(y).getPosition()))
                    {
                        Shapes.at(i).Sekil.at(j).setHareketImkani(false);
                        x=Shapes.size();//for double break;
                        break;
                    }

                }

            }
        }
    }
}
bool Rules::AssagiHareketEdebilirMi(glm::vec3 v1,glm::vec3 v2)
{
    if (v1.y<=-4.0f)
    {
        return false;
    }
    if (v2.y>v1.y || v2.x!=v1.x)
    {
        return true;
    }
    else if((v1.y-v2.y)>0.5||((v1.y-v2.y)==0&&v2.x==v1.x))
    {
        return true;
    }
    else if (AltiBosMu(v1))
    {
        return true;
    }
    return false;
}
bool Rules::AltiBosMu(glm::vec3 v1)
{
    bool bos=false;
    bool c=false;
    float pos=v1.y;
    for (int i = 0; i < int(abs((-4.0f-v1.y)*2)); i++)
    {
        pos-=0.5f;
        c=false;
        for (int i = 0; i < Shapes.size(); i++)
        {
            if (c)
            {
                c=false;
                break;
            }
            for (int j = 0; j < Shapes.at(i).Sekil.size(); j++)
            {
                if (v1.x==Shapes.at(i).Sekil.at(j).getPosition().x&&v1.y>Shapes.at(i).Sekil.at(j).getPosition().y)
                {
                    if (pos!=Shapes.at(i).Sekil.at(j).getPosition().y)
                    {
                        bos=true;
                    }
                    else
                    {
                        for (int x = 0; x < Shapes.at(i).Sekil.size(); x++)
                        {
                            if (!(Shapes.at(i).Sekil.at(x).getHareketImkani()))
                            {
                                return false;
                            }
                        }

                        bos=false;
                        c=true;
                        break;
                    }
                }
            }
        }
        if (bos)
        {
            return true;
        }
    }
    return false;
}
void Rules::HareketEttir()
{
    end=clock();
    time_spent=double(end-begin)/CLOCKS_PER_SEC;
    if (time_spent>0.6)
    {
        for (int i = 0; i < Shapes.size(); i++)
        {
            if (Shapes.at(i).Sekil.size()==4)
            {
                if(Shapes.at(i).Sekil.at(0).getHareketImkani()&&Shapes.at(i).Sekil.at(1).getHareketImkani()&&Shapes.at(i).Sekil.at(2).getHareketImkani()&&Shapes.at(i).Sekil.at(3).getHareketImkani())
                {
                    for (int j = 0; j <Shapes.at(i).Sekil.size() ; j++)
                    {
                        Shapes.at(i).Sekil.at(j).assagiGit();
                    }
                }
            }
            else
            {
                for (int j = 0; j <Shapes.at(i).Sekil.size() ; j++)
                {
                    if (Shapes.at(i).Sekil.at(j).getHareketImkani())
                    {
                        Shapes.at(i).Sekil.at(j).assagiGit();
                    }
                }
            }
        }
        begin=clock();
    }
}
void Rules::SutunKontrol()
{
    bool Var=false;
    for (float y = -4.0f; y <= +4.0f; y+=0.5f)
    {
        for (float x = -4.0f; x <= +4.0f; x+=0.5f)
        {
            Var=false;
            for (int i = 0; i < Shapes.size(); i++)
            {
                for (int j = 0; j < Shapes.at(i).Sekil.size(); j++)
                {
                    if (Shapes.at(i).Sekil.at(j).getPosition()==glm::vec3(x,y,0.0f))
                    {
                        i=Shapes.size();
                        Var=true;
                        break;
                    }
                                        
                }
            }
            if (!Var)
            {
                break;
            }
            if (Var&&x==+4.0f)
            {
                SutunuSil(y);
                
            }
        }
    }
    
}
void Rules::SutunuSil(float y1)
{
    for (int i = 0; i < Shapes.size(); i++)
    {
        for (int j = 0; j < Shapes.at(i).Sekil.size(); j++)
        {
            if (Shapes.at(i).Sekil.at(j).getPosition().y==y1)
            {
                Shapes.at(i).Sekil.erase(Shapes.at(i).Sekil.begin()+j);
                j--;
                
            }    
        }
        if (Shapes.at(i).Sekil.size()==0)
        {
            Shapes.erase(Shapes.begin()+i);
            i--;
        }
    }

}
void Rules::SetMoves()
{
    for (int x = 0; x < Shapes.size(); x++)
    {
        for (int y=0; y < Shapes.at(x).Sekil.size(); y++)
        {
            Shapes.at(x).Sekil.at(y).setHareketImkani(true);   
        }

    }
}
void Rules::KlavyeHareketiKontrol()
{
    if (KlavyeHareketIzin())
    {
        Shapes.at(Shapes.size()-1).Hareket();
    }
}
bool Rules::KlavyeHareketIzin()
{
    if (Shapes.at(Shapes.size()-1).getYon()==Shape::Left)
    {
        for (int i = 0; i < Shapes.size()-1; i++)
        {
            for (int j = 0; j < Shapes.at(i).Sekil.size(); j++)
            {
                for (int x = 0; x < Shapes.at(Shapes.size()-1).Sekil.size(); x++)
                {
                    if ((Shapes.at(Shapes.size()-1).Sekil.at(x).getPosition()-glm::vec3(0.5,0.0,0.0))==Shapes.at(i).Sekil.at(j).getPosition())
                    {
                        return false;
                    }
                    
                }
                   
            }
            
        }
        for (int i = 0; i < Shapes.at(Shapes.size()-1).Sekil.size(); i++)
        {
            if ((Shapes.at(Shapes.size()-1).Sekil.at(i).getPosition().x-0.5)==-4.5f)
            {
                return false;
            }
            
        }
    
    }
    else if (Shapes.at(Shapes.size()-1).getYon()==Shape::Right)
    {
        for (int i = 0; i < Shapes.size()-1; i++)
        {
            for (int j = 0; j < Shapes.at(i).Sekil.size(); j++)
            {
                for (int x = 0; x < Shapes.at(Shapes.size()-1).Sekil.size(); x++)
                {
                    if ((Shapes.at(Shapes.size()-1).Sekil.at(x).getPosition()+glm::vec3(0.5,0.0,0.0))==Shapes.at(i).Sekil.at(j).getPosition())
                    {
                        return false;
                    }
                    
                }
                   
            }
            
        }
        for (int i = 0; i < Shapes.at(Shapes.size()-1).Sekil.size(); i++)
        {
            if ((Shapes.at(Shapes.size()-1).Sekil.at(i).getPosition().x+0.5)==+4.5f)
            {
                return false;
            }
            
        }
    
    }
    else if (Shapes.at(Shapes.size()-1).getYon()==Shape::Down)
    {
        for (int i = 0; i < Shapes.size()-1; i++)
        {
            for (int j = 0; j < Shapes.at(i).Sekil.size(); j++)
            {
                for (int x = 0; x < Shapes.at(Shapes.size()-1).Sekil.size(); x++)
                {
                    if ((Shapes.at(Shapes.size()-1).Sekil.at(x).getPosition()-glm::vec3(0.0,0.5,0.0))==Shapes.at(i).Sekil.at(j).getPosition())
                    {
                        return false;
                    }
                    
                }
                   
            }
            
        }
        for (int i = 0; i < Shapes.at(Shapes.size()-1).Sekil.size(); i++)
        {
            if ((Shapes.at(Shapes.size()-1).Sekil.at(i).getPosition().y-0.5)==-4.5f)
            {
                return false;
            }
        }
    }

    return true;
}
void Rules::Dondur()
{
    glm::vec3 Mind=Shapes.at(Shapes.size()-1).Sekil.at(0).getPosition();
    for (int i = 0; i < Shapes.at(Shapes.size()-1).Sekil.size(); i++)
    {
        glm::vec3 Temp=Shapes.at(Shapes.size()-1).Sekil.at(i).cevirsekNeOlur(Mind);
        if(Temp.x==4.5||Temp.x==-4.5)
            return;
        for (int j = 0; j < Shapes.size()-1; j++)
        {
            for (int x = 0; x < Shapes.at(j).Sekil.size(); x++)
            {
                if (Shapes.at(j).Sekil.at(x).getPosition()==Temp)
                {
                    return;
                }
                
            }
        }
        
    }
    for (int i = 0; i < Shapes.at(Shapes.size()-1).Sekil.size(); i++)
    {
        Shapes.at(Shapes.size()-1).Sekil.at(i).Cevir(Mind);
    }
    
}
bool Rules::CisimlerDurduMu()
{
    for (int i = 0; i < Shapes.size(); i++)
    {
        if (Shapes.at(i).Sekil.size()==4)
        {
            if((Shapes.at(i).Sekil.at(0).getHareketImkani()&&Shapes.at(i).Sekil.at(1).getHareketImkani()&&Shapes.at(i).Sekil.at(2).getHareketImkani()&&Shapes.at(i).Sekil.at(3).getHareketImkani()))
            {
                return false;
            }
        }
        else
        {
            for (int j = 0; j < Shapes.at(i).Sekil.size(); j++)
            {
                if (Shapes.at(i).Sekil.at(j).getHareketImkani())
                {
                    return false;
                }
            }
            
        }
    }
    return true;
}
void Rules::SatiriSil()
{
    if(CisimlerDurduMu())
        SutunKontrol();
}