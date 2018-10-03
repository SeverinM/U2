#include "BufferManager.h"

BufferManager::BufferManager()
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, SIZEX * 18, SIZEY * 18, true);
    id = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);
    bufferSize = { SIZEX, SIZEY };
    bufferCoord = {0,0};
    region = {0,0, SIZEX - 1, SIZEY - 1};
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(id, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(id, &cursorInfo);
    defaultCar.Char.AsciiChar = 'O';
    defaultCar.Attributes = Visuel::getColor(Visuel::Couleur::Transparent,Visuel::Couleur::Transparent);
}

void BufferManager::placeInBuffer(CHAR_INFO * car, int &x, int &y)
{
    if (x >= 0 && x < SIZEX && y >= 0 && y < SIZEY)
    {
        buffer[y][x]= *car;
    }
}

void BufferManager::draw()
{
    WriteConsoleOutput(id,(CHAR_INFO *)buffer,bufferSize,bufferCoord,&region);
}

void BufferManager::resetScreen()
{
    for (int x = 0; x < SIZEX; x++)
    {
        for (int y= 0; y < SIZEY; y++)
        {
            buffer[y][x] = defaultCar;
        }
    }
}
