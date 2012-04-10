#pragma once

#include "GameModule.types.h"
#include <SDL.h>
#include <SDL_opengl.h>

namespace Fry
{

class GameModule
{
public:
    GameModule();
    virtual ~GameModule();
    virtual void Render(float elapsedTime);
    virtual void Initialize();
    virtual void Destroy();
    virtual void ProcessEvent(SDL_Event *event);
    const std::string& GetName() const;
    virtual void ProcessModule(float elapsedTime);
protected:
    std::string name_;
};

};
