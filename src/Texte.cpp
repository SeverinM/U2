#include "Texte.h"

Texte::Texte(float &startPosX,float &startPosY) : Positionable(startPosX, startPosY){}

void Texte::update(float &time){}

typePosable Texte::getTypePosable()
{
    return typePosable::Txt;
}

Texte::~Texte(){}
