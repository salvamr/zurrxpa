#ifndef _WEAPON_H_
#define _WEAPON_H_

#include "Include.h"
#include "Offsets.h"
#include "Settings.h"

class CWeapon
{
public:
	void	Main();
	bool	IsBadWeapon();
	bool	IsPistol();

private:
	int OldWeapon = 0;
	void Load(int);
	
}; extern CWeapon Weapon;

#endif