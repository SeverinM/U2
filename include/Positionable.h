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
#include <queue>
#include <functional>
#include <math.h>
#include <memory>

enum typePosable
{
    Proj,
    Enn,
    Her,
    Txt
};

struct Lambda
{
    float time;
    std::function<void()> func;
    bool repeatItself;
};

class Positionable
{
    public:

        Positionable(float &startPosX,float &startPosY);
        void init(float &posXBy,float &posY, string spriteFileName = "sprite/spaceship.txt");

        //positions
        void moveBy(float &posXBy, float &posY);
        float getVitesse();
        std::pair<float,float> getPos();
        inline std::pair<int , int> getIntPos(){return {(int)floor(posX),(int)floor(posY)};};
        virtual void setPosition(float &newX,float &newY);
        vector<pair<int,int>> getAllPosition();

        //animations
        void addAnimation(shared_ptr<Visuel> visu);
        map<pair<int,int>, CHAR_INFO *> getAnimation();
        bool isEnabled;
        bool physicEnabled;
        virtual typePosable getTypePosable() = 0;
        void removeAllAnimation();
        bool increaseSprite(float &amount);
        bool decreaseSprite(float &amount);
        int getLengthAnimation();
        void setColor(int &newColor);

        //Lambdas
        virtual void update(float &time);
        inline int sizeLambda(){return funcQueue.size();};
        inline Lambda& addLambda(std::function<void()> lambda, float time,bool repeat = false)
        {
            //Securité
            if (repeat && time <= 0)
            {
                repeat = false;
            }
            Lambda lamb;
            lamb.time = time;
            lamb.func = lambda;
            lamb.repeatItself = repeat;
            funcQueue.push(lamb);
            return funcQueue.back();
        }

        //directions
        inline void setDirection(std::pair<float, float> &newDir){dir = newDir;}
        static void normalizeDirection(std::pair<float,float> &direction)
        {
            float hypo = (direction.first * direction.first) + (direction.second * direction.second);
            hypo = sqrt(hypo);
            direction.first /= hypo;
            direction.second /= hypo;
        }


    protected:
        float indexAnimation = 0;
        std::pair<float , float> dir;
        float vitesse;
        vector<shared_ptr<Visuel>> animations;
        float timer;
        float lastTime;
        float timerFunc;
        float posX;
        float posY;

        queue<Lambda> funcQueue;
};

#endif // POSITIONABLE_H
