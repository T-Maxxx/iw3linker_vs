#pragma once
#include "utility/utility.h"

namespace database
{
    void _cdecl DB_ReserveStreamMemory();
    void _cdecl DB_ReleaseStreamMemory();

    void _cdecl DB_InitStream();
    void _cdecl DB_InitTempStream();
    void _cdecl DB_InitOutStream();

    void _cdecl DB_FreeStream();
    void _cdecl DB_FreeTempStream();
    void _cdecl DB_FreeOutStream();

    utility::byte* _cdecl DB_AllocTempStream(int Size_);
    void _cdecl DB_AllocStreamOut(utility::byte StreamIndex_, utility::byte* Src_, size_t Size_, utility::byte** Dst_);
    utility::byte* _cdecl DB_AllocStreamPosSave(int Size_);

    void _cdecl DB_ResetTempStream();

    utility::byte* _cdecl DB_GetStreamPos();
    void _cdecl DB_IncStreamPos(int Size_);
} // end namespace database
