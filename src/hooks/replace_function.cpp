#include "replace_function.hpp"

#include <cassert>

#include "memory.hpp"


namespace hooks
{
    CReplaceFunc::~CReplaceFunc()
    {
        assert(!m_pOriginalInstruction && "WTF? Destructor called earlier than Release method RECHECK urself");
    }

    void CReplaceFunc::Install()
    {
        assert(!m_pOriginalInstruction);
        m_pOriginalInstruction = new SJumpHook();

        ReadFromMemory(CBaseHook::GetStartAddress(), m_pOriginalInstruction);
        SJumpHook hook;
        hook.OpCode = 0xe9;
        hook.JumpOffset = m_iRawTarget - CBaseHook::GetStartAddress() - sizeof(SJumpHook);
        WriteToMemory(CBaseHook::GetStartAddress(), &hook);

        SetInstalled(true);
    }

    void CReplaceFunc::Release()
    {
        WriteToMemory(CBaseHook::GetStartAddress(), m_pOriginalInstruction);
        delete m_pOriginalInstruction;
        m_pOriginalInstruction = nullptr;

        SetInstalled(false);
    }
}
