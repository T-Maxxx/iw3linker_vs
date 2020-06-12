#pragma once
#include <vector>
#include <memory>
#include <cassert>
#include <typeindex>

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
        std::type_index ti(typeid(T));
        if (isModuleExist(ti))
        {
            assert(!"Module already exist");
            return;
        }

        m_vModules.emplace_back(ti, spModule);
    }

    void InitGlobals() const;
    void Patch() const;

private:
    bool isModuleExist(const std::type_index& TI_) const;

private:
    std::vector<std::pair<std::type_index, std::shared_ptr<CModule>>> m_vModules;
};
