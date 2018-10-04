#include "../include/Ennemi.h"
#define SIZEX 70
#define SIZEY 70

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
    moveBy(0,1);
}

void Ennemi::setPosition(int newX, int newY)
{
    Positionable::setPosition(newX,newY);
    if (posX < 0 || posX >= SIZEX || posY < 0 || posY >= SIZEY)
    {
        isEnabled = false;
    }
}
