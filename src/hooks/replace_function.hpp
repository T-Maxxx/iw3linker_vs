#pragma once
#include "hook_storage.hpp"
#include "base_hook.hpp"


namespace hooks
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
        static CReplaceFunc& Create(uint32_t StartAddress_, uint32_t EndAddress_, T Replacement_)
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
        CReplaceFunc(uint32_t StartAddress_, uint32_t EndAddress_, T Replacement_)
            : CBaseHook(StartAddress_, EndAddress_ - StartAddress_ + 1)
        {
            m_iRawTarget = reinterpret_cast<uint32_t>(Replacement_);
        }

        ~CReplaceFunc();

#pragma pack(push, 1)
        struct SJumpHook
        {
            uint8_t OpCode = 0;
            int32_t JumpOffset = 0;
        };
#pragma pack(pop)

        SJumpHook* m_pOriginalInstruction;
        uint32_t m_iRawTarget;
    };
}
