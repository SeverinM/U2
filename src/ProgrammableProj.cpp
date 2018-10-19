#include "ProgrammableProj.h"

string ProgrammableProj::nameFile = "Sequences.json";

json_t * ProgrammableProj::allSequences;

ProgrammableProj::ProgrammableProj(int posX, int posY, std::pair<double , double> direction, string tag)
: Projectile(posX,posY, direction) , isCyclic(false) , timeSinceBegin(0)
{
    //ctor
}

void ProgrammableProj::setTag(string &newValue)
{

}

void ProgrammableProj::update(float time)
{
    Projectile::update(time);
}

