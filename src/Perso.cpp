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
    //TO DO :
}
void Perso::Tirer(){
    //TO DO :
}

