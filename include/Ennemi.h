#ifndef ENNEMI_H
#define ENNEMI_H
#include "Perso.h"


class Ennemi : public Perso
{
    public:
        Ennemi();
        Ennemi(int posX,int posY);
        virtual ~Ennemi();
        void init(int posX,int posY);
        virtual std::pair<int,int> directionTir();
        void update(float time);
};

#endif // ENNEMI_H
