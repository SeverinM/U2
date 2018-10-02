#include "../include/NYTimer.h"

NYTimer::NYTimer()
{
    QueryPerformanceCounter(&lastUpdate);
    LARGE_INTEGER li_freq;
    QueryPerformanceFrequency(&li_freq);
    freq = li_freq.QuadPart / 1000;
};

void NYTimer::start()
{
    QueryPerformanceCounter(&lastUpdate);
};

float NYTimer::getElapsedSeconds(bool restart)
{
    LARGE_INTEGER timeNow;
    QueryPerformanceCounter(&timeNow);
    LONGLONG elapsedLong = timeNow.QuadPart - lastUpdate.QuadPart;

    float elapsed = (float)((float)elapsedLong/(float)freq) / 1000;

    if (restart)
    {
        lastUpdate = timeNow;
    }
    return elapsed;
};

