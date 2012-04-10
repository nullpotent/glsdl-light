#pragma once

#define PI 3.14159265

const float DEG2RAD = 3.14159/180;

namespace Fry
{

inline int nextPow(int a)
{
    int rval=1;
    while(rval<a)
    {
        rval<<=1;
    }
    return rval;
}

};
