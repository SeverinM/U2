#include "ProgrammableProj.h"

string ProgrammableProj::nameFile = "Sequences.json";

json_t * ProgrammableProj::allSequences;

ProgrammableProj::ProgrammableProj(int posX, int posY, std::pair<double , double> direction, string tag, Positionable * p)
: Projectile(posX,posY, direction) , isCyclic(false) , timeSinceBegin(0) ,
posXTarget(&(p->getTrueX())) , posYTarget(&(p->getTrueY())),
vars{{"tarX",posXTarget}, {"tarY", posYTarget}, {"posX" , &posX} , {"posY", &posY}}
{
    timeSpent = 0;
}

void ProgrammableProj::setTag(char * &newValue)
{
    actualSequence = sequence = readSequence(newValue);
    nextSequence();
}

void ProgrammableProj::update(float time)
{
    cout << time << endl;
    Projectile::update(time);
    timeSpent += time;
    if (currentSequence.time >= timeSpent * 1000)
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
    te_expr * expr = te_compile(str,vars,2,&err);
    double output(0);
    if (expr)
    {
        output = te_eval(expr);
    }
    return output;
}

