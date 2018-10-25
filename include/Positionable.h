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
    Her,
    Txt,
    ProjProg
};

class Positionable
{
    public:

        Positionable(int startPosX,int startPosY);
        void init(int posXBy, int posY, string spriteFileName = "sprite/spaceship.txt");

        //positions
        void moveBy(float posXBy, float posY);
        void moveBy(int posXBy, int posYBy);
        float getVitesse();
        std::pair<int,int> getPos();
        virtual void setPosition(double newX,double newY);
        inline int getX(){return posX;}
        inline int getY(){return posY;}
        inline double * getTrueX(){return &posX;}
        inline double * getTrueY(){return &posY;}
        vector<pair<int,int>> getAllPosition();

        //animations
        void addAnimation(Visuel * visu);
        map<pair<int,int>, CHAR_INFO *> getAnimation();
        virtual void update(float time) = 0;
        bool isEnabled;
        bool physicEnabled;
        virtual typePosable getTypePosable() = 0;
        void removeAllAnimation();
        bool increaseSprite(float amount = 1);
        bool decreaseSprite(float amount = 1);
        int getLengthAnimation();
        void setColor(int newColor);

        //directions
        inline void setDirection(std::pair<double, double> &newDir){dir = newDir;}
        static void normalizeDirection(std::pair<double, double> &direction)
        {
            float hypo = (direction.first * direction.first) + (direction.second * direction.second);
            hypo = sqrt(hypo);
            direction.first /= hypo;
            direction.second /= hypo;
        }


    protected:
        float indexAnimation = 0;
        std::pair<double , double > dir;
        float vitesse;
        vector<Visuel *> animations;
        float timer;
        float lastTime;
        double posX;
        double posY;
};

#endif // POSITIONABLE_H
