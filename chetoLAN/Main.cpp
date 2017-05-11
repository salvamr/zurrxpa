#include "Include.h"
#include "Offsets.h"
#include "Settings.h"
#include "Secure.h"
#include "base64.h"

#include "Aimbot.h"
#include "Triggerbot.h"
#include "Misc.h"

CStatus Game;

void Aimbot_Trigger()
{
	for (;; Sleep(5))
	{
		Triggerbot.Main();
		Aimbot.Main();
		Sleep(1);
	}
}

void MiscT()
{
	for (;; Sleep(25))
	{
		Misc.Main();
		Sleep(1);
	}
}

void WeaponCFGT()
{
	for (;; Sleep(25))
	{
		Weapon.Main();
		Sleep(1);
	}
}

void ForegroundWindow()
{
	for (;; Sleep(50))
	{
		if (GetForegroundWindow() == FindWindow(NULL, decode(/*Counter-Strike: Global Offensive*/"Q291bnRlci1TdHJpa2U6IEdsb2JhbCBPZmZlbnNpdmU").c_str()))
			Game.Status = true;
		else
			Game.Status = false;
	}
}

void IsDebuggerActive()
{
	for (;; Sleep(50))
	{
		if (IsDebuggerPresent())
		{
			Secure.BorrarZurrapa();
		}
	}
}
 
extern "C" __declspec(dllexport) void Zurrapa(char* hwid)
{ 
	Settings.hwid = string(hwid);
	thread One(IsDebuggerActive);

	Secure.LookingForCSGO();

	Settings.Load();
	Offset.Load();

	thread Two(Aimbot_Trigger);
	thread Three(MiscT);
	thread Four(WeaponCFGT);
	thread Six(ForegroundWindow);

	Beep(500, 500);

	while (FindWindow(NULL, decode(/*Counter-Strike: Global Offensive*/"Q291bnRlci1TdHJpa2U6IEdsb2JhbCBPZmZlbnNpdmU").c_str()))
		Sleep(100);

	One.detach();
	Two.detach();
	Four.detach();
	Six.detach();

	CloseHandle(Process.HandleProcess);
	ExitProcess(EXIT_SUCCESS);
}