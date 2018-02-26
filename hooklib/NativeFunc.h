#pragma once
#include "BaseHook.h"

namespace hooklib
{
    // A helper class to perform native function call.
    template <class Type_>
    class NativeFunc : public CBaseHook
    {
    public:
        NativeFunc(uint Address_) : CBaseHook(Address_)
        {
            Invoke = reinterpret_cast<Type_>(Address_);
        }

        Type_ Invoke;

    protected:
        EHookType GetHookType() const override final
        {
            return EHT_NativeFunc;
        }
    };
}
