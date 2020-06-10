#pragma once
#include "core/functions.hpp"


#define QASSERT(expr) \
    if (!(expr)) \
        core::Com_Assert(__FILE__, __LINE__, 0, "%s", #expr);

#define QASSERTMSG(expr, msg) \
    if (!(expr)) \
        core::Com_Assert(__FILE__, __LINE__, 0, "%s\n\t(\"%s\")", #expr, msg);

#define QASSERTFMT(expr, fmt, ...) \
    if (!(expr)) \
        core::Com_Assert(__FILE__, __LINE__, 0, "%s\n" fmt, #expr, __VA_ARGS__);

#define PAGE_ROUNDUP(x) (((x) + 4095) & 0xFFFFF000)
