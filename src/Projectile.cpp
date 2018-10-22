#include <iostream>
#include "../include/Projectile.h"
#define SIZEX 70
#define SIZEY 70

Projectile::Projectile() : Positionable(0, 0)
{
    dir = std::pair<int, int>(0,0.01);
    timer = (1/getVitesse());
    lastTime = 0;
}

Projectile::Projectile(int posX, int posY, std::pair<double, double> direction) : Positionable(posX, posY)
{
    dir = direction;
}

void Projectile::init(int posX, int posY, std::pair<double, double> direction, bool fromPlayer)
{
    Positionable::init(posX, posY, "sprites/ProjectileHero.txt");
    dir = direction;
    isFromPlayer = fromPlayer;
}

void Projectile::update(float time){
    moveBy((float)dir.first, (float)dir.second);
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

