#include "Include.h"
#include "Offsets.h"
#include "Settings.h"
#include "Secure.h"

#include "Aimbot.h"
#include "Triggerbot.h"
#include "Bunnyhop.h"
#include "Misc.h"

CGameStatus GameStatus;

void ForegroundWindow()
{
	while (FindWindow(NULL, "Counter-Strike: Global Offensive"))
	{
		if (GetForegroundWindow() == FindWindow(NULL, "Counter-Strike: Global Offensive"))
		{
			GameStatus.Status = true;
		}
		else
		{
			GameStatus.Status = false;
		}
		Sleep(50);
	}
}

void IsDebuggerActive()
{
	while (FindWindow(NULL, "Counter-Strike: Global Offensive"))
	{
		if (IsDebuggerPresent())
		{
			Secure.BorrarZurrapa();
		}
		Sleep(50);
	}
}

extern "C" __declspec(dllexport) void Zurrapa(char* hwid)
{
	Settings.hwid = string(hwid);

	EnableMenuItem(GetSystemMenu(GetConsoleWindow(), FALSE), SC_CLOSE, MF_GRAYED);

	thread debugThread(IsDebuggerActive);

	Print.warning("Visit http://zurrapa.host/ to change your settings");
	Print.warning("READ THE README IF YOU DIDN'T -> http://zurrapa.host/readme");

	Secure.LookingForCSGO();

	Settings.Load();
	Offset.Load();

	thread aimbotThread(&CAimbot::Main, CAimbot());
	thread triggerbotThread(&CTrigger::Main, CTrigger());
	thread weaponCfgThread(&CWeapon::Main, CWeapon());
	thread miscThread(&CMisc::Main, CMisc());
	thread bunnyhopThread(&CBunny::Main, CBunny());
	thread foregroundWinThread(ForegroundWindow);

	Print.succes("Done");
	Beep(500, 500);

	foregroundWinThread.join();
	aimbotThread.join();
	triggerbotThread.join();
	miscThread.join();
	weaponCfgThread.join();
	bunnyhopThread.join();
	debugThread.join();

	remove(Settings.settingsDecode);
	CloseHandle(Process.HandleProcess);
	ExitProcess(EXIT_SUCCESS);
}