#include <Windows.h>

#include "proxy_lib.hpp"
#include "ep_patch.hpp"


BOOL APIENTRY DllMain(HMODULE /*hModule*/, DWORD ul_reason_for_call, LPVOID /*lpReserved*/)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        if (!CProxyLib::Instance().IsReady())
        {
            MessageBox(NULL, "'d3dx9_34.dll' not found. Application will be shut down immediately.", "Library not found", MB_ICONERROR | MB_OK);
            ExitProcess(FALSE);
        }

        if (IsSuitableExe())
            PatchEntryPoint();
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
