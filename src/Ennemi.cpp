#include "../include/Ennemi.h"

Ennemi::Ennemi() : Perso()
{
}

Ennemi::Ennemi(int posX,int posY, PoolManager * refPool) : Perso(posX, posY)
{
    pool = refPool;
    pv = 1;
    dir = std::pair<double, double>(0.01,0.01);
}

Ennemi::~Ennemi()
{
    //dtor
}

void Ennemi::init(int posX,int posY)
{
    Perso::init(posX, posY);
}

std::pair<double,double> Ennemi::directionTir(){
    return std::pair<double, double>(dir.first,dir.second);
}

void Ennemi::update(float deltaTime)
{
    if (isEnabled)
    {
        time += deltaTime;
        moveBy(dir.first, dir.second);
        if (time - timeSinceLastShoot > frequencyShoot)
        {
            timeSinceLastShoot = time;
            Projectile * p = (Projectile *)pool->getInPool(typePosable::Proj);
            p->isEnabled = true;
            p->init(posX + 2,posY,{0,0.002},false);
            p->removeAllAnimation();
            p->addAnimation(Visuel::createFromFile("sprites/ProjectileHero.txt",
                                                   Visuel::getColor(Visuel::Couleur::Rouge,
                                                                    Visuel::Couleur::Transparent)));
        }
    }
}

void Ennemi::setPosition(int newX, int newY)
{
    Positionable::setPosition(newX,newY);
}

typePosable Ennemi::getTypePosable(){
    return Enn;
}

