#include "module_manager.hpp"

#include "module.hpp"


CModuleManager::CModuleManager() = default;
CModuleManager::~CModuleManager() = default;


void CModuleManager::InitGlobals() const
{
    for (auto spModule : m_vModules)
        spModule->InitGlobals();
}


void CModuleManager::Patch() const
{
    for (auto spModule : m_vModules)
        spModule->Patch();
}


bool CModuleManager::isModuleExist(const CModule* pModule_) const
{
    for (const auto spModule : m_vModules)
        if (typeid(spModule) == typeid(pModule_))
            return true;

    return false;
}
