#ifndef FACTORYPROJECTILE_H
#define FACTORYPROJECTILE_H
#include "PoolManager.h"

enum TypeProjectile
{
    ToTarget,
    ToDirection,
    ToTargetProgressive,
    CircleProj,
};

struct Arguments
{
    float arg1;
    float arg2;
    float arg3;
    float arg4;
    float arg5;
};

class FactoryProjectile
{
    public:
        FactoryProjectile(PoolManager * manager);
        Projectile * build(TypeProjectile typeproj, std::pair<float,float> origin, Arguments arguments);
        void setDefaultProjectileSprite(Projectile * proj);

    private:
        PoolManager * manager;
};

#endif // FACTORYPROJECTILE_H
