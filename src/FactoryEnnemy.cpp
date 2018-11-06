#include "FactoryEnnemy.h"

FactoryEnnemy::FactoryEnnemy(PoolManager * newPool , queue<Lambda> &allSeq, vector<shared_ptr<Visuel>> &anim)
{
    pool = newPool;
    allSequences = allSeq;
    animations = anim;
}

Ennemi * FactoryEnnemy::build()
{
    Ennemi * output;

    output = static_cast<Ennemi *>(pool->getInPool(typePosable::Enn));
    output->init(direction.first, direction.second);
    output->setDirection(direction);
    output->removeAllAnimation();
    for (auto &anim : animations)
    {
        output->addAnimation(anim);
    }
}

