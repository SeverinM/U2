#ifndef BUFFERMANAGER_H
#define BUFFERMANAGER_H
#include "Positionable.h"
#include <vector>

using namespace std;

class BufferManager
{
    public:
        BufferManager();

    private:
        vector<Positionable> enne;
        vector<Ennemi> secondLoop;
        vector<Projectile> thirdLoop;
        vector<Hero> fourthLoop;
};

#endif // BUFFERMANAGER_H
