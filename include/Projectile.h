#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "Positionable.h"

class Projectile : public Positionable
{
    public:
        Projectile();
        Projectile(int posX, int posY, std::pair<int, int> direction);
        virtual ~Projectile();
        void init(int posX, int posY, std::pair<int, int> direction, bool fromPlayer);
        void goOn(float time);
        virtual void update(float time);
        int hit();
        bool getIsFromPlayer();
        virtual typePosable getTypePosable();

    protected:
        bool isFromPlayer;

    private:
        std::pair<int, int> directionMove;
};

#endif // PROJECTILE_H
