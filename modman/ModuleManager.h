#pragma once
#include <list>
#include "Module.h"

namespace modman
{
    class CModuleManager
    {
    public:
        CModuleManager();
        ~CModuleManager();

        void AddModule(CModule* pModule_);
        void InitGlobals() const;
        void Patch() const;

    private:
        bool isModuleExist(const CModule* pModule_) const;

        std::list<CModule*> m_vModules;
    };
}
