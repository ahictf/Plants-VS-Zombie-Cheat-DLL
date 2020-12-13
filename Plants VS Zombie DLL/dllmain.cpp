// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include "mem.h"
#include "proc.h"

DWORD WINAPI HackThread(HMODULE hModule)
{
	// Create console
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);

	std::cout << "\n";
	std::cout << " [NUMPAD1] Hack Money 999999.\n";
	std::cout << " [NUMPAD2] Hack Sun 999999.\n";
	std::cout << " [NUMPAD3] Hack Item Delay.\n";
	std::cout << " [NUMPAD4] GOD MODE Plants.\n";
	std::cout << " [NUMPAD5] One Shoot Kill Zombie.\n";
	 

	//get module base
	uintptr_t moduleBase = (uintptr_t)GetModuleHandle(L"popcapgame1.exe");

	bool bMoney = false, bSun = false, bItemCoulddown = false, bGMPlants = false, bOSOK = false;
	

	//hack loop
	while (true)
	{
		//key input

		if (GetAsyncKeyState(VK_END) & 1)
		{
			break;
		}

		if (GetAsyncKeyState(VK_NUMPAD1) & 1)
		{
			bMoney = !bMoney;
		}

		if (GetAsyncKeyState(VK_NUMPAD2) & 1)
		{
			bSun = !bSun;
		}

		if (GetAsyncKeyState(VK_NUMPAD3) & 1)
		{
			bItemCoulddown = !bItemCoulddown;
			if (bItemCoulddown)
			{
				mem::Patch((BYTE*)(moduleBase + 0x91E4C), (BYTE*)"\x81\x47\x24\x00\x02\x00\x00\x90\x90", 9);
			}
			else {
				mem::Patch((BYTE*)(moduleBase + 0x91E4C), (BYTE*)"\xFF\x47\x24\x8B\x47\x24\x3B\x47\x28", 9);
			}
		}

		if (GetAsyncKeyState(VK_NUMPAD4) & 1)
		{
			bGMPlants = !bGMPlants;
			if (bGMPlants)
			{
				mem::Nop((BYTE*)(moduleBase + 0x140680), 7);
			}
			else {
				mem::Patch((BYTE*)(moduleBase + 0x140680), (BYTE*)"\x83\x46\x40\xFC\x8B\x4E\x40", 7);
			}
		}
		if (GetAsyncKeyState(VK_NUMPAD5) & 1)
		{
			bOSOK = !bOSOK;
			if (bOSOK)
			{
				mem::Patch((BYTE*)(moduleBase + 0x141CE4), (BYTE*)"\xC7\x87\xC8\x00\x00\x00\x99\x99\x99\x99\x90", 11);
			}
			else {
				mem::Patch((BYTE*)(moduleBase + 0x141CE4), (BYTE*)"\x89\xAF\xC8\x00\x00\x00\xE8\x91\xC3\xFF\xFF", 11);
			}
		}
		//continus write/freeze
		uintptr_t* localPlayerPtr = (uintptr_t*)(moduleBase + 0x329670);

		if (localPlayerPtr)
		{
			if (bMoney)
			{
				uintptr_t numMoney = mem::FindDMAAddy(moduleBase + 0x329670, { 0x94C, 0x50 });
				int* num = (int*)numMoney;
				*num = 999999;
				// or *(int*)mem::FindDMAAddy(moduleBase + 0x329670, { 0x94C, 0x50 }) = 99999;
			}

			if (bSun)
			{
				uintptr_t numSun = mem::FindDMAAddy(moduleBase + 0x329670, { 0x868, 0x5578 });
				int* num = (int*)numSun;
				*num = 999999;
			}
		}
		Sleep(5);
	}

	

	//cleanup & eject
	fclose(f);
	FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
	{
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr));
	}
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

