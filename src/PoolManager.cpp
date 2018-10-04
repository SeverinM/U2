#include "../include/PoolManager.h"
#include <typeinfo>
#include <iostream>
#include <string>

PoolManager::PoolManager()
{
    for (int i = 0 ; i < 25 ; i++)
    {
        poolProjectile[i] = 0;
    }

    for (int i = 0 ; i < 15 ; i++)
    {
        poolEnnemi[i] = 0;
    }

    hero[0] = 0;
};


Positionable * PoolManager::getInPool(PoolManager::typePool type)
{
    Positionable * output;
    switch (type)
    {
        case PoolManager::Enn:
            for (int i = 0; i < 15; i++)
            {
                if (poolEnnemi[i] == 0)
                {
                    poolEnnemi[i] = new Ennemi();
                }
                if (!poolEnnemi[i]->isEnabled)
                {
                    output = poolEnnemi[i];
                    break;
                }
            }
            break;

        case PoolManager::Proj:
            for (int i = 0; i < 25; i++)
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

        case PoolManager::Her:
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

Positionable** PoolManager::getEnnemies()
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
