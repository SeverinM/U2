#ifndef PERSO_H
#define PERSO_H
#include "Positionable.h"


class Perso : public Positionable
{
    public:
        struct shootInfo {
            std::pair<int,int> startPosition;
            std::pair<int,int> direction;
        } ;
        Perso();
        Perso(int posX,int posY);
        void init(int posX,int posY);
        virtual ~Perso();

        shootInfo Tirer();
        void takeDamage(int damage);
        std::pair<int,int> hitbox = std::pair<int,int>(2,0);
        void update(float time);
        virtual std::pair<int,int> directionTir() = 0;
        bool isShot = false;

    protected:
        int pv;
        float timerShoot;
        float timerHit;
        void Mourir();
        float delayShoot = 0.1;
};

#endif // PERSO_H
