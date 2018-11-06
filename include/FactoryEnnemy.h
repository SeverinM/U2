#ifndef FACTORYENNEMY_H
#define FACTORYENNEMY_H
#include <queue>
#include "Positionable.h"
#include <memory>
#include "PoolManager.h"
#include "Ennemi.h"

class FactoryEnnemy
{
    public:
        FactoryEnnemy(PoolManager * newPool , queue<Lambda> &allSeq, vector<shared_ptr<Visuel>> &anim);
        Ennemi * build();

        inline std::pair<float, float> getDirection(){return direction;}
        inline void setDirection(std::pair<float, float> &newValue){direction = newValue;}

        inline std::pair<float , float> getPosition(){return std::pair<float, float>(posX, posY);}
        inline void setPosition(std::pair<float,float> &newValue)
        {
            posX = newValue.first;
            posY = newValue.second;
        }

        inline vector<shared_ptr<Visuel>> getAnimations(){return animations;}
        inline void setAnimations(vector<shared_ptr<Visuel>> &newValue){animations = newValue;}

        inline queue<Lambda> getAllSequences(){return allSequences;}
        inline void setAllSequences(queue<Lambda> &newValue){allSequences = newValue;}

        inline float getSpeedAnimation(){return speedAnimation;}
        inline void setSpeedAnimation(float &newValue){speedAnimation = newValue;}

        inline float getFrequenceyShoot(){return frequencyShoot;}
        inline void setFrequencyShoot(float &newValue){frequencyShoot = newValue;}

        inline int getScoreWorth(){return scoreWorth;}
        inline void setScoreWorth(float &newValue){scoreWorth = newValue;}

        inline PoolManager * getPoolManager(){return pool;}
        inline void setPoolManager(PoolManager * &newValue){pool = newValue;}

    protected:
        std::pair<float, float> direction;
        float posX = 0;
        float posY = 0;
        vector<shared_ptr<Visuel>> animations;
        queue<Lambda> allSequences;
        float speedAnimation = 0;
        float frequencyShoot = 0;
        int scoreWorth = 0;
        PoolManager * pool;
};

#endif // FACTORYENNEMY_H
