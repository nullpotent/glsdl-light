#include "BaseModuleManager.h"
#include "GameModule.h"
#include <typeinfo>

using namespace Fry;

BaseModuleManager::BaseModuleManager()
{
    Clean();
    destroyList_.clear();
}

BaseModuleManager::~BaseModuleManager()
{
    Destroy();
}

void BaseModuleManager::AddModule(GameModule* module)
{
    GameModuleList::iterator it = std::find(moduleList_.begin(),moduleList_.end(),module);

    if(it==moduleList_.end())
    {
        moduleList_.push_back(module);
    }
}

void BaseModuleManager::RemoveModule(GameModule* module)
{
    GameModuleList::iterator it = std::find(moduleList_.begin(),moduleList_.end(),module);

    if(it!=moduleList_.end())
    {
        moduleList_.erase(it);
    }
}

GameModule* BaseModuleManager::GetNextModule(GameModule* module, bool loop)
{
    GameModule* returnModule = NULL;

    if(moduleList_.size())
    {
        GameModuleList::iterator it = std::find(moduleList_.begin(),moduleList_.end(),module);
        if(it!=moduleList_.end())
        {
            it++;
            if(it==moduleList_.end())
            {
                    if(loop)
                    {
                        returnModule = (*moduleList_.begin());
                    }
                    else
                    {
                        returnModule = (*it);
                    }
            }
        }
    }
    return returnModule;
}

GameModule* BaseModuleManager::GetNextOfSameType(GameModule* module,bool loop)
{
    GameModule* returnModule = NULL;
    bool found = false;
    bool end = false;

    returnModule = GetNextModule(module,loop);

    while(returnModule && (!found) && (!end))
    {
        if(returnModule == module)
        {
            returnModule = NULL;
            end = true;
        }
        else
        {
            if(typeid(*returnModule)==typeid(*module))
            {
                found = true;
            }
            else
            {
                returnModule = GetNextModule(returnModule,loop);
            }
        }
    }
    return returnModule;
}

GameModule* BaseModuleManager::GetModule(const std::string& name)
{
    GameModule* returnModule = NULL;

    GameModuleList::iterator it = moduleList_.begin();
    GameModuleList::iterator itEnd = moduleList_.end();

    bool found = false;
    while((it!=itEnd) && (!found))
    {
        if((*it)->GetName()==name)
        {
            found = true;
            returnModule = (*it);
        }
        else
        {
            it++;
        }
    }
    return returnModule;
}

void BaseModuleManager::Clean()
{
    moduleList_.clear();
}

void BaseModuleManager::Destroy()
{
    while(moduleList_.begin() != moduleList_.end())
    {
        GameModule* module = moduleList_.front();
        moduleList_.pop_front();
        delete module;
    }
    moduleList_.clear();
    DestroyModules();
}

const GameModuleList& BaseModuleManager::GetModuleList() const
{
    return moduleList_;
}

void BaseModuleManager::AddToDestroyList(GameModule* module)
{
    GameModuleList::iterator it = std::find(destroyList_.begin(),destroyList_.end(),module);
    if(it==destroyList_.end())
    {
        destroyList_.push_back(module);
    }
}

void BaseModuleManager::RemoveFromDestroyList(GameModule* module)
{
    GameModuleList::iterator it = std::find(destroyList_.begin(),destroyList_.end(),module);
    if(it!=destroyList_.end())
    {
        destroyList_.erase(it);
    }
}

const GameModuleList& BaseModuleManager::GetDestroyList() const
{
    return destroyList_;
}

void BaseModuleManager::DestroyModules()
{
    while(destroyList_.begin() != destroyList_.end())
    {
        GameModule* module = destroyList_.front();
        destroyList_.pop_front();
        delete module;
    }
    destroyList_.clear();
}

