// Copyright (c) 2024 Project Nova LLC

#include "framework.h"

static void Main()
{
    while (!Memcury::Scanner::FindStringRef<const wchar_t*, false>(L"Fortnite").IsValid()) // Wait for the game to be unpacked
    {
        Sleep(250);
    }

    Sleep(7500);

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