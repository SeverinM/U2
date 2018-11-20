#include "FactoryProjectile.h"

FactoryProjectile::FactoryProjectile(PoolManager * man)
{
    manager = man;
}

void FactoryProjectile::setDefaultProjectileSprite(Projectile * proj)
{
    string sprt("sprites/ProjectileHero.txt");
    proj->removeAllAnimation();
    int color(Visuel::getColor(Visuel::Couleur::Rouge,Visuel::Couleur::Transparent));
    proj->addAnimation(Visuel::createFromFile(sprt,color));
    proj->isEnabled = true;
}

Projectile * FactoryProjectile::build(TypeProjectile typeproj, std::pair<float,float> origin, Arguments arguments)
{
    Projectile * proj = static_cast<Projectile *>(manager->getInPool(typePosable::Enn));
    proj->setIsFromPlayer(false);
    proj->removeAllAnimation();
    std::pair<float,float> direction;
    switch (typeproj)
    {
        case ToTarget:
                //Arg 1 : destination x
                //Arg 2 : destination y
                //Arg 3 : speed
                direction = {arguments.arg1 - origin.first ,arguments.arg2 - origin.second};
                Positionable::normalizeDirection(direction);
                direction.first *= arguments.arg3;
                direction.second *= arguments.arg3;
                proj->setPosition(origin.first,origin.second);
                proj->setDirection(direction);
                break;

        case ToDirection:
                direction = {arguments.arg1, arguments.arg2};
                Positionable::normalizeDirection(direction);
                direction.first *= arguments.arg3;
                direction.second *= arguments.arg3;
                proj->setPosition(origin.first,origin.second);
                proj->setDirection(direction);
                break;
    }
    return proj;
}
