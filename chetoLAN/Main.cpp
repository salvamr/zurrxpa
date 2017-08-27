#include "Include.h"
#include "Offsets.h"
#include "Settings.h"
#include "Secure.h"
#include "Aimbot.h"
#include "Triggerbot.h"
#include "Misc.h"

#include "AccCtrl.h"
#include "Aclapi.h"

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
	for (;;Sleep(500))
	{
		if (IsDebuggerPresent())
		{
			CloseHandle(Process.HandleProcess);
			ExitProcess(0);
		}
	}
}

//argv[0] es el nombre del ejecutable
//argv[1] es el hwid

int main(int argc, char* argv[])
{
	thread debugThread(IsDebuggerActive);
	
	//Settings.hwid = "MTI1NDY3NTI0Ng"; 
	Settings.hwid = string(argv[1]);

	Settings.Load();

	Process.HandleProcess = Process.NewProcess(Settings.launchOptions);

	Secure.LookingForCSGO();

	Offset.Load();

	thread aimbotThread(&CAimbot::Main, CAimbot());
	thread triggerbotThread(&CTrigger::Main, CTrigger());
	thread weaponCfgThread(&CWeapon::Main, CWeapon());
	thread miscThread(&CMisc::Main, CMisc());
	thread foregroundWinThread(ForegroundWindow);

	Beep(500, 500);

	foregroundWinThread.join();

	CloseHandle(Process.HandleProcess);

	return 0;
}