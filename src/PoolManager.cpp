#include "PoolManager.h"

PoolManager::PoolManager()
{
    poolDecor =      new Positionable *[25];
    poolEnnemi =     new Ennemi *[15];
    poolProjectile = new Projectile *[25];
    poolHero =       new Hero *[1];
}

PoolManager::~PoolManager()
{
    //dtor
}




Positionable * PoolManager::addDecor(/**/){
    Positionable * result = nullptr;
    int emptySpace = -1;
    for(int index = 0; index < sizeof(poolDecor)/sizeof(poolDecor[0]); index++){
        if(poolDecor[index] != nullptr){
            if(!poolDecor[index]->isEnabled){
                result = poolDecor[index];
                break;
            }
        }
        else {
            emptySpace = index;
        }

    }
    if(result == nullptr){
        if(emptySpace != -1){
            Hero d = * new Hero();
            poolDecor[emptySpace] = &d;
            result = &d;
        }
        else {
            /*TO DO : construire un tableau plus grand de 25 */
        }
    }
    result->isEnabled = true;
    return result;
}

void PoolManager::remDecor(Positionable * decor){
    decor->isEnabled = false;
}

Ennemi * PoolManager::addEnnemi(int posX,int posY){

}

void PoolManager::remEnnemi(Positionable * ennemi){

}

Projectile * PoolManager::addProjectile(int posX, int posY, std::pair<int, int> direction){

}

void PoolManager::remProjectile(Positionable * projec){

}

Hero * PoolManager::addHero(int posX,int posY){
    Hero * result = nullptr;
    int emptySpace = -1;
    for(int index = 0; index < sizeof(poolHero)/sizeof(poolHero[0]); index++){
        if(poolHero[index] != nullptr){
            if(!poolHero[index]->isEnabled){
                result = poolHero[index];
                break;
            }
        }
        else {
            emptySpace = index;
        }

    }
    if(result == nullptr){
        if(emptySpace != -1){
            Hero h = * new Hero();
            poolHero[emptySpace] = &h;
            result = &h;
        }
        else {
            /*TO DO : construire un tableau plus grand de 25 */
        }
    }
    result->isEnabled = true;
    return result;
}

void PoolManager::remHero(Positionable * hero){

}
