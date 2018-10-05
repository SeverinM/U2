#include "../include/Hero.h"

Hero::Hero() : Perso()
{

}
Hero::Hero(int posX,int posY) : Perso(posX, posY)
{

}

Hero::~Hero()
{

}

void Hero::init(int posX,int posY)
{
    Perso::init(posX, posY);
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
        timerShoot = 0.1 ;
    }
}



std::pair<int,int> Hero::directionTir(){
    return std::pair<int,int>(0,-1);
}

typePosable Hero::getTypePosable(){
    return Her;
}



