#ifndef POSITIONABLE_H
#define POSITIONABLE_H
#include <stdio.h>
#include "Visuel.h"
#include <vector>
#include <map>

class Positionable
{
    public:
        Positionable(int startPosX,int startPosY);
        void moveBy(int posXBy, int posY);
        float getVitesse();
        std::pair<int,int> getPos();
        void addAnimation(Visuel * visu);
        map<pair<int,int>, CHAR_INFO *>& getAnimation(int index);
        virtual void update(float time) = 0;
        bool isEnabled;

    private:
        int posX;
        int posY;
        float vitesse;
        vector<Visuel *> animations;
};

#endif // POSITIONABLE_H
