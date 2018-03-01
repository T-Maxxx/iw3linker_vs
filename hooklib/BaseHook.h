#pragma once
#include "Types.h"

namespace hooklib
{
    /**
    \brief A base class for every hook in this library.
    */
    class CBaseHook
    {
    public:
        /**
        \brief Constructor.
        \param [in] Address_ - an address of this hook.
        */
        CBaseHook(uint Address_);

        /**
        \brief Constructor.
        \param [in] Address_ - an address of this hook.
        \param [in] Size_ - count of bytes captured with this hook.
        */
        CBaseHook(uint Address_, uint Size_);

        /**
        \brief Destructor.
        \note It checks if child object was not properly destroyed and show assert message.
        */
        virtual ~CBaseHook();

        /**
        \brief An actions used to install hook.
        \note Called directly by this CBaseHook class constructor.
        \note You must use "SetInstalled(true)" method inside.
        */
        virtual void Install();

        /**
        \brief An actions used to free used by hook resources.
        \note Must be called directly by inherited class destructor.
        \note You must use "SetInstalled(false)" method inside. 
        \note   Otherwise you will see assertion message.
        */
        virtual void Release();

        /**
        \brief Returns address of first byte captured by this hook.
        */
        uint GetStartAddress() const;

        /**
        \brief Returns address of last byte captured by this hook.
        \note Total size of captured memory: GetEndAddress() - GetStartAddress() + 1
        */
        uint GetEndAddress() const;

    protected:
        /**
        \brief Returns flag used to check if this hook was installed.
        */
        bool IsInstalled() const;

        /**
        \brief Sets flag used to check if this hook installed.
        \param [in] bState_ - if true then hook installed.
        */
        void SetInstalled(bool bState_);

    private:
        uint m_StartAddress;    // Address of first byte.
        uint m_EndAddress;      // Address of last byte.
        bool m_bInstalled;      // This hook is installed.
    };
}
