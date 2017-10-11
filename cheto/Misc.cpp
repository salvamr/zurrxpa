#include "Misc.h"

#include "Settings.h"
#include "Process.h"
#include "Offsets.h"

#include <Windows.h>

CMisc::CMisc()
{
	localPlayer = new CLocalPlayer();
}

CMisc::~CMisc()
{
	delete localPlayer;
}

void CMisc::featureNoFlash()
{
	if (Settings.NoFlash)
	{
		if (Process.Read<int>(localPlayer->GetPlayer() + Offset.m_flFlashDuration) > 0)
			Process.Write<int>(localPlayer->GetPlayer() + Offset.m_flFlashDuration, 0);
	}
}

void CMisc::featurePanicKey()
{
	if (GetAsyncKeyState(Settings.PanicKey))
	{
		Beep(500, 500);
		CloseHandle(Process.HandleProcess);
		ExitProcess(EXIT_SUCCESS);
	}
}

void CMisc::featureReloadKey()
{
	if (GetAsyncKeyState(Settings.ReloadKey))
	{
		Beep(500, 100);
		Settings.Load(Settings.hwid);
		Beep(500, 100);
	}
}

void CMisc::featureHideWindow()
{
	if (Settings.HideWindow)
	{
		FreeConsole();
	}
}

void CMisc::featureMarioBrosSong()
{
	if (GetAsyncKeyState(Settings.SuperMarioBrosKey) & 0x8000)
	{
		Beep(330, 100); Sleep(50);
		Beep(330, 100); Sleep(150);
		Beep(330, 100); Sleep(150);
		Beep(262, 100); Sleep(50);
		Beep(330, 100); Sleep(150);
		Beep(392, 100); Sleep(350);
		Beep(196, 100); Sleep(350);
		Beep(262, 300); Sleep(150);
		Beep(196, 300); Sleep(150);
		Beep(164, 300); Sleep(150);
		Beep(220, 300); Sleep(50);
		Beep(246, 100); Sleep(150);
		Beep(233, 200);
		Beep(220, 100); Sleep(150);
		Beep(196, 100); Sleep(100);
		Beep(330, 100); Sleep(100);
		Beep(392, 100); Sleep(100);
		Beep(440, 100); Sleep(150);
		Beep(349, 100); Sleep(50);
		Beep(392, 100); Sleep(150);
		Beep(330, 100); Sleep(150);
		Beep(262, 100); Sleep(50);
		Beep(294, 100); Sleep(50);
		Beep(247, 100); Sleep(500);
		Beep(262, 300); Sleep(150);
		Beep(196, 300); Sleep(150);
		Beep(164, 300); Sleep(150);
		Beep(220, 300); Sleep(50);
		Beep(246, 100); Sleep(150);
		Beep(233, 200);
		Beep(220, 100); Sleep(150);
		Beep(196, 100); Sleep(100);
		Beep(330, 100); Sleep(100);
		Beep(392, 100); Sleep(100);
		Beep(440, 100); Sleep(150);
		Beep(349, 100); Sleep(50);
		Beep(392, 100); Sleep(150);
		Beep(330, 100); Sleep(150);
		Beep(262, 100); Sleep(50);
		Beep(294, 100); Sleep(50);
		Beep(247, 100); Sleep(900);
		Beep(392, 100); Sleep(50);
		Beep(370, 100); Sleep(50);
		Beep(349, 100); Sleep(50);
		Beep(311, 100); Sleep(150);
		Beep(330, 100); Sleep(150);
		Beep(207, 100); Sleep(50);
		Beep(220, 100); Sleep(50);
		Beep(262, 100); Sleep(150);
		Beep(220, 100); Sleep(50);
		Beep(262, 100); Sleep(50);
		Beep(294, 100); Sleep(500);
		Beep(392, 100); Sleep(50);
		Beep(370, 100); Sleep(50);
		Beep(349, 100); Sleep(50);
		Beep(311, 100); Sleep(150);
		Beep(330, 100); Sleep(150);
		Beep(523, 100); Sleep(150);
		Beep(523, 100); Sleep(50);
		Beep(523, 100); Sleep(1100);
		Beep(392, 100); Sleep(50);
		Beep(370, 100); Sleep(50);
		Beep(349, 100); Sleep(50);
		Beep(311, 100); Sleep(150);
		Beep(330, 100); Sleep(150);
		Beep(207, 100); Sleep(50);
		Beep(220, 100); Sleep(50);
		Beep(262, 100); Sleep(150);
		Beep(220, 100); Sleep(50);
		Beep(262, 100); Sleep(50);
		Beep(294, 100); Sleep(500);
		Beep(311, 300); Sleep(150);
		Beep(296, 300); Sleep(150);
		Beep(262, 300); Sleep(1300);
		Beep(262, 100); Sleep(50);
		Beep(262, 100); Sleep(150);
		Beep(262, 100); Sleep(150);
		Beep(262, 100); Sleep(50);
		Beep(294, 100); Sleep(150);
		Beep(330, 200); Sleep(50);
		Beep(262, 200); Sleep(50);
		Beep(220, 200); Sleep(50);
		Beep(196, 100); Sleep(350);
		Beep(262, 100); Sleep(50);
		Beep(262, 100); Sleep(150);
		Beep(262, 100); Sleep(150);
		Beep(262, 100); Sleep(50);
		Beep(294, 100); Sleep(50);
		Beep(330, 100); Sleep(350);
		Beep(440, 100); Sleep(150);
		Beep(392, 100); Sleep(500);
		Beep(262, 100); Sleep(50);
		Beep(262, 100); Sleep(150);
		Beep(262, 100); Sleep(150);
		Beep(262, 100); Sleep(50);
		Beep(294, 100); Sleep(150);
		Beep(330, 200); Sleep(50);
		Beep(262, 200); Sleep(50);
		Beep(220, 200); Sleep(50);
		Beep(196, 100); Sleep(350);
		//Intro
		Beep(330, 100); Sleep(50);
		Beep(330, 100); Sleep(150);
		Beep(330, 100); Sleep(150);
		Beep(262, 100); Sleep(50);
		Beep(330, 100); Sleep(150);
		Beep(392, 100); Sleep(350);
		Beep(196, 100); Sleep(350);
		Beep(196, 100); Sleep(63);
		Beep(262, 100); Sleep(63);
		Beep(330, 100); Sleep(63);
		Beep(392, 100); Sleep(63);
		Beep(523, 100); Sleep(63);
		Beep(660, 100); Sleep(63);
		Beep(784, 100); Sleep(288);
		Beep(660, 100); Sleep(288);
		Beep(207, 100); Sleep(63);
		Beep(262, 100); Sleep(63);
		Beep(311, 100); Sleep(63);
		Beep(415, 100); Sleep(63);
		Beep(523, 100); Sleep(63);
		Beep(622, 100); Sleep(63);
		Beep(830, 100); Sleep(288);
		Beep(622, 100); Sleep(288);
		Beep(233, 100); Sleep(63);
		Beep(294, 100); Sleep(63);
		Beep(349, 100); Sleep(63);
		Beep(466, 100); Sleep(63);
		Beep(587, 100); Sleep(63);
		Beep(698, 100); Sleep(63);
		Beep(932, 100); Sleep(288);
		Beep(932, 100); Sleep(63);
		Beep(932, 100); Sleep(63);
		Beep(932, 100); Sleep(63);
		Beep(1046, 675);
	}
}

void CMisc::Main()
{
	featureHideWindow();

	while (FindWindow(NULL, "Counter-Strike: Global Offensive"))
	{
		Sleep(50);
		if (GetForegroundWindow() == FindWindow(NULL, "Counter-Strike: Global Offensive"))
		{
			featureNoFlash();
			featureMarioBrosSong();
		}

		featurePanicKey();
		featureReloadKey();		
	}
}

thread CMisc::miscThread(&CMisc::Main, CMisc());
