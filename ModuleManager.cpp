#include "ModuleManager.h"
#include "GameModule.h"

using namespace Fry;

ModuleManager *ModuleManager::mManager_ = NULL;

ModuleManager::ModuleManager()
{
    Initialize();
}

ModuleManager::~ModuleManager()
{
    std::cout<<"ModuleManager down"<<std::endl;
    delete EventManager::Instance();
}

ModuleManager* ModuleManager::Instance()
{
    assert(mManager_!=NULL);
    return mManager_;
}

void ModuleManager::ProcessModules(float elapsedTime)
{
    DestroyModules();
    GameModuleList::iterator it = moduleList_.begin();
    GameModuleList::iterator itEnd = moduleList_.end();
    while(it!=itEnd)
    {
        (*it)->ProcessModule(elapsedTime);
        it++;
    }
}

bool ModuleManager::Instantiate()
{
    mManager_ = new ModuleManager();
    return mManager_!=NULL;
}

void ModuleManager::Initialize()
{
    if(EventManager::Instantiate(&moduleList_))
    {
        std::cout<<"EventManager initialized"<<std::endl;
    }
}
