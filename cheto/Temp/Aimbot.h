#ifndef __AIMBOT_H__
#define __AIMBOT_H__

#include "Include.h"
#include "Offsets.h"
#include "Settings.h"
#include "WeaponConfig.h"

class CAimbot
{
public:
	CAimbot();
	~CAimbot();

	void	Main();

private:
	bool	IsValid(int nIndex);

	void	NormalizeAngles(Vector &angle);
	void    GetViewAngles(Vector &angle);
	void    SetViewAngles(Vector &angle);
	void    MakeVector(Vector vecIn, Vector &vecOut);
	void    CalcAngle(Vector vecSrc, Vector vecEnd, Vector &qaOut);
	void	DropTarget();
	void	GetBestTarget();

	float	Get3D(float X, float Y, float Z, float eX, float eY, float eZ);
	double  VectorNormalize(Vector &vec);
	double	GetFov(Vector vecAngles, Vector vecSrc, Vector vecEnd);
	double	ATAN2(double x, double y);

	Vector  PerfectRecoilControl(Vector vPunchAngle);

};extern CAimbot* Aimbot;

#endif
