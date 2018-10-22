#include "../include/Hero.h"
#include "../include/Positionable.h"

Hero::Hero() : Perso()
{
    timerShoot = 0;
    pv = 100;
    vitesse = 4;
}
Hero::Hero(int posX,int posY) : Perso(posX, posY)
{
    timerShoot = 0;
    pv = 3;
}

void Hero::init(int posX,int posY)
{
    Perso::init(posX, posY);
    timerShoot = 0;
    pv = 3;
}

void Hero::update(float time)
{
    isOnRecovery = (recoveryTimeEnd > totalTime);
    indexAnimation = (isOnRecovery ? 1 : 0);
    totalTime += time;
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

std::pair<double , double> Hero::directionTir(){
    return dir;
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

bool Hero::takeDamage(int damage)
{
    bool output = Perso::takeDamage(damage);
    recoveryTimeEnd = totalTime + recoveryTime;
    return output;
}

typePosable Hero::getTypePosable(){
    return Her;
}


