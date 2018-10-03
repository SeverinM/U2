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
        virtual ~Perso();

        shootInfo Tirer();
        void takeDamage(int damage);
        std::pair<int,int> hitbox;
        void update(float time);
        virtual std::pair<int,int> directionTir() = 0;
        bool isShot;

    private:
        int pv;
        float timerShoot;
        float timerHit;
        void Mourir();
};

#endif // PERSO_H
