#include <Windows.h>

#include "Secure.h"
#include "Printing.h"
#include "Process.h"

CSecure Secure;

void CSecure::LookingForCSGO()
{
	Print::it("2 minutes left to launch CS:GO");
	Print::it("Waiting for CSGO ");

	int	count = 0;									
	while (!FindWindow(NULL, "Counter-Strike: Global Offensive" ) ||
		!(Process.Attach( "csgo.exe" )))
	{
		if (count < 120)
		{
			Sleep(1000);
			count++;
		}
		else
		{
			ExitProcess(EXIT_SUCCESS);
		}
	}

	count = 0;
	while (CLIENT == 0x0)
	{
		if (count < 10)
		{
			Process.Client = Process.GetModule("client.dll");
			Sleep(1000);
			count++;
		}
		else
		{
			Print::error("Client.dll not located");
		}
	}

	count = 0;
	while (ENGINE == 0x0)
	{
		if (count < 10)
		{
			Process.Engine = Process.GetModule("engine.dll");
			Sleep(1000);
			count++;
		}
		else
		{
			Print::error("Engine.dll not located");
		}
	}
}

void CSecure::LookingForCSGOLAN()
{
	int count = 0;
	while (CLIENT == 0x0)
	{
		if (count < 20)
		{
			Process.Client = Process.GetModule("client.dll");
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
			Process.Engine = Process.GetModule("engine.dll");
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