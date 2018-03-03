#include "stdafx.h"
#include "globals.h"

using namespace utility;

namespace database
{
    byte* g_streamMemory = nullptr;
    byte* g_tempStreamMemory = nullptr;
    byte* g_streamOutMemory = nullptr;

    hooklib::CGlobalVar<utility::byte*>& g_tempStreamPos = hooklib::CGlobalVar<utility::byte*>::Create(0x00656960);
    hooklib::CGlobalVar<utility::byte*>& g_streamPosSave = hooklib::CGlobalVar<utility::byte*>::Create(0x0065675C);
    hooklib::CGlobalVar<utility::byte*>& g_streamPosStart = hooklib::CGlobalVar<utility::byte*>::Create(0x0065671C);
    hooklib::CGlobalVar<utility::byte*>& g_tempStreamPosStart = hooklib::CGlobalVar<utility::byte*>::Create(0x00656B74);
    hooklib::CGlobalVar<utility::byte*>& g_streamOut = hooklib::CGlobalVar<utility::byte*>::Create(0x00656754);
    hooklib::CGlobalVar<utility::byte*>& g_streamOutPos = hooklib::CGlobalVar<utility::byte*>::Create(0x00656750);
}
