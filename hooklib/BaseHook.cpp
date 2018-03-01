#include "stdafx.h"
#include "BaseHook.h"

namespace hooklib
{
    CBaseHook::CBaseHook(uint Address_) : CBaseHook(Address_, Address_) {}

    CBaseHook::CBaseHook(uint StartAddress_, uint EndAddress_)
        : m_StartAddress(StartAddress_)
        , m_EndAddress(EndAddress_ - 1)
    {
        // This constructor called always first.
        Install();
    }


    CBaseHook::~CBaseHook()
    {
        // This destructor called always last. So need to check if child class
        //   was destructed proper.
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
}
