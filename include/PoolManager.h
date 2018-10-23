#ifndef POOLMANAGER_H
#define POOLMANAGER_H
#define SIZE_PROJ 60
#define SIZE_ENN 20
#define SIZE_PROJ2 60
#include "Hero.h"
#include "Ennemi.h"
#include "Projectile.h"
#include "ProgrammableProj.h"

struct Ennemi;

class PoolManager
{
    public:
        PoolManager();
        Positionable * getInPool(typePosable type);
        Positionable ** getEnnemies();
        Positionable ** getProjectiles();
        Positionable ** getProjectilesProg();
        Positionable ** getHero();
        int             getEnnPoolSize();
        int             getProPoolSize();
        int             getProProgPoolSize();
        int             getHerPoolSize();
        void            clearPool(typePosable type = typePosable::Enn);
        int             poolCount(typePosable type = typePosable::Enn);

    private:
        Ennemi       * poolEnnemi[SIZE_ENN];
        Projectile   * poolProjectile[SIZE_PROJ];
        ProgrammableProj * poolProgProj[SIZE_PROJ2];
        Hero         * hero[1];
        int            sizePoolEnn = SIZE_ENN;
        int            sizePoolPro = SIZE_PROJ;
        int            sizePoolHer = 1;
        int            sizePoolProProg = SIZE_PROJ2;

};

#endif // POOLMANAGER_H
