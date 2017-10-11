#ifndef _h_settings
#define _h_settings

#include <iostream>

using namespace std;

class CSettings
{
public:

	void Load(string);
	bool iniExist(char*);

	/*Settings*/
	int	AimbotKey;
	float AimbotFOV;
	int	AimbotTime;
	int	AimbotRCS;
	bool AimbotDisableRCSPistols;
	float AimbotSmooth;
	int	AimbotBone;
	bool AimbotDisableForPistols;
	bool AimbotMouse;

	int	TriggerKey;
	int	TriggerDelay;
	bool TriggerDisableForPistols;

	int	BunnyHopKey;
	bool HideWindow;
	bool NoFlash;
	int	ReloadKey;
	int	PanicKey;
	int	SuperMarioBrosKey;
	bool WeaponConfig;

	string hwid;
	char settingsPath[_MAX_PATH];
}; 

extern CSettings Settings;
#endif