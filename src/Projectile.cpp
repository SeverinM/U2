#include <iostream>
#include "../include/Projectile.h"

Projectile::Projectile() : Positionable(0, 0)
{
    direction = std::pair<int, int>(0,0);
    timer = (1/getVitesse());
    lastTime = 0;
}
Projectile::Projectile(int posX, int posY, std::pair<int, int> dir) : Positionable(posX, posY)
{
    direction = dir;
}

Projectile::~Projectile()
{
    //dtor
}

///Movement automatique via une direction en m�moire !
void Projectile::goOn(float time){
    float deltaTime = time - lastTime;
    timer -= deltaTime;

    if(timer < 0){
        moveBy(direction.first,direction.second);
        timer = (1/getVitesse());;
    }
    lastTime = time;
    //std::cout << timer << std::endl ;
}

int Projectile::hit(){
    return 1;
}
