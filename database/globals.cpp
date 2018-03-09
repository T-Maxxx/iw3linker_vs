#include "stdafx.h"
#include "globals.h"

using namespace utility;

namespace database
{
    byte* g_streamMemory = nullptr;
    byte* g_tempStreamMemory = nullptr;
    byte* g_streamOutMemory = nullptr;
    int g_streamBlockSize[9] = { 0x10000000,0x10000000,0x10000000,0x10000000,0x10000000,0x10000000,0x10000000, 0x2000000, 0x800000 };

    hooklib::CGlobalVar<utility::byte*>& g_tempStreamPos = hooklib::CGlobalVar<utility::byte*>::Create(0x00656960);
    hooklib::CGlobalVar<utility::byte*>& g_streamPosSave = hooklib::CGlobalVar<utility::byte*>::Create(0x0065675C);
    hooklib::CGlobalVar<utility::byte*>& g_streamPosStart = hooklib::CGlobalVar<utility::byte*>::Create(0x0065671C);
    hooklib::CGlobalVar<utility::byte*>& g_tempStreamPosStart = hooklib::CGlobalVar<utility::byte*>::Create(0x00656B74);
    hooklib::CGlobalVar<utility::byte*>& g_streamOut = hooklib::CGlobalVar<utility::byte*>::Create(0x00656754);
    hooklib::CGlobalVar<utility::byte*>& g_streamOutPos = hooklib::CGlobalVar<utility::byte*>::Create(0x00656750);
    hooklib::CGlobalVar<utility::byte*>& g_streamPos = hooklib::CGlobalVar<utility::byte*>::Create(0x118A54B8);
    hooklib::CGlobalVar<xfile_t*> & g_streamZoneMem = hooklib::CGlobalVar<xfile_t*>::Create(0x118A54AC);
    hooklib::CGlobalVar<utility::byte*>& g_sourcePos = hooklib::CGlobalVar<utility::byte*>::Create(0x00656724);
    hooklib::CGlobalVar<int>& g_streamPosIndex = hooklib::CGlobalVar<int>::Create(0x118A54E4);
    hooklib::CGlobalVar<int>& g_streamDelayIndex = hooklib::CGlobalVar<int>::Create(0x118A54B4);
    hooklib::CGlobalArr<int, 0x2000>& g_streamDelayArray = hooklib::CGlobalArr<int, 0x2000>::Create(0x118A54E8);
}
