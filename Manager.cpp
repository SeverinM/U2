#include "Manager.h"
#include <conio.h>

Manager::Manager()
{
    stop = false;
    ix = 11;
    iy = 5;
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
                iy--;
                break;
            case 's':
                iy++;
                break;
            case 'q':
                ix--;
                break;
            case 'd':
                ix++;
                break;
            case ' ':
                stop = true;
                break;
            default :
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

    buffer[5][10].Char.AsciiChar = 'H';
    buffer[5][10].Attributes = 0x0E;
    buffer[iy][ix].Char.AsciiChar = 'i';
    buffer[iy][ix].Attributes = 0x0B;
    buffer[5][12].Char.AsciiChar = '!';
    buffer[5][12].Attributes = 0x0A;
    WriteConsoleOutput(id, (CHAR_INFO *)buffer, bufferSize, bufferCoord, &region);
}
