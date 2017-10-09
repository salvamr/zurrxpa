#include "Process.h"

#include <Windows.h>
#include "Settings.h"

CProcess Process;

HMODULE CProcess::GetModules(char* moduleName)
{
	HMODULE hMods[1024];
	DWORD cbNeeded;

	// Get a list of all the modules in this process.

	if (EnumProcessModules(Process.HandleProcess, hMods, sizeof(hMods), &cbNeeded))
	{
		for (unsigned int i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
		{
			char szModName[260];

			// Get the full path to the module's file.

			if (GetModuleFileNameEx(Process.HandleProcess, hMods[i], szModName,
				sizeof(szModName) / sizeof(TCHAR)))
			{
				// Print the module name and handle value.
				
				if (strcmp(PathFindFileName(szModName), moduleName) == 0)
				{
					//cout << "Path: " << PathFindFileName(szModName) << " Base: " << hMods[i] << endl;
					return hMods[i];
				}
			}
		}
	}

	return NULL;
}

HANDLE CProcess::NewProcess(std::string launchOptions)
{
	PROCESS_INFORMATION             pi = { 0 };
	STARTUPINFOA                    si = { 0 };
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_HIDE;
	
	std::string FullPath
	(
		Settings.gameLocation + (" -steam " + launchOptions)
	);
	
	if (FindWindow(NULL, "Counter-Strike: Global Offensive"))
	{
		MessageBox(NULL, "Please, do not launch the cheat with CSGO opened", "Zurrapa", MB_ICONERROR | MB_OK);
		ExitProcess(0);
	}

	if (!CreateProcessA(
		nullptr, (LPSTR)FullPath.c_str(),
		nullptr, nullptr, FALSE, FALSE,
		nullptr, nullptr, &si, &pi))
	{
		MessageBox(NULL, "Unable to launch CSGO", "Zurrapa", MB_ICONERROR | MB_OK);
		ExitProcess(0);
	}

	CloseHandle(pi.hThread);

	return pi.hProcess;
}

MODULEINFO CProcess::GetModuleInfo(HMODULE module)
{
	MODULEINFO moduleInfo = { 0 };
	GetModuleInformation(Process.HandleProcess, module, &moduleInfo, sizeof(moduleInfo));
	return moduleInfo;
}

