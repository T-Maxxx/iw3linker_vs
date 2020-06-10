#include "functions.hpp"

namespace core
{
    hooks::CNativeFunc<FPComAssert>& Com_Assert = hooks::CNativeFunc<FPComAssert>::Create(0x0048E6A0, 0x0048E806);
}
