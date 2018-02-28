#include "stdafx.h"
#include "HookStorage.h"

namespace hooklib
{
    CHookStorage::CHookStorage()
    {
    }

    CHookStorage::~CHookStorage()
    {
        clear();
    }

    void CHookStorage::clear()
    {
        for (IBaseHook* pHook : m_lstHooks)
            delete pHook;

        m_lstHooks.clear();
    }

    IBaseHook* CHookStorage::AddHook(IBaseHook* pHook_)
    {
        if (findIntersection(pHook_))
        {
            assert(!"This hook intersects with other");
            return nullptr;
        }
        pHook_->Install();
        m_lstHooks.push_back(pHook_);
        return pHook_;
    }

    void CHookStorage::RemoveHook(IBaseHook * pHook_)
    {
        for (auto itHook = m_lstHooks.begin(), end = m_lstHooks.end(); itHook != end; ++itHook)
            if (*itHook == pHook_)
            {
                pHook_->Release();
                m_lstHooks.erase(itHook);
                return;
            }
    }

    const IBaseHook* CHookStorage::findIntersection(const IBaseHook* pHook_) const
    {
        for (const auto* pItHook : m_lstHooks)
        { 
            uint iMyLeft = pHook_->GetStartAddress();
            uint iMyRight = pHook_->GetEndAddress();
            uint iLeft = pItHook->GetStartAddress();
            uint iRight = pItHook->GetEndAddress();

            if (iMyRight >= iLeft && iRight >= iMyLeft)
                return pItHook;
        }
        return nullptr;
    }

    CHookStorage* GetHookStorage()
    {
        static CHookStorage g_HookStorage;
        return &g_HookStorage;
    }
} // end namespace hooklib
