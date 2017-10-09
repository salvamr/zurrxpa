#include "Printing.h"
#include "Offsets.h"
#include "Settings.h"
#include "Secure.h"
#include "Process.h"
#include "GameStatus.h"

#include "Aimbot.h"
#include "Triggerbot.h"
#include "Bunnyhop.h"
#include "WeaponConfig.h"
#include "Misc.h"

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
	while (FindWindow(NULL, "Counter-Strike: Global Offensive"))
	{
		if (IsDebuggerPresent())
		{
			CloseHandle(Process.HandleProcess);
			ExitProcess(0);
		}
		Sleep(50);
	}
}

int main(int argc, char* argv[])
{
	thread debugThread(IsDebuggerActive);

	//Settings.hwid = "MTk2MzA1MTI1Mg";
	Settings.hwid = string(argv[1]);

	Print::warning("Visit http://zurrapa.host/ to change your settings");
	Print::warning("READ THE README IF YOU DIDN'T -> http://zurrapa.host/readme");

	Secure.LookingForCSGO();

	Settings.Load();

	Print::it("Dumping offsets ...");

	Offset.Load();

	thread aimbotThread(&CAimbot::Main, CAimbot());
	thread triggerbotThread(&CTrigger::Main, CTrigger());
	thread weaponCfgThread(&CWeapon::Main, CWeapon());
	thread miscThread(&CMisc::Main, CMisc());
	thread bunnyhopThread(&CBunny::Main, CBunny());

	Print::success("Done");
	Beep(500, 500);	

	ForegroundWindow();
	aimbotThread.join();
	triggerbotThread.join();
	weaponCfgThread.join();
	miscThread.join();
	bunnyhopThread.join();
	return 0;
}