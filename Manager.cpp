#include "Manager.h"
#include <conio.h>
#include "include/Visuel.h"
#include <iostream>
#include <map>

Manager::Manager()
{
    stop = false;
    h = Hero(3,7);
    e = Ennemi(12,12);
    Visuel * vis = Visuel::createFromFile("Spaceship.txt");
    h.addAnimation(vis);
    bufferManager = new BufferManager();
    poolManager = new PoolManager();
}



void Manager::stopLoop()
{
    stop = true;
}

bool Manager::isStop()
{
    return stop;
}

void Manager::MainLoop(float time)
{
    int key = 0;
    if (_kbhit())
    {
        key =_getch();
        switch(key){
            case 'z':
                h.moveBy(0,-1);
                break;
            case 's':
                h.moveBy(0,1);
                break;
            case 'q':
                h.moveBy(-1,0);
                break;
            case 'd':
                h.moveBy(1,0);
                break;
            default :
                    break;
        }
    }

    bufferManager->resetScreen();
    for (auto& element : h.getAnimation(0))
    {
        int x(element.first.first);
        int y(element.first.second);
        bufferManager->placeInBuffer(element.second,x,y);
    }
    bufferManager->draw();
}

void Manager::init()
{
    Hero * h = poolManager->addHero(10,10);
    Visuel * vis = Visuel::createFromFile("spaceship.txt");
    h->addAnimation(vis);
}
