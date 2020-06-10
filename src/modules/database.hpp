#pragma once
#include "module.hpp"
#include "hooks/global_variable.hpp"
#include "hooks/global_array.hpp"
#include "core/structs.hpp"

namespace core { struct xfile_t; }

#define STREAM_OUT_SIZE 0x18000000
#define STREAM_SIZE 0x14000000
#define TEMP_STREAM_SIZE 0x8000000

namespace modules
{
    class CDatabase : public CModule
    {
    public:
        void InitGlobals() const override final;
        void Patch() const override final;

    public:
        static void DB_ReserveStreamMemory();
        static void DB_ReleaseStreamMemory();

        static void DB_InitStream();
        static void DB_InitTempStream();
        static void DB_InitOutStream();

        static void DB_FreeStream();
        static void DB_FreeTempStream();
        static void DB_FreeOutStream();

        static uint8_t* DB_AllocTempStream(int Size_);
        static void DB_AllocStreamOut(uint8_t StreamIndex_, uint8_t* Src_, size_t Size_, uint8_t** Dst_);
        static uint8_t* DB_AllocStreamPosSave(int Size_);

        static void DB_ResetTempStream();

        static uint8_t* DB_GetStreamPos();
        static void DB_IncStreamPos(int Size_);

        static void DB_InitXFile(core::xfile_t* pXFile_);
        static void DB_UpdateXFileSizes();

        static void DB_InitZoneMem(core::xfile_t* pXFile_);

    public:
        static hooks::CGlobalVar<uint8_t*>& g_streamPosSave;
        static hooks::CGlobalVar<uint8_t*>& g_streamPosStart;
        static hooks::CGlobalVar<uint8_t*>& g_tempStreamPos;
        static hooks::CGlobalVar<uint8_t*>& g_tempStreamPosStart;
        static hooks::CGlobalVar<uint8_t*>& g_streamOut;
        static hooks::CGlobalVar<uint8_t*>& g_streamOutPos;
        static hooks::CGlobalVar<uint8_t*>& g_streamPos;
        static hooks::CGlobalVar<core::xfile_t*>& g_streamZoneMem;
        static hooks::CGlobalVar<uint8_t*>& g_sourcePos;
        static hooks::CGlobalVar<int>& g_streamPosIndex;
        static hooks::CGlobalVar<int>& g_streamDelayIndex;
        static hooks::CGlobalArr<int, 0x2000>& g_streamDelayArray;
        static hooks::CGlobalVar<uint32_t>& g_streamSize;
        static hooks::CGlobalArr<uint8_t*, core::MAX_XFILE_COUNT>& g_streamBlockMem;
        static hooks::CGlobalVar<uint32_t>& g_streamPosStackIndex;

        static uint8_t* g_streamMemory;
        static uint8_t* g_tempStreamMemory;
        static uint8_t* g_streamOutMemory;
        static uint32_t g_streamBlockSize[core::MAX_XFILE_COUNT];
    };
}
