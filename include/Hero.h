#ifndef HERO_H
#define HERO_H
#include "Perso.h"

class Hero : public Perso
{
    public:
        Hero(float &posX,float &posY);
        void init(float &posX,float &posY);
        virtual std::pair<float, float> directionTir();
        void update(float &time);
        void tryToShoot();
        void setPosition(float &newX,float &newY);
        virtual typePosable getTypePosable();
        bool takeDamage(int &damage);
        inline bool getIsInRecovery(){
            return isOnRecovery;
        }

    private:
        float totalTime = 0;
        float recoveryTimeEnd = 0;
        float recoveryTime = 3;
        bool isOnRecovery = false;
};

#endif // HERO_H
