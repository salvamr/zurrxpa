#include "../cheto/Offsets.h"
#include "../cheto/Secure.h"
#include "../cheto/Process.h"
#include "../cheto/Settings.h"

#include "../cheto/Aimbot.h"
#include "../cheto/Triggerbot.h"
#include "../cheto/Misc.h"
#include "../cheto/WeaponConfig.h"

#include <thread>

void StartThreads()
{
	CAimbot Aimbot;
	CTrigger Trigger;
	CMisc Misc;
	CWeapon WeaponConfig;

	thread t1(&CAimbot::Main, &Aimbot);
	thread t2(&CTrigger::Main, &Trigger);
	thread t3(&CMisc::Main, &Misc);
	thread t4(&CWeapon::Main, &WeaponConfig);

	Beep(500, 500);

	t1.join();
	t2.join();
	t3.join();
	t4.join();
}

//argv[0] es el nombre del ejecutable
//argv[1] es el hwid
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
	
	Settings.DownloadSettings(string(argv[1]));
	//Settings.DownloadSettings("NDE0NDQ2NzcwMQ");

	Settings.Load();

	Process.HandleProcess = Process.NewProcess(Settings.launchOptions);

	Secure.LookingForCSGOLAN();

	Offset.Load();

	StartThreads();

	dbg.detach();

	return 0;
}