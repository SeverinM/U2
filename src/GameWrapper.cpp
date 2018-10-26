#include "../include/GameWrapper.h"
#include <conio.h>

GameWrapper::GameWrapper(BufferManager * buffer)
{
    buff = buffer;
    float defaultPosition(30);
    textPreGame = new Texte(defaultPosition,defaultPosition);
    textPreGame->removeAllAnimation();
    textGameOver = new Texte(defaultPosition,defaultPosition);
    textGameOver->removeAllAnimation();
    string sprtIntro("sprites/Intro.txt");
    string sprtGameOver("sprites/gameover.txt");
    shared_ptr<Visuel> vis = Visuel::createFromFile(sprtIntro);
    shared_ptr<Visuel> vis2 = Visuel::createFromFile(sprtGameOver);
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


