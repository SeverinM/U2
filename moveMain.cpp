#include <iostream>
#include <stdio.h>
//#include "Manager.h"
//#include "NYTimer.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#define SCREEN_WIDTH	80
#define SCREEN_HEIGHT	25
#include <conio.h>

using namespace std;

int moveMain()
{
    bool finish = false;
    int x = 11;
    int y = 5;
    int memX = x;
    int memY = y;
    while(!finish){

        /*NYTimer time;
        time.start();*/

        HANDLE hOutput = (HANDLE)GetStdHandle( STD_OUTPUT_HANDLE );

        COORD dwBufferSize = { SCREEN_WIDTH,SCREEN_HEIGHT };
        COORD dwBufferCoord = { 0, 0 };
        SMALL_RECT rcRegion = { 0, 0, SCREEN_WIDTH-1, SCREEN_HEIGHT-1 };

        CHAR_INFO buffer[SCREEN_HEIGHT][SCREEN_WIDTH];

        ReadConsoleOutput( hOutput, (CHAR_INFO *)buffer, dwBufferSize,
        dwBufferCoord, &rcRegion );

        buffer[memY][memX].Char.AsciiChar = ' ';
        buffer[5][10].Char.AsciiChar = 'H';
        buffer[5][10].Attributes = 0x0E;
        buffer[y][x].Char.AsciiChar = 'i';
        buffer[y][x].Attributes = 0x0B;
        buffer[5][12].Char.AsciiChar = '!';
        buffer[5][12].Attributes = 0x0A;

        memX = x;
        memY = y;

        WriteConsoleOutput( hOutput, (CHAR_INFO *)buffer, dwBufferSize,
        dwBufferCoord, &rcRegion );
        //cout << time.getElapsedSeconds(false);

        //key handler
        int key = 0;
        if (_kbhit())
        {
            key =_getch();

            switch(key){
            case 'z':
                y--;
                break;
            case 's':
                y++;
                break;
            case 'q':
                x--;
                break;
            case 'd':
                x++;
                break;
            case ' ':
                finish = true;
                break;
            default :
                    break;
            }
        }
    }

    return 0;
}
