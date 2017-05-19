#ifndef _WEAPON_H_
#define _WEAPON_H_

#include "Include.h"
#include "Offsets.h"
#include "Settings.h"

class CWeapon
{
public:
	void	Main();
	bool	IsBadWeapon(int);
}; extern CWeapon* Weapon;

#endif
