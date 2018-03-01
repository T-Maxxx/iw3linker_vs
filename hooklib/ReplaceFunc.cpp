#include "stdafx.h"
#include "ReplaceFunc.h"
#include "Memory.h"

namespace hooklib
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
        SJumpHook hook(m_iRawTarget - CBaseHook::GetStartAddress() - sizeof(SJumpHook), false);
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
