#include "../framework.h"

#include "EOS.h"

#include "Unreal/CurlHttp.h"

bool EOS::ProcessRequestHook(FCurlHttpRequest* Request)
{
	return _ProcessRequest(Request->RedirectRequest());
}

void EOS::Init()
{
	auto EOSHandle = (uintptr_t)GetModuleHandleA("EOSSDK-Win64-Shipping.dll");
	if (!EOSHandle) return;

	auto ProcessRequestStrRef = Memcury::Scanner::FindStringRef(L"ProcessRequest failed. URL '%s' is not using a whitelisted domain. %p", EOSHandle);

	_ProcessRequest = ProcessRequestStrRef
		.ScanFor({ 0x48, 0x89, 0x5C }, false)
		.GetAs<decltype(_ProcessRequest)>();

	auto ProcessRequestRef = Memcury::Scanner::FindPointerRef(_ProcessRequest, EOSHandle);

	DWORD dwProtection;
	VirtualProtect(ProcessRequestRef.GetAs<PVOID>(), 8, PAGE_EXECUTE_READWRITE, &dwProtection);

	*ProcessRequestRef.GetAs<void**>() = ProcessRequestHook;

	DWORD dwTemp;
	VirtualProtect(ProcessRequestRef.GetAs<PVOID>(), 8, dwProtection, &dwTemp);
}