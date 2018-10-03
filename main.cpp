#include <iostream>
#include <windows.h>
#include <stdio.h>
#include "NYTimer.h"
#include "Manager.h"

using namespace std;

int main()
{
    NYTimer time;
    time.start();
    Manager man;
    man.init();
    while (!man.isStop())
    {
        man.MainLoop(time.getElapsedSeconds(false));
    }
    cout << time.getElapsedSeconds(false);

    return 0;
}
