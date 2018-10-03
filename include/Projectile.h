#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "Positionable.h"

class Projectile : public Positionable
{
    public:
        Projectile();
        Projectile(int posX, int posY, std::pair<int, int> direction);
        virtual ~Projectile();
        void goOn(float time);
        int hit();
    protected:

    private:
        std::pair<int, int> directionMove;
};

#endif // PROJECTILE_H
