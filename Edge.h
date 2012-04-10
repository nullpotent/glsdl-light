#pragma once
#include "Point.h"
#include <iostream>

namespace Fry
{

class Edge
{
public:
    Edge();
    Edge(float x,float y,float x1,float y1);
    Edge(const Point& a,const Point& b);
    ~Edge();

    Point GetFirstPoint();
    Point GetSecondPoint();
    //klasa je jednostavna struktura pa se ne preporucuju get/set/+eri
    float x_;
    float y_;
    float x1_;
    float y1_;

protected:
private:
};

};
