#include <iostream>
#include <windows.h>
#include <stdio.h>
#include "NYTimer.h"
#include "Manager.h"
#include "./include/GameWrapper.h"
#include "./include/BufferManager.h"

using namespace std;

int main()
{
    BufferManager * bm = new BufferManager();
    NYTimer time;
    time.start();
    Manager man(bm);
    man.init();
    GameWrapper gw(bm);
    gw.switchStop();
    while (!gw.isStop())
    {
        gw.PreGameLoop();
    }
    while (!man.isStop())
    {
        man.MainLoop(time.getElapsedSeconds(true));
    }

    return 0;
}
