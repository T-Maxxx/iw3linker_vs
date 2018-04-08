#include "stdafx.h"
#include "db_stream_save.h"
#include "globals.h"
#include "common/common.h"

using namespace common;
using namespace utility;

namespace database
{
    //static bool g_bPatchedAlloc = false;
    static byte g_HeapMem[STREAM_OUT_SIZE + STREAM_SIZE + TEMP_STREAM_SIZE];

    void DB_ReserveStreamMemory()
    {
        g_streamOutMemory = g_HeapMem;
        g_streamMemory = g_streamOutMemory + STREAM_OUT_SIZE;
        g_tempStreamMemory = g_streamMemory + STREAM_SIZE;
    }

    void DB_ReleaseStreamMemory()
    {
        g_streamOutMemory = nullptr;
        g_tempStreamMemory = nullptr;
        g_streamMemory = nullptr;
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

        g_streamPosStart = 0;
        g_streamPosSave = 0;
    }

    void DB_FreeTempStream()
    {
        QASSERT(g_tempStreamPosStart == g_tempStreamMemory);

        g_tempStreamPosStart = 0;
        g_tempStreamPos = 0;
    }

    void DB_FreeOutStream()
    {
        QASSERT(g_streamOut == g_streamOutMemory);

        g_streamOut = 0;
    }

    byte* DB_AllocTempStream(int Size_)
    {
        QASSERT(g_tempStreamPos);
        QASSERT(g_tempStreamPos >= g_tempStreamPosStart);
        QASSERT(g_tempStreamPos + Size_ <= g_tempStreamPosStart + TEMP_STREAM_SIZE);

        byte* pMem = g_tempStreamPos;
        g_tempStreamPos += Size_;
        return pMem;
    }

    void DB_ResetTempStream()
    {
        QASSERT(g_tempStreamPosStart);

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
            QASSERTFMT((uint)((DB_GetStreamPos() + Size_) - g_streamZoneMem.Raw()->blocks[g_streamPosIndex.Raw()].data) <= g_streamBlockSize[g_streamPosIndex],
                "Attempt to overflow stream memory block\n\tRequested size: %d\n\tStream index: %d", Size_, g_streamPosIndex.Raw());

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

                memcpy(g_streamOutPos, Src_, Size_);
                *Dst_ = g_streamOutPos;
                g_streamOutPos += Size_;
            }
            DB_IncStreamPos(Size_);
        }
        g_sourcePos = Src_ + Size_;

    }

    byte* DB_AllocStreamPosSave(int Size_)
    {
        QASSERT(g_streamPosSave);
        QASSERT(g_streamPosSave >= g_streamPosStart);
        QASSERT(g_streamPosSave + Size_ <= g_streamPosStart + STREAM_SIZE);

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

    void DB_InitXFile(xfile_t *pXFile_)
    {
        memset(pXFile_, 0, sizeof(xfile_t));
        uint size = 4096;
        for (int i = 0; i < MAX_XFILE_COUNT; ++i)
        {
            pXFile_->blocks[i].data = (byte *)size;
            size += g_streamBlockSize[i];
            QASSERT(pXFile_->blocks[i].data);
        }
    }

    void DB_UpdateXFileSizes()
    {
        QASSERT(!g_streamPosIndex);

        g_streamZoneMem.Raw()->blocks[0].size = g_streamSize;
        QASSERT(g_streamZoneMem.Raw()->blocks[XFILE_BLOCK_TEMP].size <= g_streamBlockSize[XFILE_BLOCK_TEMP]);

        for (int i = 1; i < MAX_XFILE_COUNT; ++i)
        {
            g_streamZoneMem.Raw()->blocks[i].size = (uint)g_streamBlockMem[i] - (uint)g_streamZoneMem.Raw()->blocks[i].data;
            QASSERT(g_streamZoneMem.Raw()->blocks[i].size <= g_streamBlockSize[i]);
        }
    }

    void DB_InitZoneMem(xfile_t *pXFile_)
    {
        g_streamZoneMem = pXFile_;
        g_streamPos = pXFile_->blocks[0].data;
        g_streamPosIndex = 0;
        g_streamDelayIndex = 0;
        g_streamSize = 0;
        g_streamPosStackIndex = 0;
        for (int i = 0; i < MAX_XFILE_COUNT; ++i)
            g_streamBlockMem[i] = pXFile_->blocks[i].data;
    }
}