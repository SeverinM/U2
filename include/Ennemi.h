#ifndef ENNEMI_H
#define ENNEMI_H
#include "Perso.h"


class Ennemi : public Perso
{
    public:
        Ennemi();
        Ennemi(int posX,int posY);
        virtual ~Ennemi();
        virtual std::pair<int,int> directionTir();
    protected:

    private:
};

#endif // ENNEMI_H
