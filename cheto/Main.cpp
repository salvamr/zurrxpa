#include "Printing.h"
#include "Offsets.h"
#include "Settings.h"
#include "Secure.h"
#include "Process.h"

#include "Aimbot.h"
#include "Triggerbot.h"
#include "Bunnyhop.h"
#include "WeaponConfig.h"
#include "Misc.h"

#include <thread>

CAimbot* Aimbot;
CTrigger* Trigger;
CMisc* Misc;
CBunny* Bunny;
CWeapon* WeaponConfig;

int main(int argc, char* argv[])
{
	Print::warning("Visit http://zurrapa.host/ to change your settings");
	Print::warning("READ THE README IF YOU DIDN'T -> http://zurrapa.host/readme");

	Secure.LookingForCSGO();

	Settings.Load(string(argv[1]));
	//Settings.Load("NDE0NDQ2NzcwMQ");

	Print::it("Dumping offsets ...");

	Offset.Load();

	Print::it("Starting threads ...");

	Trigger->triggerbotThread;
	Bunny->bunnyThread;
	WeaponConfig->wcThread;
	Aimbot->aimbotThread;
	Misc->miscThread;

	Print::success("Done");

	Beep(500, 500);

	Misc->miscThread.join();

	CloseHandle(Process.HandleProcess);

	return 0;
}