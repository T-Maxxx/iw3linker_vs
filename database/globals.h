#pragma once
#include "hooklib/hooklib.h"

namespace database
{
    extern hooklib::CGlobalVar<void*>& g_streamMemory;
    extern hooklib::CGlobalVar<void*>& g_tempStreamMemory;
    extern hooklib::CGlobalVar<void*>& g_streamOutMemory;
}
