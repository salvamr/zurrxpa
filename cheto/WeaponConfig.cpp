#include "WeaponConfig.h"

CWeapon Weapon;

CWeapon::CWeapon()
{
	localPlayer = new CLocalPlayer();
	Settings.OldWeapon = 0;
	CurrentWeapon = 0;
}

CWeapon::~CWeapon()
{
}

void CWeapon::Main()
{
	while (FindWindow(NULL, "Counter-Strike: Global Offensive"))
	{
		if (Settings.WeaponConfig == true && GameStatus.Status)
		{
			CurrentWeapon = localPlayer->GetWeaponID();

			if (CurrentWeapon != Settings.OldWeapon)
			{
				Load(CurrentWeapon);
				Settings.OldWeapon = CurrentWeapon;
			}
		}
		Sleep(50);
	}
}

//Private
void CWeapon::Load(int weaponID)
{
	INIReader* file = new INIReader(Settings.settingsDecode);

	Settings.AimbotKey = file->GetInteger(to_string(weaponID), "AKey", 0);
	Settings.AimbotFOV = file->GetFloat(to_string(weaponID), "AFOV", 0);
	Settings.AimbotTime = file->GetInteger(to_string(weaponID), "ATime", 0);
	Settings.AimbotRCS = file->GetInteger(to_string(weaponID), "ARCS", 0);
	Settings.AimbotSmooth = file->GetFloat(to_string(weaponID), "ASmooth", 0);
	Settings.AimbotBone = file->GetInteger(to_string(weaponID), "ABone", 0);
	Settings.TriggerKey = file->GetInteger(to_string(weaponID), "TKey", 0);
	Settings.TriggerDelay = file->GetInteger(to_string(weaponID), "TDelay", 0);

	delete file;
}