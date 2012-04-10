#pragma once
#include "GameModule.types.h"
namespace Fry
{

class BaseModuleManager
{
    public:
        BaseModuleManager();
        virtual ~BaseModuleManager();

        void AddModule(GameModule* module);
        void RemoveModule(GameModule *module);
        GameModule* GetNextModule(GameModule* module, bool loop=false);
        GameModule* GetNextOfSameType(GameModule* module, bool loop=false);
        GameModule* GetModule(const std::string& name);
        void Clean();
        void Destroy();
        const GameModuleList& GetModuleList() const;
        /* Destroy list */
        void AddToDestroyList(GameModule* module);
        void RemoveFromDestroyList(GameModule* module);
        const GameModuleList& GetDestroyList() const;
        void DestroyModules();
    protected:
        GameModuleList moduleList_;
        GameModuleList destroyList_;
    private:
};

};
