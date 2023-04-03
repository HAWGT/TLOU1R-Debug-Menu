// dllmain.cpp : Defines the entry point for the DLL application.
#include "Helpers.h"

char __fastcall hk_IsReleaseBuild(__int64 a1);

void EnableDebugMenu()
{
    BYTE* Orig_IsReleaseBuild = PatternScan("80 B9 2F 3F 00 00 00");
    if (!Orig_IsReleaseBuild) return;
    Detour64(Orig_IsReleaseBuild, (BYTE*)hk_IsReleaseBuild, 16);
}

char __fastcall hk_IsReleaseBuild(__int64 a1)
{
    *(byte*)(a1 + 0x3F2F) = 1;
    return *(byte*)(a1 + 0x4900);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)EnableDebugMenu, hModule, 0, nullptr);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
