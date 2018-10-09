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
        Positionable * getInPool(Positionable::typePosable type);
        Positionable ** getEnnemies();
        Positionable ** getProjectiles();
        Positionable ** getHero();
        int             getEnnPoolSize();
        int             getProPoolSize();
        int             getHerPoolSize();

    private:
        Ennemi       * poolEnnemi[30];
        Projectile   * poolProjectile[60];
        Hero         * hero[1];
        int            sizePoolEnn = 30;
        int            sizePoolPro = 60;
        int            sizePoolHer = 1;

};

#endif // POOLMANAGER_H
