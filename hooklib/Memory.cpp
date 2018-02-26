#include "stdafx.h"
#include "Memory.h"

namespace hooklib
{
    void ReadFromMemory(void* FromAddress_, void * ToStorage_, size_t Size_)
    {
        memcpy(ToStorage_, FromAddress_, Size_);
    }

    void WriteToMemory(void * ToAddress_, void * FromStorage_, size_t Size_)
    {
        auto oldProtect = ProtectMemory(ToAddress_, Size_, PMF_RWX);
        memcpy(ToAddress_, FromStorage_, Size_);
        ProtectMemory(ToAddress_, Size_, oldProtect);
    }

#ifdef WIN32
    static DWORD protectFlags2WinFlag(EProtectMemoryFlags Flags_)
    {
        switch (Flags_)
        {
        case PMF_R:
            return PAGE_READONLY;
        case PMF_W:
            return PAGE_WRITECOPY;
        case PMF_X:
            return PAGE_EXECUTE;
        case PMF_RW:
            return PAGE_READWRITE;
        case PMF_RX:
            return PAGE_EXECUTE_READ;
        case PMF_WX:
            return PAGE_READWRITE;
        case PMF_RWX:
            return PAGE_EXECUTE_READWRITE;
        default:
            assert(!"Unknown memory protection constant");
        }
        return 0;
    }

    static EProtectMemoryFlags winFlag2ProtectFlags(DWORD Flags_)
    {
        switch (Flags_)
        {
        case PAGE_READONLY:
            return PMF_R;
        case PAGE_WRITECOPY:
            return PMF_W;
        case PAGE_EXECUTE:
            return PMF_X;
        case PAGE_READWRITE:
            return PMF_RW;
        case PAGE_EXECUTE_READ:
            return PMF_RX;
        case PAGE_EXECUTE_WRITECOPY:
            return PMF_WX;
        case PAGE_EXECUTE_READWRITE:
            return PMF_RWX;
        default:
            assert(!"Unknown memory protection constant");
        }
        return PMF_Unknown;
    }
#endif

    EProtectMemoryFlags ProtectMemory(void* Where_, size_t Size_, EProtectMemoryFlags NewProtectType_)
    {
#ifdef WIN32
        DWORD dwOldProtect = 0;
        if (!VirtualProtect(Where_, Size_, protectFlags2WinFlag(NewProtectType_), &dwOldProtect))
        {
            assert(!"Unable to change protection of memory");
        }
        return winFlag2ProtectFlags(dwOldProtect);
#endif
    }
} // end namespace hooklib