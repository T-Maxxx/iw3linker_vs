#pragma once
#include "common/common.h"

#define QASSERT(expr) \
    if (!(expr)) \
        common::Com_Assert(__FILE__, __LINE__, 0, "%s", #expr);

#define QASSERTMSG(expr, msg) \
    if (!(expr)) \
        common::Com_Assert(__FILE__, __LINE__, 0, "%s\n\t(\"%s\")", #expr, msg);

#define QASSERTFMT(expr, fmt, ...) \
    if (!(expr)) \
        common::Com_Assert(__FILE__, __LINE__, 0, fmt, #expr, __VA_ARGS__);

#define PAGE_ROUNDUP(x) (((x) + 4095) & 0xFFFFF000)
