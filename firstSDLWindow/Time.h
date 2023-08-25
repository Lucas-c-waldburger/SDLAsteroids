#pragma once
#include "sdl2.h"


struct Time
{
    Time();

    Uint64 timeStamp;

    void setWait(int msToWait);
    bool waitOver();
};

