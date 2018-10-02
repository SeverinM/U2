#include "Perso.h"
#include "Positionable.h"

Perso::Perso()
{
    Positionable();
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

void Perso::Mourir(){
    //TO DO :
}
void Perso::Tirer(){
    //TO DO :
}
