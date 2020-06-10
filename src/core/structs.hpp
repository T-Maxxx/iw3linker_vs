#pragma once
#include <cstdint>


namespace core
{
    enum BlockType
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
        uint8_t* data;
        uint32_t size;
    };

    struct xfile_t
    {
        xblock_t blocks[MAX_XFILE_COUNT];
    };
}
