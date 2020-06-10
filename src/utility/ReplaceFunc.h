#pragma once
#include "BaseHook.h"
#include "HookStorage.h"

namespace hooklib
{
    /**
    \brief Replace native function call with our own. Keep calling convention the same and everything will be fine.
    */
    class CReplaceFunc : public CBaseHook
    {
    public:
        /**
        \brief A class factory.
        \param [in] StartAddress_ - an address of first byte of a function to replace.
        \param [in] EndAddress_ - an address of LAST BYTE of a function to replace.
        \param [in] Replacement_ - a function pointer of a replacement function.
        \return A reference to instance.
        */
        template <class T>
        static CReplaceFunc& Create(uint StartAddress_, uint EndAddress_, T Replacement_)
        {
            return *static_cast<CReplaceFunc*>(CHookStorage::Instance().AddHook(new CReplaceFunc(StartAddress_, EndAddress_, Replacement_)));
        }

        void Install() override final;
        void Release() override final;

    private:
        /**
        \brief Constructor. Same parameters as in factory.
        */
        template <class T>
        CReplaceFunc(uint StartAddress_, uint EndAddress_, T Replacement_)
            : CBaseHook(StartAddress_, EndAddress_ - StartAddress_ + 1)
        {
            m_iRawTarget = reinterpret_cast<uint>(Replacement_);
        }

        ~CReplaceFunc();

        SJumpHook* m_pOriginalInstruction;
        uint m_iRawTarget;
    };
}