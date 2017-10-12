
#ifndef weaponconfig
#define weaponconfig

#include "Engine.h"
#include <thread>
#include "INIReader.h"

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
	int OldWeapon;
	void Load(int);
};

extern CWeapon Weapon;

#endif