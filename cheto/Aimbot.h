
#ifndef aimbot
#define aimbot

#include "Include.h"
#include "Offsets.h"
#include "Settings.h"
#include "WeaponConfig.h"
#include "BSP.h"

class CAimbot
{
public:
	CAimbot();
	~CAimbot();
	void	Main();

private:
	bool	IsValid(int nIndex);

	void	NormalizeAngles(Vector &angle);
	Vector  GetViewAngles();
	void    SetViewAngles(Vector &angle);
	void    MakeVector(Vector vecIn, Vector &vecOut);
	void    CalcAngle(Vector vecSrc, Vector vecEnd, Vector &qaOut);
	void	DropTarget();
	void	doAimbot();
	void	GetBestTarget();

	float	Get3D(float X, float Y, float Z, float eX, float eY, float eZ);
	double  VectorNormalize(Vector &vec);
	float	GetFov(Vector vecAngles, Vector vecSrc, Vector vecEnd);
	double	ATAN2(double x, double y);
	float RandomFloat(float Start, float End);

	CLocalPlayer* localPlayer;
	CEntity* entityList;

	Vector  PerfectRecoilControl(Vector vPunchAngle);

	int		m_iTickCount;

	Vector	vecAimAngle;
	float	m_flBestTarget;
	int		m_iBestTarget;

	Vector	AimPosition;
	float	Pixels;

	int iDelta;
	float Distance;

	Vector m_Aimmin;
	Vector m_vecPunch;
	Vector m_localEyePosition;
	Vector m_entityBone;
};

extern CAimbot Aimbot;

#endif