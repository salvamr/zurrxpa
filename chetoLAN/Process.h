#ifndef __PROCESS_H__
#define __PROCESS_H__

#include "Include.h"

class CProcess
{
public:
	HANDLE HandleProcess;

	HMODULE Client;
	HMODULE Engine;

	HMODULE GetModules(char*);
	HANDLE NewProcess(std::string);
	MODULEINFO GetModuleInfo(HMODULE module);
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