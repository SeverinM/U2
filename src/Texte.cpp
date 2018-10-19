#include "Texte.h"
#include <jansson.h>

Texte::Texte(int startPosX, int startPosY) : Positionable(startPosX, startPosY)
{
    //A supprimer par la suite , c'etait juste pour test
    /*json_t *root;
    json_t * liste;
    json_t * obj;
    json_t * arr;
    json_t * zero;
    json_t * nb;

    json_error_t error;
    string line;
    string jsonFile;

    ifstream file("Sequences.json");
    if (file.is_open())
    {
        while (getline(file, line))
        {
            jsonFile += line;
        }
        file.close();
    }

    root = json_loads(jsonFile.c_str(),0,&error);
    liste = json_object_get(root, "Projectiles");
    obj = json_object_get(liste,"Test");
    arr = json_object_get(obj,"steps");
    zero = json_array_get(arr,0);
    nb = json_object_get(zero,"x");

    cout << json_string_value(nb) << endl;*/
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
