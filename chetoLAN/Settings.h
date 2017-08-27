#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include "Include.h"

class CSettings
{
public:

	void Load();
	bool iniExist(string);

	// Extra, from weaponconfig
	int OldWeapon;

	/*Settings*/
	int	AimbotKey;
	float AimbotFOV;
	int	AimbotTime;
	int	AimbotRCS;
	bool AimbotDisableRCSPistols;
	float AimbotSmooth;
	int	AimbotBone;
	bool AimbotDisableForPistols;
	bool AimbotMouse = true;

	int	TriggerKey;
	int	TriggerDelay;
	bool TriggerDisableForPistols;

	int	ReloadKey;
	int	PanicKey;
	bool WeaponConfig;
	string launchOptions;
	string gameLocation;

	string hwid;
	char settingsDecode[MAX_PATH];
}; extern CSettings Settings;

#endif