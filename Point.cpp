#include "Point.h"

using namespace Fry;

Point::Point(float x,float y)
{
    x_ = x;
    y_ = y;
}

Point::~Point()
{

}

Point::Point()
{
    x_ = 0.f;
    y_ = 0.f;
}
