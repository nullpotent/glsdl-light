#include "Engine.h"
#include "Assert.h"
#include "TestModule.h"
/* GLOBALS */
using namespace Fry;

Engine *Engine::engine_ = NULL;

Engine::Engine()
{
    timeAcc_                    = 0.0f;
    perspectiveRatio_           = 0; //possibly redundant
    endProcess_                 = false;
    name_                       = "";
    posX_                       = 0;
    posY_                       = 0;
    bits_                       = 16;
    width_                      = 640;
    height_                     = 480;
    active_                     = true;
    fullscreen_                 = false;
    lastTime_                   = 0.0f;
    currentTime_                = 0.0f;
    elapsedTime_                = 0.0f;
    totalTime_                  = 0.0f;
    numFrames_                  = 0;
    FPS_                        = 0;
    SDL_Surface *screen_        = NULL;
    videoFlags_                 = 0;
    sdlFlags_                   = 0;
    timer_                      = NULL;
}

Engine::~Engine()
{
    Destroy();
}

bool Engine::Instantiate(std::string title, short int width, short int height, char bits, Uint32 sdlFlags, Uint32 videoFlags)
{
    assert(width>0);
    assert(height>0);
    assert(bits>8);
    assert(title!=""); //I think it should work
    engine_ = new Engine();
    if(engine_->Create(title,width,height,bits,sdlFlags,videoFlags))
    {
        std::cout<<"Window sucessfully created"<<std::endl;
    }
    else
    {
        throw std::runtime_error("Window could not be created ");
    }
    return engine_!=NULL;
}

Engine* Engine::Instance()
{
    assert(engine_!=NULL);
    return engine_;
}

void Engine::Resize(unsigned int width, unsigned int height)
{
    this->width_ = width;
    this->height_ = height;

    if(height_==0)
    {
        height_ = 1;
    }

    glViewport(0,0,width_,height_);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, width_, height_, 0.0f, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

bool Engine::Initialize()
{

    glClearColor(0.0f,0.0f,0.0f,1.f);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST); //anti aliasing
    glShadeModel(GL_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER,0.1f);

    glDisable(GL_DEPTH_TEST);

    if(glGetError() != GL_NO_ERROR)
    {
        std::cout<<glGetError()<<std::endl;
        return false;
    }
    std::cout<<"OpenGL initialized"<<std::endl;

    if(Graphics::Instantiate())
    {
        std::cout<<"Graphics initialized"<<std::endl;
    }
    if(ModuleManager::Instantiate())
    {
        std::cout<<"ModuleManager initialized"<<std::endl;
    }

    tahomaFont = new Font("tahoma.ttf",16);

    ModuleManager::Instance()->AddModule(new TestModule("Dynamic lighting"));

    return true;
}

void Engine::Render(float elapsedTime)
{
    glClear(GL_COLOR_BUFFER_BIT);

    ModuleManager::Instance()->ProcessModules(elapsedTime);
    Graphics::Instance()->SetColor(COLOR_WHITE);
    Graphics::Instance()->DrawText(tahomaFont,0,0,"FPS: %i",FPS_);
}

void Engine::Display()
{
    currentTime_ = timer_->GetElapsedTime();
    elapsedTime_ = currentTime_-lastTime_;
    lastTime_ = currentTime_;

    Render(elapsedTime_);

    totalTime_+=elapsedTime_;
    numFrames_++;

    if(totalTime_>=1.0f)
    {
        FPS_ = (int)(numFrames_ / totalTime_);
        numFrames_ = 0;
        totalTime_ = 0.0f;
    }
}

bool Engine::Create(std::string title, short int width, short int height, char bits, Uint32 sdlFlags, Uint32 videoFlags)
{
    videoFlags_ = videoFlags;
    sdlFlags_ = sdlFlags;
    width_ = width;
    height_ = height;
    name_ = title;
    bits_ = bits;
    int rgb_size[3];
    int value;

    switch (bits_)
    {
        case 8:
            rgb_size[0] = 3;
            rgb_size[1] = 3;
            rgb_size[2] = 2;
            break;
        case 15:
        case 16:
            rgb_size[0] = 5;
            rgb_size[1] = 5;
            rgb_size[2] = 5;
            break;
        default:
            rgb_size[0] = 8;
            rgb_size[1] = 8;
            rgb_size[2] = 8;
            break;
    }

    if(SDL_Init(sdlFlags_)<0)
    {
        std::cout<<"Couldn't initialize SDL - "<<SDL_GetError()<<std::endl;
        return false;
    }
    if(fullscreen_)
    {
        videoFlags_ |= SDL_FULLSCREEN;
    }
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER,1);
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, rgb_size[0] );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, rgb_size[1] );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, rgb_size[2] );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 0); //No Z-buffer
    SDL_GL_SetAttribute( SDL_GL_BUFFER_SIZE, 32); //RGBA
    SDL_GL_SetAttribute( SDL_GL_ACCELERATED_VISUAL, 1 );
    /*
    	SDL_GL_SetAttribute( SDL_GL_MULTISAMPLEBUFFERS, 1 );
    	SDL_GL_SetAttribute( SDL_GL_MULTISAMPLESAMPLES, fsaa );
    }
    if ( accel ) {
    	SDL_GL_SetAttribute( SDL_GL_ACCELERATED_VISUAL, 1 );
    */

    if(SDL_SetVideoMode(width_, height_,bits_,videoFlags_)==NULL)
    {
        std::cout<<"Couldn't set GL mode -"<<SDL_GetError()<<std::endl;
        SDL_Quit();
        return false;
    }

    std::cout<<"Screen BPP: "<<SDL_GetVideoSurface()->format->BitsPerPixel<<std::endl;
    std::cout<<"Vendor: "<<glGetString(GL_VENDOR)<<std::endl;
    std::cout<<"Renderer: "<<glGetString(GL_RENDERER)<<std::endl;
    std::cout<<"Version: "<<glGetString(GL_VERSION)<<std::endl;
    std::cout<<"Extensions "<<glGetString(GL_EXTENSIONS)<<std::endl;

    std::cout<<std::endl<<std::endl;
    SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER,&value);
    std::cout<<"Doublebuffer: "<<value<<std::endl;
    SDL_GL_GetAttribute(SDL_GL_ACCELERATED_VISUAL,&value);
    std::cout<<"Acceleration: "<<value<<std::endl;
    SDL_GL_GetAttribute( SDL_GL_MULTISAMPLEBUFFERS, &value );
    std::cout<<"GL_MULTISAMPLEBUFFERS: "<<value<<std::endl;
    SDL_GL_GetAttribute( SDL_GL_MULTISAMPLESAMPLES, &value );
    std::cout<<"GL_MULTISAMPLESAMPLES"<<&value<<std::endl;

    SDL_WM_SetCaption(name_.c_str(),NULL); //second parameter is an icon

    if(!Initialize())
    {
        return false;
    }
    Resize(width_,height_);
    screen_ = SDL_GetVideoSurface();
    timer_ = new Timer();
    timer_->Init();
    return true;
}

void Engine::SetFullScreen()
{
    SDL_WM_ToggleFullScreen(screen_);
}

void Engine::Run()
{
    while(!endProcess_)
    {
        //SDL_Event event;
        Display();
        SDL_GL_SwapBuffers();
        while( SDL_PollEvent( &event ) )
        {

            switch(event.type)
            {
                case SDL_ACTIVEEVENT:
                {
                    if(event.active.gain==0)
                    {
                        active_ = false;
                    }
                    else
                    {
                        active_ = true;
                    }
                    break;
                }
                case SDL_VIDEORESIZE:
                {
                    screen_ = SDL_SetVideoMode( event.resize.w,
                                                event.resize.h,
                                                bits_, videoFlags_ );
                    Resize(event.resize.w,event.resize.h);
                    break;
                }
                case SDL_KEYDOWN:
                {
                    if(event.key.keysym.sym==SDLK_F1)
                    {
                        SetFullScreen();
                    }
                    else if(event.key.keysym.sym==SDLK_ESCAPE)
                    {
                        endProcess_ = true;
                    }
                    break;
                }
                case SDL_QUIT:
                {
                    endProcess_ = true;
                    break;
                }
            }
            EventManager::Instance()->SendEvent(&event);
        }
    }
}

void Engine::Destroy()
{
    std::cout<<"Engine down"<<std::endl;
    delete timer_;
    delete tahomaFont;
    delete ModuleManager::Instance();
    SDL_FreeSurface(screen_);
    SDL_Quit();
}
