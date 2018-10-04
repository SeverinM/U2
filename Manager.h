#ifndef MANAGER_H
#define MANAGER_H
#define _WIN32_WINNT 0x0500
#include<windows.h>
#include "include/Hero.h"
#include "include/Ennemi.h"
#include "include/BufferManager.h"
#include "include/PoolManager.h"

class Manager
{
    public:
        Manager();
        void MainLoop(float time);
        void stopLoop();
        bool isStop();
        void init();
        Hero * h;

    private:
        bool stop;
        int timeUpdate;
        float timeSpent;
        float timeSpentUpdate;
        float frequencySpawn;
        BufferManager *  bufferManager;
        PoolManager * poolManager;
        void drawAllElementIn(Positionable ** listElement, int sizeA);
};

#endif // MANAGER_H
