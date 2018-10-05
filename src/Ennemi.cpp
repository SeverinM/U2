#include "../include/Ennemi.h"

Ennemi::Ennemi() : Perso()
{
    vitesse = 0.001;
}

Ennemi::Ennemi(int posX,int posY, PoolManager * refPool) : Perso(posX, posY)
{
    pool = refPool;
    vitesse = 0.001;
}

Ennemi::~Ennemi()
{
    //dtor
}

void Ennemi::init(int posX,int posY)
{
    Perso::init(posX, posY);
}

std::pair<int,int> Ennemi::directionTir(){
    return std::pair<int,int>(0,1);
}

void Ennemi::update(float deltaTime)
{
    if (isEnabled)
    {
        Positionable::setPosition(posX, posY + vitesse);
        time += 0.00001;

        if (time - timeSinceLastShoot > frequencyShoot)
        {
            timeSinceLastShoot = time;
            Projectile * p = (Projectile *)pool->getInPool(PoolManager::typePool::Proj);
            p->isEnabled = true;
            p->init(posX,posY,{0,0.001},false);
        }
    }
}

