#include "../include/GameWrapper.h"
#include <conio.h>

GameWrapper::GameWrapper(BufferManager * buffer)
{
    buff = buffer;
    textPreGame = new Texte(30,30);
    textPreGame->removeAllAnimation();
    textGameOver = new Texte(30,30);
    textGameOver->removeAllAnimation();
    Visuel * vis = Visuel::createFromFile("sprites/Intro.txt");
    Visuel * vis2 = Visuel::createFromFile("sprites/gameover.txt");
    textGameOver->addAnimation(vis2);
    textPreGame->addAnimation(vis);
}

bool GameWrapper::isStop()
{
    return stop;
}

void GameWrapper::switchStop()
{
    stop = !stop;
}

void GameWrapper::PreGameLoop()
{
    if (_kbhit())
    {
        char key = _getch();
        if (key == ' ')
        {
            stop = true;
        }
    }

    buff->resetScreen();
    map<pair<int,int>, CHAR_INFO *> temp(textPreGame->getAnimation());
    for (auto& a : temp)
    {
        buff->placeInBuffer(a.second,a.first.first,a.first.second);
    }
    buff->draw();
}

void GameWrapper::GameOver()
{
    if (_kbhit())
    {
        char key = _getch();
        if (key == ' ')
        {
            stop = true;
        }
    }

    buff->resetScreen();
    map<pair<int,int>, CHAR_INFO *> temp(textGameOver->getAnimation());
    for (auto& a : temp)
    {
        buff->placeInBuffer(a.second,a.first.first,a.first.second);
    }
    buff->draw();
}


