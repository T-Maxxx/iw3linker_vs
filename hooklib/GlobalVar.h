#pragma once
#include "BaseHook.h"
#include "Memory.h"

namespace hooklib
{
    template <class T>
    class GlobalVar : public CBaseHook
    {
    public:
        GlobalVar(uint Address_) : CBaseHook(Address_, Address_) {}

        T& operator = (const T& Other_)
        {
            WriteToMemory(GetStartAddress(), &Other_);
            return *this;
        }

        operator T () const
        {
            T data;
            ReadFromMemory(GetStartAddress, &data);
            return data;
        }

    protected:
        EHookType GetHookType() const override final
        {
            return EHT_GlobalVar;
        }
    };
}
