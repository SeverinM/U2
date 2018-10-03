#include "PoolManager.h"

PoolManager::PoolManager()
{
    poolDecor =      new Positionable[25];
    poolEnnemi =     new Positionable[15];
    poolProjectile = new Positionable[25];
    poolHero =       new Positionable[1];
}

PoolManager::~PoolManager()
{
    //dtor
}





Positionable *  addDecor(/**/){
    Positionable * result = nullptr;

    for(int index = 0; i < poolDecor.size; i++){
        if(!poolDecor[i].isEnabled){
            result = poolDecor[i];
            break;
        }
    }


    poolDecor.insert(result);
}

void remDecor(Positionable * decor){

}

Ennemi * addEnnemi(int posX,int posY){

}

void remEnnemi(Positionable * ennemi){

}

Projectile * addProjectile(int posX, int posY, std::pair<int, int> direction){

}

void remProjectil(Positionable * projec){

}

Hero * addHero(){

}

void remHero(int posX,int posY){

}
