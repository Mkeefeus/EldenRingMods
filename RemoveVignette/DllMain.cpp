#include <Windows.h>

#include "ModUtils.h"

using namespace ModUtils;

DWORD WINAPI MainThread(LPVOID lpParam)
{
	Log("Activating RemoveVignette...");
	std::vector<uint16_t> pattern = { 0xf3, 0x0f, 0x10, MASKED, MASKED, 0xf3, 0x0f, 0x59, MASKED, MASKED, MASKED, MASKED, MASKED, 0xe8, MASKED, MASKED, MASKED, MASKED, 0xf3, 0x41, 0x0f, MASKED, MASKED, 0xf3, 0x45, 0x0f, MASKED, MASKED, 0x4c, 0x8d, MASKED, MASKED, MASKED, MASKED, MASKED, MASKED, 0x48 };
	std::vector<uint16_t> originalBytes = { 0xf3, 0x45, 0x0f, 0x59, 0xc2 };
	std::vector<uint8_t> newBytes = { 0xf3, 0x0f, 0x5c, 0xc0, 0x90 };
	uintptr_t patchAddress = SigScan(pattern);
	if (patchAddress != 0)
	{
		patchAddress += 0x17;
		Replace(patchAddress, originalBytes, newBytes);
	}
	CloseLog();
	return 0;
}

BOOL WINAPI DllMain(HINSTANCE module, DWORD reason, LPVOID)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(module);
		CreateThread(0, 0, &MainThread, 0, 0, NULL);
	}
	return 1;
}