#include "../include/Ennemi.h"

Ennemi::Ennemi() : Perso()
{

}

Ennemi::Ennemi(int posX,int posY) : Perso(posX, posY)
{

}

Ennemi::~Ennemi()
{
    //dtor
}

std::pair<int,int> Ennemi::directionTir(){
    return std::pair<int,int>(0,1);
}
