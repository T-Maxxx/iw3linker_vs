#pragma once

#define DECLARE_NO_COPY_CLASS(className) \
    className(const className&) = delete; \
    void operator = (const className&) = delete;

namespace hooklib
{
    enum EHookType
    {
        EHT_Unknown,
        EHT_GlobalVar,
        EHT_JumpHook,
        EHT_NativeFunc
    };

    using uint = unsigned int;
    using byte = unsigned char;

#pragma pack(push, 1)
    struct SJumpHook
    {
        SJumpHook() : Opcode(0x00), Offset(0) {}
        SJumpHook(uint Offset_, bool bCallHook_ = false) : Opcode(bCallHook_ ? 0xE8 : 0xE9), Offset(Offset_) {}

        byte Opcode;
        uint Offset;
    };
#pragma pack(pop)
} // end namespace hooklib
