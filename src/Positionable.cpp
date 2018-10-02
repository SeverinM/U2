#include "../include/Positionable.h"
#include <windows.h>
#include <algorithm>
#include <iostream>

using namespace std;

Positionable::Positionable(int startPosX,int startPosY){
    posX = startPosX;
    posY = startPosY;
}

void Positionable::moveBy(int posXBy, int posYBy)
{
    posX += posXBy;
    posY += posYBy;
};

void Positionable::addAnimation(Visuel * visu)
{
   animations.push_back(visu);
}


std::pair<int,int> Positionable::getPos(){
    return std::pair<int,int>(posX,posY);
}

map<pair<int,int>, CHAR_INFO *>& Positionable::getAnimation(int index)
{
    map<pair<int,int>, CHAR_INFO *> output;
    map<pair<int,int>, CHAR_INFO *> inputRef = animations[index]->getPositions();
    map<pair<int,int>, CHAR_INFO *>::iterator i = inputRef.begin();
    while (i != inputRef.end())
    {
        output[make_pair(i->first.second + posX,i->first.first + posY)] = i->second;
        i++;
    }
    return output;
}

