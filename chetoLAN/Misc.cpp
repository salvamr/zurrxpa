#include "Misc.h"

CMisc Misc;

void CMisc::featurePanicKey()
{
	if (GetAsyncKeyState(Settings.PanicKey))
	{
		Beep(500, 500);
		CloseHandle(Process.HandleProcess);
		ExitProcess(EXIT_SUCCESS);
	}
	else
	{
		return;
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
	else
	{
		return;
	}
}

void CMisc::Main()
{
	featurePanicKey();
	featureReloadKey();
}
