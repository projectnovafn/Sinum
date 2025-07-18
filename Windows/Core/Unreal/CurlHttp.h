#pragma once

class FCurlHttpRequest
{
private:
	void** VTable;

public:

	class FString GetURL();
	void SetURL(FString URL);

	FCurlHttpRequest* RedirectRequest();
};