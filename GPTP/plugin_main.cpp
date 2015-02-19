#include "Plugin.h"

//The main for users is hooks/game_hooks.cpp

Plugin plugin;

BOOL WINAPI GetMPQDraftPlugin(IMPQDraftPlugin **lppMPQDraftPlugin) {
  *lppMPQDraftPlugin = &plugin;
  return TRUE;
}

BOOL WINAPI DllMain(HINSTANCE hModule, DWORD fdwReason, LPVOID lpReserved) {
  switch (fdwReason) {
    case DLL_PROCESS_ATTACH:
      break;

    case DLL_PROCESS_DETACH:
      break;

    case DLL_THREAD_ATTACH:
      break;

    case DLL_THREAD_DETACH:
      break;
  }

  return TRUE;
}
