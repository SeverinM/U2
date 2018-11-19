#include "FactoryProjectile.h"

FactoryProjectile::FactoryProjectile(PoolManager * man)
{
    manager = man;
}

Projectile * FactoryProjectile::build(TypeProjectile typeproj, Arguments arguments)
{
    Projectile * proj = static_cast<Projectile *>(manager->getInPool(typePosable::Enn));
    proj->setIsFromPlayer(false);
    proj->removeAllAnimation();
    switch (typeproj)
    {
        case ToTarget:
                //Arg 1 : source x
                //Arg 2 : source y
                //Arg 3 : destination x
                //Arg 4 : destination y
                //Arg 5 : speed
                std::pair<float,float> direction(arguments.arg3 - arguments.arg1 , arguments.arg4 - arguments.arg2);
                Positionable::normalizeDirection(direction);
                direction.first *= arguments.arg5;
                direction.second *= arguments.arg5;
                proj->setPosition(arguments.arg1, arguments.arg2);
                proj->setDirection(direction);
    }
    return proj;
}
