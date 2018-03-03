#pragma once

namespace database
{
    void _cdecl DB_ReserveStreamMemory();
    void _cdecl DB_ReleaseStreamMemory();

    void _cdecl DB_InitStream();
    void _cdecl DB_InitTempStream();
    void _cdecl DB_InitOutStream();

    void _cdecl DB_ClearStream();
    void _cdecl DB_ClearTempStream();
    void _cdecl DB_ClearOutStream();
} // end namespace database
