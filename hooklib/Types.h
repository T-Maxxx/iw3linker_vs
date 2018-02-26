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

    // Various structs forward declaration.
    struct SJumpHook;
} // end namespace hooklib
