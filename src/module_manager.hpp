#pragma once
#include <vector>
#include <memory>
#include <cassert>

class CModule;

class CModuleManager
{
public:
    CModuleManager();
    ~CModuleManager();

    template<class T>
    void AddModule()
    {
        std::shared_ptr<CModule> spModule = std::make_unique<T>();
        if (isModuleExist(spModule.get()))
        {
            assert(!"Module already exist");
            return;
        }

        m_vModules.push_back(spModule);
    }

    void InitGlobals() const;
    void Patch() const;

private:
    bool isModuleExist(const CModule* pModule_) const;

    std::vector<std::shared_ptr<CModule>> m_vModules;
};
