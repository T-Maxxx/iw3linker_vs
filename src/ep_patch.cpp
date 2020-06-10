#include <Windows.h>
#include <Psapi.h>

#include "hashing.hpp"
#include "module_manager.hpp"
#include "hooks/jump_hook.hpp"
#include "hooks/native_function.hpp"

#include "modules/database.hpp"


using FPMain = int(__cdecl*)(const int argc, const char **const argv);

bool IsSuitableExe()
{
    char path[MAX_PATH] = { '\0' };
    GetModuleFileNameEx(GetCurrentProcess(), NULL, path, sizeof(path));

    return GetFileHash_CRC32(path) == 0x21E01F1E;
}


static int __cdecl FakeMain(const int argc, const char **const argv)
{
    CModuleManager manager;
    manager.AddModule<modules::CDatabase>();
    manager.AddModule<modules::CDatabase>();

    // Process modules' logic.
    manager.InitGlobals();
    manager.Patch();

    // Call original untouched winmain.
    return (hooks::CNativeFunc<FPMain>::Create(0x00416060, 0x004160C2))(argc, argv);
}


void PatchEntryPoint()
{
    hooks::CJumpHook::Create(0x004B7944, FakeMain, true);
}
