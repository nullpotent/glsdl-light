#pragma once
#include <list>
#include "Edge.h"
#include "Graphics.h"

namespace Fry
{

class PolyStruct
{
public:

    PolyStruct();
    PolyStruct(float r,float g, float b);
    virtual ~PolyStruct();

    void AddPoint(float x,float y);
    void ConstructEdges();
    void Render();
    void Print();

    std::list<Point> list_;
    std::list<Edge> edges_;

    float r_;
    float g_;
    float b_;
    float intensity_;
    int size_;

};

};
