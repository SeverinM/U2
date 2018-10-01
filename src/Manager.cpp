#include "Manager.h"

Manager::Manager()
{
    stop = false;
    id = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);
    bufferSize = { 700, 700 };
    bufferCoord = {0,0};
    region = {0,0, 699, 699};
}

Manager::~Manager()
{
    //dtor
}

void Manager::MainLoop()
{
    while (!stop)
    {
        ReadConsoleOutput(id, (CHAR_INFO *)buffer, bufferSize, bufferCoord , &region);
        WriteConsoleOutput(id, (CHAR_INFO *)buffer, bufferSize, bufferCoord, &region);
    }
}
