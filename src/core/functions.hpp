#pragma once
#include "hooks/native_function.hpp"

namespace core
{
    using Com_Assert_t = void(*)(const char *FilePath_, int Line_, int Unknown_, const char *MsgFormat_, ...);
    extern hooks::CNativeFunc<Com_Assert_t>& Com_Assert;

    using Com_PrintErrorf_t = void(*)(int Channel_, const char* Format_, ...);
    extern hooks::CNativeFunc<Com_PrintErrorf_t>& Com_PrintErrorf;

    using main_t = int(*)(const int, const char**);
    extern hooks::CNativeFunc<main_t>& main;

    using printf_t = int(*)(const char*, ...);
    extern hooks::CNativeFunc<printf_t>& printf;
}
