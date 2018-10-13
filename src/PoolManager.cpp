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


Positionable * PoolManager::getInPool(typePosable type)
{
    Positionable * output;
    switch (type)
    {
        case Enn:
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

        case Proj:
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

        case Her:
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

    cout << output << endl;
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

void PoolManager::clearPool(Positionable::typePosable type)
{
    switch (type)
    {
        case Positionable::typePosable::Enn:
            for (int i = 0 ; i < 30 ; i++)
            {
                delete poolEnnemi[i];
                poolEnnemi[i] = 0;
            }
            break;
        case Positionable::typePosable::Proj:
            for (int i = 0 ; i < 60 ; i++)
            {
                delete poolProjectile[i];
                poolProjectile[i] = 0;
            }
            break;
        case Positionable::typePosable::Her:
            delete hero[0];
            hero[0] = 0;
            break;
    }
}

int PoolManager::poolCount(Positionable::typePosable type)
{
    int nb = 0;
    switch (type)
    {
        case Positionable::typePosable::Enn:
            for (int i = 0 ; i < 30 ; i++)
            {
                if (poolEnnemi[i] != nullptr && poolEnnemi[i]->isEnabled)
                {
                    nb++;
                }
            }
            break;
        case Positionable::typePosable::Proj:
            for (int i = 0 ; i < 60 ; i++)
            {
                if (poolProjectile[i] != nullptr && poolProjectile[i]->isEnabled)
                {
                    nb++;
                }
            }
            break;
        case Positionable::typePosable::Her:
            nb += (hero[0] != 0 ? 1 : 0);
            break;
    }
    return nb;
}

