#include "Aimbot.h"

CAimbot::CAimbot() 
{
	localPlayer = new CLocalPlayer();
	entityList = new CEntity();

	m_iTickCount = 0;

	vecAimAngle = Vector(0.0f, 0.0f, 0.0f);
	m_flBestTarget = 360.0f;
	m_iBestTarget = -1;

	AimPosition = Vector(0.0f, 0.0f, 0.0f);
	Pixels = 0;

	iDelta = 0;
	Distance = 0.0f;

	m_Aimmin = Vector(0.0f, 0.0f, 0.0f);
	m_vecPunch = Vector(0.0f, 0.0f, 0.0f);
	m_localEyePosition = Vector(0.0f, 0.0f, 0.0f);
	m_entityBone = Vector(0.0f, 0.0f, 0.0f);
}

CAimbot::~CAimbot()
{
}

float CAimbot::RandomFloat(float Start, float End)
{
	return Start + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (End - Start)));
}

Vector CAimbot::GetViewAngles()
{
	return Process.Read<Vector>(Process.Read<DWORD>(ENGINE + Offset.m_dwClientState) + Offset.m_dwViewAngles);
}

void CAimbot::SetViewAngles(Vector& angle)
{
	Process.Write<Vector>(Process.Read<DWORD>(ENGINE + Offset.m_dwClientState) + Offset.m_dwViewAngles, angle);
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

	qaOut.x = RAD2DEG(atan(vecDelta.z / vecDelta.Length2D()));
	qaOut.y = RAD2DEG(atan(vecDelta.y / vecDelta.x));

	if (vecDelta.x >= 0.0f){ qaOut.y += 180.0f; };
}

float CAimbot::GetFov(Vector vecAngles, Vector vecSrc, Vector vecEnd)
{
	Vector flAim, flAng;

	CalcAngle(vecSrc, vecEnd, flAng);
	MakeVector(vecAngles, flAim);
	MakeVector(flAng, flAng);

	float mag_s = sqrt((flAim[0] * flAim[0]) + (flAim[1] * flAim[1]) + (flAim[2] * flAim[2]));
	float mag_d = sqrt((flAim[0] * flAim[0]) + (flAim[1] * flAim[1]) + (flAim[2] * flAim[2]));

	float u_dot_v = flAim[0] * flAng[0] + flAim[1] * flAng[1] + flAim[2] * flAng[2];

	float fov = acos(u_dot_v / (mag_s*mag_d)) * (180.0f / M_PI);

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
	if (!entityList->GetEntity(Index))
		return false;
	if (localPlayer->HasBadWeapon())
		return false;
	if (Settings.AimbotDisableForPistols && localPlayer->HasPistol())
		return false;
	if (entityList->IsAlive(Index))
		return false;
	if (entityList->IsDormant(Index))
		return false;
	if (!entityList->GetBoneMatrix(Index))
		return false;
	if (localPlayer->GetTeam() == entityList->GetTeam(Index))
		return false;
	if (entityList->GetHealth(Index) > 100 || entityList->IsInvisible(Index))
		return false;
	if (entityList->GetBone(Index, Settings.AimbotBone).IsZero())
		return false;
	return true;
}

void CAimbot::DropTarget()
{
	if (!IsValid(m_iBestTarget))
	{
		m_iBestTarget = -1;
	}
}

void CAimbot::GetBestTarget()
{
	for (int i = 0; i < 64; i++)
	{
		if (IsValid(i))
		{
			float flFOV = GetFov(GetViewAngles(), localPlayer->GetEyePosition(), entityList->GetBone(i, Settings.AimbotBone));

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

void CAimbot::doAimbot()
{
	if (Settings.AimbotKey > 0 && GameStatus.Status)
	{
		DropTarget();

		if (!GetAsyncKeyState(Settings.AimbotKey) || m_iBestTarget == -1)
		{
			m_flBestTarget = Settings.AimbotFOV;
			m_iTickCount = timeGetTime();
			GetBestTarget();
			return;
		}

		if (Settings.AimbotTime)
		{
			iDelta = timeGetTime() - m_iTickCount;

			if (Settings.AimbotTime < iDelta)
				return;
		}
		if (m_iBestTarget > 0)
		{
			m_vecPunch = localPlayer->GetVecPunch();
			m_localEyePosition = localPlayer->GetEyePosition();
			m_entityBone = entityList->GetBone(m_iBestTarget, Settings.AimbotBone);

			Distance = Get3D(m_localEyePosition.x, m_localEyePosition.y, m_localEyePosition.z, m_entityBone.x, m_entityBone.y, m_entityBone.z);
			AimPosition.x = (vec_t)((asin((m_entityBone.z - m_localEyePosition.z) / Distance) * 180.0f / M_PI) * -1.0f);
			AimPosition.y = (vec_t)(ATAN2(m_entityBone.x - m_localEyePosition.x, m_entityBone.y - m_localEyePosition.y) / M_PI * 180.0f);

			if (Settings.AimbotRCS == 0)
			{
				m_Aimmin[0] = AimPosition.x - (GetViewAngles().x);
				m_Aimmin[1] = AimPosition.y - (GetViewAngles().y);
			}
			else
			{
				m_Aimmin[0] = AimPosition.x - (GetViewAngles().x + m_vecPunch.x);
				m_Aimmin[1] = AimPosition.y - (GetViewAngles().y + m_vecPunch.y);
			}

			NormalizeAngles(m_Aimmin);

			float fovdist = sqrt((m_Aimmin[0] * m_Aimmin[0]) + (m_Aimmin[1] * m_Aimmin[1]));

			if (fovdist < Settings.AimbotFOV)
			{
				if (!(Settings.AimbotDisableRCSPistols && localPlayer->HasPistol()))
				{
					if (Settings.AimbotRCS == 1 && localPlayer->IsShooting())
					{
						m_vecPunch.x *= 2.f;
						m_vecPunch.y *= 2.f;

						m_vecPunch = PerfectRecoilControl(m_vecPunch);

						AimPosition.x -= m_vecPunch.x;
						AimPosition.y -= m_vecPunch.y;
					}
					else if (Settings.AimbotRCS == 2 && localPlayer->IsShooting())
					{
						m_vecPunch.x *= RandomFloat(1.50f, 2.0f);
						m_vecPunch.y *= RandomFloat(1.50f, 2.0f);

						m_vecPunch = PerfectRecoilControl(m_vecPunch);

						AimPosition.x -= m_vecPunch.x;
						AimPosition.y -= m_vecPunch.y;
					}
				}

				if (Settings.AimbotMouse)
				{
					AimPosition.x = GetViewAngles().x - AimPosition.x;
					AimPosition.y = GetViewAngles().y - AimPosition.y;

					NormalizeAngles(AimPosition);

					Pixels = 0.22f * localPlayer->GetSensitivity() * (Settings.AimbotSmooth + 2) / 10.0f;

					AimPosition.x /= -Pixels;
					AimPosition.y /= Pixels;

					mouse_event(MOUSEEVENTF_MOVE, (DWORD)AimPosition.y, (DWORD)AimPosition.x, 0, 0);
				}
				else
				{
					if (Settings.AimbotSmooth)
					{
						Vector vecDelta(GetViewAngles() - AimPosition);

						NormalizeAngles(vecDelta);

						AimPosition = GetViewAngles() - vecDelta / (Settings.AimbotSmooth * 2.0f);
					}

					NormalizeAngles(AimPosition);
					SetViewAngles(AimPosition);
				}
			}
		}
	}
}

void CAimbot::Main()
{
	while (FindWindow(NULL, "Counter-Strike: Global Offensive"))
	{
		doAimbot();
		Sleep(1);	
	}
}