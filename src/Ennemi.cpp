#include "../include/Ennemi.h"

Ennemi::Ennemi(float &posX,float &posY, PoolManager * refPool) : Perso(posX, posY)
{
    pool = refPool;
    pv = 1;
    dir = std::pair<double, double>(0.01,0.01);
}

Ennemi::~Ennemi()
{
    //dtor
}

void Ennemi::init(float &posX,float &posY){
    Positionable::init(posX, posY);
    dying = false;
    indexAnimation = 0;
    physicEnabled = true;
    pv = 1;
    alreadyShot = false;
}

void Ennemi::Mourir()
{
    dir.first /= 5;
    dir.second /= 5;
    dying = true;
    physicEnabled = false;
    int grey(Visuel::getColor(Visuel::Couleur::Gris, Visuel::Couleur::Transparent));
    setColor(grey);
}

std::pair<float,float> Ennemi::directionTir(){
    return dir;
}

void Ennemi::update(float &deltaTime, Hero * her)
{
    if (dying && !increaseSprite(speedAnimation))
    {
        isEnabled = false;
    }
    float x(deltaTime * dir.first);
    float y(deltaTime * dir.second);
    moveBy(x,y);

    if (!dying)
    {
        Positionable::update(deltaTime);
    }
}

typePosable Ennemi::getTypePosable(){
    return Enn;
}

