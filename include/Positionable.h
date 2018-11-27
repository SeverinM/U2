#ifndef POSITIONABLE_H
#define POSITIONABLE_H
#include <stdio.h>
#include "Visuel.h"
#include <vector>
#include <map>
#include <iostream>
#include <tgmath.h>
#define SIZEX 60
#define SIZEY 60
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
        Lambda& addLambda(std::function<void()> lambda, float time,bool repeat = false);
        inline Lambda& addLambda(Lambda &lamb)
        {
            funcQueue.push(lamb);
            return lamb;
        }

        inline void addLambda(queue<Lambda> &newValue)
        {
            funcQueue = newValue;
        }

        inline void cleanQueue()
        {
            while (!funcQueue.empty())
            {
                funcQueue.pop();
            }
        }

        //directions
        inline void setDirection(std::pair<float, float> &newDir){dir = newDir;}
        inline std::pair<float, float> getDirection(){return dir;}
        static void normalizeDirection(std::pair<float,float> &direction)
        {
            float hypo = (direction.first * direction.first) + (direction.second * direction.second);
            hypo = sqrt(hypo);
            direction.first /= hypo;
            direction.second /= hypo;
        }

        inline void setFlag(int &newValue){flag = newValue;}
        inline int getFlag(){return flag;}
        void stop();


    protected:
        float indexAnimation = 0;
        std::pair<float , float> dir;
        vector<shared_ptr<Visuel>> animations;
        float timer;
        float lastTime;
        float timerFunc;
        float posX;
        float posY;
        int flag;

        queue<Lambda> funcQueue;
};

#endif // POSITIONABLE_H
