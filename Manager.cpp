#include "Manager.h"
#include <conio.h>

Manager::Manager()
{
    stop = false;
    ix = 5;
    iy = 11;
    memx = ix;
    memy = iy;
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
    int key = 0;
    if (_kbhit())
    {
        key =_getch();
        switch(key){
            case 'z':
                ix--;
                break;
            case 's':
                ix++;
                break;
            case 'q':
                iy--;
                break;
            case 'd':
                iy++;
                break;
            case ' ':
                break;
            default :
                stop = true;
                    break;
        }
    }

    ReadConsoleOutput(id, (CHAR_INFO *)buffer, bufferSize, bufferCoord , &region);
    for (int x = 0; x < SIZEY; x++)
    {
        for (int y = 0 ; y < SIZEY; y++)
        {
            buffer[y][x].Char.AsciiChar = 'I';
            buffer[y][x].Attributes = (x + y) / 2;
        }
    }
    buffer[5][10].Char.AsciiChar = 'H';
    buffer[5][10].Attributes = 0x0E;
    buffer[ix][iy].Char.AsciiChar = 'i';
    buffer[ix][iy].Attributes = 0x0B;
    buffer[5][12].Char.AsciiChar = '!';
    buffer[5][12].Attributes = 0x0A;
    WriteConsoleOutput(id, (CHAR_INFO *)buffer, bufferSize, bufferCoord, &region);
}
