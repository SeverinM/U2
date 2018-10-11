#include <iostream>
#include "../include/Projectile.h"
#define SIZEX 70
#define SIZEY 70

Projectile::Projectile() : Positionable(0, 0)
{
    directionMove = std::pair<int, int>(0,1);
    timer = (1/getVitesse());
    lastTime = 0;
}
Projectile::Projectile(int posX, int posY, std::pair<int, int> dir) : Positionable(posX, posY)
{
    directionMove = dir;
}

Projectile::~Projectile()
{
    //dtor
}

void Projectile::init(int posX, int posY, std::pair<int, int> dir, bool fromPlayer)
{
    Positionable::init(posX, posY, "sprites/ProjectileHero.txt");
    directionMove = dir;
    isFromPlayer = fromPlayer;
}

void Projectile::update(float time){
    goOn(time);
}




///Movement automatique via une direction en memoire !
void Projectile::goOn(float time){
    //cout << "Hello, i'm  : " << timer << " at " << getVitesse() << endl;
    timer -= time;

    if(timer < 0){
        moveBy(directionMove.first,directionMove.second);
        timer = (1/getVitesse());;
    }
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

