#include "Aimbot.h"

#include "Process.h"
#include "Settings.h"
#include "Offsets.h"
#include <stdlib.h>
#include <Windows.h>
#include <cfloat>
#include <map>
#include <list>
#include <algorithm>

#pragma comment(lib,"winmm.lib")

CAimbot::CAimbot()
{
	localPlayer = new CLocalPlayer();
	entityList = new CEntity();

	vecAimAngle = Vector(0.0f, 0.0f, 0.0f);
	m_iBestTarget = 0;
	oldBestTarget = 0;

	AimPosition = Vector(0.0f, 0.0f, 0.0f);
	Pixels = 0;

	iDelta = 0;
	Distance = 0.0f;
	iTickCount = 0;

	m_vecPunch = Vector(0.0f, 0.0f, 0.0f);
	m_localEyePosition = Vector(0.0f, 0.0f, 0.0f);
	m_entityBone = Vector(0.0f, 0.0f, 0.0f);

	bAim = false;
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

	if (vecDelta.x >= 0.0f) { qaOut.y += 180.0f; };
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

float CAimbot::Get3DDistance(Vector source, Vector destination)
{
	return(sqrtf((destination.x - source.x) * (destination.x - source.x) + (destination.y - source.y) * (destination.y - source.y) + (destination.z - source.z) * (destination.z - source.z)));
}

void CAimbot::GetBestTarget()
{
	//int(entity index) float(angle)
	map<int, float> CrosshairToPlayers;
	list<int> maxPlayers;

	//we get all players from the game
	maxPlayers = entityList->GetMaxPlayers();

	//some aimbot checks
	if (maxPlayers.empty() ||
		(Settings.AimbotDisableForPistols && localPlayer->HasPistol()) ||
		(localPlayer->HasBadWeapon()))
	{
		bAim = false;
		return;
	}

	//find all the players in our field of view
	for (auto it = maxPlayers.begin(); it != maxPlayers.end(); ++it)
	{
		//if the player from the list is not in our team add it to the target map
		if (entityList->GetTeam(*it) != localPlayer->GetTeam())
			CrosshairToPlayers.emplace(*it, GetFov(GetViewAngles(), localPlayer->GetEyePosition(), entityList->GetBone(*it, Settings.AimbotBone)));
	}

	//if we got no players closer to our crosshair do not aim
	//we return because if we dont have any target to aim ... we dont want to aim, right?
	if (CrosshairToPlayers.empty())
	{
		bAim = false;
		return;
	}

	//find the closest target to the crosshair
	auto minAnglesToPlayers = min_element(CrosshairToPlayers.begin(), CrosshairToPlayers.end(),
		[](const pair<int, float>& p1, const pair<int, float>& p2) {
		return p1.second < p2.second;
	});

	//if the closest target to the crosshair is less than the fov from settings aim to that target. Else do not aim to that target
	if (minAnglesToPlayers->second < Settings.AimbotFOV)
	{
		m_iBestTarget = minAnglesToPlayers->first;
		bAim = true;
	}
	else
	{
		m_iBestTarget = 0;
		bAim = false;
	}

	//If the new best target is not the old best target, start counting ticks again to check later the AimbotTime. And update the old best target
	if (m_iBestTarget != oldBestTarget)
	{
		iTickCount = timeGetTime();
		oldBestTarget = m_iBestTarget;
	}
}

void CAimbot::Main()
{
	while (FindWindow(NULL, "Counter-Strike: Global Offensive"))
	{
		Sleep(1);

		if (GetForegroundWindow() == FindWindow(NULL, "Counter-Strike: Global Offensive") &&
			localPlayer->IsInGame() &&
			!localPlayer->HasMouseEnabled() && 
			GetAsyncKeyState(Settings.AimbotKey) & 0x8000)
		{
			GetBestTarget();

			if (bAim && m_iBestTarget > 0)
			{
				m_vecPunch = localPlayer->GetVecPunch();
				m_localEyePosition = localPlayer->GetEyePosition();
				m_entityBone = entityList->GetBone(m_iBestTarget, Settings.AimbotBone);

				Distance = Get3DDistance(m_localEyePosition, m_entityBone);

				AimPosition.x = (vec_t)((asin((m_entityBone.z - m_localEyePosition.z) / Distance) * 180.0f / M_PI) * -1.0f);
				AimPosition.y = (vec_t)(ATAN2(m_entityBone.x - m_localEyePosition.x, m_entityBone.y - m_localEyePosition.y) / M_PI * 180.0f);
				AimPosition.z = 0.0f;

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
						m_vecPunch.x *= RandomFloat(1.50f, 1.99f);
						m_vecPunch.y *= RandomFloat(1.50f, 1.99f);

						m_vecPunch = PerfectRecoilControl(m_vecPunch);

						AimPosition.x -= m_vecPunch.x;
						AimPosition.y -= m_vecPunch.y;
					}
				}

				if (Settings.AimbotTime)
				{
					int iDelta = timeGetTime() - iTickCount;

					if (Settings.AimbotTime < iDelta)
						continue;
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

