#include "jump_hook.hpp"
#include "memory.hpp"


namespace hooks
{
    CJumpHook::~CJumpHook()
    {
        Release();
    }

    void CJumpHook::Install()
    {
        ReadFromMemory(CBaseHook::GetStartAddress(), &m_OriginalInstruction);
        SJumpHook hook;
        hook.OpCode = m_bCallHook ? 0xE8 : 0xE9;
        hook.JumpOffset = m_iRawTarget - CBaseHook::GetStartAddress() - sizeof(SJumpHook);
        WriteToMemory(CBaseHook::GetStartAddress(), &hook);

        SetInstalled(true);
    }

    void CJumpHook::Release()
    {
        WriteToMemory(CBaseHook::GetStartAddress(), &m_OriginalInstruction);
        SetInstalled(false);
    }
}
