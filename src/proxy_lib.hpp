#pragma once
#include <Windows.h>

class CProxyLib
{
public:
    static CProxyLib& Instance();

    bool IsReady() const;

    HRESULT D3DXGetShaderOutputSemantics(const DWORD* pFunction, void* pSemantics, UINT* pCount);
    HRESULT D3DXCreateBuffer(DWORD NumBytes, DWORD ppBuffer);
    HRESULT D3DXGetShaderInputSemantics(const DWORD* pFunction, void* pSemantics, UINT* pCount);
    HRESULT D3DXGetShaderConstantTable(const DWORD* pFunction, void* ppConstantTable);

private:
    CProxyLib();
    ~CProxyLib();

    HMODULE m_hOriginalLib = nullptr;
};
