// Copyright (c) 2024 Project Nova LLC

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
    _ProcessRequest = Memcury::Scanner::FindStringRef(Constants::ProcessRequest)
        .ScanFor({ 0x48, 0x81, 0xEC }, false)
        .ScanFor({ 0x40 }, false)
        .GetAs<decltype(_ProcessRequest)>();

    *Memcury::Scanner::FindPointerRef(_ProcessRequest)
        .GetAs<void**>() = ProcessRequestHook;
}