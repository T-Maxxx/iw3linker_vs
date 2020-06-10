#pragma once
#include "base_hook.hpp"
#include "hook_storage.hpp"

namespace hooks
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
        static CNativeFunc& Create(uint32_t StartAddress_, uint32_t EndAddress_)
        {
            return *static_cast<CNativeFunc*>(CHookStorage::Instance().AddHook(new CNativeFunc<Type_>(StartAddress_, EndAddress_)));
        }

        /**
        \brief Type cast operator.
        */
        operator Type_ ()
        {
            return m_Pointer;
        }
        
    private:
        /**
        \brief Constructor. Same params as in factory.
        */
        CNativeFunc(uint32_t StartAddress_, uint32_t EndAddress_) : CBaseHook(StartAddress_, EndAddress_ - StartAddress_ + 1)
        {
            m_Pointer = reinterpret_cast<Type_>(StartAddress_);
        }

        Type_ m_Pointer;
    };
}
