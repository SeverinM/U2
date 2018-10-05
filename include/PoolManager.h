#ifndef POOLMANAGER_H
#define POOLMANAGER_H
#include "Hero.h"
#include "Ennemi.h"
#include "Projectile.h"

struct Ennemi;

class PoolManager
{
    public:
        PoolManager();
        Positionable * getInPool(typePosable type);
        Positionable ** getEnnemies();
        Positionable ** getProjectiles();
        Positionable ** getHero();
        int             getEnnPoolSize();
        int             getProPoolSize();
        int             getHerPoolSize();

    private:
        Ennemi       * poolEnnemi[60];
        Projectile   * poolProjectile[120];
        Hero         * hero[1];
        int            sizePoolEnn = 60;
        int            sizePoolPro = 120;
        int            sizePoolHer = 1;

};

#endif // POOLMANAGER_H
