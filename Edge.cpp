#include "Edge.h"

using namespace Fry;

Edge::Edge(float x,float y,float x1,float y1)
{
    x_ = x;
    y_ = y;
    x1_ = x1;
    y1_ = y1;
}

Edge::Edge()
{
    x_  = 0.f;
    y_  = 0.f;
    x1_ = 0.f;
    y1_ = 0.f;
}

Edge::Edge(const Point& a,const Point& b)
{
    x_ = a.x_;
    y_ = a.y_;
    x1_ = b.x_;
    y1_ = b.y_;
}

Edge::~Edge()
{

}

Point Edge::GetFirstPoint()
{
    return Point(x_,y_);
}

Point Edge::GetSecondPoint()
{
    return Point(x1_,y1_);
}
