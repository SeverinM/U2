#include "../include/Ennemi.h"

Ennemi::Ennemi() : Perso()
{
    vitesse = 0.001;
}

Ennemi::Ennemi(int posX,int posY, PoolManager * refPool) : Perso(posX, posY)
{
    pool = refPool;
    vitesse = 0.001;
    pv = 1;
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
        time += 0.0001;
        if (time - timeSinceLastShoot > frequencyShoot)
        {
            timeSinceLastShoot = time;
            Projectile * p = (Projectile *)pool->getInPool(typePosable::Proj);
            p->isEnabled = true;
            p->init(posX,posY,{0,0.001},false);
            p->removeAnimation(0);
            p->addAnimation(Visuel::createFromFile("sprites/ProjectileHero.txt",
                                                   Visuel::getColor(Visuel::Couleur::Rouge,
                                                                    Visuel::Couleur::Transparent)));
            p->isEnabled = true;
            p->init(posX,posY,{0,0.001},false);
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

