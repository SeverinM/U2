#ifndef ENNEMI_H
#define ENNEMI_H
#include "Perso.h"
#include "PoolManager.h"

struct PoolManager;

class Ennemi : public Perso
{
    public:
        Ennemi();
        Ennemi(int posX,int posY, PoolManager * pool);
        virtual ~Ennemi();
        void init(int posX,int posY);
        virtual std::pair<double,double> directionTir();
        void update(float deltaTime, Hero * her);
        void setPosition(int newX,int newY);
        virtual typePosable getTypePosable();
        inline int getScore(){return score;}
        inline void setScore(int &value){score = value;}
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
