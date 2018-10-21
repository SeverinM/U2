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

        case ProjProg:
            for (int i = 0; i < sizePoolProProg; i++)
            {
                if (poolProgProj[i] == 0)
                {
                    poolProgProj[i] = new ProgrammableProj(0,0,{-0.07,0}, "Test", hero[0]);
                }

                if (!poolProgProj[i]->isEnabled)
                {
                    output = poolProgProj[i];
                    break;
                }
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

int PoolManager::getProProgPoolSize()
{
    return sizePoolProProg;
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

