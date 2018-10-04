#include "Manager.h"
#include <conio.h>
#include "include/Visuel.h"
#include <iostream>
#include <map>
#include <typeinfo>
#include <cstdlib>
#include <time.h>

Manager::Manager()
{
    stop = false;
    bufferManager = new BufferManager();
    poolManager = new PoolManager();
    timeSpent = 0;
    frequencySpawn = 3;
    srand(time(NULL));
    timeUpdate = 0.5;
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
    timeSpent += time;
    timeSpentUpdate += time;
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
        proj->init(info.startPosition.first,info.startPosition.second,info.direction);
    }

    //Projectile section
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

    if (timeSpent > frequencySpawn )
    {
        timeSpent -= frequencySpawn;
        Ennemi * e = (Ennemi *)poolManager->getInPool(PoolManager::typePool::Enn);
        int random(std::rand() % 20);
        e->setPosition(random,1);
        e->isEnabled = true;
        e->addAnimation(Visuel::createFromFile("Spaceship.txt",Visuel::getColor(Visuel::Couleur::Rouge,Visuel::Couleur::Transparent)));

        Positionable ** ennemies = (Positionable **)poolManager->getEnnemies();
        for (int i = 0; i < 15; i++)
        {
            if (ennemies[i] != nullptr && ennemies[i]->isEnabled)
            {
                ennemies[i]->update(timeSpent);
            }
        }
    }
}

void Manager::drawAllElementIn(Positionable * listElement[]){

    if (listElement[0] == nullptr)
    {
        return;
    }
    int sizeA(sizeof(listElement) / sizeof(listElement[0]));
    for (int i = 0; i < sizeA ; i++)
    {
        if(listElement[i] != nullptr && listElement[i]->isEnabled)
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
}
