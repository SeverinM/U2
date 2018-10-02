#ifndef POSITIONABLE_H
#define POSITIONABLE_H
#include <stdio.h>
#include "Visuel.h"

class Positionable
{
    public:
        Positionable();
        virtual moveBy(int posXBy, int posY);

    private:
        int posX;
        int posY;
        Visuel * animations[5];
};

#endif // POSITIONABLE_H
