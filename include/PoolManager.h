#ifndef POOLMANAGER_H
#define POOLMANAGER_H
#include "Hero.h"
#include "Ennemi.h"
#include "Projectile.h"


class PoolManager
{
    public:
        PoolManager();
        virtual ~PoolManager();


        Positionable *  addDecor     (/*int posX,int posY*/);
        void            remDecor     (Positionable * decor);
        Ennemi *        addEnnemi    (int posX,int posY);
        void            remEnnemi    (Positionable * ennemi);
        Projectile *    addProjectile(int posX, int posY, std::pair<int, int> direction);
        void            remProjectile(Positionable * projec);
        Hero *          addHero      (int posX,int posY);
        void            remHero      (Positionable * hero);

        Positionable ** * getAllPosVector();

    protected:

    private:
        Positionable ** poolDecor;
        Positionable ** poolEnnemi;
        Positionable ** poolProjectile;
        Positionable ** poolHero;

};

#endif // POOLMANAGER_H
