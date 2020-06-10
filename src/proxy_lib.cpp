#include "proxy_lib.hpp"

#include <cstdio>


template<class FP>
FP GetLibFunction(HMODULE hLib_, const char* FunctionName_)
{
    return reinterpret_cast<FP>(GetProcAddress(hLib_, FunctionName_));
}


CProxyLib::CProxyLib()
{
    char path[MAX_PATH] = { '\0' };
    char sysPath[MAX_PATH - 13] = { '\0' };
    GetSystemDirectoryA(sysPath, sizeof(sysPath));
    sprintf_s(path, "%s\\d3dx9_34.dll", sysPath);
    m_hOriginalLib = LoadLibrary(path);
}


CProxyLib::~CProxyLib()
{
    if (m_hOriginalLib)
        FreeLibrary(m_hOriginalLib);
}


CProxyLib& CProxyLib::Instance()
{
    static CProxyLib proxyLib;
    return proxyLib;
}


bool CProxyLib::IsReady() const
{
    return m_hOriginalLib != NULL;
}


HRESULT CProxyLib::D3DXGetShaderOutputSemantics(const DWORD* pFunction, void* pSemantics, UINT* pCount)
{
    using D3DXGetShaderOutputSemantics_t = HRESULT(WINAPI*)(const DWORD*, void*, UINT*);
    static D3DXGetShaderOutputSemantics_t fn = nullptr;
    if (!fn)
        fn = GetLibFunction<D3DXGetShaderOutputSemantics_t>(m_hOriginalLib, "D3DXGetShaderOutputSemantics");

    return fn ? fn(pFunction, pSemantics, pCount) : -1;
}


HRESULT CProxyLib::D3DXCreateBuffer(DWORD NumBytes, DWORD ppBuffer)
{
    using D3DXCreateBuffer_t = HRESULT(WINAPI*)(DWORD, DWORD);
    static D3DXCreateBuffer_t fn = nullptr;
    if (!fn)
        fn = GetLibFunction<D3DXCreateBuffer_t>(m_hOriginalLib, "D3DXCreateBuffer");

    return fn ? fn(NumBytes, ppBuffer) : -1;
}


HRESULT CProxyLib::D3DXGetShaderInputSemantics(const DWORD* pFunction, void* pSemantics, UINT* pCount)
{
    using D3DXGetShaderInputSemantics_t = HRESULT(WINAPI*)(const DWORD*, void*, UINT*);
    static D3DXGetShaderInputSemantics_t fn = nullptr;
    if (!fn)
        fn = GetLibFunction<D3DXGetShaderInputSemantics_t>(m_hOriginalLib, "D3DXGetShaderInputSemantics");

    return fn ? fn(pFunction, pSemantics, pCount) : -1;
}


HRESULT CProxyLib::D3DXGetShaderConstantTable(const DWORD* pFunction, void* ppConstantTable)
{
    using FPD3DXGetShaderConstantTable_t = HRESULT(WINAPI*)(const DWORD*, void*);
    static FPD3DXGetShaderConstantTable_t fn = nullptr;
    if (!fn)
        fn = GetLibFunction<FPD3DXGetShaderConstantTable_t>(m_hOriginalLib, "D3DXGetShaderConstantTable");

    return fn ? fn(pFunction, ppConstantTable) : -1;
}
