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

    private:
        bool stop;
        BufferManager *  bufferManager;
        PoolManager * poolManager;
        Hero h;
        Ennemi e;
        void drawAllElementIn(Positionable ** listElement);
};

#endif // MANAGER_H
