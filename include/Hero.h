#ifndef HERO_H
#define HERO_H
#include "Perso.h"

class Hero : public Perso
{
    public:
        Hero();
        Hero(int posX,int posY);
        virtual ~Hero();
        virtual std::pair<int,int> directionTir();

    protected:

    private:

};

#endif // HERO_H