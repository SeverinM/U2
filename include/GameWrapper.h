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
        void Win();

        bool isStop();
        void switchStop();
        inline void setStop(bool value)
        {
            stop = value;
        }
        inline void setWon(bool value)
        {
            won = value;
        }
        inline bool getWon()
        {
            return won;
        }

    protected:

    private:
        bool won = true;
        bool stop = false;
        BufferManager * buff;
        Texte * textGameOver;
        Texte * textVictory;
        Texte * textPreGame;
};

#endif // GAMEWRAPPER_H
