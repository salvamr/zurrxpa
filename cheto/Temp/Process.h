#ifndef __PROCESS_H__
#define __PROCESS_H__

#include "Include.h"
struct Module
{
	DWORD Base;
	DWORD Size;
};
class CProcess
{
public:
	MODULEENTRY32	ME32;

	HANDLE HandleProcess;

	DWORD PID;
	DWORD SteamPID;

	Module Client;
	Module Engine;

	bool Attached;

	Module GetModule(char* moduleName);
	int GetProcID(string ProcName);
	bool Attach(char* pName, DWORD rights = PROCESS_ALL_ACCESS);
	void Detach();

	template <class T>
	T Read(DWORD addr) {
		T _read;
		ReadProcessMemory(HandleProcess, (LPVOID)addr, &_read, sizeof(T), NULL);
		return _read;
	}
	template <class T>
	void Write(DWORD addr, T val) {
		WriteProcessMemory(HandleProcess, (LPVOID)addr, &val, sizeof(T), NULL);
	}
};

extern CProcess* Process;

#endif
