#pragma once
#include "Types.h"

namespace hooklib
{
    class IBaseHook
    {
    public:
        virtual ~IBaseHook() {}
        virtual void Install() = 0;
        virtual void Release() = 0;
        virtual uint GetStartAddress() const = 0;
        virtual uint GetEndAddress() const = 0;

    protected: 
        virtual EHookType GetHookType() const = 0;
    };
}
