#include "Manager.h"
#include <conio.h>
#include "include/Visuel.h"
#include <iostream>
#include <map>
#include <typeinfo>

Manager::Manager()
{
    stop = false;
    Visuel * vis = Visuel::createFromFile("Spaceship.txt");
    h.addAnimation(vis);
    bufferManager = new BufferManager();
    poolManager = new PoolManager();

    h = Hero(3,7);
    e = Ennemi(12,12);
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
    //Input section
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
                case ' ':
            h.tryToShoot();
                break;
            default :
                    break;
        }
    }
    //Hero section
    h.update(time);
    //Projectil section


    //Ennemi section

    bufferManager->resetScreen();
    drawAllElementIn(poolManager->getProjectiles());
    drawAllElementIn(poolManager->getEnnemies());
    drawAllElementIn(poolManager->getHero());

    bufferManager->draw();
}

void Manager::drawAllElementIn(Positionable * listElement[]){
    int sizeA(sizeof(listElement) / sizeof(listElement[0]));
    for (int i = 0; i < sizeA ; i++)
    {
        map<pair<int,int>, CHAR_INFO *> temp(listElement[i]->getAnimation(0));
    }
}

void Manager::init()
{
    Positionable * h = poolManager->addHero(10,10);
    Visuel * vis = Visuel::createFromFile("spaceship.txt");
    h->addAnimation(vis);
}
