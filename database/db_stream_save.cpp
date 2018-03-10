#include "stdafx.h"
#include "db_stream_save.h"
#include "globals.h"
#include "common/common.h"

using namespace common;
using namespace utility;

namespace database
{
    static bool g_bPatchedAlloc = false;
    static byte g_HeapMem[STREAM_OUT_SIZE + STREAM_SIZE + TEMP_STREAM_SIZE];

    void DB_ReserveStreamMemory()
    {
#pragma region One block allocation
#if 0
        // Try to reserve all possible size in one piece: around 800 mb.
        byte* pMem = static_cast<byte*>(VirtualAlloc(nullptr, STREAM_OUT_SIZE + STREAM_SIZE + TEMP_STREAM_SIZE, MEM_RESERVE, PAGE_READWRITE));
        if (pMem)
        {
            g_streamOutMemory = pMem;
            g_streamMemory = g_streamOutMemory + STREAM_OUT_SIZE;
            g_tempStreamMemory = g_streamMemory + STREAM_SIZE;
            g_bPatchedAlloc = true;
            return;
    }
#endif
#pragma endregion

#pragma region Original allocation
#if 0
        g_bPatchedAlloc = false; // I don't actually know if this code can be called more than once.

        // Oops, we failed. Let's fall back to original code.
        g_streamOutMemory = static_cast<byte*>(VirtualAlloc(0, STREAM_OUT_SIZE, MEM_RESERVE, PAGE_READWRITE));
        QASSERTMSG(g_streamOutMemory, "VirtualAlloc returned NULL; may be out of memory");

        g_streamMemory = static_cast<byte*>(VirtualAlloc(0, STREAM_SIZE, MEM_RESERVE, PAGE_READWRITE));
        QASSERTMSG(g_streamMemory, "VirtualAlloc returned NULL; may be out of memory");

        g_tempStreamMemory = static_cast<byte*>(VirtualAlloc(0, TEMP_STREAM_SIZE, MEM_RESERVE, PAGE_READWRITE));
        QASSERTMSG(g_tempStreamMemory, "VirtualAlloc returned NULL; may be out of memory");
#endif
#pragma endregion

#pragma region Static allocation
        g_streamOutMemory = g_HeapMem;
        g_streamMemory = g_streamOutMemory + STREAM_OUT_SIZE;
        g_tempStreamMemory = g_streamMemory + STREAM_SIZE;
        g_bPatchedAlloc = true;
#pragma endregion
    }

    void DB_ReleaseStreamMemory()
    {
#pragma region Original allocation
#if 0
        VirtualFree(g_streamOutMemory, 0, MEM_RELEASE);

#pragma region One block allocation
        // If we're reserving memory by patch logic then no additional release required.
        // Otherwise we have to free other two data blocks.
        if (!g_bPatchedAlloc)
        {
            VirtualFree(g_tempStreamMemory, 0, MEM_RELEASE);
            VirtualFree(g_streamMemory, 0, MEM_RELEASE);
        }
#pragma endregion
#endif
#pragma endregion

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

    void DB_FreeStream()
    {
        QASSERT(g_streamPosStart == g_streamMemory);

#pragma region Original allocation
#if 0
        VirtualFree(g_streamMemory, STREAM_SIZE, MEM_DECOMMIT);
#endif
#pragma endregion

        g_streamPosStart = 0;
        g_streamPosSave = 0;
    }

    void DB_FreeTempStream()
    {
        QASSERT(g_tempStreamPosStart == g_tempStreamMemory);

#pragma region Original allocation
#if 0
        VirtualFree(g_tempStreamMemory, TEMP_STREAM_SIZE, MEM_DECOMMIT);
#endif
#pragma endregion

        g_tempStreamPosStart = 0;
        g_tempStreamPos = 0;
    }

    void DB_FreeOutStream()
    {
        QASSERT(g_streamOut == g_streamOutMemory);

#pragma region Original allocation
#if 0
        VirtualFree(g_streamOutMemory, STREAM_OUT_SIZE, MEM_DECOMMIT);
#endif
#pragma endregion

        g_streamOut = 0;
    }

    byte* DB_AllocTempStream(int Size_)
    {
        QASSERT(g_tempStreamPos);
        QASSERT(g_tempStreamPos >= g_tempStreamPosStart);
        QASSERT(g_tempStreamPos + Size_ <= g_tempStreamPosStart + TEMP_STREAM_SIZE);

#pragma region Original allocation
#if 0
        unsigned int startPage = PAGE_ROUNDUP((unsigned int)g_tempStreamPos.Raw());
        unsigned int endPage = PAGE_ROUNDUP((unsigned int)g_tempStreamPos.Raw() + Size_);
        if (startPage != endPage)
        {
            LPVOID buf = VirtualAlloc(reinterpret_cast<LPVOID>(startPage), endPage - startPage, MEM_COMMIT, PAGE_READWRITE);
            QASSERT(buf);
        }
#endif
#pragma endregion

        byte* pMem = g_tempStreamPos;
        g_tempStreamPos += Size_;
        return pMem;
    }

    void DB_ResetTempStream()
    {
        QASSERT(g_tempStreamPosStart);

#pragma region Original allocation
#if 0
        VirtualFree(g_tempStreamPosStart, TEMP_STREAM_SIZE - (g_tempStreamPosStart - g_tempStreamMemory), MEM_DECOMMIT);
#endif
#pragma endregion

        g_tempStreamPos = g_tempStreamPosStart;
    }

    void DB_AllocStreamOut(byte StreamIndex_, byte* Src_, size_t Size_, byte** Dst_)
    {
        if (!StreamIndex_)
            return;

        if (Size_)
        {
            QASSERT(Size_ > 0);
            // Cur size + requested size <= max size;
            QASSERTFMT((DB_GetStreamPos() + Size_) - g_streamZoneMem.Raw()->blocks[g_streamPosIndex.Raw()].data <= g_streamBlockSize[g_streamPosIndex], "Attempt to overflow stream memory block\n\tRequested size: %d\n\tStream index: %d", Size_, g_streamZoneMem);

            if ((unsigned int)(g_streamPosIndex - 1) < 3)
            {
                *Dst_ = nullptr;
                if (g_streamPosIndex != 1)
                {
                    QASSERTFMT(g_streamDelayIndex < 0x1000, "g_streamDelayIndex doesn't index ARRAY_COUNT( g_streamDelayArray )\n\t%i not in [0, %i)", g_streamDelayIndex, 4096);
                    g_streamDelayArray[2 * g_streamDelayIndex] = (int)Src_;
                    g_streamDelayArray[2 * g_streamDelayIndex + 1] = Size_;
                    g_streamDelayIndex += 1;
                }
            }
            else
            {
                QASSERT((g_streamOutPos + Size_) - g_streamOut <= STREAM_OUT_SIZE);

#pragma region Original allocation
#if 0
                uint startPage = PAGE_ROUNDUP((uint)g_streamOutPos.Raw());
                uint endPage = PAGE_ROUNDUP((uint)g_streamOutPos.Raw() + Size_);
                if (startPage != endPage)
                {
                    LPVOID buf = VirtualAlloc((LPVOID)startPage, endPage - startPage, MEM_COMMIT, PAGE_READWRITE);
                    QASSERT(buf);
                }
#endif
#pragma endregion

                memcpy(g_streamOutPos, Src_, Size_);
                *Dst_ = g_streamOutPos;
                g_streamOutPos += Size_;
            }
            DB_IncStreamPos(Size_);
        }
        g_sourcePos = Src_ + Size_;

    }

    utility::byte* DB_AllocStreamPosSave(int Size_)
    {
        QASSERT(g_streamPosSave);
        QASSERT(g_streamPosSave >= g_streamPosStart);
        QASSERT(g_streamPosSave + Size_ <= g_streamPosStart + STREAM_SIZE);

#pragma region Original allocation
#if 0
        uint startPage = PAGE_ROUNDUP((uint)g_streamPosSave.Raw());
        uint endPage = PAGE_ROUNDUP((uint)g_streamPosSave.Raw() + Size_);
        if (startPage != endPage)
        {
            auto buf = VirtualAlloc((LPVOID)startPage, endPage - startPage, MEM_COMMIT, PAGE_READWRITE);
            QASSERT(buf);
        }
#endif
#pragma endregion

        byte* result = g_streamPosSave;
        g_streamPosSave += Size_;
        return result;
    }

    byte* DB_GetStreamPos()
    {
        return g_streamPos;
    }

    void DB_IncStreamPos(int Size_)
    {
        QASSERT(g_streamPos);
        g_streamPos += Size_;
    }
}