#ifndef POOLMANAGER_H
#define POOLMANAGER_H
#include "Hero.h"
#include "Ennemi.h"
#include "Projectile.h"


class PoolManager
{
    public:
        PoolManager();
        void addInPool(Positionable * element);
        Positionable ** getEnnemies();
        Positionable ** getProjectiles();
        Positionable ** getHero();

    private:
        Ennemi       * poolEnnemi[15];
        Projectile   * poolProjectile[25];
        Hero        * hero[1];

};

#endif // POOLMANAGER_H