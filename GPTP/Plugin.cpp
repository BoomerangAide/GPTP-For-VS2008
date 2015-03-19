#include "definitions.h"
#include "Plugin.h"
#include <cstring>
#include <cstdio>

//Checks that the plugin's name is within the max length set by MPQDraft
C_ASSERT(sizeof(PLUGIN_NAME) <= MPQDRAFT_MAX_PLUGIN_NAME);
//static_assert(sizeof(PLUGIN_NAME) <= MPQDRAFT_MAX_PLUGIN_NAME,
//  "The plugin's name string is longer than the maximum limit set by MPQDraft");


BOOL WINAPI Plugin::Identify(LPDWORD lpdwPluginID) {
  if (lpdwPluginID == NULL) {
    MessageBox(NULL, "Cannot assign plugin ID", NULL, MB_OK);
    return FALSE;
  }

  *lpdwPluginID = PLUGIN_ID;
  return TRUE;
}

BOOL WINAPI Plugin::GetPluginName(LPSTR lpszPluginName, DWORD nNameBufferLength) {
  if (lpszPluginName == NULL) {
    MessageBox(NULL, "Cannot assign plugin name", NULL, MB_OK);
    return FALSE;
  }

  if (nNameBufferLength < sizeof(PLUGIN_NAME)) {
    MessageBox(NULL, "Plugin name buffer is too short", NULL, MB_OK);
    return FALSE;
  }

  strcpy_s(lpszPluginName, nNameBufferLength, PLUGIN_NAME);
  return TRUE;
}

BOOL WINAPI Plugin::CanPatchExecutable(LPCSTR lpszEXEFileName) {
  if (lpszEXEFileName == NULL) {
    MessageBox(NULL, "Invalid path to patch target executable", NULL, MB_OK);
    return FALSE;
  }

  if (!checkStarCraftExeVersion(lpszEXEFileName))
    return FALSE;

  return TRUE;
}

//Gotta define this in a separate file
//BOOL WINAPI Plugin::Configure(HWND hParentWnd);

BOOL WINAPI Plugin::ReadyForPatch() {
  //By default, nothing to check
  return TRUE;
}

BOOL WINAPI Plugin::GetModules(MPQDRAFTPLUGINMODULE *lpPluginModules, LPDWORD lpnNumModules) {
  if (lpnNumModules == NULL) {
    MessageBox(NULL, "Cannot assign number of modules", NULL, MB_OK);
    return FALSE;
  }

  //By default, the plugin uses no modules
  *lpnNumModules = 0;
  return TRUE;
}

//Gotta define this in a separate file
//BOOL WINAPI Plugin::InitializePlugin(IMPQDraftServer *lpMPQDraftServer);

BOOL WINAPI Plugin::TerminatePlugin() {
  //By default, do nothing
  return TRUE;
}

//Checks the file version of StarCraft.exe.
//If the version is correct, returns TRUE. Otherwise, this displays appropriate
//error messages and returns FALSE.
BOOL Plugin::checkStarCraftExeVersion(LPCSTR exePath) const {
  BOOL result = FALSE;
  DWORD dummy;
  char errorMessage[500];

  const DWORD fileVersionInfoBufferSize = GetFileVersionInfoSize(exePath, &dummy);

  if (fileVersionInfoBufferSize > 0) {
    VOID *fileVersionInfoBuffer = new BYTE[fileVersionInfoBufferSize];
    VS_FIXEDFILEINFO *fileInfo;
    UINT fileInfoSize;

    if (GetFileVersionInfo(exePath, NULL, fileVersionInfoBufferSize, fileVersionInfoBuffer)
      && VerQueryValue(fileVersionInfoBuffer, "\\", (LPVOID*)&fileInfo, &fileInfoSize))
    {
      //The FileVersion of StarCraft.exe must be 1.16.1.1
      const WORD requiredVersion[4] = {1, 16, 1, 1};
      const WORD currentVersion[4] = {
        HIWORD(fileInfo->dwFileVersionMS), LOWORD(fileInfo->dwFileVersionMS),
        HIWORD(fileInfo->dwFileVersionLS), LOWORD(fileInfo->dwFileVersionLS)
      };

      if (requiredVersion[0] == currentVersion[0]
          && requiredVersion[1] == currentVersion[1]
          && requiredVersion[2] == currentVersion[2]
          && requiredVersion[3] == currentVersion[3])
      {
        result = TRUE;
      }
      else
      if (   currentVersion[0] == 1
          && currentVersion[1] == 0
          && currentVersion[2] == 0
          && currentVersion[3] == 2) 
      {
	sprintf_s(
	    errorMessage,
	    "Error: GPTP cannot patch %s"
	    "\n"
	    "\n StarEdit may be able to be loaded, but the plugin features"
	    "\n cannot connect, so the mod is more likely to be incompatible"
	    "\n with the map editor than mods not using GPTP.",
	    exePath
	    );
      }
      else {
        sprintf_s(errorMessage,
          "Error: Cannot patch %s"
          "\n"
          "\nThis plugin (" PLUGIN_NAME ") is incompatible with the current version of StarCraft."
          " The game will still be loaded, but no plugin features will be available."
          "\n"
          "\nCurrent StarCraft version: %hu.%hu.%hu.%hu"
          "\nRequired StarCraft version: %hu.%hu.%hu.%hu",
          exePath,
          currentVersion[0],  currentVersion[1],  currentVersion[2],  currentVersion[3],
          requiredVersion[0], requiredVersion[1], requiredVersion[2], requiredVersion[3]);
      }
    }
    else {
      sprintf_s(errorMessage, "Cannot retrieve version information from:\n  %s", exePath);
    }
    delete [] fileVersionInfoBuffer;
  }
  else {
    sprintf_s(errorMessage, "Cannot retrieve version information size from:\n  %s", exePath);
  }

  if (!result)
    MessageBox(NULL, errorMessage, NULL, MB_OK);
  return result;
}
