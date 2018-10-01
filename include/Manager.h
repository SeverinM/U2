#ifndef MANAGER_H
#define MANAGER_H
#include <windows.h>

class Manager
{
    public:
        Manager();
        virtual ~Manager();
        void MainLoop();

    private:
        CHAR_INFO buffer[700][700];
        bool stop;
        COORD bufferSize;
        COORD bufferCoord;
        HANDLE id;
        SMALL_RECT region;
};

#endif // MANAGER_H
