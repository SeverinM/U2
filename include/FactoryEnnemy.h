#ifndef FACTORYENNEMY_H
#define FACTORYENNEMY_H
#include <queue>
#include "Positionable.h"
#include <memory>
#include "PoolManager.h"
#include "Ennemi.h"
#include "FactoryProjectile.h"

enum TypeEnnemy
{
    StraightDown,
    Circle,
    StraightDownStop,
};

class FactoryEnnemy
{
    public:
        FactoryEnnemy(PoolManager * newPool);
        Ennemi * build(TypeEnnemy enn);

        inline std::pair<float, float> getDirection(){return direction;}
        inline void setDirection(std::pair<float, float> &newValue){direction = newValue;}

        inline std::pair<float , float> getPosition(){return std::pair<float, float>(posX, posY);}
        inline void setPosition(std::pair<float,float> &newValue)
        {
            posX = newValue.first;
            posY = newValue.second;
        }

        inline float getSpeedAnimation(){return speedAnimation;}
        inline void setSpeedAnimation(float newValue){speedAnimation = newValue;}

        inline float getFrequencyShoot(){return frequencyShoot;}
        inline void setFrequencyShoot(float newValue){frequencyShoot = newValue;}

        inline int getScoreWorth(){return scoreWorth;}
        inline void setScoreWorth(float newValue){scoreWorth = newValue;}

        inline PoolManager * getPoolManager(){return pool;}
        inline void setPoolManager(PoolManager * newValue){pool = newValue;}

    protected:
        std::pair<float, float> direction;
        float posX = 0;
        float posY = 0;
        float speedAnimation = 0;
        float frequencyShoot = 0;
        int scoreWorth = 0;
        PoolManager * pool;
        FactoryProjectile * factProj;
};

#endif // FACTORYENNEMY_H
