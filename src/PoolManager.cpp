#include "../include/PoolManager.h"
#include <typeinfo>
#include <iostream>
#include <string>

PoolManager::PoolManager()
{
    for (int i = 0 ; i < sizePoolPro ; i++)
    {
        poolProjectile[i] = 0;
    }

    for (int i = 0 ; i < sizePoolEnn ; i++)
    {
        poolEnnemi[i] = 0;
    }

    hero[0] = 0;
};


Positionable * PoolManager::getInPool(Positionable::typePosable type)
{
    Positionable * output;
    switch (type)
    {
        case Positionable::typePosable::Enn:
            for (int i = 0; i < sizePoolEnn; i++)
            {
                if (poolEnnemi[i] == 0)
                {
                    poolEnnemi[i] = new Ennemi(0,0,this);
                }
                if (!poolEnnemi[i]->isEnabled)
                {
                    output = poolEnnemi[i];
                    break;
                }
            }
            break;

        case Positionable::typePosable::Proj:
            for (int i = 0; i < sizePoolPro; i++)
            {
                if (poolProjectile[i] == 0)
                {
                    poolProjectile[i] = new Projectile();
                }
                if (!poolProjectile[i]->isEnabled)
                {
                    output = poolProjectile[i];
                    break;
                }
            }
            break;

        case Positionable::typePosable::Her:
            if (hero[0] == 0)
            {
                hero[0] = new Hero();
            }

            if (!hero[0]->isEnabled)
            {
                output = hero[0];
            }
            break;
    }

    return output;
}

Positionable ** PoolManager::getEnnemies()
{
    return (Positionable **)poolEnnemi;
}

Positionable ** PoolManager::getProjectiles()
{
    return (Positionable **)poolProjectile;
}

Positionable ** PoolManager::getHero()
{
    return (Positionable **)hero;
}

int PoolManager::getEnnPoolSize(){
    return sizePoolEnn;
}
int PoolManager::getProPoolSize(){
    return sizePoolPro;
}
int PoolManager::getHerPoolSize(){
    return sizePoolHer;
}

