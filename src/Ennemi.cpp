#include "../include/Ennemi.h"
#include "ProgrammableProj.h"

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

void Ennemi::init(int posX,int posY){
    Perso::init(posX, posY);
    dying = false;
    indexAnimation = 0;
    physicEnabled = true;
    pv = 1;
}

void Ennemi::Mourir()
{
    dir.first /= 5;
    dir.second /= 5;
    dying = true;
    physicEnabled = false;
    setColor(Visuel::getColor(Visuel::Couleur::Gris, Visuel::Couleur::Transparent));
}

std::pair<double,double> Ennemi::directionTir(){
    return std::pair<double, double>(dir.first,dir.second);
}

void Ennemi::update(float deltaTime, Hero * her)
{
    if (dying && !increaseSprite(speedAnimation))
    {
        isEnabled = false;
    }

    if (isEnabled)
    {
        time += deltaTime;
        moveBy((float)dir.first,(float)dir.second);
        if (time - timeSinceLastShoot > frequencyShoot && !dying)
        {
            std::pair<double , double> dir;
            dir.first = her->getPos().first - getPos().first;
            dir.second = her->getPos().second - getPos().second;
            Positionable::normalizeDirection(dir);
            timeSinceLastShoot = time;
            //ProgrammableProj * p = (ProgrammableProj *)pool->getInPool(typePosable::ProjProg);
            //En cas d'urgence decommentez la ligne
            Projectile * p = (Projectile *)pool->getInPool(typePosable::Proj);
            p->isEnabled = true;
            p->init(posX + 2,posY,{dir.first / 100, dir.second / 100},false);
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

