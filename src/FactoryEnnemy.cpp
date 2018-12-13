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
                                                    {her->getPos().first + 2,her->getPos().second,10});


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

            /*pattern = [this, output]
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
            output->addLambda(pattern,2,false);*/
            /*pattern = [this, output]
            {
                for (float angle = 0 ; angle < M_PI * 2; angle += M_PI / 8)
                {
                    std::function<void()> forwardProj;
                    Projectile * proj;
                    for (int i = 3; i < 6 ; i++)
                    {
                        std::pair<float,float> normalAngle;
                        std::pair<float,float> delayedAngle;

                        normalAngle.first = cos(angle);
                        normalAngle.second = sin(angle);

                        delayedAngle.first = cos(angle + M_PI / 3);
                        delayedAngle.second = sin(angle + M_PI / 3);

                        proj = factProj->build(TypeProjectile::ToDirection,
                                           {output->getPos().first + 2 + (normalAngle.first * i) + (i - 3) * delayedAngle.first,
                                            output->getPos().second + (normalAngle.second * i) + (i - 3) * delayedAngle.second
                                           },
                                           {
                                               1,1,0
                                           }
                                           );

                        factProj->setDefaultProjectileSprite(proj);
                        forwardProj = [this,proj,normalAngle, &i]
                        {
                            std::pair<float,float> direction;
                            direction.first = normalAngle.first;
                            direction.second = normalAngle.second;
                            Positionable::normalizeDirection(direction);
                            direction.first *= 10;
                            direction.second *= 10;
                            proj->setDirection(direction);
                        };
                        proj->addLambda(forwardProj, 1,false);
                    }
                }
            };*/

            //Mouvement 1
            std::vector<std::function<void()>> attack1;
            std::pair<float, float> * directionTransition = new std::pair<float, float>(20,4);
            std::function<void()> mvmt1;
            mvmt1 = [this, output, directionTransition]
            {
                output->setDirection(*directionTransition);
                directionTransition->first *= -1;
                directionTransition->second *= -1;
            };

            //Attaque 1
            for (int i = 0; i < 3; i++)
            {
                attack1.push_back([this, output, i]
                {
                    output->stop();
                    float offset(M_PI / 15);
                    Projectile * proj;
                    for (float angle = 0 + (i * offset); angle < 2 * M_PI + (i * offset); angle += M_PI / 8)
                    {
                        for (int j = 0 ; j < 2 ; j++)
                        {
                            proj = factProj->build(TypeProjectile::ToDirection,
                                        {
                                           output->getPos().first + (j * cos(angle)), output->getPos().second + (j * sin(angle))
                                        },
                                        {
                                           cos(angle), sin(angle), 10
                                        });

                            factProj->setDefaultProjectileSprite(proj);
                        }
                    }
                });
            }

            for (int j = 0; j < 10; j++)
            {
                output->addLambda(mvmt1,2,false);
                for (auto &fc : attack1)
                {
                    output->addLambda(fc,1,false);
                }
            }

            //Mouvement 2
            /*std::function<void()> mvmt2;
            std::pair<float, float> * directionTransition2 = new std::pair<float, float>(15,0);
            mvmt2 = [this, output, directionTransition2, mvmt2]
            {
                output->setDirection(*directionTransition2);
                directionTransition2->first *= -1;
                output->addLambda(mvmt2,1,false);
            };
            output->addLambda(mvmt2,1,false);


            //Attaque 2
            std::function<void()> attack2;
            int offset;
            for (int i = 0 ; i < 5 ; i++)
            {
                attack2 = [this, output, &offset, &i, attack2]
                {
                    output->stop();
                    for (float angle = 0 ; angle < M_PI * 2; angle += M_PI / 6)
                    {
                        offset = std::rand() % 4;
                        Projectile * proj = factProj->build(TypeProjectile::ToDirection,
                                                            {
                                                                output->getPos().first,
                                                                output->getPos().second
                                                            },
                                                            {
                                                                cos(angle + (offset * (M_PI / 16))),
                                                                sin(angle + (offset * (M_PI / 16))),
                                                                ((std::rand() % 8) * 3) + 3
                                                            });
                        factProj->setDefaultProjectileSprite(proj);
                    }
                    output->addLambda(attack2,i == 0 ? 2 : 0.25, false);
                };
                output->addLambda(attack2,i == 0 ? 2 : 0.25, false);
            }*/

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

