#include "Texte.h"
#include <jansson.h>

Texte::Texte(int startPosX, int startPosY) : Positionable(startPosX, startPosY)
{

    // A supprimer , servait juste a voir si la lib a bien été linké
    json_t *arr, *integ;

    arr = json_array();
    integ = json_integer(42);

    json_array_append(arr, integ);
    json_decref(integ);

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
