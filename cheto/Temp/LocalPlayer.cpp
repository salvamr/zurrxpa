#include "Engine.h"

CLocalPlayer* Local = new CLocalPlayer();

CLocalPlayer::CLocalPlayer()
{}

CLocalPlayer::~CLocalPlayer()
{}

DWORD CLocalPlayer::GetPlayer()
{
	return Process->Read<DWORD>(CLIENT + Offset->m_dwLocalPlayer);
}

bool CLocalPlayer::IsShooting()
{
	return Process->Read<bool>(GetPlayer() + Offset->m_iShotsFired);
}

int CLocalPlayer::GetStatus()
{
	return Process->Read<int>(GetPlayer() + Offset->m_fFlags);
}

int CLocalPlayer::GetHealth()
{
	return Process->Read<int>(GetPlayer() + Offset->m_iHealth);
}

int CLocalPlayer::GetCrosshairID()
{
	return Process->Read<int>(GetPlayer() + Offset->m_iCrossHairID);
}

int CLocalPlayer::GetTeam()
{
	return Process->Read<int>(GetPlayer() + Offset->m_iTeamNum);
}

int CLocalPlayer::GetWeaponID()
{
	DWORD CurrentWeapon = Process->Read<DWORD>(GetPlayer() + Offset->m_hActiveWeapon) & 0xFFF;
	DWORD WeaponEntity	= Process->Read<DWORD>(CLIENT + Offset->m_dwEntityList + (CurrentWeapon - 1) * 0x10);

	return Process->Read<int>(WeaponEntity + Offset->m_iItemDefinitionIndex);
}

Vector CLocalPlayer::GetEyePosition()
{ 
	Vector	temp	= Process->Read<Vector>(GetPlayer() + Offset->m_vecViewOffset);
	Vector	temp2	= Process->Read<Vector>(GetPlayer() + Offset->m_vecOrigin);
	return	temp + temp2;
}

float CLocalPlayer::GetSpeed()
{
	Vector w = Process->Read<Vector>(GetPlayer() + Offset->m_vecVelocity);

	return sqrt(w.x * w.x + w.y * w.y + w.z * w.z);
}

Vector CLocalPlayer::GetVecPunch()
{
	return Process->Read<Vector>(GetPlayer() + Offset->m_vecPunch);
}

void CLocalPlayer::SetAttack()
{
	if (!GetAsyncKeyState(0x01))
	{
		Process->Write(CLIENT + Offset->m_dwForceAttack, 1);
		Sleep(10);
		Process->Write(CLIENT + Offset->m_dwForceAttack, 0);
	}
}

