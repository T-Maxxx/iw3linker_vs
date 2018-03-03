#include "stdafx.h"
#include "db_stream_save.h"
#include "globals.h"
#include "common/common.h"
#include "utility/utility.h"

using namespace common;
using namespace utility;

namespace database
{
    static bool g_bPatchedAlloc = false;

    void DB_ReserveStreamMemory()
    {
        // Try to reserver all possible size in one piece: around 800 mb.
        byte* pMem = static_cast<byte*>(VirtualAlloc(nullptr, STREAM_OUT_SIZE + STREAM_SIZE + TEMP_STREAM_SIZE, MEM_RESERVE, PAGE_READWRITE));
        if (pMem)
        {
            g_streamOutMemory = pMem;
            g_streamMemory = g_streamOutMemory + STREAM_OUT_SIZE;
            g_tempStreamMemory = g_streamMemory + STREAM_SIZE;
            g_bPatchedAlloc = true;
            return;
        }
        
        g_bPatchedAlloc = false; // I don't actually know if this code can be called more than once.

        // Oops, we failed. Let's fall back to original code.
        g_streamOutMemory = static_cast<byte*>(VirtualAlloc(0, STREAM_OUT_SIZE, MEM_RESERVE, PAGE_READWRITE));
        QASSERTMSG(g_streamOutMemory, "VirtualAlloc returned NULL; may be out of memory");

        g_streamMemory = static_cast<byte*>(VirtualAlloc(0, STREAM_SIZE, MEM_RESERVE, PAGE_READWRITE));
        QASSERTMSG(g_streamMemory, "VirtualAlloc returned NULL; may be out of memory");

        g_tempStreamMemory = static_cast<byte*>(VirtualAlloc(0, TEMP_STREAM_SIZE, MEM_RESERVE, PAGE_READWRITE));
        QASSERTMSG(g_tempStreamMemory, "VirtualAlloc returned NULL; may be out of memory");
    }

    void DB_ReleaseStreamMemory()
    {
        VirtualFree(g_streamOutMemory, 0, MEM_RELEASE);
        // If we're reserving memory by patch logic then no additional release required.
        // Otherwise we have to free other two data blocks.
        if (!g_bPatchedAlloc)
        {
            VirtualFree(g_tempStreamMemory, 0, MEM_RELEASE);
            VirtualFree(g_streamMemory, 0, MEM_RELEASE);
        }

        g_streamOutMemory = 0;
        g_tempStreamMemory = 0;
        g_streamMemory = 0;
    }

    void DB_InitStream()
    {
        QASSERT(!g_streamPosStart);
        QASSERT(g_streamMemory);

        g_streamPosSave = g_streamMemory;
        g_streamPosStart = g_streamMemory;
    }

    void DB_InitTempStream()
    {
        QASSERT(!g_tempStreamPosStart);
        QASSERT(g_tempStreamMemory);

        g_tempStreamPosStart = g_tempStreamMemory;
        g_tempStreamPos = g_tempStreamMemory;
    }

    void DB_InitOutStream()
    {

        QASSERT(!g_streamOut);
        QASSERT(g_streamOutMemory);

        g_streamOut = g_streamOutMemory;
        g_streamOutPos = g_streamOutMemory;
    }

    void DB_ClearStream()
    {
        QASSERT(g_streamPosStart == g_streamMemory);

        VirtualFree(g_streamMemory, STREAM_SIZE, MEM_DECOMMIT);
        g_streamPosStart = 0;
        g_streamPosSave = 0;
    }

    void DB_ClearTempStream()
    {
        QASSERT(g_tempStreamPosStart == g_tempStreamMemory);

        VirtualFree(g_tempStreamMemory, TEMP_STREAM_SIZE, MEM_DECOMMIT);
        g_tempStreamPosStart = 0;
        g_tempStreamPos = 0;
    }

    void DB_ClearOutStream()
    {
        QASSERT(g_streamOut == g_streamOutMemory);

        VirtualFree(g_streamOutMemory, STREAM_OUT_SIZE, MEM_DECOMMIT);
        g_streamOut = 0;
    }
}