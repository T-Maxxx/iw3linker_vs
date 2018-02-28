#include "stdafx.h"
#include "globals.h"
#include "hooklib/hooklib.h"

using namespace hooklib;

namespace common
{
    CNativeFunc<FPComAssert>& Com_Assert = CNativeFunc<FPComAssert>::CreateHook(0x0048E6A0);
}