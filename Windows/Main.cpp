// Copyright (c) 2024 Project Nova LLC

#include "framework.h"
#include <iostream>

static void Main()
{
    AllocConsole();
    FILE* fptr;
    freopen_s(&fptr, "CONOUT$", "w+", stdout);

    Sleep(7500);

    std::cout << "Initializing with base address: " << std::hex << __int64(GetModuleHandleW(0)) << '\n';

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