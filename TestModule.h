#pragma once
#include "GameModule.h"
#include "Light.h"
#include "Vector2D.h"
#include "PolyStruct.h"

namespace Fry
{

class TestModule:public GameModule
{
    public:
        TestModule(const std::string& name);
        virtual ~TestModule();
        virtual void Render(float elapsedTime);
        virtual void Initialize();
        virtual void Destroy();
        virtual void ProcessEvent(SDL_Event* event);
        virtual void ProcessModule(float elapsedTime);
    protected:
    private:
        float timeAcc_;
        int textX;
        int textY;
        Light* l0;
        PolyStruct* mmm;
        PolyStruct *bb;
        Vector2D lightVec,pointA,pointB;
        float counter;
        GLenum blendPrvi[15];
        GLenum blendDrugi[14];
        GLint texEnv[10];
        int bl1,bl2,tex;
        int bl11,bl22;
};

};
