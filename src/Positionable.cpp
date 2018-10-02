#include "Positionable.h"

using namespace std;

Positionable::Positionable(int startPosX,int startPosY){
    posX = startPosX;
    posY = startPosY;
}

Positionable::moveBy(int posXBy, int posYBy)
{
    posX += posXBy;
    posY += posYBy;
}




std::pair<int,int> Positionable::getPos(){
    return std::pair<int,int>(posX,posY);

}

