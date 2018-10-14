#ifndef HERO_H
#define HERO_H
#include "Perso.h"

class Hero : public Perso
{
    public:
        Hero();
        Hero(int posX,int posY);
        virtual ~Hero();
        void init(int posX,int posY);
        virtual std::pair<double, double> directionTir();
        void update(float time);
        void tryToShoot();
        void setPosition(double newX, double newY);
        virtual typePosable getTypePosable();

    protected:

    private:

};

#endif // HERO_H
