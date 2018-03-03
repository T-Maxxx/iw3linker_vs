#pragma once
#include "common/common.h"

#define QASSERT(expr) \
    if (!(expr)) \
        common::Com_Assert(__FILE__, __LINE__, 0, "%s", #expr);

#define QASSERTMSG(expr, msg) \
    if (!(expr)) \
        common::Com_Assert(__FILE__, __LINE__, 0, "%s\n\t(\"%s\")", #expr, msg);
