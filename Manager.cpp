#include "Manager.h"

Manager::Manager()
{
    stop = false;
    id = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);
    bufferSize = { SIZEX, SIZEY };
    bufferCoord = {0,0};
    region = {0,0, SIZEX - 1, SIZEY - 1};
}



void Manager::stopLoop()
{
    stop = true;
}

bool Manager::isStop()
{
    return stop;
}

void Manager::MainLoop(float time)
{
    //[y][x]
    ReadConsoleOutput(id, (CHAR_INFO *)buffer, bufferSize, bufferCoord , &region);
    for (int x = 0; x < SIZEY; x++)
    {
        for (int y = 0 ; y < SIZEY; y++)
        {
            buffer[y][x].Char.AsciiChar = 'I';
            buffer[y][x].Attributes = (x + y) / 2;
        }
    }
    buffer[6][10].Char.AsciiChar = 'H';
    buffer[6][10].Attributes = 0x0E;
    buffer[5][11].Char.AsciiChar = 'i';
    buffer[5][11].Attributes = 0x0B;
    buffer[5][12].Char.AsciiChar = '!';
    buffer[5][12].Attributes = 0x0A;
    WriteConsoleOutput(id, (CHAR_INFO *)buffer, bufferSize, bufferCoord, &region);
}
