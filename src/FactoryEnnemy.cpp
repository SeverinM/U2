#include "FactoryEnnemy.h"
#include <math.h>

FactoryEnnemy::FactoryEnnemy(PoolManager * newPool)
{
    pool = newPool;
    factProj = new FactoryProjectile(newPool);
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
            pattern = [output, this, direction2]
            {
                std::pair<float,float> dir(getDirection());
                output->setDirection(dir);
                Positionable * her = pool->getHero()[0];
                Projectile * proj = factProj->build(TypeProjectile::ToTarget,
                                                    {output->getPos().first,output->getPos().second},
                                                    {her->getPos().first,her->getPos().second,10});


                factProj->setDefaultProjectileSprite(proj);
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
                        Positionable * her = pool->getHero()[0];
                        std::pair<float,float> deltaDirection
                        {
                            her->getPos().first - output->getPos().first,
                            her->getPos().second - output->getPos().second
                        };

                        Projectile * proj = factProj->build(TypeProjectile::ToDirection,
                                                            {output->getPos().first, output->getPos().second},
                                                            {deltaDirection.first, deltaDirection.second, 10}
                                                            );

                        factProj->setDefaultProjectileSprite(proj);
                    }
                };
                output->addLambda(pattern,0.2,false);
            }
            break;

        case StraightDownStop:
            pattern = [this , output, direction2]
            {
                std::pair<float,float> temp(output->getDirection().first / 1.3, output->getDirection().second / 1.3);
                output->setDirection(temp);
                if (output->getDirection().second < 0.1 && !output->getAlreadyShot())
                {
                    bool alreadyShot(true);
                    output->setAlreadyShot(alreadyShot);
                    for (float angle = 0; angle < M_PI ; angle += M_PI / 8)
                    {
                        std::pair<float,float> directionProj(cos(angle) / 100, sin(angle) / 100);

                        Projectile * proj = factProj->build(TypeProjectile::ToDirection,
                                                            {output->getPos().first,output->getPos().second},
                                                            {directionProj.first, directionProj.second, 10});

                        factProj->setDefaultProjectileSprite(proj);
                    }
                }
            };
            output->addLambda(pattern,0.2,true);
            break;

        case Boss:
            pattern = [this, output, direction2]
            {
                std::pair<float,float> speed(0,0);
                output->setDirection(speed);
            };
            output->addLambda(pattern , 2, false);
            pattern = [this, output]
            {
                Projectile * proj;
                for (float angle = 0; angle < M_PI; angle += M_PI / 8)
                {
                    for (int i = 0; i < 3; i++)
                    {
                        proj = factProj->build(TypeProjectile::ToDirection,
                                               {output->getPos().first, output->getPos().second},
                                               {cos(angle),sin(angle),10 + (i * 1.1)}
                                               );

                        factProj->setDefaultProjectileSprite(proj);
                    }
                }
            };
            output->addLambda(pattern,2,false);
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

