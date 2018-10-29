#ifndef NYTIMER_H
#define NYTIMER_H
#include <windows.h>

class NYTimer
{
    public:
        NYTimer();
        void start();
        void restart();
        float getElapsedSeconds(bool restart);

    private:
        LARGE_INTEGER lastUpdate;
        LONGLONG freq;
};

#endif // NYTIMER_H
