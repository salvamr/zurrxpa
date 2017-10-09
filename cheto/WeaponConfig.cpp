#include "WeaponConfig.h"

#include "Settings.h"
#include "GameStatus.h"

CWeapon::CWeapon()
{
	localPlayer = new CLocalPlayer();
	OldWeapon = -1;
	CurrentWeapon = 0;
	file = new INIReader(Settings.settingsPath);
}

CWeapon::~CWeapon()
{
	delete localPlayer;
	delete file;
}

void CWeapon::Main()
{
	while (FindWindow(NULL, "Counter-Strike: Global Offensive"))
	{
		Sleep(50);

		if (Settings.WeaponConfig && GameStatus.Status)
		{
			CurrentWeapon = localPlayer->GetWeaponID();

			if (CurrentWeapon != OldWeapon)
			{
				Load(CurrentWeapon);
				OldWeapon = CurrentWeapon;
			}
		}
	}
}

void CWeapon::Load(int weaponID)
{
	Settings.AimbotKey = file->GetInteger(to_string(weaponID), "AKey", 0);
	Settings.AimbotFOV = file->GetFloat(to_string(weaponID), "AFOV", 0);
	Settings.AimbotTime = file->GetInteger(to_string(weaponID), "ATime", 0);
	Settings.AimbotRCS = file->GetInteger(to_string(weaponID), "ARCS", 0);
	Settings.AimbotSmooth = file->GetFloat(to_string(weaponID), "ASmooth", 0);
	Settings.AimbotBone = file->GetInteger(to_string(weaponID), "ABone", 0);
	Settings.TriggerKey = file->GetInteger(to_string(weaponID), "TKey", 0);
	Settings.TriggerDelay = file->GetInteger(to_string(weaponID), "TDelay", 0);
}