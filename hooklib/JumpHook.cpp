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
        assert(!m_pOriginalInstruction);
        m_pOriginalInstruction = new SJumpHook();

        ReadFromMemory(CBaseHook::GetStartAddress(), m_pOriginalInstruction);
        SJumpHook hook(m_iRawTarget - CBaseHook::GetStartAddress() - sizeof(SJumpHook), m_bCallHook);
        WriteToMemory(CBaseHook::GetStartAddress(), &hook);
    }

    void CJumpHook::Release()
    {
        WriteToMemory(CBaseHook::GetStartAddress(), m_pOriginalInstruction);
        delete m_pOriginalInstruction;
        m_pOriginalInstruction = nullptr;
    }

    EHookType CJumpHook::GetHookType() const
    {
        return EHT_JumpHook;
    }
}
