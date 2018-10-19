#ifndef POOLMANAGER_H
#define POOLMANAGER_H
#define SIZE_PROJ 200
#define SIZE_ENN 60
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
        void            clearPool(typePosable type = typePosable::Enn);
        int             poolCount(typePosable type = typePosable::Enn);

    private:
        Ennemi       * poolEnnemi[SIZE_ENN];
        Projectile   * poolProjectile[SIZE_PROJ];
        Hero         * hero[1];
        int            sizePoolEnn = SIZE_ENN;
        int            sizePoolPro = SIZE_PROJ;
        int            sizePoolHer = 1;

};

#endif // POOLMANAGER_H
