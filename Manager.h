#ifndef MANAGER_H
#define MANAGER_H
#define SIZEX 20
#define SIZEY 20
#include <windows.h>

class Manager
{
    public:
        Manager();
        void MainLoop(float time);
        void stopLoop();
        bool isStop();
        int ix;
        int iy;
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
