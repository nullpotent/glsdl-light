#pragma once
#include "GameModule.types.h"
#include <SDL.h>
namespace Fry
{

class EventManager
{
    public:
        EventManager(GameModuleList* list);
        EventManager();
        virtual ~EventManager();
        void SendEvent(SDL_Event *event);
        static bool Instantiate(GameModuleList* list);
        static EventManager* Instance();
    protected:
    private:
        GameModuleList* moduleList_;
        static EventManager* manager_;
};

};
