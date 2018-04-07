#pragma once
#include "utility/types.h"

namespace database
{
    enum EBlockType
    {
        XFILE_BLOCK_TEMP = 0,
        XFILE_BLOCK_RUNTIME,
        XFILE_BLOCK_LARGE_RUNTIME,
        XFILE_BLOCK_PHYSICAL_RUNTIME,
        XFILE_BLOCK_VIRTUAL,
        XFILE_BLOCK_LARGE,
        XFILE_BLOCK_PHYSICAL,
        XFILE_BLOCK_VERTEX,
        XFILE_BLOCK_INDEX,

        MAX_XFILE_COUNT
    };

    struct xblock_t
    {
        utility::byte* data;
        utility::uint size;
    };
    
    struct xfile_t
    {
        xblock_t blocks[MAX_XFILE_COUNT];
    };
}