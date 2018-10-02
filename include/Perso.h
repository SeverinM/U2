#ifndef PERSO_H
#define PERSO_H
#include "Positionable.h"


class Perso : public Positionable
{
    public:
        Perso();
        virtual ~Perso();
        void takeDamage(int damage);
        std::pair<int,int> hitbox;

    private:
        int pv;
        void Mourir();
        void Tirer();
};

#endif // PERSO_H
