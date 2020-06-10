#include "functions.hpp"

namespace core
{
    hooks::CNativeFunc<Com_Assert_t>& Com_Assert = hooks::CNativeFunc<Com_Assert_t>::Create(0x0048E6A0, 0x0048E806);
    hooks::CNativeFunc<Com_PrintErrorf_t>& Com_PrintErrorf = hooks::CNativeFunc<Com_PrintErrorf_t>::Create(0x00412AC0, 0x00412C3F);
    hooks::CNativeFunc<main_t>& main = hooks::CNativeFunc<main_t>::Create(0x00416060, 0x004160C2);
    hooks::CNativeFunc<printf_t>& printf = hooks::CNativeFunc<printf_t>::Create(0x4B4778, 0x4B4826);
}
