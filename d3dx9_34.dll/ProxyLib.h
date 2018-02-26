#pragma once

namespace proxylib
{
    class CProxyLib
    {
    public:
        CProxyLib();
        ~CProxyLib();

        bool IsReady() const;

        HRESULT D3DXGetShaderOutputSemantics(const DWORD *pFunction, void *pSemantics, UINT *pCount);
        HRESULT D3DXCreateBuffer(DWORD NumBytes, void *ppBuffer);
        HRESULT D3DXGetShaderInputSemantics(const DWORD *pFunction, void *pSemantics, UINT *pCount);
        HRESULT D3DXGetShaderConstantTable(const DWORD *pFunction, void *ppConstantTable);

    private:
        HMODULE m_hOriginalLib;
    };

    CProxyLib* GetProxyLib();
} // end namespace proxylib
