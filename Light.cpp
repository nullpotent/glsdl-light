#include "Light.h"

using namespace Fry;

Light::Light()
{
    intensity_  = 255;
    r_          = 255;
    g_          = 0;
    b_          = 0;
    posX_       = 0.0f;
    posY_       = 0.0f;
    range_      = 100.0f;
    angle_      = 0.0f;
}

Light::~Light()
{

}

Light::Light(int r,int g,int b, int intensity, float posX, float posY, float range)
{
    intensity_  = intensity;
    r_          = r;
    g_          = g;
    b_          = b;
    posX_       = posX;
    posY_       = posY;
    range_      = range;
    angle_      = 0.0f;
}

void Light::Render()
{
    glBegin(GL_TRIANGLE_FAN);
    {
        Graphics::Instance()->SetColor(r_,g_,b_,intensity_);
        glVertex2f(posX_,posY_);

        glColor4f(0.f, 0.f, 0.f, 0.0f);

        for (angle_=0.0; angle_<=PI*2; angle_+=((PI*2)/64.0f) )
        {
            /** FIX
                Precomputed sin & cos table
            */
            glVertex2f(range_*(float)cos(angle_) + posX_,
                       range_*(float)sin(angle_) + posY_);
        }

        glVertex2f(posX_+range_, posY_);
    }
    glEnd();
}

void Light::ProjectShadow(PolyStruct& poly)
{
    if(Intersects(poly))
    {
        for(std::list<Edge>::iterator i=poly.edges_.begin(); i!=poly.edges_.end(); i++)
        {
            Vector2D lineAVec((*i).x_,(*i).y_);
            Vector2D lineBVec((*i).x1_,(*i).y1_);
            Vector2D lineVec = lineBVec - lineAVec;

            lineVec.Normal();

            Vector2D lightSource(posX_,posY_);
            Vector2D lightToA = lineAVec - lightSource;

            if(lineVec.DotProduct(lightToA)<0.0f)
            {
                Vector2D projA = ProjectVector(Vector2D((*i).x_,(*i).y_));
                Vector2D projB = ProjectVector(Vector2D((*i).x1_,(*i).y1_));
                glColor3f(0.0f,0.0f,0.0f);
                glBegin(GL_POLYGON);
                {
                    glVertex2f((*i).x_,(*i).y_);
                    glVertex2f((*i).x1_,(*i).y1_);
                    glVertex2f(projB.x_,projB.y_);
                    glVertex2f(projA.x_,projA.y_);
                }
                glEnd();
            }
        }
        poly.Render();
    }
}

Vector2D Light::ProjectVector(const Vector2D point)
{
    Vector2D light(posX_,posY_);
    Vector2D ligh2point = point - light;
    Vector2D offset = Vector2D(point.x_,point.y_);
    Vector2D projectedPoint = point + ligh2point*100;
    return projectedPoint;
}

bool Light::Intersects(PolyStruct& poly)
{
    for(std::list<Point>::iterator i=poly.list_.begin(); i!=poly.list_.end(); ++i)
    {
        float dist = sqrt(((*i).x_ - posX_) * ((*i).x_ - posX_) + ((*i).y_ - posY_) * ((*i).y_ - posY_));

        if(dist<range_)
        {
            poly.intensity_ = dist / range_;
            return true;
        }
        else
        {
            poly.intensity_ = 0.0f;
            return false;
        }
    }
}

void Light::SetPosX(float posX)
{
    posX_ = posX;
}

void Light::SetPosY(float posY)
{
    posY_ = posY;
}

float Light::GetPosX()
{
    return posX_;
}

float Light::GetPosY()
{
    return posY_;
}
