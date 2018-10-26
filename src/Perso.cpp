#include "../include/Perso.h"
#include "../include/Positionable.h"

Perso::Perso() : Positionable(1,1)
{
    pv = 1;
}

Perso::Perso(int posX,int posY) :  Positionable(posX, posY)
{
    timerShoot = 0;
}

Perso::~Perso()
{
}

void Perso::init(int posX,int posY)
{
    Positionable::init(posX, posY);
}

Perso::shootInfo Perso::Tirer(){
    shootInfo sI;
    sI.direction = directionTir();
    sI.startPosition = getPos();
    isShot = false;
    return sI;
}

bool Perso::takeDamage(int damage){
    bool output = false;
    pv -= damage;
    if(pv <= 0){
        Mourir();
        output = true;
    }
    return output;
}

void Perso::update(float time)
{
    Positionable::update(time);
}

void Perso::Mourir(){
    isEnabled = false;
}

