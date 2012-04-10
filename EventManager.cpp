#include "EventManager.h"
#include "GameModule.h"
#include <iostream>

using namespace Fry;

EventManager* EventManager::manager_ = NULL;

EventManager::EventManager(GameModuleList* list)
{
    moduleList_ = list;
}

EventManager::EventManager()
{
    //NOTHING HERE
}

EventManager::~EventManager()
{
    std::cout<<"EventManager down"<<std::endl;
}

EventManager* EventManager::Instance()
{
    if(manager_==NULL)
    {
        manager_ = new EventManager();
    }
    return manager_;
}

bool EventManager::Instantiate(GameModuleList* list)
{
    manager_ = new EventManager(list);
    return manager_!=NULL;
}

void EventManager::SendEvent(SDL_Event* event)
{
    GameModuleList::iterator it = moduleList_->begin();
    GameModuleList::iterator itEnd = moduleList_->end();

    while(it!=itEnd)
    {
        (*it)->ProcessEvent(event);
        it++;
    }
}
