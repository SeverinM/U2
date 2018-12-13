#include "../include/GameWrapper.h"
#include <conio.h>

GameWrapper::GameWrapper(BufferManager * buffer)
{
    buff = buffer;
    float defaultPosition(10);
    textPreGame = new Texte(defaultPosition,defaultPosition);
    textPreGame->removeAllAnimation();
    textGameOver = new Texte(defaultPosition,defaultPosition);
    textGameOver->removeAllAnimation();
    textVictory = new Texte(defaultPosition, defaultPosition);
    textVictory->removeAllAnimation();

    string sprtIntro("sprites/Intro.txt");
    string sprtGameOver("sprites/gameover.txt");
    string sprtVictory("sprites/Win.txt");
    shared_ptr<Visuel> vis = Visuel::createFromFile(sprtIntro);
    shared_ptr<Visuel> vis2 = Visuel::createFromFile(sprtGameOver);
    shared_ptr<Visuel> vis3 = Visuel::createFromFile(sprtVictory);
    textGameOver->addAnimation(vis2);
    textPreGame->addAnimation(vis);
    textVictory->addAnimation(vis3);
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
        if (key == 'P')
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

void GameWrapper::Win()
{
    if (_kbhit())
    {
        char key = _getch();
        if (key == 'P')
        {
            stop = true;
        }
    }

    buff->resetScreen();
    map<pair<int,int>, CHAR_INFO *> temp(textVictory->getAnimation());
    for (auto& a : temp)
    {
        buff->placeInBuffer(a.second,a.first.first,a.first.second);
    }
    buff->draw();
}


