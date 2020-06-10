#pragma once
#include "modman\Module.h"

namespace common
{
    class CCommonModule : public modman::CModule
    {
    public:
        void InitGlobals() const override final;
        void Patch() const override final;

        static CCommonModule* GetModule();
    };
}
