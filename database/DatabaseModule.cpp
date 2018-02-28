#include "stdafx.h"
#include "DatabaseModule.h"
#include "hooklib/hooklib.h"
#include "db_stream_save.h"

using namespace hooklib;

namespace database
{
    void CDatabaseModule::InitGlobals() const
    {
    }

    void CDatabaseModule::Patch() const
    {
        CReplaceFunc::Create(0x0044B270, 0x0044B329, DB_InitStream);
    }

    CDatabaseModule* CDatabaseModule::GetModule()
    {
        static CDatabaseModule g_DatabaseModule;
        return &g_DatabaseModule;
    }
}