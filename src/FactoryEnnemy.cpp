#include "FactoryEnnemy.h"

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

    switch (enn)
    {
        case StraightDown:
            std::function<void()> shoot;
            shoot = [output, this]
            {
                Projectile * proj = static_cast<Projectile *>(pool->getInPool(typePosable::Proj));
                proj->removeAllAnimation();
                int color(Visuel::getColor(Visuel::Couleur::Rouge,Visuel::Couleur::Transparent));
                string sprt("sprites/ProjectileHero.txt");
                proj->addAnimation(Visuel::createFromFile(sprt, color));
                proj->isEnabled = true;
                float x(getPosition().first);
                float y(getPosition().second);
                proj->setPosition(x, y);
                Positionable * her = pool->getHero()[0];
                float posXDelta(her->getPos().first - proj->getPos().first);
                float posYDelta(her->getPos().second - proj->getPos().second);
                std::pair<float, float> positionDelta{posXDelta,posYDelta};
                Positionable::normalizeDirection(positionDelta);
                positionDelta = {positionDelta.first / 100 , positionDelta.second / 100};
                bool isAlly(false);
                x = output->getPos().first;
                y = output->getPos().second;
                proj->init(x,y,positionDelta,isAlly);
            };

            output->addLambda(shoot,frequencyShoot,true);
            break;
    }

    return output;
}

