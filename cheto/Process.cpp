#include "Process.h"

CProcess Process;

HMODULE CProcess::GetModule(char* moduleName)
{
	HMODULE hMods[1024];
	DWORD cbNeeded;

	// Get a list of all the modules in this process.

	if (EnumProcessModules(HandleProcess, hMods, sizeof(hMods), &cbNeeded))
	{
		for (unsigned int i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
		{
			char szModName[MAX_PATH];

			// Get the full path to the module's file.

			if (GetModuleFileNameEx(HandleProcess, hMods[i], szModName,
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

MODULEINFO CProcess::GetModuleInfo(HMODULE module)
{
	MODULEINFO moduleInfo = { 0 };
	GetModuleInformation(HandleProcess, module, &moduleInfo, sizeof(moduleInfo));
	return moduleInfo;
}

bool CProcess::Attach(char* pName, DWORD rights)
{
	HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(entry);

	do
	{
		if (!strcmp(entry.szExeFile, pName))
		{
			CloseHandle(handle);

			HandleProcess = OpenProcess(rights, false, entry.th32ProcessID);

			return true;
		}
	} while (Process32Next(handle, &entry));

	return false;
}

void CProcess::Detach()
{
	CloseHandle(HandleProcess);
}

