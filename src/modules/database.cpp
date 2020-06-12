#include "database.hpp"

#include "hooks/replace_function.hpp"
#include "utility/macro.hpp"


namespace modules
{
    uint8_t* CDatabase::g_streamMemory = nullptr;
    uint8_t* CDatabase::g_tempStreamMemory = nullptr;
    uint8_t* CDatabase::g_streamOutMemory = nullptr;
    uint32_t CDatabase::g_streamBlockSize[core::MAX_XFILE_COUNT] = { 0x10000000, 0x10000000, 0x10000000, 0x10000000, 0x10000000, 0x10000000, 0x10000000, 0x2000000, 0x800000 };

    hooks::CGlobalVar<uint8_t*>& CDatabase::g_tempStreamPos = hooks::CGlobalVar<uint8_t*>::Create(0x00656960);
    hooks::CGlobalVar<uint8_t*>& CDatabase::g_streamPosSave = hooks::CGlobalVar<uint8_t*>::Create(0x0065675C);
    hooks::CGlobalVar<uint8_t*>& CDatabase::g_streamPosStart = hooks::CGlobalVar<uint8_t*>::Create(0x0065671C);
    hooks::CGlobalVar<uint8_t*>& CDatabase::g_tempStreamPosStart = hooks::CGlobalVar<uint8_t*>::Create(0x00656B74);
    hooks::CGlobalVar<uint8_t*>& CDatabase::g_streamOut = hooks::CGlobalVar<uint8_t*>::Create(0x00656754);
    hooks::CGlobalVar<uint8_t*>& CDatabase::g_streamOutPos = hooks::CGlobalVar<uint8_t*>::Create(0x00656750);
    hooks::CGlobalVar<uint8_t*>& CDatabase::g_streamPos = hooks::CGlobalVar<uint8_t*>::Create(0x118A54B8);
    hooks::CGlobalVar<core::xfile_t*>& CDatabase::g_streamZoneMem = hooks::CGlobalVar<core::xfile_t*>::Create(0x118A54AC);
    hooks::CGlobalVar<uint8_t*>& CDatabase::g_sourcePos = hooks::CGlobalVar<uint8_t*>::Create(0x00656724);
    hooks::CGlobalVar<int>& CDatabase::g_streamPosIndex = hooks::CGlobalVar<int>::Create(0x118A54E4);
    hooks::CGlobalVar<int>& CDatabase::g_streamDelayIndex = hooks::CGlobalVar<int>::Create(0x118A54B4);
    hooks::CGlobalArr<int, 0x2000>& CDatabase::g_streamDelayArray = hooks::CGlobalArr<int, 0x2000>::Create(0x118A54E8);
    hooks::CGlobalVar<uint32_t>& CDatabase::g_streamSize = hooks::CGlobalVar<uint32_t>::Create(0x118A54BC);
    hooks::CGlobalArr<uint8_t*, core::MAX_XFILE_COUNT>& CDatabase::g_streamBlockMem = hooks::CGlobalArr<uint8_t*, core::MAX_XFILE_COUNT>::Create(0x118A54C0);
    hooks::CGlobalVar<uint32_t>& CDatabase::g_streamPosStackIndex = hooks::CGlobalVar<uint32_t>::Create(0x118A54A8);

    void CDatabase::InitGlobals() const
    {
        // This globals are just marked to track hooks interceptions.
        //hooks::CGlobalVar<uint8_t*>::Create(0x0065696C); // g_streamMemory
        //hooks::CGlobalVar<uint8_t*>::Create(0x00656968); // g_tempStreamMemory
        //hooks::CGlobalVar<uint8_t*>::Create(0x00656B70); // g_streamOutMemory
        //hooks::CGlobalArr<uint32_t, 9>::Create(0x005109F8); // g_streamBlockSize
    }

    //static bool g_bPatchedAlloc = false;
    static uint8_t g_HeapMem[STREAM_OUT_SIZE + STREAM_SIZE + TEMP_STREAM_SIZE];

    void CDatabase::DB_ReserveStreamMemory()
    {
        g_streamOutMemory = g_HeapMem;
        g_streamMemory = g_streamOutMemory + STREAM_OUT_SIZE;
        g_tempStreamMemory = g_streamMemory + STREAM_SIZE;
    }

    void CDatabase::DB_ReleaseStreamMemory()
    {
        g_streamOutMemory = nullptr;
        g_tempStreamMemory = nullptr;
        g_streamMemory = nullptr;
    }

    void CDatabase::DB_InitStream()
    {
        QASSERT(!g_streamPosStart);
        QASSERT(g_streamMemory);

        g_streamPosSave = g_streamMemory;
        g_streamPosStart = g_streamMemory;
    }

    void CDatabase::DB_InitTempStream()
    {
        QASSERT(!g_tempStreamPosStart);
        QASSERT(g_tempStreamMemory);

        g_tempStreamPosStart = g_tempStreamMemory;
        g_tempStreamPos = g_tempStreamMemory;
    }

    void CDatabase::DB_InitOutStream()
    {

        QASSERT(!g_streamOut);
        QASSERT(g_streamOutMemory);

        g_streamOut = g_streamOutMemory;
        g_streamOutPos = g_streamOutMemory;
    }

    void CDatabase::DB_FreeStream()
    {
        QASSERT(g_streamPosStart == g_streamMemory);

        g_streamPosStart = 0;
        g_streamPosSave = 0;
    }

    void CDatabase::DB_FreeTempStream()
    {
        QASSERT(g_tempStreamPosStart == g_tempStreamMemory);

        g_tempStreamPosStart = 0;
        g_tempStreamPos = 0;
    }

    void CDatabase::DB_FreeOutStream()
    {
        QASSERT(g_streamOut == g_streamOutMemory);

        g_streamOut = 0;
    }

    uint8_t* CDatabase::DB_AllocTempStream(int Size_)
    {
        QASSERT(g_tempStreamPos);
        QASSERT(g_tempStreamPos >= g_tempStreamPosStart);
        QASSERT(g_tempStreamPos + Size_ <= g_tempStreamPosStart + TEMP_STREAM_SIZE);

        uint8_t* pMem = g_tempStreamPos;
        g_tempStreamPos += Size_;
        return pMem;
    }

    void CDatabase::DB_ResetTempStream()
    {
        QASSERT(g_tempStreamPosStart);

        g_tempStreamPos = g_tempStreamPosStart;
    }

    void CDatabase::DB_AllocStreamOut(uint8_t StreamIndex_, uint8_t* Src_, size_t Size_, uint8_t** Dst_)
    {
        if (!StreamIndex_)
            return;

        if (Size_)
        {
            QASSERT(Size_ > 0);
            // Cur size + requested size <= max size;
            QASSERTFMT((uint32_t)((DB_GetStreamPos() - g_streamZoneMem.Raw()->blocks[g_streamPosIndex.Raw()].data) + Size_) <= g_streamBlockSize[g_streamPosIndex],
                "Attempt to overflow stream memory block\n\tRequested size: %d\n\tStream index: %d", Size_, g_streamPosIndex.Raw());

            if ((unsigned int)(g_streamPosIndex - 1) < 3)
            {
                *Dst_ = nullptr;
                if (g_streamPosIndex != 1)
                {
                    QASSERTFMT(g_streamDelayIndex < 0x1000, "g_streamDelayIndex doesn't index ARRAY_COUNT( g_streamDelayArray )\n\t%i not in [0, %i)", g_streamDelayIndex.Raw(), 4096);
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

    uint8_t* CDatabase::DB_AllocStreamPosSave(int Size_)
    {
        QASSERT(g_streamPosSave);
        QASSERT(g_streamPosSave >= g_streamPosStart);
        QASSERT(g_streamPosSave + Size_ <= g_streamPosStart + STREAM_SIZE);

        uint8_t* result = g_streamPosSave;
        g_streamPosSave += Size_;
        return result;
    }

    uint8_t* CDatabase::DB_GetStreamPos()
    {
        return g_streamPos;
    }

    void CDatabase::DB_IncStreamPos(int Size_)
    {
        QASSERT(g_streamPos);
        g_streamPos += Size_;
    }

    void CDatabase::DB_InitXFile(core::xfile_t* pXFile_)
    {
        memset(pXFile_, 0, sizeof(core::xfile_t));
        uint32_t size = 4096;
        for (int i = 0; i < core::MAX_XFILE_COUNT; ++i)
        {
            pXFile_->blocks[i].data = (uint8_t*)size;
            size += g_streamBlockSize[i];
            QASSERT(pXFile_->blocks[i].data);
        }
    }

    void CDatabase::DB_UpdateXFileSizes()
    {
        QASSERT(!g_streamPosIndex);

        g_streamZoneMem.Raw()->blocks[0].size = g_streamSize;
        QASSERT(g_streamZoneMem.Raw()->blocks[core::XFILE_BLOCK_TEMP].size <= g_streamBlockSize[core::XFILE_BLOCK_TEMP]);

        for (int i = 1; i < core::MAX_XFILE_COUNT; ++i)
        {
            g_streamZoneMem.Raw()->blocks[i].size = (uint32_t)g_streamBlockMem[i] - (uint32_t)g_streamZoneMem.Raw()->blocks[i].data;
            QASSERT(g_streamZoneMem.Raw()->blocks[i].size <= g_streamBlockSize[i]);
        }
    }

    void CDatabase::DB_InitZoneMem(core::xfile_t* pXFile_)
    {
        g_streamZoneMem = pXFile_;
        g_streamPos = pXFile_->blocks[0].data;
        g_streamPosIndex = 0;
        g_streamDelayIndex = 0;
        g_streamSize = 0;
        g_streamPosStackIndex = 0;
        for (int i = 0; i < core::MAX_XFILE_COUNT; ++i)
            g_streamBlockMem[i] = pXFile_->blocks[i].data;
    }

    void CDatabase::Patch() const
    {
        hooks::CReplaceFunc::Create(0x0044B270, 0x0044B329, DB_ReserveStreamMemory);
        hooks::CReplaceFunc::Create(0x0044B330, 0x0044B385, DB_ReleaseStreamMemory);

        hooks::CReplaceFunc::Create(0x0044B390, 0x0044B3EC, DB_InitStream);
        hooks::CReplaceFunc::Create(0x0044B3F0, 0x0044B477, DB_InitTempStream);
        hooks::CReplaceFunc::Create(0x0044AB00, 0x0044AB7D, DB_InitOutStream);

        hooks::CReplaceFunc::Create(0x0044B480, 0x0044B4D3, DB_FreeStream);
        hooks::CReplaceFunc::Create(0x0044B4E0, 0x0044B533, DB_FreeTempStream);
        hooks::CReplaceFunc::Create(0x0044AB80, 0x0044ABC9, DB_FreeOutStream);

        hooks::CReplaceFunc::Create(0x0044B120, 0x0044B21D, DB_AllocTempStream);
        hooks::CReplaceFunc::Create(0x0044ABD0, 0x0044AD76, DB_AllocStreamOut);
        hooks::CReplaceFunc::Create(0x0044B020, 0x0044B11D, DB_AllocStreamPosSave);

        hooks::CReplaceFunc::Create(0x0044B220, 0x0044B266, DB_ResetTempStream);

        hooks::CReplaceFunc::Create(0x0049EE50, 0x0049EE55, DB_GetStreamPos);
        hooks::CReplaceFunc::Create(0x0049EE80, 0x0049EEBD, DB_IncStreamPos);

        hooks::CReplaceFunc::Create(0x0044A9D0, 0x0044AA29, DB_InitXFile);
        hooks::CReplaceFunc::Create(0x0044AA30, 0x0044AAF0, DB_UpdateXFileSizes);

        hooks::CReplaceFunc::Create(0x0049EC60, 0x0049ECDE, DB_InitZoneMem);
    }
}
