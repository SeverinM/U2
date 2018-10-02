#include "Positionable.h"

using namespace std;

Positionable::Positionable(){

}

Positionable::moveBy(int posXBy, int posYBy)
{
    posX += posXBy;
    posY += posYBy;
}

