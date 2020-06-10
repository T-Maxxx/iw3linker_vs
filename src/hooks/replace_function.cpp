#include "replace_function.hpp"

#include <cassert>

#include "memory.hpp"


namespace hooks
{
    CReplaceFunc::~CReplaceFunc()
    {}

    void CReplaceFunc::Install()
    {
        if (IsInstalled())
            return;

        ReadFromMemory(CBaseHook::GetStartAddress(), &m_Original);
        SJumpHook hook;
        hook.OpCode = 0xe9;
        hook.JumpOffset = m_iRawTarget - CBaseHook::GetStartAddress() - sizeof(SJumpHook);
        WriteToMemory(CBaseHook::GetStartAddress(), &hook);

        SetInstalled(true);
    }

    void CReplaceFunc::Release()
    {
        if (!IsInstalled())
            return;

        WriteToMemory(CBaseHook::GetStartAddress(), &m_Original);
        SetInstalled(false);
    }
}
