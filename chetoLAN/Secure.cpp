#include "Secure.h"
#include "Process.h"

CSecure Secure;

void CSecure::LookingForCSGO()
{
	int count = 0;
	while (CLIENT == 0x0)
	{
		if (count < 20)
		{
			Process.Client = Process.GetModules("client.dll");
			Sleep(1000);
			count++;
		}
		else
		{
			MessageBox(NULL, "client.dll not found", "Zurrapa", MB_ICONERROR | MB_OK);
			CloseHandle(Process.HandleProcess);
			ExitProcess(0);
		}
	}

	count = 0;
	while (ENGINE == 0x0)
	{
		if (count < 20)
		{
			Process.Engine = Process.GetModules("engine.dll");
			Sleep(1000);
			count++;
		}
		else
		{
			MessageBox(NULL, "engine.dll not found", "Zurrapa", MB_ICONERROR | MB_OK);
			CloseHandle(Process.HandleProcess);
			ExitProcess(0);
		}
	}
}