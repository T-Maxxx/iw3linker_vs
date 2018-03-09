#pragma once
#include "hooklib/hooklib.h"
#include "utility/utility.h"
#include "types.h"

#define STREAM_OUT_SIZE 0x18000000
#define STREAM_SIZE 0x14000000
#define TEMP_STREAM_SIZE 0x8000000

namespace database
{
    extern hooklib::CGlobalVar<utility::byte*>& g_streamPosSave;
    extern hooklib::CGlobalVar<utility::byte*>& g_streamPosStart;
    extern hooklib::CGlobalVar<utility::byte*>& g_tempStreamPos;
    extern hooklib::CGlobalVar<utility::byte*>& g_tempStreamPosStart;
    extern hooklib::CGlobalVar<utility::byte*>& g_streamOut;
    extern hooklib::CGlobalVar<utility::byte*>& g_streamOutPos;
    extern hooklib::CGlobalVar<utility::byte*>& g_streamPos;
    extern hooklib::CGlobalVar<xfile_t*>& g_streamZoneMem;
    extern hooklib::CGlobalVar<utility::byte*>& g_sourcePos;
    extern hooklib::CGlobalVar<int>& g_streamPosIndex;
    extern hooklib::CGlobalVar<int>& g_streamDelayIndex;
    extern hooklib::CGlobalArr<int, 0x2000>& g_streamDelayArray;

    extern utility::byte* g_streamMemory;
    extern utility::byte* g_tempStreamMemory;
    extern utility::byte* g_streamOutMemory;
    extern int g_streamBlockSize[9];
}
