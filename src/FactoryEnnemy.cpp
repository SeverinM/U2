#include "FactoryEnnemy.h"
#include <math.h>

FactoryEnnemy::FactoryEnnemy(PoolManager * newPool , vector<shared_ptr<Visuel>> &anim)
{
    pool = newPool;
    animations = anim;
}

Ennemi * FactoryEnnemy::build(TypeEnnemy enn)
{
    Ennemi * output;

    output = static_cast<Ennemi *>(pool->getInPool(typePosable::Enn));
    output->init(posX, posY);
    output->setDirection(direction);
    output->removeAllAnimation();
    for (auto &anim : animations)
    {
        output->addAnimation(anim);
    }
    output->cleanQueue();
    output->setSpeedAnimation(speedAnimation);
    output->setFrequencyShoot(frequencyShoot);
    output->setScore(scoreWorth);
    output->isEnabled = true;
    std::function<void()> pattern;

    switch (enn)
    {
        case StraightDown:
            pattern = [output, this]
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
                Positionable::normalizeDirection(direction);
                direction.first /= 100;
                direction.second /= 100;
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
            std::pair<float,float> direction(output->getDirection());
            for (double angle = 0; angle <= M_PI; angle += M_PI / 20)
            {
                pattern = [this, output , angle, direction]
                {
                    float y(cos(angle) * direction.second);
                    float x(direction.first);
                    std::pair<float,float> dir(x,y);
                    output->setDirection(dir);
                    if (angle == M_PI / 2)
                    {
                        Projectile * proj = static_cast<Projectile *>(pool->getInPool(typePosable::Proj));
                        Positionable * her = pool->getHero()[0];
                        std::pair<float,float> direction
                        {
                            her->getPos().first - output->getPos().first,
                            her->getPos().second - output->getPos().second
                        };
                        Positionable::normalizeDirection(direction);
                        direction.first /= 100;
                        direction.second /= 100;
                        float x(output->getPos().first);
                        float y(output->getPos().second);
                        bool isAlly(false);
                        proj->init(x,y,direction,isAlly);
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
    }

    return output;
}

