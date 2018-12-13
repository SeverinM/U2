#ifndef GAMEWRAPPER_H
#define GAMEWRAPPER_H
#include <windows.h>
#include "BufferManager.h"
#include "Texte.h"

class GameWrapper
{
    public:
        GameWrapper(BufferManager * buffer);
        void PreGameLoop();
        void GameOver();
        bool isStop();
        void switchStop();
        inline void setStop(bool value)
        {
            stop = value;
        }

    protected:

    private:
        bool stop = false;
        BufferManager * buff;
        Texte * textGameOver;
        Texte * textPreGame;
};

#endif // GAMEWRAPPER_H
