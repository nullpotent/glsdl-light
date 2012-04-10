#include "Vector2D.h"

using namespace Fry;

Vector2D::Vector2D()
{
    //ctor
}

Vector2D::~Vector2D()
{
    //dtor
}

Vector2D::Vector2D(float x,float y)
{
    Assign(x,y);
    CalcMagnitude();
}

void Vector2D::Assign(float x,float y)
{
    x_ = x;
    y_ = y;
}

void Vector2D::CalcMagnitude()
{
    m_ = sqrt(x_*x_+y_*y_);
}

float Vector2D::GetMagnitude()
{
    return m_;
}

Vector2D Vector2D::operator * (float scalar) const
{
    return Vector2D(x_*scalar,y_*scalar);
}

Vector2D operator*(float scalar, const Vector2D& vec)
{
    return Vector2D(vec.x_*scalar,vec.y_*scalar);
}

Vector2D Vector2D::operator + (const Vector2D& vec) const
{
    return Vector2D(x_+vec.x_,y_+vec.y_);
}

Vector2D Vector2D::operator - (const Vector2D& vec) const
{
    return Vector2D(x_-vec.x_,y_-vec.y_);
}

void Vector2D::Normalize()
{
    CalcMagnitude();
    x_ = x_ / m_;
    y_ = y_ / m_;
}

void Vector2D::Normal()
{
    float temp = x_;
    x_ = y_;
    y_ = temp;
    y_ = -y_;
}

float Vector2D::DotProduct(const Vector2D& vec)
{
    return x_*vec.x_ + y_*vec.y_;
}


