#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "Include.h"
#include "Offsets.h"

class CLocalPlayer
{
public:
	CLocalPlayer();
	~CLocalPlayer();

	DWORD	GetPlayer();

	float	GetSpeed();

	bool	IsShooting();

	int		GetStatus();
	int		GetHealth();
	int		GetCrosshairID();
	int		GetTeam();
	int		GetWeaponID();

	void	SetAttack();

	Vector	GetEyePosition();
	Vector	GetVecPunch();

}; extern CLocalPlayer* Local;

class CEntity
{
public:
	CEntity();
	~CEntity();

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

}; extern CEntity* Entity;

#endif
