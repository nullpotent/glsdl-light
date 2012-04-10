#pragma once
#include "Graphics.h"
#include <math.h>
#include "PolyStruct.h"
#include "Vector2D.h"
#include "Math.h"

namespace Fry
{

class Light
{
public:

    Light();
    Light(int r,int g,int b, int intensity, float posX, float posY, float range);
    virtual ~Light();

    void SetPosX(float posX);
    void SetPosY(float posY);
    float GetPosX();
    float GetPosY();
    void Render();
    void ProjectShadow(PolyStruct& poly);
    Vector2D ProjectVector(const Vector2D point);
    bool Intersects(PolyStruct& poly);

protected:
private:
    float range_;
    int r_;
    int g_;
    int b_;
    float posX_,posY_;
    float angle_;
    int intensity_;
};

};


