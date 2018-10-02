#include "../include/Positionable.h"

using namespace std;

Positionable::Positionable(int startPosX,int startPosY){
    posX = startPosX;
    posY = startPosY;
    vitesse = 8; //TO DO : change this
}

Positionable::moveBy(int posXBy, int posYBy)
{
    posX += posXBy;
    posY += posYBy;
};

float Positionable::getVitesse(){
    return vitesse;
}




std::pair<int,int> Positionable::getPos(){
    return std::pair<int,int>(posX,posY);

}

