#include "Manager.h"
#include <conio.h>

Manager::Manager()
{
    stop = false;
    ix = 11;
    iy = 5;
    memx = ix;
    memy = iy;
    h = Hero(3,7);
    e = Ennemi(12,12);
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
                h.moveBy(0,-1);
                break;
            case 's':
                h.moveBy(0,1);
                break;
            case 'q':
                h.moveBy(-1,0);
                break;
            case 'd':
                h.moveBy(1,0);
                break;
            case ' ':
                stopLoop();
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
    std::pair<int,int> posToDraw =  h.getPos();
    buffer[posToDraw.second][posToDraw.first].Char.AsciiChar = 'H';
    buffer[posToDraw.second][posToDraw.first].Attributes = 0x0B;
    posToDraw =  e.getPos();
    buffer[posToDraw.second][posToDraw.first].Char.AsciiChar = 'e';
    buffer[posToDraw.second][posToDraw.first].Attributes = 0x0E;

    WriteConsoleOutput(id, (CHAR_INFO *)buffer, bufferSize, bufferCoord, &region);
}
