#pragma once
#include <list>
#include "BaseHook.h"

namespace hooklib
{
    /**
    \brief The only storage for hooks used with this library. 
    \brief This class designed to track overlappings between used hooks.
    */
    class CHookStorage
    {
        DECLARE_SINGLETON(CHookStorage)

    public:

        /**
        \brief Add new hook in storage.
        \param [in] pHook_ - pointer to hook.
        \return pHook_.
        */
        CBaseHook* AddHook(CBaseHook* pHook_);

        /**
        \brief Removes hook from storage.
        \param [in] pHook_ - pointer to hook.
        */
        void RemoveHook(CBaseHook* pHook_);

    private:
        // Constructor. Prevents from creating instances.
        CHookStorage();

        // Destructor.
        ~CHookStorage();

        // Clears storage and deletes all hooks.
        void clear();

        // Returns hook which intersects with passed one.
        const CBaseHook* findIntersection(const CBaseHook* pHook_) const;

        std::list<CBaseHook*> m_lstHooks; // Storage.
    };
}