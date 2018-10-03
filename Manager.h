#ifndef MANAGER_H
#define MANAGER_H
#define _WIN32_WINNT 0x0500
#include<windows.h>
#include "include/Hero.h"
#include "include/Ennemi.h"
#include "BufferManager.h"

class Manager
{
    public:
        Manager();
        void MainLoop(float time);
        void stopLoop();
        bool isStop();

    private:
        bool stop;
        BufferManager *  bufferManager;
        Hero h;
        Ennemi e;
};

#endif // MANAGER_H
