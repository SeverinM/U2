#include "../include/PoolManager.h"
#include <typeinfo>
#include <iostream>
#include <string>

PoolManager::PoolManager()
{
};


void PoolManager::addInPool(Positionable * element)
{
    std::string str(typeid(*element).name());
    str = str.substr(1,str.size() -1);
    if (str == "Hero")
    {
        delete hero;
        hero = (Hero *)element;
    }

    if (str == "Projectile")
    {
        for (int i = 0; i < 25; i++)
        {
            if (poolProjectile[i] == 0)
            {
                poolProjectile[i] = (Projectile *)element;
            }
        }
    }

    if (str == "Ennemi")
    {
        for (int i = 0; i < 15 ; i++)
        {
            if (poolEnnemi[i] == 0)
            {
                poolEnnemi[i] = (Ennemi *)element;
            }
        }
    }
};

Ennemi** PoolManager::getEnnemies()
{
    return poolEnnemi;
}

Projectile ** PoolManager::getProjectiles()
{
    return poolProjectile;
}

Hero ** PoolManager::getHero()
{
    return hero;
}
