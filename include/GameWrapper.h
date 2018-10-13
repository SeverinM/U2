#ifndef GAMEWRAPPER_H
#define GAMEWRAPPER_H
#include <windows.h>
#include "BufferManager.h"

class GameWrapper
{
    public:
        GameWrapper(BufferManager * buffer);
        void PreGameLoop();
        void GameOver();
        bool isStop();
        void switchStop();

    protected:

    private:
        bool stop = false;
        BufferManager * buff;
        Hero * textGameOver;
        Hero * textPreGame;
};

#endif // GAMEWRAPPER_H
