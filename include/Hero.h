#ifndef HERO_H
#define HERO_H
#include "Perso.h"

class Hero : public Perso
{
    public:
        Hero();
        Hero(int posX,int posY);
        void init(int posX,int posY);
        virtual std::pair<double, double> directionTir();
        void update(float time);
        void tryToShoot();
        void setPosition(double newX, double newY);
        virtual typePosable getTypePosable();
        bool takeDamage(int damage);
        inline bool getIsInRecovery(){
            return isOnRecovery;
        }

    protected:

    private:
        float totalTime = 0;
        float recoveryTimeEnd = 0;
        float recoveryTime = 3;
        bool isOnRecovery = false;
};

#endif // HERO_H
