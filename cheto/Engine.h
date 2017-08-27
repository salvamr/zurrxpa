
#ifndef engine
#define engine

#include "Offsets.h"

class CLocalPlayer
{
public:
	CLocalPlayer();

	DWORD	GetPlayer();

	float	GetSpeed();
	float	GetSensitivity();

	bool	IsShooting();
	bool	IsBadWeapon();
	bool	IsPistol();

	int		GetStatus();
	int		GetHealth();
	int		GetCrosshairID();
	int		GetTeam();
	int		GetWeaponID();

	void	SetSensitivity(float);
	void	SetAttack();

	Vector	GetEyePosition();
	Vector	GetVecPunch();

};

class CEntity
{
public:
	CEntity();

	DWORD	GetEntity(int);
	int		GetTeam(int);
	Vector	GetBone(int,int);
	DWORD	GetBoneMatrix(int);
	bool	IsAlive(int);
	bool	IsDormant(int); 
	int		GetHealth(int);
	bool	IsInvisible(int);

};

#endif