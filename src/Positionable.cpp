#include "../include/Positionable.h"
#include <windows.h>
#include <algorithm>
#include <iostream>
#include <tgmath.h>
#include <math.h>

using namespace std;

Positionable::Positionable(float &startPosX,float &startPosY){
    posX = startPosX;
    posY = startPosY;
    isEnabled = false;
    physicEnabled = true;
    dir = std::pair<float , float>(0.001,0.001);
    timerFunc = 0;
    animations = {};
}

void Positionable::update(float &time)
{
    timerFunc += time;

    while (funcQueue.size() > 0 && funcQueue.front().time <= timerFunc)
    {
        funcQueue.front().func();
        if (!funcQueue.front().repeatItself)
        {
            funcQueue.pop();
        }
        timerFunc = 0;
    }
}

void Positionable::moveBy(float &posXBy, float &posYBy)
{
    float newPosX = posXBy + posX;
    float newPosY = posYBy + posY;
    setPosition(newPosX, newPosY);
};

void Positionable::setColor(int &newColor)
{
    for (auto &a : animations)
    {
        a->setColor(newColor);
    }
}

void Positionable::init(float &startPosX,float &startPosY,string spritefileName){
    setPosition(startPosX, startPosY);
    addAnimation(Visuel::createFromFile(spritefileName));
    timerFunc = 0;
    while (funcQueue.size() > 0)
    {
        funcQueue.pop();
    }
}

void Positionable::addAnimation(shared_ptr<Visuel> visu)
{
   animations.push_back(visu);
}

std::pair<float,float> Positionable::getPos(){
    return std::pair<float,float>((float)floor(posX),(float)floor(posY));
}

map<pair<int,int>, CHAR_INFO *> Positionable::getAnimation()
{
    map<pair<int,int>, CHAR_INFO *> output;
    map<pair<int,int>, CHAR_INFO *> inputRef = animations[floor(indexAnimation)]->getPositions();
    map<pair<int,int>, CHAR_INFO *>::iterator i = inputRef.begin();
    while (i != inputRef.end())
    {
        output[make_pair(i->first.first + getIntPos().first,i->first.second + getIntPos().second)] = i->second;
        i++;
    }
    return output;
}

void Positionable::setPosition(float &newX,float &newY)
{
    posX = newX;
    posY = newY;
    if (posX < 0 || posX >= SIZEX || posY < 0 || posY >= SIZEY)
    {
        isEnabled = false;
    }
}

vector<pair<int,int>> Positionable::getAllPosition()
{
    vector<pair<int,int>> output;
    for(auto &a : getAnimation())
    {
        output.push_back(a.first);
    }
    return output;
}

void Positionable::removeAllAnimation()
{
    animations.clear();
}

bool Positionable::decreaseSprite(float &amount)
{
    bool output;
    indexAnimation = max((float)0, indexAnimation - amount);
    output = ((float)0 < indexAnimation);
    return output;
}

bool Positionable::increaseSprite(float &amount)
{
    bool output;
    indexAnimation = min((float)getLengthAnimation() -1 ,indexAnimation + amount);
    output = (getLengthAnimation() - 1 > indexAnimation );
    return output;
}

int Positionable::getLengthAnimation()
{
    return animations.size();
}

Lambda& Positionable::addLambda(std::function<void()> lambda,float time,bool repeat)
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
