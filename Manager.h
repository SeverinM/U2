#ifndef MANAGER_H
#define MANAGER_H
#define SIZEX 70
#define SIZEY 70
#include <windows.h>
#include "Hero.h"
#include "Ennemi.h"

class Manager
{
    public:
        Manager();
        void MainLoop(float time);
        void stopLoop();
        bool isStop();
        int ix;
        int iy;
        /*test : */Hero h;
        /*test : */Ennemi e;
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
