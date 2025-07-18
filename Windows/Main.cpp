// Copyright (c) 2025 Project Nova LLC

#include "framework.h"

static void Main()
{
#if 0
    AllocConsole();
    FILE* fptr;
    freopen_s(&fptr, "CONOUT$", "w+", stdout);
#endif

    Core::Init();
    Sinum::Init();
}

bool DllMain(HMODULE hModule, DWORD dwReason, void* lpReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        Windows::Thread::Create(Main);
    }

    return true;
}