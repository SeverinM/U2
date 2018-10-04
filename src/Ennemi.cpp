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

void Ennemi::init(int posX,int posY)
{
    Perso::init(posX, posY);
}

std::pair<int,int> Ennemi::directionTir(){
    return std::pair<int,int>(0,1);
}

void Ennemi::update(float time)
{

}
