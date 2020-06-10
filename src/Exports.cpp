#include "proxy_lib.hpp"

#pragma comment(linker, "/export:D3DXGetShaderOutputSemantics=_D3DXGetShaderOutputSemantics@12")
// pSemantics is D3DXSEMANTIC*
extern "C" HRESULT WINAPI D3DXGetShaderOutputSemantics(const DWORD *pFunction, void *pSemantics, UINT *pCount)
{
    return CProxyLib::Instance().D3DXGetShaderOutputSemantics(pFunction, pSemantics, pCount);
}

#pragma comment(linker, "/export:D3DXCreateBuffer=_D3DXCreateBuffer@8")
// ppBuffer is LPD3DXBUFFER*
extern "C" HRESULT WINAPI D3DXCreateBuffer(DWORD NumBytes, DWORD ppBuffer)
{
    return CProxyLib::Instance().D3DXCreateBuffer(NumBytes, ppBuffer);
}

#pragma comment(linker, "/export:D3DXGetShaderInputSemantics=_D3DXGetShaderInputSemantics@12")
// pSemantics is D3DXSEMANTIC*
extern "C" HRESULT WINAPI D3DXGetShaderInputSemantics(const DWORD *pFunction, void *pSemantics, UINT *pCount)
{
    return CProxyLib::Instance().D3DXGetShaderInputSemantics(pFunction, pSemantics, pCount);
}

#pragma comment(linker, "/export:D3DXGetShaderConstantTable=_D3DXGetShaderConstantTable@8")
// ppConstantTable is LPD3DXCONSTANTTABLE*
extern "C" HRESULT WINAPI D3DXGetShaderConstantTable(const DWORD *pFunction, void *ppConstantTable)
{
    return CProxyLib::Instance().D3DXGetShaderConstantTable(pFunction, ppConstantTable);
}
