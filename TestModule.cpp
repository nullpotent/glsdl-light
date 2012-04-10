#include "TestModule.h"

using namespace Fry;

TestModule::TestModule(const std::string& name)
{
    timeAcc_ = 0.0f;
    bl1 = 1;
    bl2 = 1;
    bl11 = 1;
    bl22 = 1;
    name_ = name;
    Initialize();
}

TestModule::~TestModule()
{
    Destroy();
}

void TestModule::Render(float elapsedTime)
{
    timeAcc_+=(float)(elapsedTime*0.2f);

    glPushMatrix();
    glLoadIdentity();

    if(timeAcc_>=1.0f)
    {
        timeAcc_=0.0f;
    }


    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    l0->Render();



    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    l0->ProjectShadow(*bb);
    l0->ProjectShadow(*mmm);

    glPopMatrix();
}

void TestModule::Initialize()
{

    l0 = new Light(COLOR_GREEN,220,320.0f,240.0f,550.0f);

    mmm = new PolyStruct(1.0f,0.0f,0.0f);

    mmm->AddPoint(100.f,100.f);
    mmm->AddPoint(50.f,100.f);
    mmm->AddPoint(50.f,50.f);
    mmm->AddPoint(100.f,50.f);
    mmm->ConstructEdges();
    mmm->Print();

    bb = new PolyStruct(0.0f,0.0f,1.0f);

    bb->AddPoint(300.f,300.f);
    bb->AddPoint(350.f,250.f);
    bb->AddPoint(350.f,300.f);
    bb->AddPoint(400.f,350.f);
    bb->AddPoint(350.f,400.f);
    bb->AddPoint(300.f,400.f);
    bb->AddPoint(250.f,350.f);

    bb->ConstructEdges();
    bb->Print();

    blendPrvi = {GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_DST_COLOR, GL_ONE_MINUS_DST_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_CONSTANT_COLOR, GL_ONE_MINUS_CONSTANT_COLOR, GL_CONSTANT_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA, GL_SRC_ALPHA_SATURATE};
    blendDrugi = {GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_DST_COLOR, GL_ONE_MINUS_DST_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_CONSTANT_COLOR, GL_ONE_MINUS_CONSTANT_COLOR, GL_CONSTANT_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA};
    texEnv = {GL_ADD, GL_MODULATE, GL_DECAL, GL_BLEND, GL_REPLACE, GL_TEXTURE, GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA};
}

void TestModule::Destroy()
{

    delete l0;
    delete mmm;
    delete bb;
}

void TestModule::ProcessModule(float elapsedTime)
{
    Render(elapsedTime);
}

void TestModule::ProcessEvent(SDL_Event* event)
{
    switch(event->type)
    {
        case SDL_MOUSEMOTION:
        {
            l0->SetPosX(event->motion.x);
            l0->SetPosY(event->motion.y);
            break;
        }
        case SDL_KEYDOWN:
        {
            if(bl1>14)
            {
                bl1 = 0;
            }
            if(bl2>15)
            {
                bl2 = 0;
            }
            if(event->key.keysym.sym==SDLK_t)
            bl1++;
            if(event->key.keysym.sym==SDLK_h)
            bl2++;
            std::cout<<"Blend1 "<<bl1<<" Blend2 "<<bl2<<std::endl;
            break;
        }
    }
}
