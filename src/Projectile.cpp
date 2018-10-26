#include <iostream>
#include "../include/Projectile.h"
#define SIZEX 70
#define SIZEY 70

Projectile::Projectile(float &posX,float &posY, std::pair<float,float> &direction) : Positionable(posX, posY)
{
    dir = direction;
    Positionable::init(posX, posY, "sprites/ProjectileHero.txt");
}

void Projectile::init(float &posX,float &posY, std::pair<float, float> &direction, bool &fromPlayer)
{
    Positionable::init(posX, posY, "sprites/ProjectileHero.txt");
    dir = direction;
    isFromPlayer = fromPlayer;
}

void Projectile::update(float &time){
    moveBy(dir.first,dir.second);
    Positionable::update(time);
}

int Projectile::hit(){
    return 1;
}

bool Projectile::getIsFromPlayer(){
    return isFromPlayer;
}

typePosable Projectile::getTypePosable(){
    return Proj;
}

