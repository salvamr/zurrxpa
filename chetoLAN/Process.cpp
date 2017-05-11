#include "Process.h"

CProcess Process;

Module CProcess::GetModule(char* moduleName)
{
	HANDLE module = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, PID);
	MODULEENTRY32 mEntry;
	mEntry.dwSize = sizeof(mEntry);

	do
	{
		if (!strcmp(mEntry.szModule, (LPSTR)moduleName))
		{
			CloseHandle(module);

			Module mod = { (DWORD)mEntry.hModule, mEntry.modBaseSize };
			return mod;
		}
	} while (Module32Next(module, &mEntry));

	Module mod = { (DWORD)false, (DWORD)false };
	return mod;
}

int CProcess::GetProcID(string ProcName)
{
	HANDLE ProcSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 PE32;

	if (ProcSnapshot == INVALID_HANDLE_VALUE)
		return 0;

	PE32.dwSize = sizeof(PROCESSENTRY32);

	if (!Process32First(ProcSnapshot, &PE32))
	{
		CloseHandle(ProcSnapshot);
		return 0;
	}
	else

		if (PE32.szExeFile == ProcName)
		{
			CloseHandle(ProcSnapshot);
			return PE32.th32ProcessID;
		}
		else
		{
			do
			{
				if (PE32.szExeFile == ProcName)
				{
					CloseHandle(ProcSnapshot);
					return PE32.th32ProcessID;
				}
			} while (Process32Next(ProcSnapshot, &PE32));
			CloseHandle(ProcSnapshot);
			return 0;
		}
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
			PID = entry.th32ProcessID;
			CloseHandle(handle);

			HandleProcess = OpenProcess(rights, false, PID);

			return true;
		}
	} while (Process32Next(handle, &entry));

	return false;
}

void CProcess::Detach()
{
	CloseHandle(HandleProcess);
}

