#include <Windows.h>
#include <Psapi.h>

#include "hashing.hpp"
#include "module_manager.hpp"
#include "hooks/jump_hook.hpp"
#include "hooks/native_function.hpp"
#include "core/functions.hpp"

#include "modules/database.hpp"


bool IsSuitableExe()
{
    char path[MAX_PATH] = { '\0' };
    GetModuleFileNameEx(GetCurrentProcess(), NULL, path, sizeof(path));

    return GetFileHash_CRC32(path) == 0x7168CCFE;
}


static int __cdecl HookedMain(const int argc, const char **const argv)
{
    CModuleManager manager;
    manager.AddModule<modules::CDatabase>();

    // Process modules' logic.
    manager.InitGlobals();
    manager.Patch();

    core::printf("IW3 linker patch by T-Max\n");

    // Call original main.
    return core::main(argc, argv);
}


void PatchEntryPoint()
{
    hooks::CJumpHook::Create(0x004B7944, HookedMain, true);
}
