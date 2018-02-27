#include "stdafx.h"
#include "EntryPointPatch.h"
#include "Hashing.h"
#include <hooklib/hooklib.h>

using namespace hooklib;

using FPMain = int(__cdecl*)(const int argc, const char **const argv);

bool IsSuitableExe()
{
    char path[MAX_PATH] = { '\0' };
    GetModuleFileNameEx(GetCurrentProcess(), NULL, path, sizeof(path));

    return hashing::GetFileHash_CRC32(path) == 0x21E01F1E;
}

int __cdecl FakeMain(const int argc, const char **const argv)
{
    // Call original untouched winmain.
    auto pMain = new NativeFunc<FPMain>(0x00416060);
    GetHookStorage()->AddHook(pMain);
    return pMain->Invoke(argc, argv);
}

void PatchEntryPoint()
{
    GetHookStorage()->AddHook(new CJumpHook(0x004B7944, FakeMain, true));
}
