#pragma once
#include "IBaseHook.h"

namespace hooklib
{
    class CBaseHook : public IBaseHook
    {
    public:
        CBaseHook(uint Address_);
        CBaseHook(uint StartAddress_, uint EndAddress_);
        virtual ~CBaseHook();

        void Install() override {}
        void Release() override {}

        uint GetStartAddress() const override final;
        uint GetEndAddress() const override final;

    protected:
        EHookType GetHookType() const override;

    private:
        uint m_StartAddress;
        uint m_EndAddress;
    };
}
