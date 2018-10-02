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
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(id, &cursorInfo);
    cursorInfo.bVisible = false; // set the cursor visibility
    SetConsoleCursorInfo(id, &cursorInfo);
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
            buffer[y][x].Char.AsciiChar = 'O';
            buffer[y][x].Attributes = x;
        }
    }
    buffer[ix][iy].Char.AsciiChar = 'i';
    buffer[ix][iy].Attributes = 0x0B;
    WriteConsoleOutput(id, (CHAR_INFO *)buffer, bufferSize, bufferCoord, &region);
}
