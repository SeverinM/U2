#ifndef MANAGER_H
#define MANAGER_H
#define SIZEX 100
#define SIZEY 100
#include <windows.h>

class Manager
{
    public:
        Manager();
        void MainLoop(float time);
        void stopLoop();
        bool isStop();
    private:
        CHAR_INFO buffer[SIZEX][SIZEY];
        bool stop;
        COORD bufferSize;
        COORD bufferCoord;
        HANDLE id;
        SMALL_RECT region;
};

#endif // MANAGER_H
