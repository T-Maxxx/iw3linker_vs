#include "stdafx.h"
#include "CommonModule.h"
#include "globals.h"

namespace common
{
    void CCommonModule::InitGlobals() const
    {

    }

    void CCommonModule::Patch() const
    {
    }

    CCommonModule* CCommonModule::GetModule()
    {
        static CCommonModule g_CommonModule;
        return &g_CommonModule;
    }
}
