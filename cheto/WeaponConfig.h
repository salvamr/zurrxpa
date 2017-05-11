#ifndef _WEAPON_H_
#define _WEAPON_H_

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
	int CurrentWeapon;
	void Load(int);
	
}; extern CWeapon weapon;

#endif