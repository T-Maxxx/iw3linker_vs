#pragma once
#include "BaseHook.h"
#include "HookStorage.h"

namespace hooklib
{
    /**
    \brief A helper class used to execute function from native code.
    \param [in] Type_ - A type of function (pointer).
    */
    template <class Type_>
    class CNativeFunc : public CBaseHook
    {
    public:
        /**
        \brief A class factory.
        \param [in] StartAddress_ - an address of first byte of a function.
        \param [in] EndAddress_ - an address of LAST BYTE of a function.
        */
        static CNativeFunc& Create(uint StartAddress_, uint EndAddress_)
        {
            return *static_cast<CNativeFunc*>(CHookStorage::Instance().AddHook(new CNativeFunc<Type_>(StartAddress_, EndAddress_)));
        }

        /**
        \brief Type cast operator.
        */
        operator Type_ ()
        {
            return Invoke;
        }
        
    private:
        /**
        \brief Constructor. Same params as in factory.
        */
        CNativeFunc(uint StartAddress_, uint EndAddress_) : CBaseHook(StartAddress_, EndAddress_ - StartAddress_ + 1)
        {
            Invoke = reinterpret_cast<Type_>(StartAddress_);
        }

        Type_ Invoke;
    };
}
