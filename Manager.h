#ifndef MANAGER_H
#define MANAGER_H
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include "include/Hero.h"
#include "include/Ennemi.h"
#include "include/BufferManager.h"
#include "include/PoolManager.h"

class Manager
{
    public:
        Manager(BufferManager * buff);
        void MainLoop(float time);
        void stopLoop();
        bool isStop();
        void init();
        Hero * h;
        Ennemi * e;

    private:
        bool stop;
        int timeUpdate;
        float timeSpent;
        float frequencySpawn;
        BufferManager *  bufferManager;
        PoolManager * poolManager;
        void drawAllElementIn(Positionable ** listElement, int sizeA);

        map<pair<int,int>,Positionable *> collisionBuffer;//add : max size == 70 / 70
};

#endif // MANAGER_H
