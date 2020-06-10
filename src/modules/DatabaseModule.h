#pragma once
#include "modman\Module.h"

namespace database
{
    class CDatabaseModule : public modman::CModule
    {
    public:
        void InitGlobals() const override final;
        void Patch() const override final;

        static CDatabaseModule* GetModule();
    };
}
