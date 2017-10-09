#ifndef _h_engine
#define _h_engine

#include "Vector.h"
#include <list>
#include <Windows.h>

using namespace std;

class CLocalPlayer
{
public:
	CLocalPlayer();

	DWORD	GetPlayer();

	float	GetSensitivity();

	bool	IsShooting();
	bool	HasBadWeapon();
	bool	HasPistol();
	bool	IsInGame();
	bool	HasMouseEnabled();

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
	list<int> GetMaxPlayers();
};

#endif