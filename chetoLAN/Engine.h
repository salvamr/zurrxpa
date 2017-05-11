#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "Offsets.h"

class CLocalPlayer
{
public:

	DWORD	GetPlayer();

	float	GetSpeed();
	float	GetSensitivity();

	bool	IsShooting();

	int		GetHealth();
	int		GetCrosshairID();
	int		GetTeam();
	int		GetWeaponID();

	void	SetSensitivity(float Value);
	void	SetAttack();

	Vector	GetEyePosition();
	Vector	GetVecPunch();

}; extern CLocalPlayer Local;

class CEntity
{
public:

	DWORD	EntityList;
	DWORD	GetBoneMatrix();

	void	GetEntity(int);

	bool	IsInvisible(); //GunGameInmunity
	bool	IsDormant();
	bool	IsAlive();

	int		GetHealth();
	int		GetTeam();
	int		GetMaxClients();

	Vector	GetBone(int);

}; extern CEntity Entity;

#endif