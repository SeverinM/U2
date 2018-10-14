#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "Positionable.h"

class Projectile : public Positionable
{
    public:
        Projectile();
        Projectile(int posX, int posY, std::pair<double, double> direction);
        void init(int posX, int posY, std::pair<double, double> direction, bool fromPlayer);
        virtual void update(float time);
        int hit();
        bool getIsFromPlayer();
        virtual typePosable getTypePosable();

    protected:
        bool isFromPlayer;
};

#endif // PROJECTILE_H
