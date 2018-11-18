#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "Positionable.h"

class Projectile : public Positionable
{
    public:
        Projectile(float &posX,float &posY, std::pair<float, float> &direction);
        void init(float &posX,float &posY, std::pair<float, float> &direction, bool &fromPlayer);
        virtual void update(float &time);
        int hit();
        bool getIsFromPlayer();
        virtual typePosable getTypePosable();
        inline void setIsFromPlayer(bool newValue)
        {
            isFromPlayer = newValue;
        }

    protected:
        bool isFromPlayer;
};

#endif // PROJECTILE_H
