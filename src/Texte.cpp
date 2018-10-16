#include "Texte.h"

Texte::Texte(int startPosX, int startPosY) : Positionable(startPosX, startPosY)
{
    //ctor
}

void Texte::update(float time)
{
}

typePosable Texte::getTypePosable()
{
    return typePosable::Txt;
}

Texte::~Texte()
{
    //dtor
}
