#include "../../framework.h"

#include "CurlHttp.h"

FString FCurlHttpRequest::GetURL()
{
	FString Result;
	return ((FString& (*)(FCurlHttpRequest*, FString&))(*VTable))(this, Result);
}

void FCurlHttpRequest::SetURL(FString URL)
{
	((void (*)(FCurlHttpRequest*, FString&))(VTable[10]))(this, URL);
}

FCurlHttpRequest* FCurlHttpRequest::RedirectRequest()
{
    std::wstring URL(this->GetURL().c_str());

    const std::vector<std::wstring> Domains = {
        L"game-social.epicgames.com",
        L"ol.epicgames.com",
        L"ol.epicgames.net",
        L"on.epicgames.com",
        L"ak.epicgames.com",
        L"epicgames.dev"
    };

    for (const auto& Domain : Domains)
    {
        size_t PathIndex = URL.find(Domain);
        if (PathIndex != std::wstring::npos)
        {
            size_t PathStart = PathIndex + Domain.length();

            std::wstring Path = URL.substr(PathStart);
            std::wstring NewURL = Constants::API_URL + Path;

            this->SetURL(NewURL.c_str());
            break;
        }
    }

    return this;
}