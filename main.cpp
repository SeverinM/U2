#include <iostream>
#include <windows.h>
#include <stdio.h>
#include "NYTimer.h"
#include "Manager.h"
#include "./include/GameWrapper.h"
#include "./include/BufferManager.h"
#include "Texte.h"

using namespace std;

int main()
{
    BufferManager * bm = new BufferManager();
    NYTimer time;
    time.start();
    Manager man(bm);
    man.init();
    GameWrapper gw(bm);
    while (!gw.isStop())
    {
        gw.PreGameLoop();
    }
    time.start();
    while (!man.isStop())
    {
        if (man.MainLoop(time.getElapsedSeconds(true)))
        {
            gw.switchStop();
            break;
        }
    }
    while (!gw.isStop())
    {
        gw.GameOver();
    }

    return 0;
}
