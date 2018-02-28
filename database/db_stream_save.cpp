#include "stdafx.h"
#include "db_stream_save.h"
#include "globals.h"
#include "common/common.h"

using namespace common;

namespace database
{
    void _cdecl DB_InitStream()
    {
        g_streamMemory = VirtualAlloc(0, 0x14000000u, MEM_RESERVE, PAGE_READWRITE);
        if (!g_streamMemory)
            Com_Assert.Invoke("C:\\trees\\cod3-pc\\cod3-modtools\\cod3src\\src\\database\\db_stream_save.cpp",
                502,
                0,
                "%s\n\t(\"VirtualAlloc returned NULL; may be out of memory\") = %s",
                "(g_streamMemory)",
                "VirtualAlloc returned NULL; may be out of memory");

        g_tempStreamMemory = VirtualAlloc(0, 0x8000000u, MEM_RESERVE, PAGE_READWRITE);
        if (!g_tempStreamMemory)
            Com_Assert.Invoke("C:\\trees\\cod3-pc\\cod3-modtools\\cod3src\\src\\database\\db_stream_save.cpp",
                505,
                0,
                "%s\n\t(\"VirtualAlloc returned NULL; may be out of memory\") = %s",
                "(g_tempStreamMemory)",
                "VirtualAlloc returned NULL; may be out of memory");

        g_streamOutMemory = VirtualAlloc(0, 0x18000000u, MEM_RESERVE, PAGE_READWRITE);
        if (!g_streamOutMemory)
            Com_Assert.Invoke("C:\\trees\\cod3-pc\\cod3-modtools\\cod3src\\src\\database\\db_stream_save.cpp",
                508,
                0,
                "%s\n\t(\"VirtualAlloc returned NULL; may be out of memory\") = %s",
                "(g_streamOutMemory)",
                "VirtualAlloc returned NULL; may be out of memory");
    }
}