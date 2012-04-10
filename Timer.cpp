#include "Timer.h"
#include <iostream>

using namespace Fry;

Timer::Timer()
{
    resolution = 1.0f/1000.0f; //0.001 je step
    Init();
}


Timer::~Timer()
{
    std::cout<<"Timer down"<<std::endl;
}

void Timer::Init()
{
    timer_start = SDL_GetTicks();
}

float Timer::GetElapsedTime()
{
    return ((float)(SDL_GetTicks()-timer_start)*resolution);
}

