#ifndef PERSO_H
#define PERSO_H
#include "Positionable.h"


class Perso : public Positionable
{
    public:
        Perso();
        Perso(int posX,int posY);
        virtual ~Perso();
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
        void Tirer();
};

#endif // PERSO_H
