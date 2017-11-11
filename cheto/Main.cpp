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

void StartThreads()
{
	CAimbot Aimbot;
	CTrigger Trigger;
	CMisc Misc;
	CBunny Bunny;
	CWeapon WeaponConfig;

	thread t1(&CAimbot::Main, &Aimbot);
	thread t2(&CTrigger::Main, &Trigger);
	thread t3(&CMisc::Main, &Misc);
	thread t4(&CBunny::Main, &Bunny);
	thread t5(&CWeapon::Main, &WeaponConfig);

	Print::success("Done");

	Beep(500, 500);

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
}

int main(int argc, char* argv[])
{
	thread dbg([]() {
		for (;; Sleep(500))
		{
			if (IsDebuggerPresent())
			{
				if (Process.HandleProcess) {
					CloseHandle(Process.HandleProcess);
				}
				ExitProcess(0);
			}
		}
	});

	//Print::warning("Your subscription expires in " + string(argv[2]) + " days");
	Print::warning("Visit http://zurrapa.host/ to change your settings");
	Print::warning("READ THE README IF YOU DIDN'T -> http://zurrapa.host/readme");

	Secure.LookingForCSGO();

	Settings.DownloadSettings(string(argv[1]));
	//Settings.DownloadSettings("NDE0NDQ2NzcwMQ");

	Settings.Load();

	Print::it("Dumping offsets ...");

	Offset.Load();

	Print::it("Starting threads ...");

	StartThreads();

	Process.Detach();

	dbg.detach();
}