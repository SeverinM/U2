#ifndef MANAGER_H
#define MANAGER_H
#define SIZEX 70
#define SIZEY 70
#define _WIN32_WINNT 0x0500
#include<windows.h>
#include "include/Hero.h"
#include "include/Ennemi.h"

class Manager
{
    public:
        Manager();
        void MainLoop(float time);
        void stopLoop();
        bool isStop();
        int ix;
        int iy;
        Hero h;
        Ennemi e;

    private:
        CHAR_INFO buffer[SIZEX][SIZEY];
        bool stop;
        COORD bufferSize;
        COORD bufferCoord;
        HANDLE id;
        SMALL_RECT region;
        int memx;
        int memy;
};

#endif // MANAGER_H
