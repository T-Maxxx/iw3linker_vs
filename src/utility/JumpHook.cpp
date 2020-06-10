#include "stdafx.h"
#include "JumpHook.h"
#include "Memory.h"

namespace hooklib
{
    CJumpHook::~CJumpHook()
    {
        Release();
    }

    void CJumpHook::Install()
    {
        ReadFromMemory(CBaseHook::GetStartAddress(), &m_OriginalInstruction);
        SJumpHook hook(m_iRawTarget - CBaseHook::GetStartAddress() - sizeof(SJumpHook), m_bCallHook);
        WriteToMemory(CBaseHook::GetStartAddress(), &hook);

        SetInstalled(true);
    }

    void CJumpHook::Release()
    {
        WriteToMemory(CBaseHook::GetStartAddress(), &m_OriginalInstruction);

        SetInstalled(false);
    }
}
