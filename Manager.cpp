#include "Manager.h"
#include <conio.h>
#include "include/Visuel.h"
#include <iostream>
#include <map>
#include <typeinfo>

Manager::Manager()
{
    stop = false;
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
    //Input section
    int key = 0;
    if (_kbhit())
    {
        key =_getch();
        switch(key){
            case 'z':
                if (h != nullptr && h->isEnabled)
                    h->moveBy(0,-1);
                break;
            case 's':
                if (h != nullptr && h->isEnabled)
                    h->moveBy(0,1);
                break;
            case 'q':
                if (h != nullptr && h->isEnabled)
                    h->moveBy(-1,0);
                break;
            case 'd':
                if (h != nullptr && h->isEnabled)
                    h->moveBy(1,0);
                break;
            case ' ':
                h->tryToShoot();
                break;
            case 27:
                stopLoop();
                break;
        }
    }

    //Hero section
    h->update(time);
    if(h->isShot){
        Perso::shootInfo info = h->Tirer();
        Projectile *proj = (Projectile*)poolManager->getInPool(PoolManager::typePool::Proj);
        proj->isEnabled = true;
        cout << info.startPosition.first << " , " << info.startPosition.second << endl;
        proj->init(info.startPosition.first,info.startPosition.second,info.direction);
    }
    //Projectil section
    Positionable ** posList = poolManager->getProjectiles();
    int sizeA = sizeof(posList)/sizeof(posList[0]);
    for(int i = 0; i < sizeA ; i ++){
        if(posList[i] != nullptr){
            if(posList[i]->isEnabled){
                //cout << "isEnabled" << endl;
                posList[i]->update(time);
            }
        }
    }
    //Ennemi section


    bufferManager->resetScreen();

    drawAllElementIn(poolManager->getProjectiles());
    drawAllElementIn(poolManager->getEnnemies());
    drawAllElementIn(poolManager->getHero());

    bufferManager->draw();
}

void Manager::drawAllElementIn(Positionable * listElement[]){

    if (listElement[0] == nullptr)
    {
        return;
    }
    int sizeA(sizeof(listElement) / sizeof(listElement[0]));
    for (int i = 0; i < sizeA ; i++)
    {
        if(listElement[i]->isEnabled)
        {
            map<pair<int,int>, CHAR_INFO *> temp(listElement[i]->getAnimation(0));
            for (auto& a : temp)
            {
                bufferManager->placeInBuffer(a.second,a.first.first,a.first.second);
            }
        }
    }
}

void Manager::init()
{
    h = (Hero *)poolManager->getInPool(PoolManager::Her);
    h->isEnabled = true;
    h->addAnimation(Visuel::createFromFile("Spaceship.txt"));
    Ennemi * e = (Ennemi *)poolManager->getInPool(PoolManager::Enn);
    e->moveBy(10,10);
    e->isEnabled = true;
    e->addAnimation(Visuel::createFromFile("Spaceship.txt",Visuel::getColor(Visuel::Couleur::Rouge,Visuel::Couleur::Transparent)));
}
