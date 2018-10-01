#ifndef NYTIMER_H_INCLUDED
#define NYTIMER_H_INCLUDED

class NYTimer
{
public :
    NYTimer();
    void start();
    float getElapsedSeconds(bool restart);
private :
    LARGE_INTEGER lastUpdateTime;
    LONGLONG freq;
};


#endif // NYTIMER_H_INCLUDED
