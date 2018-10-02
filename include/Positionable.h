#ifndef POSITIONABLE_H
#define POSITIONABLE_H
#include <stdio.h>
#include "Visuel.h"

class Positionable
{
    public:
        Positionable(int startPosX,int startPosY);
        moveBy(int posXBy, int posY);
        float getVitesse();
        std::pair<int,int> getPos();
    private:
        int posX;
        int posY;
        float vitesse;
        Visuel * animations[5];
};

#endif // POSITIONABLE_H
