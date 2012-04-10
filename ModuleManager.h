#pragma once
#include "EventManager.h"
#include "BaseModuleManager.h"
#include "Assert.h"

namespace Fry
{

class ModuleManager:public BaseModuleManager
{
    public:
        virtual ~ModuleManager();
        void ProcessModules(float elapsedTime);
        void Initialize();
        static ModuleManager* Instance();
        static bool Instantiate();
    private:
        ModuleManager();
		ModuleManager(const ModuleManager& ref); //Not implemented
        static ModuleManager* mManager_;
};

};
