#ifndef ENNEMI_H
#define ENNEMI_H
#include "Perso.h"
#include "PoolManager.h"

struct PoolManager;

class Ennemi : public Perso
{
    public:
        Ennemi();
        Ennemi(int posX,int posY, PoolManager * pool);
        virtual ~Ennemi();
        void init(int posX,int posY);
        virtual std::pair<int,int> directionTir();
        void update(float time);
        void setPosition(int newX,int newY);

    private:
        float time = 0;
        float frequencyShoot = 2;
        float timeSinceLastShoot = 0;
        PoolManager * pool;
};

#endif // ENNEMI_H
