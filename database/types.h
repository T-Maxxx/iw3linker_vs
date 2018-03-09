#pragma once
#include "utility/types.h"

namespace database
{
    struct xblock_t
    {
        utility::byte* data;
        int size;
    };
    
    struct xfile_t
    {
        xblock_t blocks[9];
    };
}