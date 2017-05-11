#include "Secure.h"

CSecure Secure;

void CSecure::BorrarZurrapa()
{
	// temporary .bat file
	static char templ[] =
		":Repeat\r\n"
		"del \"%s\"\r\n"
		"if exist \"%s\" goto Repeat\r\n"
		"rmdir \"%s\"\r\n"
		"del \"%s\"";


	char modulename[_MAX_PATH];    // absolute path of calling .exe file
	char temppath[_MAX_PATH];      // absolute path of temporary .bat file
	char folder[_MAX_PATH];

	GetModuleFileName(NULL, modulename, MAX_PATH);
	strcpy(folder, modulename);
	char *pb = strrchr(folder, '\\');
	if (pb != NULL)
		*pb = 0;

	HANDLE hf;

	GetTempPath(_MAX_PATH, temppath);
	strcat(temppath, "X3VuaW5zZXA.bat");

	hf = CreateFile(temppath, GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hf != INVALID_HANDLE_VALUE)
	{
		DWORD len;
		char *bat;

		bat = (char*)_malloca(strlen(templ) +
			strlen(modulename) * 2 + strlen(temppath) + 20);

		wsprintf(bat, templ, modulename, modulename, folder, temppath);

		WriteFile(hf, bat, strlen(bat), &len, NULL);
		CloseHandle(hf);

		while (ShellExecute(NULL, "open", temppath, NULL, NULL, SW_HIDE) < (HINSTANCE)32)
		{
			Sleep(1);
		}
	} 
	DeleteFile(temppath);
	ExitProcess(EXIT_SUCCESS);
}

void CSecure::LookingForCSGO()
{
	Print.it("2 minutes left to launch CS:GO");
	Print.it("Waiting for CSGO ");

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
			Print.error("Client.dll not located");
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
			Print.error("Engine.dll not located");
		}
	}
}