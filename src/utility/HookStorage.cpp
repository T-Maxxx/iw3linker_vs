#include "stdafx.h"
#include "HookStorage.h"

namespace hooklib
{
    CHookStorage::CHookStorage()
    {}

    CHookStorage::~CHookStorage()
    {
        clear();
    }

    void CHookStorage::clear()
    {
        for (CBaseHook* pHook : m_lstHooks)
        {
            pHook->Release();
            delete pHook;
        }

        m_lstHooks.clear();
    }

    CBaseHook* CHookStorage::AddHook(CBaseHook* pHook_)
    {
        auto pFoundHook = findIntersection(pHook_);
        if (pFoundHook)
        {
            assert(!"This hook intersects with other. Check debugger for more info.");
            return nullptr;
        }

        pHook_->Install();
        m_lstHooks.push_back(pHook_);
        return pHook_;
    }

    void CHookStorage::RemoveHook(CBaseHook * pHook_)
    {
        for (auto itHook = m_lstHooks.begin(), end = m_lstHooks.end(); itHook != end; ++itHook)
            if (*itHook == pHook_)
            {
                pHook_->Release();
                m_lstHooks.erase(itHook);
                return;
            }
    }

    const CBaseHook* CHookStorage::findIntersection(const CBaseHook* pHook_) const
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
} // end namespace hooklib
