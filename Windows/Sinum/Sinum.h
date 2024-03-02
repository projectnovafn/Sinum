// Copyright (c) 2024 Project Nova LLC

#pragma once
#include "../framework.h"

class FCurlHttpRequest
{
private:
	unsigned char Pad[0x58];

public:

	FString URL;
};

namespace Sinum
{
	static bool IsPastUAC = false;

	static bool (*_ProcessRequest)(FCurlHttpRequest*);
	static bool ProcessRequestHook(FCurlHttpRequest* Request);

	void Init();
}