#ifndef ENNEMI_H
#define ENNEMI_H
#include "Perso.h"
#include "PoolManager.h"

struct PoolManager;

class Ennemi : public Perso
{
    public:
        Ennemi(float &posX,float &posY, PoolManager * pool);
        virtual ~Ennemi();
        void init(float &posX,float &posY);
        virtual std::pair<float,float> directionTir();
        void update(float &deltaTime, Hero * her);
        virtual typePosable getTypePosable();
        inline int getScore(){return score;}
        inline void setScore(int &value){score = value;}

        inline float getSpeedAnimation(){return speedAnimation;}
        inline void setSpeedAnimation(float &newValue){speedAnimation = newValue;}

        inline float getFrequencyShoot(){return frequencyShoot;}
        inline void setFrequencyShoot(float &newValue){frequencyShoot = newValue;}

        void Mourir();

    private:
        float speedAnimation = 0.001;
        float time = 0;
        float frequencyShoot = 1;
        float timeSinceLastShoot = 0;
        int score = 1;
        PoolManager * pool;
        bool dying = false;
};

#endif // ENNEMI_H
