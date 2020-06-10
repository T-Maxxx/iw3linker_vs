#pragma once
#include <hooklib\hooklib.h>

namespace common
{
    using FPComAssert = void(*)(const char *FilePath_, int Line_, int Unknown_, const char *MsgFormat_, ...);

    extern hooklib::CNativeFunc<FPComAssert>& Com_Assert;
}
