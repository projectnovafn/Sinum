// Copyright (c) 2025 Project Nova LLC

#include "../framework.h"
#include "../Core/Unreal/CurlHttp.h"

#include "Sinum.h"

bool Sinum::ProcessRequestHook(FCurlHttpRequest* Request)
{
    return _ProcessRequest(Request->RedirectRequest());
}

void Sinum::Init()
{
    auto StringRef = Memcury::Scanner::FindStringRef<const wchar_t*, false>(Constants::ProcessRequest_C2);
    if (StringRef.IsValid())
    {
        bool bFound = false;
        _ProcessRequest = StringRef
            .ScanFor({ 0x4C, 0x8B, 0xDC }, false, 0, 200, &bFound)
            .GetAs<decltype(_ProcessRequest)>();

        if (!bFound)
        {
            _ProcessRequest = StringRef
                .ScanFor({ 0x40, 0x53, 0x55 }, false, 0, 200, &bFound) // checked on: 12.41
                .GetAs<decltype(_ProcessRequest)>();

            if (!bFound)
            {
                _ProcessRequest = StringRef
                    .ScanFor({ 0x48, 0x8B, 0xC4 }, false, 0, 200, &bFound) // checked on: 16.50, 19.10, 23.50
                    .GetAs<decltype(_ProcessRequest)>();
            }
        }
    }
    else
    {
        _ProcessRequest = Memcury::Scanner::FindStringRef(Constants::ProcessRequest)
            .ScanFor({ 0x48, 0x81, 0xEC }, false, 1000)
            .ScanFor({ 0x40 }, false)
            .GetAs<decltype(_ProcessRequest)>();
    }

    auto ProcessRequestRef = Memcury::Scanner::FindPointerRef(_ProcessRequest);
    
    DWORD dwProtection;
    VirtualProtect(ProcessRequestRef.GetAs<PVOID>(), 8, PAGE_EXECUTE_READWRITE, &dwProtection);

    *ProcessRequestRef.GetAs<void**>() = ProcessRequestHook;

    DWORD dwTemp;
    VirtualProtect(ProcessRequestRef.GetAs<PVOID>(), 8, dwProtection, &dwTemp);
}