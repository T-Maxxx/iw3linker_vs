#include "base_hook.hpp"

namespace hooks
{
    CBaseHook::CBaseHook(uint32_t Address_)
        : CBaseHook(Address_, 1)
    {}

    
    CBaseHook::CBaseHook(uint32_t Address_, uint32_t Size_)
        : m_StartAddress(Address_)
        , m_EndAddress(Address_ + Size_ - 1)
    {
    }


    CBaseHook::~CBaseHook()
    {
        if (IsInstalled())
            Release();
    }

    
    void CBaseHook::Install()
    {
        if (IsInstalled())
            return;

        SetInstalled(true);
    }

    
    void CBaseHook::Release()
    {
        SetInstalled(false);
    }


    uint32_t CBaseHook::GetStartAddress() const
    {
        return m_StartAddress;
    }


    uint32_t CBaseHook::GetEndAddress() const
    {
        return m_EndAddress;
    }


    bool CBaseHook::IsInstalled() const
    {
        return m_bInstalled;
    }


    void CBaseHook::SetInstalled(bool bState_)
    {
        m_bInstalled = bState_;
    }
}
