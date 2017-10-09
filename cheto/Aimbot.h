#ifndef aimbot
#define aimbot

#include "Vector.h"
#include "Engine.h"

#define M_PI			3.14159265358979323846f
#define M_PI_F			( ( float )( M_PI ) )
#define RAD2DEG( x )	( ( float )( x ) * ( float )( 180.0f / M_PI_F ) )

using namespace std;

class CAimbot
{
public:
	CAimbot();
	~CAimbot();
	void	Main();

private:
	void	NormalizeAngles(Vector &angle);
	Vector  GetViewAngles();
	void    SetViewAngles(Vector &angle);
	void    MakeVector(Vector vecIn, Vector &vecOut);
	void    CalcAngle(Vector vecSrc, Vector vecEnd, Vector &qaOut);
	void	GetBestTarget();

	float	Get3DDistance(Vector, Vector);
	double  VectorNormalize(Vector &vec);
	float	GetFov(Vector vecAngles, Vector vecSrc, Vector vecEnd);
	double	ATAN2(double x, double y);
	float	RandomFloat(float Start, float End);

	CLocalPlayer* localPlayer;
	CEntity* entityList;

	Vector  PerfectRecoilControl(Vector vPunchAngle);

	Vector	vecAimAngle;
	int		m_iBestTarget;
	int		oldBestTarget;

	Vector	AimPosition;
	float	Pixels;

	int iDelta;
	float Distance;

	Vector m_vecPunch;
	Vector m_localEyePosition;
	Vector m_entityBone;

	int iTickCount;
	bool bAim;
};

extern CAimbot Aimbot;

#endif