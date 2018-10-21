#include <iostream>
#include <windows.h>
#include <stdio.h>
#include "NYTimer.h"
#include "Manager.h"
#include "./include/GameWrapper.h"
#include "./include/BufferManager.h"
#include "./include/ProgrammableProj.h"

using namespace std;

int main()
{
    ProgrammableProj::initSequences();
    char * str;
    str = "Test";

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
