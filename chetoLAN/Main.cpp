#include "..\cheto\Offsets.h"
#include "..\cheto\Secure.h"
#include "../cheto/GameStatus.h"
#include "Process.h"

#include "Settings.h"

#include "..\cheto\Aimbot.h"
#include "..\cheto\Triggerbot.h"
#include "..\cheto\Misc.h"
#include "../cheto/WeaponConfig.h"

#include <thread>

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

	CloseHandle(Process.HandleProcess);
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
	
	//Settings.hwid = "NDE0NDQ2NzcwMQ"; 
	Settings.hwid = string(argv[1]);

	Settings.Load();

	Process.HandleProcess = Process.NewProcess(Settings.launchOptions);

	Secure.LookingForCSGO();

	Offset.Load();

	thread aimbotThread(&CAimbot::Main, CAimbot());
	thread triggerbotThread(&CTrigger::Main, CTrigger());
	thread weaponCfgThread(&CWeapon::Main, CWeapon());
	thread miscThread(&CMisc::Main, CMisc());

	Beep(500, 500);

	ForegroundWindow();
	aimbotThread.join();
	triggerbotThread.join();
	weaponCfgThread.join();
	miscThread.join();

	return 0;
}