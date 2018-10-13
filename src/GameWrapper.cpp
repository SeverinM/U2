#include "../include/GameWrapper.h"
#include <conio.h>

GameWrapper::GameWrapper(BufferManager * buffer)
{
    buff = buffer;
    textPreGame = new Hero(30,30);
    textPreGame->removeAnimation(0);
    Visuel * vis = Visuel::createFromFile("sprites/Intro.txt");
    textPreGame->addAnimation(vis);
    textPreGame->isEnabled = true;
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
    map<pair<int,int>, CHAR_INFO *> temp(textPreGame->getAnimation(0));
    for (auto& a : temp)
    {
        buff->placeInBuffer(a.second,a.first.first,a.first.second);
    }
    buff->draw();
}

void GameWrapper::GameOver()
{
    buff->resetScreen();
    map<pair<int,int>, CHAR_INFO *> temp(textPreGame->getAnimation(0));
    for (auto& a : temp)
    {
        buff->placeInBuffer(a.second,a.first.first,a.first.second);
    }
    buff->draw();
}


