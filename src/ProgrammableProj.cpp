#include "ProgrammableProj.h"

string ProgrammableProj::nameFile = "Sequences.json";

json_t * ProgrammableProj::allSequences;

ProgrammableProj::ProgrammableProj(int posX, int posY, std::pair<double , double> direction, string tag, Positionable * p)
: Projectile(posX,posY, direction) , isCyclic(true) , timeSinceBegin(0)
{
    timeSpent = 0;
    posXTarget = p->getTrueX();
    posYTarget = p->getTrueY();
    vars[0] = {"tarx",posXTarget};
    vars[1] = {"tary",posYTarget};
    vars[2] = {"posx" ,&posX};
    vars[3] = {"posy", &posY};
    setTag(tag.c_str());
}

ProgrammableProj::ProgrammableProj(int posX, int posY, std::pair<double, double> direction) : Projectile(posX,posY, direction)
{
    isCyclic = true;
    timeSinceBegin = 0;
}

void ProgrammableProj::setTag(const char * newValue)
{
    actualSequence = sequence = readSequence(newValue);
    nextSequence();
}

void ProgrammableProj::update(float time)
{
    if (!isEnabled)
    {
        return;
    }

    Projectile::update(time);

    if (currentSequence.directionX == "default" || currentSequence.directionY == "default")
    {
        return;
    }

    timeSpent += time;
    if (currentSequence.time < timeSpent * 1000)
    {
        double x(evaluateString(currentSequence.directionX.c_str()));
        double y(evaluateString(currentSequence.directionY.c_str()));
        std::pair<double , double> input(x,y);
        setDirection(input);
        nextSequence();
    }
}

void ProgrammableProj::nextSequence()
{
    if (actualSequence.size() > 0)
    {
        currentSequence = actualSequence.front();
        actualSequence.pop();
    }

    else
    {
        if (sequence.size() > 0 && isCyclic)
        {
            timeSpent = 0;
            actualSequence = sequence;
            nextSequence();
        }
    }
}

double ProgrammableProj::evaluateString(const char * str)
{
    int err;
    te_expr * expr = te_compile(str,vars,4,&err);
    double output(0);
    if (expr)
    {
        output = te_eval(expr);
    }
    delete expr;
    return output;
}


