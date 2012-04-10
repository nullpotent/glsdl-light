#pragma once
#include <string>
#include <stdexcept>
#include <iostream>
#include <SDL.h>
#include <SDL_opengl.h>
#include "Timer.h"
#include "ModuleManager.h"
#include "Graphics.h"


namespace Fry
{

class Engine
{
    public:
        /* CTORS && DTORS */
        Engine();
        virtual ~Engine();
        /* Creates the main rendering context and sets up a window.
            @params:
                    title   - Window title
                    width   - Window width
                    height  - Window height
                    bits    - Bits per pixel - PFD
            @return
                    true    - Successfully created window
                    false   - Something went wrong - probably SDL_Init(). Set DEBUG=true when asserting for condition
        */
        bool Create(std::string title, short int width, short int height, char bits, Uint32 sdlFlags, Uint32 videoFlags);
        /*
            @return
                    Frames per second calculated in Diplay function
        */
        const int GetFps() const;
        /* Sets fullscreen rendering mode
        */
        void SetFullScreen();
        /*
            @return
                    Returns a boolean value 'true' if the window is in fullscreen, 'false' otherwise
        */
        bool GetFullScreen();
        /*
            Renders all game modules and utilizes Timer
        */
        void Display();
        /*
            Placed inside class destructor. Frees all surfaces. Pointers used are automatically deleted thanks to boost smart_ptr library
        */
        void Destroy();
        /*
            Initializes members: Freetype,SDL,
        */
        virtual bool Initialize();
        /*
            Function for handling window's resize event
        */
        virtual void Resize(unsigned int width,unsigned int height);
        /*
            Main rendering function which provides elapsedtime value to all loaded modules.
        */
        void Render(float elapsedTime);
        /*
            Starts the game loop
        */
        void Run();
        /*
            Provides singleton pattern - returns first instance
        */
        static Engine *Instance();
        /*
            Instantiates the Engine class. Replaces default constructor
        */
        static bool Instantiate(std::string title, short int width, short int height, char bits, Uint32 sdlFlags, Uint32 videoFlags);
        /** Show,Hide Cursor
        */
    protected:
    private:
        float timeAcc_;
        float perspectiveRatio_; //possibly redundant
        bool endProcess_;
        std::string name_;

        unsigned int posX_;
        unsigned int posY_;
        char bits_;
        unsigned int width_;
        unsigned int height_;

        bool active_;
        bool fullscreen_;
        /** TO-DO: */
        Timer *timer_;
        float lastTime_;
        float currentTime_;
        float elapsedTime_;
        float totalTime_;
        int numFrames_;
        int FPS_;
        Uint32 videoFlags_;
        Uint32 sdlFlags_;
        /** TO-DO: */
        Font* tahomaFont;
        SDL_Surface *screen_;
        SDL_Event event;
        //static pointer (singleton pattern)
        static Engine* engine_;
};

};
