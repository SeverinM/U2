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
        Perso(float &posX,float &posY);
        virtual ~Perso();

        shootInfo Tirer();
        virtual bool takeDamage(int &damage);
        void update(float time);
        virtual std::pair<float,float> directionTir() = 0;
        bool isShot = false;

    protected:
        int pv;
        float timerShoot;
        float timerHit;
        virtual void Mourir();
        float delayShoot = 0.3;
};

#endif // PERSO_H
