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

void Hero::update(float time)
{
    float deltaTime = time - lastTime;
    if(timerShoot > 0)
        timerShoot -= deltaTime;



    lastTime = time;
}

void Hero::tryToShoot(){
    if(timerShoot <= 0){
        isShot = true;
        timerShoot = 5;
    }
}



std::pair<int,int> Hero::directionTir(){
    return std::pair<int,int>(0,-1);
}



