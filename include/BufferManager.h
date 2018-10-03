#ifndef BUFFERMANAGER_H
#define BUFFERMANAGER_H
#include "Positionable.h"
#include <vector>
#include "PoolManager.h"
#include <windows.h>
#define SIZEX 70
#define SIZEY 70

using namespace std;

class BufferManager
{
    public:
        BufferManager();
        void placeInBuffer(CHAR_INFO * car, int &x, int &y);
        void draw();
        void resetScreen();

    private:
        CHAR_INFO buffer[SIZEX][SIZEY];
        COORD bufferSize;
        COORD bufferCoord;
        HANDLE id;
        SMALL_RECT region;
        CHAR_INFO defaultCar;
};

#endif // BUFFERMANAGER_H
