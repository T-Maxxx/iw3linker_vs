#pragma once
#include "BaseHook.h"
#include "HookStorage.h"

namespace hooklib
{
    /**
    \brief A hook used to setup "jmp XXX" or "call XXX" instructions in native code.
    */
    class CJumpHook : public CBaseHook
    {
    public:
        /**
        \brief A class factory. Used to register hook in storage.
        \param [in] T - type of function pointer.
        \param [in] Address_ - an address to place hook.
        \param [in] JumpTo_ - a function pointer.
        \param [in] bCallHook_ - if true, "call" hook will be dispatched.
        \return Reference to instance.
        */
        template <class T>
        static CJumpHook& Create(uint Address_, T JumpTo_, bool bCallHook_ = false)
        {
            return *static_cast<CJumpHook*>(CHookStorage::Instance().AddHook(new CJumpHook(Address_, JumpTo_, bCallHook_)));
        }

        void Install() override final;
        void Release() override final;

    private:
        /**
        \brief Constructor. Same params as for factory.
        */
        template<class T>
        CJumpHook(uint Address_, T JumpTo_, bool bCallHook_ = false)
            : CBaseHook(Address_, sizeof(SJumpHook))
        {
            m_iRawTarget = reinterpret_cast<uint>(JumpTo_);
            m_bCallHook = bCallHook_;
        }

        ~CJumpHook();

        SJumpHook m_OriginalInstruction;
        uint m_iRawTarget;
        bool m_bCallHook;
    };
}
