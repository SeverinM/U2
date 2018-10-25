#include "Manager.h"
#include <conio.h>
#include "include/Visuel.h"
#include <iostream>
#include <map>
#include <typeinfo>
#include <cstdlib>
#include <time.h>
#include <ProgrammableProj.h>

Manager::Manager(BufferManager * buff)
{
    bufferManager = buff;
    stop = false;
    poolManager = new PoolManager();
    timeSpent = 0;
    frequencySpawn = 3;
    srand(time(NULL));
    timeUpdate = 0.5;

    inputAutorisation[0][0] = 0;
    inputAutorisation[0][1] = 0;
    inputAutorisation[1][0] = 0;
    inputAutorisation[1][1] = 0;
}



void Manager::stopLoop()
{
    stop = true;
}

bool Manager::isStop()
{
    return stop;
}

bool Manager::MainLoop(float time)
{
    timeSpent += time;
    //Input section
    update_input_keys();
    inputKeysNow[INPUT_KEY_Z] = GetAsyncKeyState('Z');
	inputKeysNow[INPUT_KEY_S] = GetAsyncKeyState('S');
	inputKeysNow[INPUT_KEY_Q] = GetAsyncKeyState('Q');
	inputKeysNow[INPUT_KEY_D] = GetAsyncKeyState('D');
	inputKeysNow[INPUT_KEY_SPACE] = GetAsyncKeyState(' ');
	pressed =  inputKeysNow[INPUT_KEY_Z] || inputKeysNow[INPUT_KEY_S]
            || inputKeysNow[INPUT_KEY_Q] || inputKeysNow[INPUT_KEY_D] || inputKeysNow[INPUT_KEY_SPACE];
    if (is_input_key_down(INPUT_KEY_Z) && inputAutorisation[0][0] <= 0)
    {
        if (h != nullptr && h->isEnabled)
                    h->moveBy(0,-1);
        inputAutorisation[0][0] = moveTimerUpDown;
    }
    else if (is_input_key_down(INPUT_KEY_S) && inputAutorisation[0][1] <= 0)
    {
        if (h != nullptr && h->isEnabled)
                    h->moveBy(0,1);
        inputAutorisation[0][1] = moveTimerUpDown;
    }
    if (is_input_key_down(INPUT_KEY_Q) && inputAutorisation[1][0] <= 0)
    {
        if (h != nullptr && h->isEnabled)
                    h->moveBy(-1,0);
        inputAutorisation[1][0] = moveTimerRightLeft;
    }
    else if (is_input_key_down(INPUT_KEY_D) && inputAutorisation[1][1] <= 0 )
    {
        if (h != nullptr && h->isEnabled)
                    h->moveBy(1,0);
        inputAutorisation[1][1] = moveTimerRightLeft;
    }
    if(is_input_key_down(INPUT_KEY_SPACE)){
        h->tryToShoot();
    }

    if(inputAutorisation[0][0] > 0)
      inputAutorisation[0][0] -= time;
    if(inputAutorisation[0][1] > 0)
      inputAutorisation[0][1] -= time;
    if(inputAutorisation[1][0] > 0)
      inputAutorisation[1][0] -= time;
    if(inputAutorisation[1][1] > 0)
      inputAutorisation[1][1] -= time;

    /*
    case 'p' :
                cout << "decal" << endl;
                break;
            case 27:
                stopLoop();
                break;
    */

    //Collision buffer : empty it
    collisionBuffer.clear();

    //Hero section
    h->update(time);
    if(h->isShot){
        h->isShot = false;
        Perso::shootInfo info = h->Tirer();
        Projectile *proj = (Projectile*)poolManager->getInPool(Proj);
        proj->isEnabled = true;
        proj->removeAllAnimation();
        proj->addAnimation(Visuel::createFromFile("sprites/ProjectileHero.txt",
                                                   Visuel::getColor(Visuel::Couleur::Cyan,
                                                                    Visuel::Couleur::Transparent)));
        std::pair<double , double> direction(0,-0.07);
        proj->init(h->getPos().first + 2,h->getPos().second,direction,true);
    }
    for (auto &a : h->getAllPosition())
    {
        map<pair<int,int>,Positionable *>::iterator it = collisionBuffer.find(a);
        if (it != collisionBuffer.end())
        {
            switch (it->second->getTypePosable())
            {
                case typePosable::Enn:
                    if (!(h->getIsInRecovery()))
                    {
                        h->takeDamage(1);
                    }
                    break;
            }
        }
        collisionBuffer[a] = h;
    }

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
                //Collision !
                map<pair<int,int>,Positionable *>::iterator it = collisionBuffer.find(pp->getPos());
                if(it != collisionBuffer.end()){
                    switch ((it->second)->getTypePosable()){
                        case typePosable::Her :
                            if( !((Projectile*)pp)->getIsFromPlayer() && !h->getIsInRecovery())
                            {
                                h->takeDamage( ((Projectile*)pp)->hit() );
                                pp->isEnabled = false;
                            }
                            break;
                        case Proj:
                            if( ((Projectile*)pp)->getIsFromPlayer() != ((Projectile*)it->second)->getIsFromPlayer() ){
                                pp->isEnabled = false;
                                (it->second)->isEnabled = false;
                            }
                            break;
                    }
                }
                if (pp->physicEnabled)
                {
                    for (auto &a : pp->getAllPosition())
                    {
                        collisionBuffer[a] = pp;
                    }
                }
            }
        }
    }

    //Programmable projectile
    posList = poolManager->getProjectilesProg();
    sizeA = poolManager->getProProgPoolSize();
    for(int i = 0; i < sizeA ; i ++){
        Positionable * pp = posList[i];
        if(pp != nullptr){
            if(pp->isEnabled){
                pp->update(time);
                //Here will be the test to see if there is hero with an ennemi projectile. An ally projectile is prio on erasing the value
                //Also : if a projectile met an opposite projectile : both died
                //Collision !
                map<pair<int,int>,Positionable *>::iterator it = collisionBuffer.find(pp->getPos());
                if(it != collisionBuffer.end()){
                    switch ((it->second)->getTypePosable()){
                        case typePosable::Her :
                            if( !((Projectile*)pp)->getIsFromPlayer() && !h->getIsInRecovery())
                            {
                                h->takeDamage( ((Projectile*)pp)->hit() );
                                pp->isEnabled = false;
                            }
                            break;
                        case Proj:
                            if( ((Projectile*)pp)->getIsFromPlayer() != ((Projectile*)it->second)->getIsFromPlayer() ){
                                pp->isEnabled = false;
                                (it->second)->isEnabled = false;
                            }
                            break;
                    }
                }
                if (pp->physicEnabled)
                {
                    for (auto &a : pp->getAllPosition())
                    {
                        collisionBuffer[a] = pp;
                    }
                }
            }
        }
    }

    //Draw section
    bufferManager->resetScreen();

    drawAllElementIn(poolManager->getProjectiles(),poolManager->getProPoolSize());
    drawAllElementIn(poolManager->getEnnemies(),poolManager->getEnnPoolSize());
    drawAllElementIn(poolManager->getHero(),poolManager->getHerPoolSize());
    drawAllElementIn(poolManager->getProjectilesProg(), poolManager->getProProgPoolSize());

    bufferManager->draw();

    //Apparition d'ennemis
    if (timeSpent > frequencySpawn )
    {
        timeSpent -= frequencySpawn;
        Ennemi * e = (Ennemi *)poolManager->getInPool(typePosable::Enn);
        int random(std::rand() % (SIZEX -2));
        e->init(random,1);
        e->removeAllAnimation();
        std::pair<double , double> speed(0,0.01);
        e->setDirection(speed);
        e->isEnabled = true;
        e->addAnimation(Visuel::createFromFile("sprites/Spaceship.txt",Visuel::getColor(Visuel::Couleur::Rouge,Visuel::Couleur::Transparent)));
        e->addAnimation(Visuel::createFromFile("sprites/Destroy1.txt",Visuel::getColor(Visuel::Couleur::Rouge,Visuel::Couleur::Transparent)));
        e->addAnimation(Visuel::createFromFile("sprites/Destroy2.txt",Visuel::getColor(Visuel::Couleur::Rouge,Visuel::Couleur::Transparent)));
    }

    //Parcours des ennemies
    Positionable ** ennemies = (Positionable **)poolManager->getEnnemies();
    for (int i = 0; i < poolManager->getEnnPoolSize(); i++)
    {
        Ennemi * currentEnnPos = (Ennemi *)ennemies[i];
        if (currentEnnPos != nullptr && currentEnnPos->isEnabled)
        {
            currentEnnPos->update(time, h);
            //Collision !
            for (auto &position : currentEnnPos->getAllPosition())
            {
                map<pair<int,int>,Positionable *>::iterator it = collisionBuffer.find(position);
                if( it != collisionBuffer.end() && (*it).second != ennemies[i]){
                    Positionable * p = (it->second);
                    switch((it->second)->getTypePosable()){
                        case Proj :
                            Projectile * proj = (Projectile *)p;
                            if(proj->getIsFromPlayer()){
                                if (currentEnnPos->physicEnabled && currentEnnPos->takeDamage(proj->hit()))
                                {
                                    score += currentEnnPos->getScore();
                                }
                                proj->isEnabled = false;
                            }
                            break;
                    }
                }
            }
            if (currentEnnPos->isEnabled)
            {
                for (auto &a : currentEnnPos->getAllPosition())
                {
                    collisionBuffer[a] = currentEnnPos;
                }
            }
        }
    }

    return !(h->isEnabled);
}

void Manager::drawAllElementIn(Positionable * listElement[], int sizeA){
    for (int i = 0; i < sizeA ; i++)
    {
        if(listElement[i] != nullptr && listElement[i]->isEnabled)
        {
            map<pair<int,int>, CHAR_INFO *> temp(listElement[i]->getAnimation());
            for (auto& a : temp)
            {
                bufferManager->placeInBuffer(a.second,a.first.first,a.first.second);
            }
        }
    }
}

void Manager::init()
{
    int color(Visuel::getColor(Visuel::Couleur::Gris, Visuel::Couleur::Transparent));
    h = (Hero *)poolManager->getInPool(Her);
    h->isEnabled = true;
    h->addAnimation(Visuel::createFromFile("sprites/Spaceship.txt"));
    h->addAnimation(Visuel::createFromFile("sprites/Spaceship.txt",color));
    h->setPosition(37, 40);

    e = (Ennemi *)poolManager->getInPool(Enn);
    e->init(39, 20);
    e->removeAllAnimation();
    e->isEnabled = true;
    int couleur(Visuel::getColor(Visuel::Couleur::Rouge, Visuel::Couleur::Transparent));
    e->addAnimation(Visuel::createFromFile("sprites/Spaceship.txt",couleur));
    e->addAnimation(Visuel::createFromFile("sprites/Destroy1.txt",couleur));
    e->addAnimation(Visuel::createFromFile("sprites/Destroy2.txt",couleur));
    std::pair<double , double> direction(0,0.001);
    e->setDirection(direction);
}




//Trying things
void Manager::is_input_key_supported(InputKey inputKey)
{
	if (inputKey < 0 || inputKey > INPUT_KEY_COUNT)
	{
		cout << "testing unsupported input key : " << inputKey << "." << endl;
	}
}

void Manager::update_input_keys()
{
	memcpy(inputKeysBefore, inputKeysNow, sizeof (inputKeysBefore));
}

bool Manager::is_input_key_up(InputKey inputKey)
{
	is_input_key_supported(inputKey);
	return !inputKeysNow[inputKey];
}

bool Manager::is_input_key_down(InputKey inputKey)
{
	is_input_key_supported(inputKey);
	return inputKeysNow[inputKey];
}

bool Manager::is_input_key_released(InputKey inputKey)
{
	is_input_key_supported(inputKey);
	return inputKeysBefore[inputKey] && !inputKeysNow[inputKey];
}

bool Manager::is_input_key_pressed(InputKey inputKey)
{
	is_input_key_supported(inputKey);
	return !inputKeysBefore[inputKey] && inputKeysNow[inputKey];
}


