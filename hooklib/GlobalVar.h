#pragma once
#include "BaseHook.h"
#include "Memory.h"
#include "HookStorage.h"

namespace hooklib
{
    template <class T>
    class CGlobalVar : public CBaseHook
    {
    public:
        CGlobalVar(uint Address_) : CBaseHook(Address_, Address_ + sizeof(T)) {}

        static CGlobalVar& CreateHook(uint Address_)
        {
            auto pHook = new CGlobalVar<T>(Address_);
            GetHookStorage()->AddHook(pHook);
            return *pHook;
        }

        CGlobalVar& operator = (const T& Other_)
        {
            WriteToMemory(GetStartAddress(), &Other_);
            return *this;
        }

        operator T () const
        {
            T data;
            ReadFromMemory(GetStartAddress(), &data);
            return data;
        }

    protected:
        EHookType GetHookType() const override final
        {
            return EHT_GlobalVar;
        }
    };
}
