#include "stdafx.h"
#include "BaseHook.h"

namespace hooklib
{
    CBaseHook::CBaseHook(uint Address_) 
        : CBaseHook(Address_, 1)
    {}

    
    CBaseHook::CBaseHook(uint Address_, uint Size_)
        : m_StartAddress(Address_)
        , m_EndAddress(Address_ + Size_ - 1)
    {
    }


    CBaseHook::~CBaseHook()
    {
        // This destructor called always last. So need to check if child class
        //   was destructed proper.
        if (IsInstalled())
        {
            assert(!"This class was not properly destructed");
            Release();
        }
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


    uint CBaseHook::GetStartAddress() const
    {
        return m_StartAddress;
    }


    uint CBaseHook::GetEndAddress() const
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
