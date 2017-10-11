#include "Settings.h"

#include <direct.h>
#include <Windows.h>
#include <fstream>
#include <Wininet.h>
#include "Printing.h"
#include "INIReader.h"

#include <Wininet.h>
#pragma comment(lib, "wininet.lib") 

#include <urlmon.h>
#pragma comment(lib, "urlmon.lib")

CSettings Settings;

bool CSettings::iniExist(char* name)
{
	ifstream file(name);

	if (file)
	{
		file.close();
		return true;
	}
	else
	{
		file.close();
		return false;
	}
}

void CSettings::Load(string serial)
{
	Settings.hwid = serial;

	Print::it("Loading config: " + serial + ".ini");

	GetTempPath(_MAX_PATH, settingsPath);
	strcat(settingsPath, (serial + ".ini").c_str());

	string URLSettings = "http://zurrapa.host/configs/" + serial + ".ini";

	if (iniExist(settingsPath))
	{
		remove(settingsPath);
	}

	DeleteUrlCacheEntry(URLSettings.c_str());
	URLDownloadToFile(NULL, URLSettings.c_str(), settingsPath, 0, NULL);

	INIReader file(settingsPath);

	for (int i = 0; i < 15; i++)
	{
		if (file.GetInteger("INIT", "SettingsINIPres", 0) == 1)
			break;

		if (i == 14)
			Print::error("Cannot read config");

		Sleep(1000);
	}

	AimbotKey = file.GetInteger("AIMBOT", "Key", 0);

	if (AimbotKey < 0)
		AimbotKey = 0;

	AimbotFOV = file.GetFloat("AIMBOT", "FOV", 0.0f);

	if (AimbotFOV > 360.0f)
		AimbotFOV = 360.0f;
	else if (AimbotFOV < 0)
		AimbotFOV = 0.0f;

	AimbotTime = file.GetInteger("AIMBOT", "Time", 0);

	if (AimbotTime < 0)
		AimbotTime = 0;

	AimbotRCS = file.GetInteger("AIMBOT", "RCS", 0);

	if (AimbotRCS < 0 || AimbotRCS > 2)
		AimbotRCS = 0;

	AimbotDisableRCSPistols = file.GetInteger("AIMBOT", "DisableRCSPistols", 0) == 1 ? true : false;

	AimbotSmooth = file.GetFloat("AIMBOT", "Smooth", 0.0f);

	if (AimbotSmooth > 100.0f)
		AimbotSmooth = 100.0f;
	else if (AimbotSmooth <= 0.0f)
		AimbotSmooth = 1.0f;

	AimbotBone = file.GetInteger("AIMBOT", "Bone", 0);

	if (AimbotBone < 0 || AimbotBone > 100)
		AimbotBone = 0;

	AimbotDisableForPistols = file.GetInteger("AIMBOT", "DisablePistols", 0) == 1 ? true : false;

	TriggerKey = file.GetInteger("TRIGGERBOT", "Key", 0);

	if (TriggerKey < 0)
		TriggerKey = 0;

	TriggerDelay = file.GetInteger("TRIGGERBOT", "Delay", 0);

	if (TriggerDelay < 0)
		TriggerDelay = 0;

	TriggerDisableForPistols = file.GetInteger("TRIGGERBOT", "DisablePistols", 0) == 1 ? true : false;

	BunnyHopKey = file.GetInteger("MISC", "BunnyHopKey", 0);

	if (BunnyHopKey < 0)
		BunnyHopKey = 0;

	HideWindow = file.GetInteger("MISC", "HideWindow", 0) == 1 ? true : false;

	NoFlash = file.GetInteger("MISC", "NoFlash", 0) == 1 ? true : false;

	ReloadKey = file.GetInteger("MISC", "ReloadKey", 0);

	if (ReloadKey < 0)
		ReloadKey = 0;

	PanicKey = file.GetInteger("MISC", "PanicKey", 0);

	if (PanicKey < 0)
		PanicKey = 0;

	SuperMarioBrosKey = file.GetInteger("MISC", "SuperMarioBrosKey", 0);

	if (SuperMarioBrosKey < 0)
		SuperMarioBrosKey = 0;

	WeaponConfig = file.GetInteger("MISC", "WeaponConfig", 0) == 1 ? true : false;

	AimbotMouse = file.GetInteger("MISC", "MouseInput", 0) == 1 ? true : false;
}