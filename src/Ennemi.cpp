#include "../include/Ennemi.h"

Ennemi::Ennemi(float &posX,float &posY, PoolManager * refPool) : Perso(posX, posY)
{
    pool = refPool;
    pv = 1;
    dir = std::pair<double, double>(0.01,0.01);
}

Ennemi::~Ennemi()
{
    //dtor
}

void Ennemi::init(float &posX,float &posY){
    Positionable::init(posX, posY);
    dying = false;
    indexAnimation = 0;
    physicEnabled = true;
    pv = 1;
}

void Ennemi::Mourir()
{
    dir.first /= 5;
    dir.second /= 5;
    dying = true;
    physicEnabled = false;
    int grey(Visuel::getColor(Visuel::Couleur::Gris, Visuel::Couleur::Transparent));
    setColor(grey);
}

std::pair<float,float> Ennemi::directionTir(){
    return dir;
}

void Ennemi::update(float &deltaTime, Hero * her)
{
    if (dying && !increaseSprite(speedAnimation))
    {
        isEnabled = false;
    }

    if (isEnabled)
    {
        Perso::update(time);
        time += deltaTime;
        float x(dir.first);
        float y(dir.second);
        moveBy(x,y);
        if (time - timeSinceLastShoot > frequencyShoot && !dying)
        {
            std::pair<float ,float> dir;
            dir.first = her->getPos().first - getPos().first;
            dir.second = her->getPos().second - getPos().second;
            Positionable::normalizeDirection(dir);
            timeSinceLastShoot = time;
            Projectile * p = (Projectile *)pool->getInPool(typePosable::Proj);
            p->isEnabled = true;

            //A supprimer (sert juste pour le test)
            /*std::function<void()> lamb = [p, her]{
                std::pair<float,float> direction;
                direction.first = her->getPos().first - p->getPos().first;
                direction.second = her->getPos().second - p->getPos().second;
                p->normalizeDirection(direction);
                direction.first /= 100;
                direction.second /= 100;
                p->setDirection(direction);
            };*/
            x = posX + 2;
            bool isPlayer(false);
            std::pair<float, float> dirTemp(dir.first / 100 ,dir.second / 100);
            p->init(x,posY,dirTemp,isPlayer);
            //p->addLambda(lamb , 1 , true);
            p->removeAllAnimation();
            string defaultSprite("sprites/ProjectileHero.txt");
            p->addAnimation(Visuel::createFromFile(defaultSprite,
                                                   Visuel::getColor(Visuel::Couleur::Rouge,
                                                                    Visuel::Couleur::Transparent)));
        }
    }
}

typePosable Ennemi::getTypePosable(){
    return Enn;
}

