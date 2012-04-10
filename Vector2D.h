#pragma once
#include <math.h>
namespace Fry
{

class Vector2D
{
    public:
        Vector2D();
        Vector2D(float x,float y);
        virtual ~Vector2D();
        friend Vector2D operator * (float scalar, const Vector2D& vec);
        Vector2D operator - (const Vector2D& vec) const;
        Vector2D operator + (const Vector2D& vec) const;
        Vector2D operator * (float scalar) const;
        float GetMagnitude();
        void CalcMagnitude();
        void Assign(float x,float y);
        void Normalize();
        void Normal();
        float DotProduct(const Vector2D& vec);
        float x_;
        float y_;
        float m_;
    protected:
    private:
};

};
