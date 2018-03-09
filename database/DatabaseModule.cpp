#include "stdafx.h"
#include "DatabaseModule.h"
#include "hooklib/hooklib.h"
#include "utility/utility.h"
#include "db_stream_save.h"
#include "globals.h"

using namespace hooklib;
using namespace utility;

namespace database
{
    void CDatabaseModule::InitGlobals() const
    {
        // This globals are just marked to track hooks interceptions.
        hooklib::CGlobalVar<byte*>::Create(0x0065696C); // g_streamMemory
        hooklib::CGlobalVar<byte*>::Create(0x00656968); // g_tempStreamMemory
        hooklib::CGlobalVar<byte*>::Create(0x00656B70); // g_streamOutMemory
        hooklib::CGlobalArr<uint, 9>::Create(0x005109F8); // g_streamBlockSize
    }

    void CDatabaseModule::Patch() const
    {
        CReplaceFunc::Create(0x0044B270, 0x0044B329, DB_ReserveStreamMemory);
        CReplaceFunc::Create(0x0044B330, 0x0044B385, DB_ReleaseStreamMemory);

        CReplaceFunc::Create(0x0044B390, 0x0044B3EC, DB_InitStream);
        CReplaceFunc::Create(0x0044B3F0, 0x0044B477, DB_InitTempStream);
        CReplaceFunc::Create(0x0044AB00, 0x0044AB7D, DB_InitOutStream);

        CReplaceFunc::Create(0x0044B480, 0x0044B4D3, DB_FreeStream);
        CReplaceFunc::Create(0x0044B4E0, 0x0044B533, DB_FreeTempStream);
        CReplaceFunc::Create(0x0044AB80, 0x0044ABC9, DB_FreeOutStream);

        CReplaceFunc::Create(0x0044B120, 0x0044B21D, DB_AllocTempStream);
        CReplaceFunc::Create(0x0044ABD0, 0x0044AD76, DB_AllocStreamOut);
        CReplaceFunc::Create(0x0044B020, 0x0044B11D, DB_AllocStreamPosSave);

        CReplaceFunc::Create(0x0044B220, 0x0044B266, DB_ResetTempStream);

        CReplaceFunc::Create(0x0049EE50, 0x0049EE55, DB_GetStreamPos);
        CReplaceFunc::Create(0x0049EE80, 0x0049EEBD, DB_IncStreamPos);
    }

    CDatabaseModule* CDatabaseModule::GetModule()
    {
        static CDatabaseModule g_DatabaseModule;
        return &g_DatabaseModule;
    }
}