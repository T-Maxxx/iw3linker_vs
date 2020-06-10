#pragma once

#define DECLARE_NO_COPY_CLASS(className) \
private: \
    className(const className&) = delete; \
    void operator = (const className&) = delete;

// Don't forget to define private constructor.
#define DECLARE_SINGLETON(className) \
public: \
    /** \
    \brief A class factory. \
    */ \
    static className& Instance() { static className g_Instance; return g_Instance; } \
private: \
    className(const className&) = delete; \
    void operator=(const className&) = delete;
    

namespace hooklib
{
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
