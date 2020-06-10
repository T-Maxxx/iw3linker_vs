#include "hook_storage.hpp"
#include "base_hook.hpp"


namespace hooks
{
    CHookStorage::CHookStorage() = default;
    CHookStorage::~CHookStorage() = default;

    void CHookStorage::clear()
    {
        for (auto spHook : m_lstHooks)
            if (spHook)
                spHook->Release();

        m_lstHooks.clear();
    }


    CHookStorage& CHookStorage::Instance()
    {
        static CHookStorage hs;
        return hs;
    }


    CBaseHook* CHookStorage::AddHook(CBaseHook* pHook_)
    {
        if (findIntersection(pHook_))
            return nullptr;

        if (!pHook_)
            return nullptr;

        m_lstHooks.emplace_back(pHook_);
        m_lstHooks.back()->Install();
        return pHook_;
    }

    void CHookStorage::RemoveHook(CBaseHook * pHook_)
    {
        for (auto itHook = m_lstHooks.begin(), end = m_lstHooks.end(); itHook != end; ++itHook)
            if (itHook->get() == pHook_)
            {
                pHook_->Release();
                m_lstHooks.erase(itHook);
                return;
            }
    }

    const CBaseHook* CHookStorage::findIntersection(const CBaseHook* pHook_) const
    {
        uint32_t iMyLeft = pHook_->GetStartAddress();
        uint32_t iMyRight = pHook_->GetEndAddress();
        for (const auto spItHook : m_lstHooks)
        { 
            uint32_t iLeft = spItHook->GetStartAddress();
            uint32_t iRight = spItHook->GetEndAddress();

            if (iMyRight >= iLeft && iRight >= iMyLeft)
                return spItHook.get();
        }

        return nullptr;
    }
} // end namespace hooks
