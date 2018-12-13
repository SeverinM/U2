#include "LambdaMachine.h"
#include <climits>

LambdaMachine::LambdaMachine()
{
    time = 0;
}

void LambdaMachine::update(float deltaTime)
{
    time += deltaTime;
    if (time >= currentTransition->time)
    {
        time = 0;
        if (currentTransition)
        {
            int output(currentTransition->func(this));
            evaluate(output);
        }
    }
}

void LambdaMachine::addToMachine(TransitionElement trans)
{
    if (allTransitions.size() == 0)
    {
        currentTransition = trans.origin;
    }
    allTransitions.push_back(trans);
}

void LambdaMachine::setArgument(string key , float value)
{
    arguments[key] = value;
}

float LambdaMachine::getArgument(string key)
{
    if (arguments.find(key) != arguments.end())
    {
        return arguments[key];
    }
    else
    {
        return INT_MIN;
    }
}

void LambdaMachine::evaluate(int input)
{
    for (std::vector<TransitionElement>::iterator it = allTransitions.begin(); it != allTransitions.end(); it++)
    {
        if ((*it).origin == currentTransition && (*it).flag == input)
        {
            currentTransition = (*it).destination;
        }
    }
}
