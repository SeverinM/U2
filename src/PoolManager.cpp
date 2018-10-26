#include "../include/PoolManager.h"
#include <typeinfo>
#include <iostream>
#include <string>

PoolManager::PoolManager()
{
    float zero(0);
    hero[0] = new Hero(zero,zero);
    for (int i = 0 ; i < sizePoolPro; i++)
    {
        poolProjectile[i] = 0;
    }

    for (int i = 0 ; i < sizePoolEnn; i++)
    {
        poolEnnemi[i] = 0;
    }
};


Positionable * PoolManager::getInPool(typePosable type)
{
    float zero(0);
    Positionable * output;
    switch (type)
    {
        case Enn:
            for (int i = 0; i < sizePoolEnn; i++)
            {
                if (poolEnnemi[i] == 0)
                {
                    poolEnnemi[i] = new Ennemi(zero,zero,this);
                }
                if (!poolEnnemi[i]->isEnabled)
                {
                    output = (Positionable *)poolEnnemi[i];
                    break;
                }
            }
            break;

        case Proj:
            for (int i = 0; i < sizePoolPro; i++)
            {
                if (poolProjectile[i] == nullptr)
                {
                    float posX(0);
                    float posY(0);
                    std::pair<float,float> dir(-0.002,0);
                    poolProjectile[i] = new Projectile(posX,posY,dir);
                }

                if (!poolProjectile[i]->isEnabled)
                {
                    output = (Positionable *)poolProjectile[i];
                    break;
                }
            }
            break;

        case Her:
            if (hero[0] == 0)
            {
                hero[0] = new Hero(zero,zero);
            }

            if (!hero[0]->isEnabled)
            {
                output = (Positionable *)hero[0];
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

void PoolManager::clearPool(typePosable type)
{
    switch (type)
    {
        case typePosable::Enn:
            for (int i = 0 ; i < sizePoolEnn ; i++)
            {
                delete poolEnnemi[i];
                poolEnnemi[i] = 0;
            }
            break;
        case typePosable::Proj:
            for (int i = 0 ; i < sizePoolPro ; i++)
            {
                delete poolProjectile[i];
                poolProjectile[i] = 0;
            }
            break;
        case typePosable::Her:
            delete hero[0];
            hero[0] = 0;
            break;
    }
}

int PoolManager::poolCount(typePosable type)
{
    int nb = 0;
    switch (type)
    {
        case typePosable::Enn:
            for (int i = 0 ; i < sizePoolEnn ; i++)
            {
                if (poolEnnemi[i] != nullptr && poolEnnemi[i]->isEnabled)
                {
                    nb++;
                }
            }
            break;
        case typePosable::Proj:
            for (int i = 0 ; i < sizePoolPro ; i++)
            {
                if (poolProjectile[i] != nullptr && poolProjectile[i]->isEnabled)
                {
                    nb++;
                }
            }
            break;
        case typePosable::Her:
            nb += (hero[0] != 0 ? 1 : 0);
            break;
    }
    return nb;
}

