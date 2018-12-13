#ifndef LAMBDAMACHINE_H
#define LAMBDAMACHINE_H
#include <vector>
#include <map>
#include "Positionable.h"


struct Lambda;

struct TransitionElement
{
    shared_ptr<Lambda> origin;
    int flag;
    shared_ptr<Lambda> destination;
};

class LambdaMachine
{
    public:
        LambdaMachine();
        void update(float deltaTime);
        void addToMachine(TransitionElement trans);
        void setArgument(string key, float value);
        float getArgument(string key);

    private:
        std::vector<TransitionElement> allTransitions;
        shared_ptr<Lambda> currentTransition;
        std::map<string,float> arguments;
        void evaluate(int input);
        float time;
};

#endif // LAMBDAMACHINE_H
