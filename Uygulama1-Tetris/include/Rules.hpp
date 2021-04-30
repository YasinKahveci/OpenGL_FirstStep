#ifndef RULES_HPP
#define RULES_HPP
#include <vector>
#include "Shape.hpp"
#include <chrono>
class Rules
{
private:
    Rules();
    static Rules* Point;
    
    void YerCekimi();
    bool AssagiHareketEdebilirMi(glm::vec3 v1,glm::vec3 v2);
    bool AltiBosMu(glm::vec3 v1);
    void HareketEttir();
    void Olustur();
    void SutunKontrol();
    void SutunuSil(float y1);
    void SetMoves();
    void KlavyeHareketiKontrol();
    bool KlavyeHareketIzin();
    bool CisimlerDurduMu();
    void SatiriSil();

    clock_t begin,end;
    double time_spent;
public:
    std::vector<Shape> Shapes;
    static Rules* getInstance();
    void OyunDongusu();
    void Dondur();
};



#endif