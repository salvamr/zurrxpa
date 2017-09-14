
#ifndef weaponconfig
#define weaponconfig

#include "Include.h"
#include "Offsets.h"
#include "Settings.h"

class CWeapon
{
public:
	void	Main();
	CWeapon();
	~CWeapon();

private:
	CLocalPlayer* localPlayer;
	INIReader* file;
	int CurrentWeapon;
	void Load(int);
	
};

extern CWeapon Weapon;

#endif