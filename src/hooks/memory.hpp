#pragma once
#include <cstdint>


namespace hooks
{
    enum EProtectMemoryFlags
    {
        PMF_Unknown,
        PMF_R,
        PMF_W,
        PMF_X,
        PMF_RW,
        PMF_RX,
        PMF_WX,
        PMF_RWX,
    };

    void ReadFromMemory(void* FromAddress_, void* ToStorage_, size_t Size_);
    void WriteToMemory(void* ToAddress_, const void* FromStorage_, size_t Size_);
    EProtectMemoryFlags ProtectMemory(void* Where_, size_t Size_, EProtectMemoryFlags NewProtectType_);

    template <class T>
    void ReadFromMemory(uint32_t FromAddress_, T* ToStorage_)
    {
        ReadFromMemory(reinterpret_cast<void*>(FromAddress_), ToStorage_, sizeof(T));
    }

    template <class T>
    void WriteToMemory(uint32_t ToAddress_, const T* FromStorage_)
    {
        WriteToMemory(reinterpret_cast<void*>(ToAddress_), FromStorage_, sizeof(T));
    }
}
