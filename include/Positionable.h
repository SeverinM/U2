#ifndef POSITIONABLE_H
#define POSITIONABLE_H
#include <stdio.h>
#include "Visuel.h"
#include <vector>
#include <map>
#include <iostream>
#include <tgmath.h>
#define SIZEX 70
#define SIZEY 70

enum typePosable
        {
            Proj,
            Enn,
            Her
        };

class Positionable
{
    public:

        Positionable(int startPosX,int startPosY);
        void init(int posXBy, int posY, string spriteFileName = "sprite/spaceship.txt");
        void moveBy(float posXBy, float posY);
        float getVitesse();
        std::pair<int,int> getPos();
        virtual void setPosition(double newX,double newY);
        void addAnimation(Visuel * visu);
        map<pair<int,int>, CHAR_INFO *> getAnimation(int index);
        virtual void update(float time) = 0;
        bool isEnabled;
        inline int getX(){return posX;}
        inline int getY(){return posY;}
        void removeAnimation(int index);
        virtual typePosable getTypePosable() = 0;
        vector<pair<int,int>> getAllPosition();
        void removeAllAnimation();
        inline void setDirection(std::pair<double, double> &newDir){dir = newDir;}
        static void normalizeDirection(std::pair<double, double> &direction)
        {
            float hypo = (direction.first * direction.first) + (direction.second * direction.second);
            hypo = sqrt(hypo);
            direction.first /= hypo;
            direction.second /= hypo;
        }


    protected:
        std::pair<double , double > dir;
        float vitesse;
        vector<Visuel *> animations;
        float timer;
        float lastTime;
        double posX;
        double posY;
};

#endif // POSITIONABLE_H
