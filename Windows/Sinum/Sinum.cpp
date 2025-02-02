// Copyright (c) 2024 Project Nova LLC

#include "Sinum.h"
#include <iostream>

bool Sinum::ProcessRequestHook(FCurlHttpRequest* Request)
{
    std::wstring URL(Request->GetURL().c_str());
    size_t PathIndex = URL.find(L"ol.epicgames.com");

    static bool bQueriedProfile = false;

    if (!bQueriedProfile)
    {
        if (URL.find(L"QueryProfile") != std::string::npos)
        {
            std::cout << "First query profile!\n";
            auto RequestExitWithStatusAddr = Memcury::Scanner::FindPattern("48 89 5C 24 ? 57 48 83 EC 40 41 B9 ? ? ? ? 0F B6 F9 44 38 0D ? ? ? ? 0F B6 DA 72 24 89 5C 24 30 48 8D 05 ? ? ? ? 89 7C 24 28 4C 8D 05 ? ? ? ? 33 D2 48 89 44 24 ? 33 C9 E8 ? ? ? ?");

            if (!RequestExitWithStatusAddr.IsValid())
            {
                RequestExitWithStatusAddr = Memcury::Scanner::FindPattern("48 8B C4 48 89 58 18 88 50 10 88 48 08 57 48 83 EC 30"); // ion know whta version this for

                if (!RequestExitWithStatusAddr.IsValid())
                    RequestExitWithStatusAddr = Memcury::Scanner::FindPattern("4C 8B DC 49 89 5B 08 49 89 6B 10 49 89 73 18 49 89 7B 20 41 56 48 83 EC 30 80 3D ? ? ? ? ? 49 8B"); // dk how often this change
            }

            if (!RequestExitWithStatusAddr.IsValid())
            {
                std::cout << "Invalid RequestExitWithStatusAddr!";
            }
            else
            {
                auto RequestExitWithStatusPtr = RequestExitWithStatusAddr.GetAs<uint8_t*>();

                DWORD oldProtect;
                VirtualProtect((void*)RequestExitWithStatusPtr, 2, PAGE_EXECUTE_READWRITE, &oldProtect);
                *RequestExitWithStatusPtr = 0xC3;
                VirtualProtect((void*)RequestExitWithStatusPtr, 2, oldProtect, &oldProtect);
            }

            bQueriedProfile = true;
        }
    }

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
    return;
    // S16+ has the Chapter 1 one so...
    auto StringRef = Memcury::Scanner::FindStringRef(Constants::ProcessRequest_C2);

    if (StringRef.IsValid())
    {
        std::cout << "Attempting S16+..\n";

        // For S16+
        _ProcessRequest = StringRef
            .ScanFor({ 0x48, 0x8B, 0xC4 }, false, 0, 300)
            .GetAs<decltype(_ProcessRequest)>();

        // S11-S15
        if (!_ProcessRequest)
        {
            std::cout << "Falling back to older Chapter 2!\n";
            _ProcessRequest = Memcury::Scanner::FindStringRef(Constants::ProcessRequest_C2)
                .ScanFor({ 0x4C, 0x8B, 0xDC }, false)
                .GetAs<decltype(_ProcessRequest)>();
        }
    }
    else
    {
        StringRef = Memcury::Scanner::FindStringRef(Constants::ProcessRequest);
        if (StringRef.IsValid())
        {
            std::cout << "Attempting Chapter 1....\n";

            _ProcessRequest = StringRef
                .ScanFor({ 0x48, 0x81, 0xEC }, false)
                .ScanFor({ 0x40 }, false)
                .GetAs<decltype(_ProcessRequest)>();
        }
        else
        {
            std::cout << "Unable to find ANY string references!";
            return;
        }
    }

    auto RequestExitWithStatusAddr = Memcury::Scanner::FindPattern("48 89 5C 24 ? 57 48 83 EC 40 41 B9 ? ? ? ? 0F B6 F9 44 38 0D ? ? ? ? 0F B6 DA 72 24 89 5C 24 30 48 8D 05 ? ? ? ? 89 7C 24 28 4C 8D 05 ? ? ? ? 33 D2 48 89 44 24 ? 33 C9 E8 ? ? ? ?");

    if (!RequestExitWithStatusAddr.IsValid())
    {
        RequestExitWithStatusAddr = Memcury::Scanner::FindPattern("48 8B C4 48 89 58 18 88 50 10 88 48 08 57 48 83 EC 30"); // ion know whta version this for

        if (!RequestExitWithStatusAddr.IsValid())
            RequestExitWithStatusAddr = Memcury::Scanner::FindPattern("4C 8B DC 49 89 5B 08 49 89 6B 10 49 89 73 18 49 89 7B 20 41 56 48 83 EC 30 80 3D ? ? ? ? ? 49 8B"); // dk how often this change
    }

    if (!RequestExitWithStatusAddr.IsValid())
    {
        std::cout << "Invalid RequestExitWithStatusAddr!";
    }
    else
    {
        auto RequestExitWithStatusPtr = RequestExitWithStatusAddr.GetAs<uint8_t*>();

        DWORD oldProtect;
        VirtualProtect((void*)RequestExitWithStatusPtr, 2, PAGE_EXECUTE_READWRITE, &oldProtect);
        *RequestExitWithStatusPtr = 0xC3;
        VirtualProtect((void*)RequestExitWithStatusPtr, 2, oldProtect, &oldProtect);
    }

    std::cout << "Finding ref for: 0x" << std::hex << __int64(_ProcessRequest) - __int64(GetModuleHandleW(0)) << '\n';
    auto PtrRef = Memcury::Scanner::FindPointerRef(_ProcessRequest);
    *PtrRef.GetAs<void**>() = ProcessRequestHook;
}