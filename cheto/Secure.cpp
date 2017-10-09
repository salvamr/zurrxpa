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