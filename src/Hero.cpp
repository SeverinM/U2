#include "../include/Hero.h"
#include "../include/Positionable.h"

Hero::Hero() : Perso()
{
    timerShoot = 0;
}
Hero::Hero(int posX,int posY) : Perso(posX, posY)
{
    timerShoot = 0;
}

Hero::~Hero()
{

}

void Hero::init(int posX,int posY)
{
    Perso::init(posX, posY);
    timerShoot = 0;
}

void Hero::update(float time)
{
    if(timerShoot > 0){
        timerShoot -= time;
    }
}

void Hero::tryToShoot(){
    if(timerShoot <= 0){
        isShot = true;
        timerShoot = delayShoot;
    }
}



std::pair<int,int> Hero::directionTir(){
    return std::pair<int,int>(0,-1);
}

void Hero::setPosition(double newX, double newY)
{
    if (newX > 0 && newX < (SIZEX - 1))
    {
        posX = newX;
    }

    if (newY > 0 && newY < (SIZEY - 1))
    {
        posY = newY;
    }
}

typePosable Hero::getTypePosable(){
    return Her;
}


