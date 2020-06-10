#pragma once
#include "HookStorage.h"

namespace hooklib
{
    /**
    \brief A hook to capture native array of type T and size N.
    */
    template <class T, size_t N>
    class CGlobalArr : public CBaseHook
    {
    public:
        /**
        \brief Create new native array hook and return reference to it.
        \param [in] Address_ - an address of first element of array.
        */
        static CGlobalArr& Create(uint Address_)
        {
            return *static_cast<CGlobalArr*>(CHookStorage::Instance().AddHook(new CGlobalArr(Address_)));
        }

        /**
        \brief A type casting operator used to get poiter to the first element of array.
        */
        operator T* ()
        {
            return reinterpret_cast<T*>(GetStartAddress());
        }



    private:
        CGlobalArr(uint Address_)
            : CBaseHook(Address_, N * sizeof(T))
        {}
    };
}
