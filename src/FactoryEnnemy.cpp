#include "FactoryEnnemy.h"
#include <math.h>

FactoryEnnemy::FactoryEnnemy(PoolManager * newPool)
{
    pool = newPool;
}

Ennemi * FactoryEnnemy::build(TypeEnnemy enn)
{
    Ennemi * output;

    output = static_cast<Ennemi *>(pool->getInPool(typePosable::Enn));
    output->init(posX, posY);
    output->setDirection(direction);
    output->removeAllAnimation();
    output->cleanQueue();
    output->setSpeedAnimation(speedAnimation);
    output->setFrequencyShoot(frequencyShoot);
    output->setScore(scoreWorth);
    output->isEnabled = true;
    std::function<void()> pattern;
    std::pair<float,float> direction2(output->getDirection());

    switch (enn)
    {
        case StraightDown:
            pattern = [output, this, &direction2]
            {
                std::pair<float,float> dir(getDirection());
                output->setDirection(dir);
                Projectile * proj = static_cast<Projectile *>(pool->getInPool(typePosable::Proj));
                Positionable * her = pool->getHero()[0];
                std::pair<float,float> direction
                {
                    her->getPos().first - output->getPos().first,
                    her->getPos().second - output->getPos().second
                };
                Positionable::normalizeDirection(direction2);
                direction.first /= 1000;
                direction.second /= 1000;
                float x(output->getPos().first);
                float y(output->getPos().second);
                bool isAlly(false);
                proj->init(x,y,direction,isAlly);
                proj->removeAllAnimation();
                int color(Visuel::getColor(Visuel::Couleur::Rouge,Visuel::Couleur::Transparent));
                string sprt("sprites/ProjectileHero.txt");
                proj->addAnimation(Visuel::createFromFile(sprt, color));
                proj->isEnabled = true;
            };

            output->addLambda(pattern,frequencyShoot,true);
            break;

        case Circle:
            for (double angle = 0; angle <= M_PI; angle += M_PI / 8)
            {
                pattern = [this, output , angle, direction2]
                {
                    float y(cos(angle) * direction2.second);
                    float x(direction2.first);
                    std::pair<float,float> dir(x,y);
                    output->setDirection(dir);
                    if (angle == M_PI / 2)
                    {
                        Projectile * proj = static_cast<Projectile *>(pool->getInPool(typePosable::Proj));
                        Positionable * her = pool->getHero()[0];
                        std::pair<float,float> deltaDirection
                        {
                            her->getPos().first - output->getPos().first,
                            her->getPos().second - output->getPos().second
                        };
                        Positionable::normalizeDirection(deltaDirection);
                        deltaDirection.first /= 100;
                        deltaDirection.second /= 100;
                        float x(output->getPos().first);
                        float y(output->getPos().second);
                        bool isAlly(false);
                        proj->init(x,y,deltaDirection,isAlly);
                        proj->removeAllAnimation();
                        int color(Visuel::getColor(Visuel::Couleur::Rouge,Visuel::Couleur::Transparent));
                        string sprt("sprites/ProjectileHero.txt");
                        proj->addAnimation(Visuel::createFromFile(sprt, color));
                        proj->isEnabled = true;
                    }
                };
                output->addLambda(pattern,0.2,false);
            }
            break;

        case StraightDownStop:
            std::pair<float,float> dir = direction;
            pattern = [this , output, dir]
            {
                std::pair<float,float> temp(output->getDirection().first / 1.3, output->getDirection().second / 1.3);
                output->setDirection(temp);
                if (output->getDirection().second < 0.1 && !output->getAlreadyShot())
                {
                    bool alreadyShot(true);
                    output->setAlreadyShot(alreadyShot);
                    for (float angle = 0; angle < M_PI ; angle += M_PI / 8)
                    {
                        Projectile * proj = static_cast<Projectile *>(pool->getInPool(typePosable::Proj));
                        std::pair<float,float> directionProj(cos(angle) / 100, sin(angle) / 100);
                        float x(output->getPos().first);
                        float y(output->getPos().second);
                        bool isAlly(false);
                        string sprt("sprites/ProjectileHero.txt");
                        proj->init(x,y,directionProj,isAlly);
                        proj->removeAllAnimation();
                        int color(Visuel::getColor(Visuel::Couleur::Rouge,Visuel::Couleur::Transparent));
                        proj->addAnimation(Visuel::createFromFile(sprt,color));
                        proj->isEnabled = true;
                    }
                }
            };
            output->addLambda(pattern,0.2,true);
            break;
    }

    string spaceship("sprites/Spaceship.txt");
    string destroy1("sprites/Destroy1.txt");
    string destroy2("sprites/Destroy2.txt");

    output->addAnimation(Visuel::createFromFile(spaceship,Visuel::getColor(Visuel::Couleur::Rouge, Visuel::Couleur::Transparent)));
    output->addAnimation(Visuel::createFromFile(destroy1,Visuel::getColor(Visuel::Couleur::Rouge, Visuel::Couleur::Transparent)));
    output->addAnimation(Visuel::createFromFile(destroy2,Visuel::getColor(Visuel::Couleur::Rouge, Visuel::Couleur::Transparent)));

    return output;
}

