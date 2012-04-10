#include "GameModule.h"
#include <iostream>

using namespace Fry;

GameModule::GameModule()
{

}

GameModule::~GameModule()
{
    Destroy();
}

void GameModule::Destroy()
{
    std::cout<<"GameModule "<<name_<<std::endl;
}

void GameModule::Initialize()
{
    //REDEFINE
}

void GameModule::ProcessEvent(SDL_Event* event)
{
    //REDEFINE
}

void GameModule::Render(float elapsedTime)
{

}

const std::string& GameModule::GetName() const
{
    return name_;
}

void GameModule::ProcessModule(float elapsedTime)
{
    Render(elapsedTime);
}


