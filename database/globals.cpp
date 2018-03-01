#include "stdafx.h"
#include "globals.h"

namespace database
{
    hooklib::CGlobalVar<void*>& g_streamMemory = hooklib::CGlobalVar<void*>::Create(0x0065696C);
    hooklib::CGlobalVar<void*>& g_tempStreamMemory = hooklib::CGlobalVar<void*>::Create(0x00656968);
    hooklib::CGlobalVar<void*>& g_streamOutMemory = hooklib::CGlobalVar<void*>::Create(0x00656B70);
}
