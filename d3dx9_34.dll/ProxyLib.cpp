#include "stdafx.h"
#include "ProxyLib.h"

namespace proxylib
{
    using FPD3DXGetShaderOutputSemantics = HRESULT(WINAPI*)(const DWORD *pFunction, void *pSemantics, UINT *pCount);
    using FPD3DXCreateBuffer = HRESULT(WINAPI*)(DWORD NumBytes, DWORD ppBuffer);
    using FPD3DXGetShaderInputSemantics = HRESULT(WINAPI*)(const DWORD *pFunction, void *pSemantics, UINT *pCount);
    using FPD3DXGetShaderConstantTable = HRESULT(WINAPI*)(const DWORD *pFunction, void *ppConstantTable);

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

    bool CProxyLib::IsReady() const
    {
        return m_hOriginalLib != NULL;
    }

    HRESULT CProxyLib::D3DXGetShaderOutputSemantics(const DWORD *pFunction, void *pSemantics, UINT *pCount)
    {
        return GetLibFunction<FPD3DXGetShaderOutputSemantics>(m_hOriginalLib, "D3DXGetShaderOutputSemantics")(pFunction, pSemantics, pCount);
    }

    HRESULT CProxyLib::D3DXCreateBuffer(DWORD NumBytes, DWORD ppBuffer)
    {
        return GetLibFunction<FPD3DXCreateBuffer>(m_hOriginalLib, "D3DXCreateBuffer")(NumBytes, ppBuffer);
    }

    HRESULT CProxyLib::D3DXGetShaderInputSemantics(const DWORD *pFunction, void *pSemantics, UINT *pCount)
    {
        return GetLibFunction<FPD3DXGetShaderInputSemantics>(m_hOriginalLib, "D3DXGetShaderInputSemantics")(pFunction, pSemantics, pCount);
    }

    HRESULT CProxyLib::D3DXGetShaderConstantTable(const DWORD *pFunction, void *ppConstantTable)
    {
        return GetLibFunction<FPD3DXGetShaderConstantTable>(m_hOriginalLib, "D3DXGetShaderConstantTable")(pFunction, ppConstantTable);
    }

    CProxyLib* GetProxyLib()
    {
        static CProxyLib g_proxyLib;
        return &g_proxyLib;
    }
}
