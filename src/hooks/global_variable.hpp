#pragma once
#include "base_hook.hpp"
#include "memory.hpp"


namespace hooks
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
        static CGlobalVar& Create(uint32_t Address_)
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
        \brief Overloading for short increasing.
        */
        template <class Type_>
        CGlobalVar& operator += (const Type_& Other_)
        {
            const T from = Raw() + Other_;
            WriteToMemory(GetStartAddress(), &from);
            return *this;
        }

        /**
        \brief Overloading for class assignment. Used to copy from one class instance to other.
        */
        CGlobalVar& operator = (const CGlobalVar& Other_)
        {
            *this = (T)Other_;
            return *this;
        }

        /**
        \brief Returns raw data which is pointed by this hook.
        */
        T Raw() const
        {
            T data;
            ReadFromMemory(GetStartAddress(), &data);
            return data;
        }

        /**
        \brief Type casting operator. Used to obtain variable value from memory.
        */
        operator T () const
        {
            return Raw();
        }

    private:
        /**
        \brief Constructor.
        \param [in] Address_ - address of global variable in native code.
        */
        CGlobalVar(uint32_t Address_) : CBaseHook(Address_, sizeof(T))
        {}
    };
}
