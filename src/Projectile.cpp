#include <iostream>
#include "../include/Projectile.h"

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

void Projectile::init(int posX, int posY, std::pair<int, int> dir)
{
    Positionable::init(posX, posY);
    directionMove = dir;
}

void Projectile::update(float time){
    goOn( time);

}

///Movement automatique via une direction en memoire !
void Projectile::goOn(float time){
    //cout << "Hello, i'm  : " << timer << " at " << getVitesse() << endl;
    float deltaTime = time - lastTime;
    timer -= deltaTime;

    if(timer < 0){
        moveBy(directionMove.first,directionMove.second);
        timer = (1/getVitesse());;
    }
    lastTime = time;
    //std::cout << timer << std::endl ;
}

int Projectile::hit(){
    return 1;
}

