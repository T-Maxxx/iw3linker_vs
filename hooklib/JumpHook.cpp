#include "stdafx.h"
#include "JumpHook.h"
#include "Memory.h"

namespace hooklib
{
#pragma pack(push, 1)
    struct SJumpHook
    {
        SJumpHook() : Opcode(0x00), Offset(0) {}
        SJumpHook(uint Offset_, bool bCallHook_ = false) : Opcode(bCallHook_ ? 0xE8 : 0xE9), Offset(Offset_) {}

        byte Opcode;
        uint Offset;
    };
#pragma pack(pop)

    CJumpHook::~CJumpHook()
    {
        assert(!m_pOriginalInstruction && "WTF? Destructor called earlier than Release method RECKECK BASE CLASS");
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
