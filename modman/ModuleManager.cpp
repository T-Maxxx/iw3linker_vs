#include "stdafx.h"
#include "ModuleManager.h"

namespace modman
{
    CModuleManager::CModuleManager()
    {
    }


    CModuleManager::~CModuleManager()
    {
    }

    void CModuleManager::AddModule(CModule * pModule_)
    {
        if (isModuleExist(pModule_))
        {
            assert(!"Module already exist");
            return;
        }

        m_vModules.push_back(pModule_);
    }

    void CModuleManager::InitGlobals() const
    {
        for (auto pModule : m_vModules)
            pModule->InitGlobals();
    }

    void CModuleManager::Patch() const
    {
        for (auto pModule : m_vModules)
            pModule->Patch();
    }

    bool CModuleManager::isModuleExist(const CModule* pModule_) const
    {
        for (const auto pModule : m_vModules)
            if (pModule == pModule_)
                return true;

        return false;
    }
}
