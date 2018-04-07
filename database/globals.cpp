#include "stdafx.h"
#include "globals.h"

using namespace utility;
using namespace hooklib;

namespace database
{
    byte* g_streamMemory = nullptr;
    byte* g_tempStreamMemory = nullptr;
    byte* g_streamOutMemory = nullptr;
    uint g_streamBlockSize[MAX_XFILE_COUNT] = { 0x10000000,0x10000000,0x10000000,0x10000000,0x10000000,0x10000000,0x10000000, 0x2000000, 0x800000};

    CGlobalVar<byte*>& g_tempStreamPos = CGlobalVar<byte*>::Create(0x00656960);
    CGlobalVar<byte*>& g_streamPosSave = CGlobalVar<byte*>::Create(0x0065675C);
    CGlobalVar<byte*>& g_streamPosStart = CGlobalVar<byte*>::Create(0x0065671C);
    CGlobalVar<byte*>& g_tempStreamPosStart = CGlobalVar<byte*>::Create(0x00656B74);
    CGlobalVar<byte*>& g_streamOut = CGlobalVar<byte*>::Create(0x00656754);
    CGlobalVar<byte*>& g_streamOutPos = CGlobalVar<byte*>::Create(0x00656750);
    CGlobalVar<byte*>& g_streamPos = CGlobalVar<byte*>::Create(0x118A54B8);
    CGlobalVar<xfile_t*> & g_streamZoneMem = CGlobalVar<xfile_t*>::Create(0x118A54AC);
    CGlobalVar<byte*>& g_sourcePos = CGlobalVar<byte*>::Create(0x00656724);
    CGlobalVar<int>& g_streamPosIndex = CGlobalVar<int>::Create(0x118A54E4);
    CGlobalVar<int>& g_streamDelayIndex = CGlobalVar<int>::Create(0x118A54B4);
    CGlobalArr<int, 0x2000>& g_streamDelayArray = CGlobalArr<int, 0x2000>::Create(0x118A54E8);
    CGlobalVar<uint>& g_streamSize = CGlobalVar<uint>::Create(0x118A54BC);
    CGlobalArr<uint, MAX_XFILE_COUNT>& g_streamBlockMem = CGlobalArr<uint, MAX_XFILE_COUNT>::Create(0x118A54C0);
}
