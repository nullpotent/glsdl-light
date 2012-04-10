#include "PolyStruct.h"

using namespace Fry;

PolyStruct::PolyStruct()
{
    r_ = 0.0f;
    g_ = 0.0f;
    b_ = 0.0f;
    intensity_ = 0;
}

PolyStruct::PolyStruct(float r,float g, float b)
{
    r_ = r;
    g_ = g;
    b_ = b;
    size_ = 0;
    intensity_ = 0;
}

PolyStruct::~PolyStruct()
{
    list_.clear();
    edges_.clear();
}

void PolyStruct::AddPoint(float x,float y)
{
    Point temp(x,y);
    list_.insert(list_.end(),temp);
    size_++;
}

void PolyStruct::ConstructEdges()
{
    for(std::list<Point>::iterator i=list_.begin(); i!=list_.end(); ++i)
    {
        std::list<Point>::iterator i1 = i;
        ++i1;
        if(i1==list_.end())
        {
            i1 = list_.begin();
        }
        Edge e((*i),(*i1));
        edges_.insert(edges_.end(),e);
        size_++;
    }
}

void PolyStruct::Render()
{
    glColor4f(r_,g_,b_,1.0f-intensity_);
    glBegin(GL_POLYGON);
    {
        for(std::list<Point>::iterator i=list_.begin(); i!=list_.end(); ++i)
        {
            glVertex2f((*i).x_,(*i).y_);
        }
    }
    glEnd();
    glFlush();
}

void PolyStruct::Print()
{
    for(std::list<Edge>::iterator i=edges_.begin(); i!=edges_.end(); ++i)
    {
        std::cout<<(*i).x_<<" "<<(*i).y_<<" "<<(*i).x1_<<" "<<(*i).y1_<<std::endl;
    }
}
