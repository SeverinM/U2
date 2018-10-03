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


        Positionable *  addDecor(/**/);
        void            remDecor(Positionable * decor);
        Ennemi *        addEnnemi(int posX,int posY);
        void            remEnnemi(Positionable * ennemi);
        Projectile *    addProjectile(int posX, int posY, std::pair<int, int> direction);
        void            remProjectil(Positionable * projec);
        Hero *          addHero();
        void            remHero(int posX,int posY);

        vector<Positionable * > * getAllPosVector();

    protected:

    private:
        vector<Positionable * > poolDecor;
        vector<Positionable * > poolEnnemi;
        vector<Positionable * > poolProjectile;
        vector<Positionable * > poolHero;

};

#endif // POOLMANAGER_H
