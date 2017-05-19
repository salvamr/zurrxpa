#include "Aimbot.h"

CAimbot* Aimbot = new CAimbot();

int		m_iTickCount = 0;

Vector	vecAimAngle = Vector(0.0f, 0.0f, 0.0f);
double	m_flBestTarget = 360.f;
int		m_iBestTarget = -1;

CAimbot::CAimbot()
{}

CAimbot::~CAimbot()
{}

void CAimbot::GetViewAngles(Vector &angle)
{
	DWORD Temp	= Process->Read<DWORD>(ENGINE + Offset->m_dwClientState);
	angle		= Process->Read<Vector>(Temp + Offset->m_dwViewAngles);
}

void CAimbot::SetViewAngles(Vector& angle)
{
	DWORD Temp	= Process->Read<DWORD>(ENGINE + Offset->m_dwClientState);
	Process->Write<Vector>(Temp + Offset->m_dwViewAngles, angle);
}

void CAimbot::MakeVector(Vector vecIn, Vector& vecOut)
{
	float pitch = (float)((float)M_PI / 180.0f) * vecIn[0];
	float yaw = (float)((float)M_PI / 180.0f) * vecIn[1];
	float temp = (float)cos(pitch);
	vecOut[0] = (float)(-temp * -cos(yaw));
	vecOut[1] = (float)(sin(yaw) * temp);
	vecOut[2] = (float)(-sin(pitch));
}

void CAimbot::CalcAngle(Vector vecSrc, Vector vecEnd, Vector& qaOut)
{
	Vector vecDelta(vecSrc - vecEnd);

	float flHyp = vecDelta.Length2D();

	qaOut.x = RAD2DEG(atan(vecDelta.z / flHyp));
	qaOut.y = RAD2DEG(atan(vecDelta.y / vecDelta.x));

	if (vecDelta.x >= 0.0f){ qaOut.y += 180.0f; };
}

double CAimbot::GetFov(Vector vecAngles, Vector vecSrc, Vector vecEnd)
{
	Vector flAim, flAng;

	CalcAngle(vecSrc, vecEnd, flAng);
	MakeVector(vecAngles, flAim);
	MakeVector(flAng, flAng);

	float mag_s = sqrt((flAim[0] * flAim[0]) + (flAim[1] * flAim[1]) + (flAim[2] * flAim[2]));
	float mag_d = sqrt((flAim[0] * flAim[0]) + (flAim[1] * flAim[1]) + (flAim[2] * flAim[2]));

	float u_dot_v = flAim[0] * flAng[0] + flAim[1] * flAng[1] + flAim[2] * flAng[2];

	double fov = acos(u_dot_v / (mag_s*mag_d)) * (180.0f / M_PI);

	return fov;
}


double CAimbot::ATAN2(double x, double y)
{
	if (y < 0)
		return -ATAN2(x, -y);
	else if (x < 0)
		return M_PI - atan(-y / x);
	else if (x > 0)
		return atan(y / x);
	else if (y != 0)
		return M_PI / 2;
	else
		return 0;
}

double CAimbot::VectorNormalize(Vector& vec)
{
	float radius = sqrtf(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);

	float iradius = 1.f / (radius + FLT_EPSILON);

	vec.x *= iradius;
	vec.y *= iradius;
	vec.z *= iradius;

	return radius;
}

void CAimbot::NormalizeAngles(Vector& vec)
{
	if (vec.x > 89.0f && vec.x <= 180.0f)
		vec.x = 89.0f;
	while (vec.x > 180.f)
		vec.x -= 360.f;
	while (vec.x < -89.0f)
		vec.x = -89.0f;
	while (vec.y > 180.f)
		vec.y -= 360.f;
	while (vec.y < -180.f)
		vec.y += 360.f;
	vec.z = 0.f;
}

Vector CAimbot::PerfectRecoilControl(Vector vPunchAngle)
{
	double len = VectorNormalize(vPunchAngle);
	len -= (10.0 + len * 0.5) * 0.015625f;
	len = max(len, 0.0);
	vPunchAngle.x *= (vec_t)len;
	vPunchAngle.y *= (vec_t)len;
	return vPunchAngle;
}

bool CAimbot::IsValid(int Index)
{
	Entity->GetEntity(Index);

	if (Weapon->IsBadWeapon(Local->GetWeaponID()))
		return false;
	
	if (Entity->IsAlive())
		return false;

	if (Entity->IsDormant())
		return false;

	if (!Entity->GetBoneMatrix())
		return false;

	if (Local->GetTeam() == Entity->GetTeam())
		return false;

	if (Entity->GetHealth() > 100 || Entity->IsInvisible())
		return false;

	if (Entity->GetBone(Settings->AimbotBone).IsZero())
		return false;

	return true;
}

void CAimbot::DropTarget()
{
	if (!IsValid(m_iBestTarget))
		m_iBestTarget = -1;
}

void CAimbot::GetBestTarget()
{
	Vector vecAngle;
	GetViewAngles(vecAngle);

	for (int i = 0; i < 64; i++)
	{ 
		if (IsValid(i))
		{ 
			double flFOV = GetFov(vecAngle, Local->GetEyePosition(), Entity->GetBone(Settings->AimbotBone));

			if (flFOV < m_flBestTarget)
			{ 
				m_flBestTarget = flFOV; 
				m_iBestTarget = i;
			}
		} 
	}
}

float CAimbot::Get3D(float X, float Y, float Z, float eX, float eY, float eZ)
{
	return(sqrtf((eX - X) * (eX - X) + (eY - Y) * (eY - Y) + (eZ - Z) * (eZ - Z)));
}

void CAimbot::Main()
{
	DropTarget();

	if (Settings->AimbotKey)
	{
		if (!GetAsyncKeyState(Settings->AimbotKey) || m_iBestTarget == -1)
		{
			m_flBestTarget = Settings->AimbotFOV;
			m_iTickCount = timeGetTime();
			GetBestTarget();
			return;
		}
	}
	else
	{
		if (m_iBestTarget == -1)
		{
			m_flBestTarget = Settings->AimbotFOV;
			m_iTickCount = timeGetTime();
			GetBestTarget();
			return;
		}
	}

	if (Settings->AimbotTime)
	{
		int iCurrentTick = timeGetTime();
		int iDelta = iCurrentTick - m_iTickCount;

		if (Settings->AimbotTime < iDelta)
			return;
	}

	Entity->GetEntity(m_iBestTarget);

	if (m_iBestTarget > 0)
	{
		Vector Aimmin;
		Vector vecPunch = Local->GetVecPunch();

		Vector ViewAngle;
		GetViewAngles(ViewAngle);

		float Distance = Get3D(Local->GetEyePosition().x, Local->GetEyePosition().y, Local->GetEyePosition().z, Entity->GetBone(Settings->AimbotBone).x, Entity->GetBone(Settings->AimbotBone).y, Entity->GetBone(Settings->AimbotBone).z);
		vecAimAngle.x = (vec_t)((asin((Entity->GetBone(Settings->AimbotBone).z - Local->GetEyePosition().z) / Distance) * 180 / M_PI) * -1);
		vecAimAngle.y = (vec_t)(ATAN2(Entity->GetBone(Settings->AimbotBone).x - Local->GetEyePosition().x, Entity->GetBone(Settings->AimbotBone).y - Local->GetEyePosition().y) / M_PI * 180);

		if (Settings->AimbotRCS == 0)
		{
			Aimmin[0] = vecAimAngle.x - (ViewAngle.x);
			Aimmin[1] = vecAimAngle.y - (ViewAngle.y);
		}
		else
		{
			Aimmin[0] = vecAimAngle.x - (ViewAngle.x + vecPunch.x);
			Aimmin[1] = vecAimAngle.y - (ViewAngle.y + vecPunch.y);
		}

		NormalizeAngles(Aimmin);

		float fovdist = sqrt((Aimmin[0] * Aimmin[0]) + (Aimmin[1] * Aimmin[1]));

		if (fovdist < Settings->AimbotFOV / 2)
		{
			if (Settings->AimbotRCS == 1 && Local->IsShooting())
			{
				vecPunch.x *= 2.f;
				vecPunch.y *= 2.f;

				vecPunch = PerfectRecoilControl(vecPunch);

				vecAimAngle.x -= vecPunch.x;
				vecAimAngle.y -= vecPunch.y;
			}
			 
			if (Settings->AimbotRCS == 2 && Local->IsShooting())
			{
				vecPunch.x *= Random->Float(1.50f, 2.f);
				vecPunch.y *= Random->Float(1.50f, 2.f);

				vecPunch = PerfectRecoilControl(vecPunch);

				vecAimAngle.x -= vecPunch.x;
				vecAimAngle.y -= vecPunch.y;
			}

			if (Settings->AimbotSmooth)
			{
				Vector vecDelta(ViewAngle - vecAimAngle);

				NormalizeAngles(vecDelta);

				vecAimAngle = ViewAngle - vecDelta / (Settings->AimbotSmooth * 2);
			}
			NormalizeAngles(vecAimAngle);
			SetViewAngles(vecAimAngle);
		}
	}
}


