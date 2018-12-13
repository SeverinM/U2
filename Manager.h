#ifndef MANAGER_H
#define MANAGER_H
#define _WIN32_WINNT 0x0500
#define INPUT_KEY_COUNT 10
#include<windows.h>
#include "include/Hero.h"
#include "include/Ennemi.h"
#include "include/BufferManager.h"
#include "include/PoolManager.h"
#include "FactoryEnnemy.h"


typedef enum InputKey
{
	INPUT_KEY_ESCAPE,
    INPUT_KEY_SPACE,
	INPUT_KEY_UP_ARROW,
	INPUT_KEY_DOWN_ARROW,
	INPUT_KEY_LEFT_ARROW,
	INPUT_KEY_RIGHT_ARROW,
	INPUT_KEY_D,
	INPUT_KEY_Q,
	INPUT_KEY_S,
	INPUT_KEY_Z
} InputKey;


class Manager
{
    public:
        Manager(BufferManager * buff);
        bool MainLoop(float time);
        void stopLoop();
        bool isStop();
        void init();
        inline void setStop(bool newValue)
        {
            stop = newValue;
        }

    private:
        Hero * h;
        bool wasHitThisFrame = false;
        bool stop;
        int timeUpdate;
        float timeSpent;
        float frequencySpawn;
        BufferManager *  bufferManager;
        PoolManager * poolManager;
        void drawAllElementIn(Positionable ** listElement, int sizeA);
        int score = 0;

        FactoryEnnemy * fact = 0;

        map<pair<int,int>,Positionable *> collisionBuffer;//add : max size == 70 / 70

        //Trying thing :

        bool inputKeysBefore[INPUT_KEY_COUNT];
        bool inputKeysNow[INPUT_KEY_COUNT];
        bool pressed;
        float inputAutorisation[2][2];
        float moveTimerRightLeft = 0.05f;
        float moveTimerUpDown = 0.1f;

        bool is_input_key_up(InputKey inputKey);
        bool is_input_key_down(InputKey inputKey);
        bool is_input_key_pressed(InputKey inputKey);
        bool is_input_key_released(InputKey inputKey);


        void is_input_key_supported(InputKey inputKey);
        void update_input_keys();

//end tries

};

#endif // MANAGER_H
