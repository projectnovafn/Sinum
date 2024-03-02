// Copyright (c) 2024 Project Nova LLC

#include "Sinum.h"

bool Sinum::ProcessRequestHook(FCurlHttpRequest* Request)
{
    std::wstring URL(Request->URL.c_str());
    size_t PathIndex = URL.find(L"ol.epicgames.com");

    if (PathIndex != std::wstring::npos)
    {
        auto Path = URL.substr(PathIndex + 4);
        auto NewURL = Constants::API_URL + Path;

        Request->URL = NewURL.c_str();
    }

    return _ProcessRequest(Request);
}

void Sinum::Init()
{
    _ProcessRequest = Memcury::Scanner::FindStringRef(Constants::ProcessRequest)
        .ScanFor({ Memcury::ASM::MNEMONIC::PUSH, 0x53 }, false)
        .GetAs<decltype(_ProcessRequest)>();

    *Memcury::Scanner::FindPointerRef(_ProcessRequest)
        .GetAs<void**>() = ProcessRequestHook;
}