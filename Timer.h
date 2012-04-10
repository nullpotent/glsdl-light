#pragma once
#include <inttypes.h>
#include <SDL.h>
namespace Fry
{

class Timer
{
public:
    Timer();
    ~Timer();
    void Init();
    float GetElapsedTime();             //vraca vreme koje je proslo od poslednjeg timer query-a
private:
    float resolution;                   //step tajmera
    unsigned long timer_start;          //multimedia counter start time
};

};
