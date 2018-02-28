#include "stdafx.h"
#include "EntryPointPatch.h"
#include "Hashing.h"
#include <hooklib/hooklib.h>
#include <modman/ModuleManager.h>
#include <database/database.h>
#include <common/common.h>

using namespace hooklib;
using namespace modman;

using FPMain = int(__cdecl*)(const int argc, const char **const argv);

bool IsSuitableExe()
{
    char path[MAX_PATH] = { '\0' };
    GetModuleFileNameEx(GetCurrentProcess(), NULL, path, sizeof(path));

    return hashing::GetFileHash_CRC32(path) == 0x21E01F1E;
}

int __cdecl FakeMain(const int argc, const char **const argv)
{
    CModuleManager manager;
    // Add modules.
    manager.AddModule(common::CCommonModule::GetModule());
    manager.AddModule(database::CDatabaseModule::GetModule());

    // Process modules' logic.
    manager.InitGlobals();
    manager.Patch();

    // Call original untouched winmain.
    return (CNativeFunc<FPMain>::CreateHook(0x00416060)).Invoke(argc, argv);
}

void PatchEntryPoint()
{
    CJumpHook::CreateHook(0x004B7944, FakeMain, true);
}
