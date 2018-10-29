#include "../include/Hero.h"
#include "../include/Positionable.h"

Hero::Hero(float &posX,float &posY) : Perso(posX, posY)
{
    setDefaultValue();
}

void Hero::init(float &posX,float &posY)
{
    Positionable::init(posX, posY);
    setDefaultValue();
}
void Hero::setDefaultValue()
{
    timerShoot = 0;
    delayShoot = 0.2f;
    pv = 10;

    shotPower = SHOT_POWER_MAX;
    powerByShot = 200;
    recoverPerUpdate = 1;
}

void Hero::update(float &time)
{
    isOnRecovery = (recoveryTimeEnd > totalTime);
    indexAnimation = (isOnRecovery ? 1 : 0);
    totalTime += time;
    if(timerShoot > 0){
        timerShoot -= time;
    }
    if(shotPower < SHOT_POWER_MAX)
        shotPower += recoverPerUpdate;
    //cout << "recharge ! " << shotPower << endl;
    shotPower = shotPower > SHOT_POWER_MAX ? SHOT_POWER_MAX : shotPower;
    //cout << "apres    ! " << shotPower << endl;
}

void Hero::tryToShoot(){
    if(timerShoot <= 0 && shotPower > powerByShot){
        isShot = true;
        timerShoot = delayShoot;
        shotPower -= powerByShot;
        //cout << shotPower << " / "  << endl;
    }
}

std::pair<float ,float> Hero::directionTir(){
    return dir;
}

void Hero::setPosition(float &newX,float &newY)
{
    if (newX > 0 && newX < (SIZEX - 1))
    {
        posX = newX;
    }

    if (newY > 0 && newY < (SIZEY - 1))
    {
        posY = newY;
    }
}

bool Hero::takeDamage(int &damage)
{
    bool output = Perso::takeDamage(damage);
    recoveryTimeEnd = totalTime + recoveryTime;
    return output;
}

typePosable Hero::getTypePosable(){
    return Her;
}


