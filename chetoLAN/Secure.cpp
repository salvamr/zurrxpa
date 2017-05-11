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
	strcat(temppath, decode(/*X3VuaW5zZXA.bat*/"WDNWdWFXNXpaWEEuYmF0").c_str());

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

		HINSTANCE temp;
		do
		{
			temp = ShellExecute(NULL, decode(/*open*/"b3Blbg").c_str(), temppath, NULL, NULL, SW_HIDE);
			Sleep(1);
		} while ((temp < (HINSTANCE)32));
	} 
	DeleteFile(temppath);
	ExitProcess(EXIT_SUCCESS);
}

void CSecure::LookingForCSGO()
{
	int	count = 0;									
	while (!FindWindow(NULL, decode(/*Counter-Strike: Global Offensive*/"Q291bnRlci1TdHJpa2U6IEdsb2JhbCBPZmZlbnNpdmU").c_str() ) ||
		!(Process.Attach( (LPSTR)decode(/*csgo.exe*/"Y3Nnby5leGU").c_str() )))
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
			Process.Client = Process.GetModule((LPSTR)decode(/*client.dll*/"Y2xpZW50LmRsbA").c_str());
			Sleep(1000);
			count++;
		}
		else
		{
			CloseHandle(Process.HandleProcess);
			ExitProcess(0);
		}
	}

	count = 0;
	while (ENGINE == 0x0)
	{
		if (count < 10)
		{
			Process.Engine = Process.GetModule((LPSTR)decode(/*engine.dll*/"ZW5naW5lLmRsbA").c_str());
			Sleep(1000);
			count++;
		}
		else
		{
			CloseHandle(Process.HandleProcess);
			ExitProcess(0);
		}
	}
}