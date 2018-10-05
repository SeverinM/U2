#include "../include/Perso.h"
#include "../include/Positionable.h"

Perso::Perso() : Positionable(1,1)
{

}

Perso::Perso(int posX,int posY) :  Positionable(posX, posY)
{

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

void Perso::takeDamage(int damage){
    pv -= damage;
    if(pv < 0){
        Mourir();
    }
}

void Perso::update(float time)
{

}


void Perso::Mourir(){
    isEnabled = false;
    std::cout << "I'm dead, I was a good soldier" << std::endl;
}

