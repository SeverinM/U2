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
    //vector<int> pressedKeys(10, 0);
    if (_kbhit())
    {
        key = _getch();
        //pressedKeys.push_back(key);
        //key = _getch();
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
        Projectile *proj = (Projectile*)poolManager->getInPool(typePosable::Proj);
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
                map<pair<int,int>,Positionable *>::iterator it = collisionBuffer.find(pp->getPos());
                if(it != collisionBuffer.end()){
                    switch ((it->second)->getTypePosable()){
                        case Her :
                            if( !((Projectile*)pp)->getIsFromPlayer() )
                                h->takeDamage( ((Projectile*)pp)->hit() );
                            break;
                        case Enn :
                            break;
                        case Proj:
                            if( ((Projectile*)pp)->getIsFromPlayer() != ((Projectile*)it->second)->getIsFromPlayer() ){
                                pp->isEnabled = false;
                                (it->second)->isEnabled = false;
                            }
                            break;
                    }
                }
                collisionBuffer[pp->getPos()] = pp;
            }
        }
    }

    //Draw section
    bufferManager->resetScreen();

    drawAllElementIn(poolManager->getProjectiles(),poolManager->getProPoolSize());
    drawAllElementIn(poolManager->getEnnemies(),poolManager->getEnnPoolSize());
    drawAllElementIn(poolManager->getHero(),poolManager->getHerPoolSize());

    bufferManager->draw();

    if (timeSpent > frequencySpawn )
    {
        timeSpent -= frequencySpawn;
        Ennemi * e = (Ennemi *)poolManager->getInPool(typePosable::Enn);
        int random(std::rand() % (SIZEX -2));
        e->setPosition(random,1);
        e->isEnabled = true;
        e->addAnimation(Visuel::createFromFile("sprites/Spaceship.txt",Visuel::getColor(Visuel::Couleur::Rouge,Visuel::Couleur::Transparent)));
    }

    Positionable ** ennemies = (Positionable **)poolManager->getEnnemies();
    for (int i = 0; i < poolManager->getEnnPoolSize(); i++)
    {
        if (ennemies[i] != nullptr && ennemies[i]->isEnabled)
        {
            ennemies[i]->update(timeSpent);
            map<pair<int,int>,Positionable *>::iterator it = collisionBuffer.find(ennemies[i]->getPos());
            if( it != collisionBuffer.end() ){
                    Positionable * p = (it->second);
                switch((it->second)->getTypePosable()){
                    case Her:
                        ((Ennemi *)ennemies[i])->takeDamage(100);
                        break;
                    case Enn:
                        break;
                    case Proj :
                        Projectile * proj = (Projectile *)p;
                        if(proj->getIsFromPlayer()){
                            ((Ennemi *)ennemies[i])->takeDamage(proj->hit());
                            proj->isEnabled = false;
                        }
                        break;
                }
            }
            else {
                collisionBuffer[ennemies[i]->getPos()] = ennemies[i];
            }
        }
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
    h = (Hero *)poolManager->getInPool(Her);
    h->isEnabled = true;
    h->addAnimation(Visuel::createFromFile("sprites/Spaceship.txt"));
}
