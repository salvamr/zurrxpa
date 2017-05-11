#include "WeaponConfig.h"

CWeapon Weapon;

void CWeapon::Main()
{ 
	if (Settings.WeaponConfig == true && Game.Status)
	{
		if (Local.GetWeaponID() != OldWeapon)
		{
			Load(Local.GetWeaponID());
			OldWeapon = Local.GetWeaponID();
			Sleep(1);
		}
	}
}

bool CWeapon::IsBadWeapon()
{
	int Index = Local.GetWeaponID();
	return Index == 31 || Index == 42 || Index == 43 || Index == 44 || Index == 45 || Index == 46 || Index == 47 || Index == 48
		|| Index == 49 || Index == 59 || Index == 64 || Index == 500 || Index == 505 || Index == 506 || Index == 507 || Index == 508
		|| Index == 509 || Index == 512 || Index == 514 || Index == 515 || Index == 516;
}

bool CWeapon::IsPistol()
{
	int Index = Local.GetWeaponID();
	return Index == 1 || Index == 2 || Index == 3 || Index == 4 || Index == 30 || Index == 32 || Index == 36
		|| Index == 61 || Index == 63;
}

void CWeapon::Load(int weaponID)
{
	INIReader file(Settings.settingsDecode);

	Settings.AimbotKey = file.GetInteger(to_string(weaponID), decode(/*AKey*/"QUtleQ"), 0);
	Settings.AimbotFOV = file.GetFloat(to_string(weaponID), decode(/*AFOV*/"QUZPVg"), 0);
	Settings.AimbotTime = file.GetInteger(to_string(weaponID), decode(/*ATime*/"QVRpbWU"), 0);
	Settings.AimbotRCS = file.GetInteger(to_string(weaponID), decode(/*ARCS*/"QVJDUw"), 0);
	Settings.AimbotSmooth = file.GetFloat(to_string(weaponID), decode(/*ASmooth*/"QVNtb290aA"), 0);
	Settings.AimbotBone = file.GetInteger(to_string(weaponID), decode(/*ABone*/"QUJvbmU"), 0);
	Settings.TriggerKey = file.GetInteger(to_string(weaponID), decode(/*TKey*/"VEtleQ"), 0);
	Settings.TriggerDelay = file.GetInteger(to_string(weaponID), decode(/*TDelay*/"VERlbGF5"), 0);
}