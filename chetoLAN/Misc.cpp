#include "Misc.h"
#include "Secure.h"

CMisc::CMisc()
{
	localPlayer = new CLocalPlayer();
}

CMisc::~CMisc()
{
}

void CMisc::featurePanicKey()
{
	if (GetAsyncKeyState(Settings.PanicKey))
	{
		Beep(500, 500);
		CloseHandle(Process.HandleProcess);
		ExitProcess(0);
	}
}
void CMisc::featureReloadKey()
{
	if (GetAsyncKeyState(Settings.ReloadKey))
	{
		Beep(500, 100);
		Settings.Load();
		Beep(500, 100);
	}
}

void CMisc::Main()
{
	while (FindWindow(NULL, "Counter-Strike: Global Offensive"))
	{
		featurePanicKey();
		featureReloadKey();
		Sleep(50);
	}
}
