#pragma once
#include "BaseHook.h"
#include "HookStorage.h"

namespace hooklib
{
    // Replace native function call with our own. Keep calling convention the same and everything will be fine.
    class CReplaceFunc : public CBaseHook
    {
    public:
        template <class T>
        CReplaceFunc(uint StartAddress_, uint EndAddress_, T Replacement_) 
            : CBaseHook(StartAddress_, EndAddress_)
        {
            m_iRawTarget = reinterpret_cast<uint>(Replacement_);
        }

        ~CReplaceFunc();

        template <class T>
        static CReplaceFunc& Create(uint StartAddress_, uint EndAddress_, T Replacement_)
        {
            auto pHook = new CReplaceFunc(StartAddress_, EndAddress_, Replacement_);
            GetHookStorage()->AddHook(pHook);
            return *pHook;
        }

        void Install() override final;
        void Release() override final;

    private:

        SJumpHook* m_pOriginalInstruction;
        uint m_iRawTarget;
    };
}