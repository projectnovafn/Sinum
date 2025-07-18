#pragma once

class FCurlHttpRequest;

namespace EOS
{
	static bool (*_ProcessRequest)(FCurlHttpRequest*);
	static bool ProcessRequestHook(FCurlHttpRequest* Request);

	void Init();
}