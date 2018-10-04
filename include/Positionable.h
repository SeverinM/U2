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
        void init(int posXBy, int posY);
        void moveBy(int posXBy, int posY);
        float getVitesse();
        std::pair<int,int> getPos();
        virtual void setPosition(int newX,int newY);
        void addAnimation(Visuel * visu);
        map<pair<int,int>, CHAR_INFO *> getAnimation(int index);
        virtual void update(float time) = 0;
        bool isEnabled;
        inline int getX(){return posX;}
        inline int getY(){return posY;}

    protected:
        float timer;
        float lastTime;
        int posX;
        int posY;

    private:
        float vitesse;
        vector<Visuel *> animations;


};

#endif // POSITIONABLE_H
