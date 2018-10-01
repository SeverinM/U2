#include "NYTimer.h"

NYTimer::NYTimer(){
    QueryPerformanceCounter(&lastUpdateTime);
    LARGE_INTEGER li_freq;
    QueryPerformanceFrequency(&li_freq);
    freq = li_freq.QuadPart;
    freq /= 1000;
};

void NYTimer::start(){
    QueryPerformanceCounter(&lastUpdateTime);
};

float NYTimer::getElapsedSeconds(bool restart)
{
    LARGE_INTEGER timeNow;
    QueryPerformanceCounter(&timeNow);
    LONGLONG elapsedLong = timeNow.QuadPart - lastUpdateTime.QuadPart;
    float elapsedTime = (float)((float)elapsedLong / (float)freq);
    elapsedTime /= 1000;

    if (restart)
    {
        lastUpdateTime = timeNow;
    }
    return elapsedTime;
};
