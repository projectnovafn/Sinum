// Copyright (c) 2025 Project Nova LLC

#include "Core.h"

void Core::Init()
{
	while (!Memcury::Scanner::FindStringRef<const wchar_t*, false>(L"Fortnite").IsValid()) // Wait for the game to be unpacked
	{
		Sleep(250);
	}

	Sleep(2500);

	FMemory::_Realloc = Memcury::Scanner::FindPattern("48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 20 48 8B F1 41 8B D8 48 8B 0D ? ? ? ? 48")
		.GetAs<decltype(FMemory::_Realloc)>(); // checked on: 1.8, 12.41, 15.50, 19.10, 23.50

	auto RequestExitRef = Memcury::Scanner::FindStringRef<const wchar_t*, false>(L"FPlatformMisc::RequestExitWithStatus(%i, %i)");

	if (RequestExitRef.IsValid()) // Only necessary for S16 really
	{
		bool bFound = false;
		auto Found = RequestExitRef
			.ScanFor({ 0x57 }, false, 0, 200)
			.ScanFor({ 0xE9 }, false, 0, 15, &bFound) // only s16 and above has this
			.GetAs<uint8_t*>();

		if (bFound)
		{
			*(Found + 6) = { 0xC3 };

			auto StringRef = Memcury::Scanner::FindStringRef<const wchar_t*, false>(L"UnsafeEnvironment_Title");

			if (StringRef.IsValid())
			{
				Found = StringRef.ScanFor({ 0x0F, 0x84 }, false, 0, 200).GetAs<uint8_t*>();
				*(Found + 1) = 0x85; // Force jmp to the end (by jz -> jnz for FortUIManagerInterface)
			}
		}
	}
}