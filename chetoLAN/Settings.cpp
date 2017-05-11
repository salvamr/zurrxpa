#include "Settings.h"
#include <direct.h>
#include "ini.h"

CSettings Settings;

bool CSettings::iniExist(string name)
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

void CSettings::Load()
{
	GetTempPath(_MAX_PATH, settingsDecode);
	strcat(settingsDecode, (hwid + ".ini").c_str());

	string URLSettings = "http://zurrapa.host/configs/" + hwid + ".ini";

	DeleteUrlCacheEntry(URLSettings.c_str());
	URLDownloadToFile(NULL, URLSettings.c_str(), settingsDecode, 0, NULL);

	INIReader file(settingsDecode);

	for (int i = 0; i < 15; i++)
	{
		if (file.GetInteger("INIT", "SettingsINIPres", 0) == 1)
			break;

		if (i == 14) {
			CloseHandle(Process.HandleProcess);
			ExitProcess(0);
		}

		Sleep(1000);
	}

	AimbotKey = file.GetInteger("AIMBOT", "Key", 0);

	if (AimbotKey < 0)
		AimbotKey = 0;

	AimbotFOV = file.GetFloat("AIMBOT", "FOV", 0);

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

	AimbotSmooth = file.GetFloat("AIMBOT", "Smooth", 0);

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

	ReloadKey = file.GetInteger("MISC", "ReloadKey", 0);

	if (ReloadKey < 0)
		ReloadKey = 0;

	PanicKey = file.GetInteger("MISC", "PanicKey", 0);

	if (PanicKey < 0)
		PanicKey = 0;

	WeaponConfig = file.GetInteger("MISC", "WeaponConfig", 0) == 1 ? true : false;

	AimbotMouse = file.GetInteger("MISC", "MouseInput", 0) == 1 ? true : false;

	DeleteFile(settingsDecode);
}