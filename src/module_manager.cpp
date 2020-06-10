#include "module_manager.hpp"

#include "module.hpp"


CModuleManager::CModuleManager() = default;
CModuleManager::~CModuleManager() = default;


void CModuleManager::InitGlobals() const
{
    for (const auto [_, spModule] : m_vModules)
        spModule->InitGlobals();
}


void CModuleManager::Patch() const
{
    for (const auto [_, spModule] : m_vModules)
        spModule->Patch();
}


bool CModuleManager::isModuleExist(const std::type_index& TI_) const
{
    for (const auto [ti, _] : m_vModules)
        if (ti == TI_)
            return true;

    return false;
}
