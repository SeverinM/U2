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
            case 'p' :
                cout << "decal" << endl;
                break;
            case 27:
                stopLoop();
                break;
        }
    }
    //Collision buffer : empty it
    collisionBuffer.clear();

    //Hero section
    h->update(time);
    if(h->isShot){
        Perso::shootInfo info = h->Tirer();
        Projectile *proj = (Projectile*)poolManager->getInPool(PoolManager::typePool::Proj);
        proj->isEnabled = true;
        int offsetX = -1;
        int offsetY = 2;
        proj->init(info.startPosition.first+offsetY,info.startPosition.second+offsetX,info.direction,true);
    }
    collisionBuffer[h->getPos()] = h;

    //Projectile section
    Positionable ** posList = poolManager->getProjectiles();
    int sizeA = poolManager->getProPoolSize();
    for(int i = 0; i < sizeA ; i ++){
        Positionable * pp = posList[i];
        if(pp != nullptr){
            if(pp->isEnabled){
                pp->update(time);
                //Here will be the test to see if there is hero with an ennemi projectile. An ally projectile is prio on erasing the value
                //Also : if a projectile met an opposite projectile : both died
                //if(collisionBuffer.find(pp->getPos()) != collisionBuffer.end())
                collisionBuffer[pp->getPos()] = pp;
            }
        }
    }

    //Ennemi section
    Positionable ** ennemies = (Positionable **)poolManager->getEnnemies();
    for (int i = 0; i < poolManager->getEnnPoolSize(); i++)
    {
        if (ennemies[i] != nullptr && ennemies[i]->isEnabled)
        {
            ennemies[i]->update(timeSpent);
            map<pair<int,int>,Positionable *>::iterator it = collisionBuffer.find(ennemies[i]->getPos());
            if( it != collisionBuffer.end() ){
                //if((it->second)->)
                ((Ennemi *)ennemies[i])->takeDamage(100);/*need to be replace by projectile.hit when change will be set*/

            }
            else {
                collisionBuffer[ennemies[i]->getPos()] = ennemies[i];
            }
        }
    }


    //Affichage
    bufferManager->resetScreen();

    drawAllElementIn(poolManager->getProjectiles(),poolManager->getProPoolSize());
    drawAllElementIn(poolManager->getEnnemies(),poolManager->getEnnPoolSize());
    drawAllElementIn(poolManager->getHero(),poolManager->getHerPoolSize());

    bufferManager->draw();

    if (timeSpent > frequencySpawn )
    {
        timeSpent -= frequencySpawn;
        Ennemi * e = (Ennemi *)poolManager->getInPool(PoolManager::typePool::Enn);
        int random(std::rand() % (SIZEX - 2));
        e->moveBy(random,1);
        e->isEnabled = true;
        e->addAnimation(Visuel::createFromFile("sprites/Spaceship.txt",Visuel::getColor(Visuel::Couleur::Rouge,Visuel::Couleur::Transparent)));
    }
}

void Manager::drawAllElementIn(Positionable * listElement[], int sizeA){
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
    h->addAnimation(Visuel::createFromFile("sprites/Spaceship.txt"));
    h->setPosition(SIZEX / 2, SIZEY / 2);
}
