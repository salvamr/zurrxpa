#ifndef __AIMBOT_H__
#define __AIMBOT_H__

#include "Include.h"
#include "Offsets.h"
#include "Settings.h"
#include "WeaponConfig.h"

class CAimbot
{
public:
	void	Main();

private:
	bool	IsValid(int nIndex);

	void	NormalizeAngles(Vector &angle);
	Vector  GetViewAngles();
	void    SetViewAngles(Vector &angle);
	void    MakeVector(Vector vecIn, Vector &vecOut);
	void    CalcAngle(Vector vecSrc, Vector vecEnd, Vector &qaOut);
	void	DropTarget();
	void	GetBestTarget();

	float	Get3D(float X, float Y, float Z, float eX, float eY, float eZ);
	double  VectorNormalize(Vector &vec);
	float	GetFov(Vector vecAngles, Vector vecSrc, Vector vecEnd);
	double	ATAN2(double x, double y);

	Vector  PerfectRecoilControl(Vector vPunchAngle);

	int		m_iTickCount = 0;

	Vector	vecAimAngle = Vector(0.0f, 0.0f, 0.0f);
	float	m_flBestTarget = 360.0f;
	int		m_iBestTarget = -1;

	Vector	AimPosition = Vector(0.0f, 0.0f, 0.0f);
	float	Pixels = 0;

	int iCurrentTick;
	int iDelta;
	float Distance;

	Vector m_Aimmin;
	Vector m_vecPunch;
	Vector m_localEyePosition;
	Vector m_entityBone;

};extern CAimbot Aimbot;

class CRandom
{
public:
	float Float(float Start, float End)
	{
		return Start + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (End - Start)));
	}
}; extern CRandom Random;

#endif