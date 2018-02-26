#pragma once
#include <list>
#include <cassert>
#include "BaseHook.h"

namespace hooklib
{
    class CHookStorage
    {
        DECLARE_NO_COPY_CLASS(CHookStorage)

    public:
        CHookStorage();
        ~CHookStorage();

        IBaseHook* AddHook(IBaseHook* pHook_);
        void RemoveHook(IBaseHook* pHook_);

    private:
        void clear();
        const IBaseHook* findIntersection(const IBaseHook* pHook_) const;

        std::list<IBaseHook*> m_lstHooks;
    };

    CHookStorage* GetHookStorage();
}