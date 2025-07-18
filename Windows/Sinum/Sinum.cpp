// Copyright (c) 2025 Project Nova LLC

#include "Sinum.h"

bool Sinum::ProcessRequestHook(FCurlHttpRequest* Request)
{
    std::wstring URL(Request->GetURL().c_str());
    size_t PathIndex = URL.find(L"ol.epicgames.com");

    if (PathIndex != std::wstring::npos)
    {
        auto Path = URL.substr(PathIndex + 16);
        auto NewURL = Constants::API_URL + Path;

        Request->SetURL(NewURL.c_str());
    }

    return _ProcessRequest(Request);
}

void Sinum::Init()
{
    auto StringRef = Memcury::Scanner::FindStringRef<const wchar_t*, false>(Constants::ProcessRequest_C2);
    if (StringRef.IsValid())
    {
        bool bFound = false;
        _ProcessRequest = StringRef
            .ScanFor({ 0x4C, 0x8B, 0xDC }, false, 0, 500, &bFound)
            .GetAs<decltype(_ProcessRequest)>();

        if (!bFound)
        {
            _ProcessRequest = StringRef
                .ScanFor({ 0x40, 0x53, 0x55 }, false, 0, 500, &bFound) // checked on: 12.41
                .GetAs<decltype(_ProcessRequest)>();

            if (!bFound)
            {
                _ProcessRequest = StringRef
                    .ScanFor({ 0x48, 0x8B, 0xC4 }, false, 0, 500, &bFound) // checked on: 16.50, 19.10
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