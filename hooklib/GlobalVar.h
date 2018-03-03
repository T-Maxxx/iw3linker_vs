#pragma once
#include "BaseHook.h"
#include "Memory.h"
#include "HookStorage.h"

namespace hooklib
{
    /**
    \brief Helper class to access global variable by its address.
    \param [in] T - type of global variable.
    */
    template <class T>
    class CGlobalVar : public CBaseHook
    {
    public:
        /**
        \brief A class factory. Used to register hook in storage.
        \param [in] Address_ - an address of a variable.
        \return A reference to instance.
        */
        static CGlobalVar& Create(uint Address_)
        {
            return *static_cast<CGlobalVar<T>*>(CHookStorage::Instance().AddHook(new CGlobalVar<T>(Address_)));
        }

        /**
        \brief Overloading for assignment. Used to update variable in native code.
        */
        template<class Type_>
        CGlobalVar& operator = (const Type_& Other_)
        {
            WriteToMemory(GetStartAddress(), &Other_);
            return *this;
        }

        /**
        \brief Overloading for class assignment. Used to copy from one class instance to other.
        */
        CGlobalVar& operator = (const CGlobalVar& Other_)
        {
            *this = (T)Other_;
            //WriteToMemory(GetStartAddress(), );
            return *this;
        }

        /**
        \brief Type casting operator. Used to obtain variable value from memory.
        */
        operator T () const
        {
            T data;
            ReadFromMemory(GetStartAddress(), &data);
            return data;
        }

    private:
        /**
        \brief Constructor.
        \param [in] Address_ - address of global variable in native code.
        */
        CGlobalVar(uint Address_) : CBaseHook(Address_, sizeof(T))
        {}
    };
}
