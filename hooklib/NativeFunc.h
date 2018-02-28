#pragma once
#include "BaseHook.h"
#include "HookStorage.h"

namespace hooklib
{
    // A helper class to perform native function call.
    // TODO: function can be replaced so need to improve this class with range.
    template <class Type_>
    class CNativeFunc : public CBaseHook
    {
    public:
        CNativeFunc(uint Address_) : CBaseHook(Address_)
        {
            Invoke = reinterpret_cast<Type_>(Address_);
        }

        static CNativeFunc& CreateHook(uint Address_)
        {
            auto pHook = new CNativeFunc<Type_>(Address_);
            GetHookStorage()->AddHook(pHook);
            return *pHook;
        }

        Type_ Invoke;

    protected:
        EHookType GetHookType() const override final
        {
            return EHT_NativeFunc;
        }
    };
}
