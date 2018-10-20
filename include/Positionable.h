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
            Txt
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
        double& getTrueX();
        double& getTrueY();
        virtual void setPosition(double newX,double newY);
        inline int getX(){return posX;}
        inline int getY(){return posY;}
        vector<pair<int,int>> getAllPosition();

        //animations
        void addAnimation(Visuel * visu);
        map<pair<int,int>, CHAR_INFO *> getAnimation();
        virtual void update(float time) = 0;
        bool isEnabled;
        virtual typePosable getTypePosable() = 0;
        void removeAllAnimation();
        void nextSprite();
        void previousSprite();
        int getLengthAnimation();

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
        int indexAnimation = 0;
        std::pair<double , double > dir;
        float vitesse;
        vector<Visuel *> animations;
        float timer;
        float lastTime;
        double posX;
        double posY;
};

#endif // POSITIONABLE_H
