#include "../include/Positionable.h"
#include <windows.h>
#include <algorithm>
#include <iostream>
#include <tgmath.h>

using namespace std;

Positionable::Positionable(int startPosX,int startPosY){
    posX = startPosX;
    posY = startPosY;
    vitesse = 4; //TO DO : change this
    isEnabled = false;
    dir = std::pair<double , double>(0.001,0.001);
}

void Positionable::moveBy(float posXBy, float posYBy)
{
    setPosition(posXBy + posX, posYBy + posY);
};

void Positionable::init(int startPosX,int startPosY,string spritefileName){
    posX = startPosX;
    posY = startPosY;
    addAnimation(Visuel::createFromFile(spritefileName));
}

float Positionable::getVitesse(){
    return vitesse;
}
void Positionable::addAnimation(Visuel * visu)
{
   animations.push_back(visu);
}


std::pair<int,int> Positionable::getPos(){
    return std::pair<int,int>((int)floor(posX),(int)floor(posY));
}

map<pair<int,int>, CHAR_INFO *> Positionable::getAnimation()
{
    map<pair<int,int>, CHAR_INFO *> output = *new map<pair<int,int>, CHAR_INFO *>();
    map<pair<int,int>, CHAR_INFO *> inputRef = animations[indexAnimation]->getPositions();
    map<pair<int,int>, CHAR_INFO *>::iterator i = inputRef.begin();
    while (i != inputRef.end())
    {
        output[make_pair(i->first.first + getPos().first,i->first.second + getPos().second)] = i->second;
        i++;
    }
    return output;
}

void Positionable::setPosition(double newX,double newY)
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
    for (auto &anims : animations)
    {
        delete anims;
    }
    animations.clear();
}

void Positionable::previousSprite()
{
    indexAnimation = max(0, indexAnimation - 1);
}

void Positionable::nextSprite()
{
    indexAnimation = (indexAnimation + 1) % getLengthAnimation();
}

int Positionable::getLengthAnimation()
{
    return animations.size();
}

