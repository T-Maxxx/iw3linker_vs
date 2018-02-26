#include "stdafx.h"
#include "EntryPointPatch.h"
#include "Hashing.h"

bool IsSuitableExe()
{
    char path[MAX_PATH] = { '\0' };
    GetProcessImageFileName(GetCurrentProcess(), path, sizeof(path));
    // TODO: recheck.
    return hashing::GetFileHash_CRC32(path) == 0x0;
}

void PatchEntryPoint()
{
}
