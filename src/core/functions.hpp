#pragma once
#include "hooks/native_function.hpp"

namespace core
{
    using FPComAssert = void(*)(const char *FilePath_, int Line_, int Unknown_, const char *MsgFormat_, ...);
    extern hooks::CNativeFunc<FPComAssert>& Com_Assert;
}
