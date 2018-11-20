#include "Manager.h"
#include <conio.h>
#include "include/Visuel.h"
#include <iostream>
#include <map>
#include <typeinfo>
#include <cstdlib>
#include <time.h>

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
    float minusOne(-1);
    float one(1);
    float zero(0);
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
                    h->moveBy(zero,minusOne);
        inputAutorisation[0][0] = moveTimerUpDown;
    }
    else if (is_input_key_down(INPUT_KEY_S) && inputAutorisation[0][1] <= 0)
    {
        if (h != nullptr && h->isEnabled)
                    h->moveBy(zero,one);
        inputAutorisation[0][1] = moveTimerUpDown;
    }
    if (is_input_key_down(INPUT_KEY_Q) && inputAutorisation[1][0] <= 0)
    {
        if (h != nullptr && h->isEnabled)
                    h->moveBy(minusOne,zero);
        inputAutorisation[1][0] = moveTimerRightLeft;
    }
    else if (is_input_key_down(INPUT_KEY_D) && inputAutorisation[1][1] <= 0 )
    {
        if (h != nullptr && h->isEnabled)
                    h->moveBy(one,zero);
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

    //Collision buffer : empty it
    collisionBuffer.clear();

    //Hero section
    h->update(time);
    if(h->isShot){
        h->isShot = false;
        h->Tirer();
        Projectile *proj = static_cast<Projectile*>(poolManager->getInPool(Proj));
        proj->isEnabled = true;
        proj->removeAllAnimation();
        string defaultSprite("sprites/ProjectileHero.txt");
        proj->addAnimation(Visuel::createFromFile(defaultSprite,
                                                   Visuel::getColor(Visuel::Couleur::Cyan,
                                                                    Visuel::Couleur::Transparent)));
        std::pair<float , float> direction(0,-0.07);
        float x(h->getPos().first + 2);
        float y(h->getPos().second);
        bool isPlayer(true);
        proj->init(x,y,direction,isPlayer);
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
                        int amount(1);
                        h->takeDamage(amount);
                    }
                    break;

                default :
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
                    Projectile * proj (static_cast<Projectile *>(pp));
                    switch ((it->second)->getTypePosable()){
                        case typePosable::Her :
                            if(!proj->getIsFromPlayer() && !h->getIsInRecovery())
                            {
                                int damage(proj->hit());
                                h->takeDamage(damage);
                                pp->isEnabled = false;
                            }
                            break;
                        case Proj:
                            if(proj->getIsFromPlayer() != static_cast<Projectile *>(it->second)->getIsFromPlayer() ){
                                pp->isEnabled = false;
                                (it->second)->isEnabled = false;
                            }
                            break;

                        default :
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
    //ShotPower slider :
    CHAR_INFO trait ;
    trait.Char.AsciiChar = '-';
    trait.Attributes = FOREGROUND_RED | FOREGROUND_INTENSITY;

    float numberOf_Full = SIZEY * (h->getShotPower()/SHOT_POWER_MAX);
    for(int yPos = 0; yPos < numberOf_Full; yPos++)
    {
        if(yPos == 3)
            trait.Attributes = FOREGROUND_GREEN;
        bufferManager->placeInBuffer(&trait, (yPos), (SIZEX-28));
    }

    drawAllElementIn(poolManager->getProjectiles(),poolManager->getProPoolSize());
    drawAllElementIn(poolManager->getEnnemies(),poolManager->getEnnPoolSize());
    drawAllElementIn(poolManager->getHero(),poolManager->getHerPoolSize());

    bufferManager->draw();

    //Parcours des ennemies
    Positionable ** ennemies(static_cast<Positionable **>(poolManager->getEnnemies()));
    for (int i = 0; i < poolManager->getEnnPoolSize(); i++)
    {
        Ennemi * currentEnnPos(static_cast<Ennemi *>(ennemies[i]));
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
                        default:
                            break;

                        case Proj :
                            Projectile * proj(static_cast<Projectile *>(p));
                            if(proj->getIsFromPlayer()){
                                int dmg(proj->hit());
                                if (currentEnnPos->physicEnabled && currentEnnPos->takeDamage(dmg))
                                {
                                    score += currentEnnPos->getScore();
                                    proj->isEnabled = false;
                                }
                            }
                            break;
                    }
                }
            }

            //Reecriture du buffer physique
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
                //Try on the PV information :
                if(a.second->Char.AsciiChar >= 48 && a.second->Char.AsciiChar <= 57 ){
                    int pvalue = (static_cast<Perso *>(listElement[i]))->getPV();
                    //string s = std::to_string (pvalue);
                    a.second->Char.AsciiChar = 48+pvalue;//s[0];
                }
                //End try
                bufferManager->placeInBuffer(a.second,a.first.first,a.first.second);
            }
        }
    }
}

void Manager::init()
{
    string spaceship("sprites/Spaceship.txt");
    string destroy1("sprites/Destroy1.txt");
    string destroy2("sprites/Destroy2.txt");

    int color(Visuel::getColor(Visuel::Couleur::Gris, Visuel::Couleur::Transparent));
    h = (Hero *)poolManager->getInPool(Her);
    h->isEnabled = true;
    h->addAnimation(Visuel::createFromFile(spaceship));
    h->addAnimation(Visuel::createFromFile(spaceship,color));
    float x(37);
    float y(40);
    h->setPosition(x,y);
    fact = new FactoryEnnemy(poolManager);
    float anim(0.001);
    fact->setSpeedAnimation(anim);

    float freq(2);
    fact->setFrequencyShoot(freq);
    std::pair<float,float> firstDirection(0,10);
    fact->setDirection(firstDirection);
    FactoryEnnemy * tempFact(fact);

    std::function<void()> func;

    //pattern 1
    func = [this,tempFact]
    {
        Ennemi * e = tempFact->build(TypeEnnemy::StraightDown);
        float x(37);
        float y(1);
        e->setPosition(x,y);
    };
    h->addLambda(func,2,false);
    for (int i = 0; i < 5 ; i++)
    {
        h->addLambda(func,0.2,false);
    };

    //Pattern 2
    func = [this,tempFact]
    {
        std::pair<float,float> direction(-3,10);
        tempFact->setDirection(direction);
        Ennemi * e = tempFact->build(TypeEnnemy::StraightDown);
        float x(SIZEX - 2);
        float y(1);
        e->setPosition(x,y);
    };
    h->addLambda(func,2,false);
    for (int i = 0; i < 5 ; i++)
    {
        h->addLambda(func,0.2,false);
    };

    //Pattern 3
    func = [this,tempFact]
    {
        std::pair<float,float> direction(-3,10);
        tempFact->setDirection(direction);
        Ennemi * e = tempFact->build(TypeEnnemy::Circle);
        float random(std::rand() % (SIZEX -2));
        float y(1);
        e->setPosition(random,y);
    };
    h->addLambda(func,2,false);
    for (int i = 0; i < 10; i++)
    {
        h->addLambda(func,0.2,false);
    }

    //Pattern 4
    func = [this,tempFact]
    {
        std::pair<float,float> direction(0,10);
        tempFact->setDirection(direction);
        Ennemi * e = tempFact->build(TypeEnnemy::StraightDownStop);
        float random(std::rand() % (SIZEX - 2));
        float y(1);
        e->setPosition(random, y);
    };
    h->addLambda(func,2,false);
    for (int i = 0; i < 5; i++)
    {
        h->addLambda(func,0.2,false);
    }

    //Pattern 5
    func = [this, tempFact]
    {
        std::pair<float,float> direction(8,3);
        std::pair<float,float> position(0,0);
        tempFact->setPosition(position);
        tempFact->setDirection(direction);
        tempFact->build(TypeEnnemy::Boss);
    };
    h->addLambda(func,5,false);
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


