
#include "Engine.h"
#include <iostream>

using namespace Fry;

int main(int argc, char** argv)
{

    if(Engine::Instantiate("blahah",640,480,24, SDL_INIT_VIDEO, SDL_OPENGL | SDL_HWACCEL | SDL_RESIZABLE | SDL_HWPALETTE))
    {
        std::cout<<"Engine operational "<<std::endl;
    }
    else
    {
        std::cout<<"Something terrible happened "<<"SDL ERROR: "<<SDL_GetError()<<std::endl<<"OPENGL ERROR: "<<glGetError()<<std::endl;
    }

    Engine::Instance()->Run();

    delete Engine::Instance();

    return 0;

}
