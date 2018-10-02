#include "../include/Hero.h"

Hero::Hero() : Perso()
{

}
Hero::Hero(int posX,int posY) : Perso(posX, posY)
{

}

Hero::~Hero()
{
    //dtor
}


std::pair<int,int> Hero::directionTir(){
    return std::pair<int,int>(1,0);
}
