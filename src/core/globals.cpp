#include "stdafx.h"
#include "globals.h"
#include "hooklib/hooklib.h"

using namespace hooklib;

namespace common
{
    CNativeFunc<FPComAssert>& Com_Assert = CNativeFunc<FPComAssert>::Create(0x0048E6A0, 0x0048E806);
}