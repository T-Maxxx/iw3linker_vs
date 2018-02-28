#include "stdafx.h"
#include "BaseHook.h"

namespace hooklib
{
    CBaseHook::CBaseHook(uint Address_) : CBaseHook(Address_, Address_) {}

    CBaseHook::CBaseHook(uint StartAddress_, uint EndAddress_)
        : m_StartAddress(StartAddress_)
        , m_EndAddress(EndAddress_ - 1)
    {
        Install();
    }


    CBaseHook::~CBaseHook()
    {
        Release();
    }


    uint CBaseHook::GetStartAddress() const
    {
        return m_StartAddress;
    }


    uint CBaseHook::GetEndAddress() const
    {
        return m_EndAddress;
    }

    EHookType CBaseHook::GetHookType() const
    {
        return EHT_Unknown;
    }
}
