
#ifndef _h_process
#define _h_process

#include "Include.h"

class CProcess
{
public:

	HANDLE HandleProcess;

	HMODULE Client;
	HMODULE Engine;

	HMODULE GetModule(char*);
	MODULEINFO GetModuleInfo(HMODULE module);
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

extern CProcess Process;

#endif