#include "Engine.h"

CLocalPlayer::CLocalPlayer() 
{

}

DWORD CLocalPlayer::GetPlayer()
{
	return Process.Read<DWORD>(CLIENT + Offset.m_dwLocalPlayer);
}

bool CLocalPlayer::IsShooting()
{
	return Process.Read<bool>(GetPlayer() + Offset.m_iShotsFired);
}

int CLocalPlayer::GetStatus()
{
	return Process.Read<int>(GetPlayer() + Offset.m_fFlags);
}

int CLocalPlayer::GetHealth()
{
	return Process.Read<int>(GetPlayer() + Offset.m_iHealth);
}

int CLocalPlayer::GetCrosshairID()
{
	return Process.Read<int>(GetPlayer() + Offset.m_iCrossHairID);
}

float CLocalPlayer::GetSensitivity()
{
	DWORD sens_ptr = CLIENT + Offset.m_pSensitivity;
	DWORD sens_value_xored = Process.Read<DWORD>(CLIENT + Offset.m_dwSensitivity);
	DWORD Value = sens_ptr ^ sens_value_xored;
	return *(float*)&Value;
}


void CLocalPlayer::SetSensitivity(float Value)
{
	DWORD sens_ptr = CLIENT + Offset.m_pSensitivity;
	DWORD sens_value_xored = *(int*)&Value ^ sens_ptr;
	Process.Write<DWORD>(CLIENT + Offset.m_dwSensitivity, sens_value_xored);
}

int CLocalPlayer::GetTeam()
{
	return Process.Read<int>(GetPlayer() + Offset.m_iTeamNum);
}

int CLocalPlayer::GetWeaponID()
{
	DWORD WeaponIndex = Process.Read<DWORD>(GetPlayer() + Offset.m_hActiveWeapon) & 0xFFF;
	DWORD WeapEnt = Process.Read<DWORD>(CLIENT + Offset.m_dwEntityList + (WeaponIndex - 1) * 0x10);

	return Process.Read<int>(WeapEnt + Offset.m_iItemDefinitionIndex);
}

Vector CLocalPlayer::GetEyePosition()
{ 
	Vector	temp = Process.Read<Vector>(GetPlayer() + Offset.m_vecViewOffset);
	Vector	temp2 = Process.Read<Vector>(GetPlayer() + Offset.m_vecOrigin);
	return	temp + temp2;
}

float CLocalPlayer::GetSpeed()
{
	Vector w = Process.Read<Vector>(GetPlayer() + Offset.m_vecVelocity);

	return sqrt(w.x * w.x + w.y * w.y + w.z * w.z);
}

Vector CLocalPlayer::GetVecPunch()
{
	return Process.Read<Vector>(GetPlayer() + Offset.m_vecPunch);
}

bool CLocalPlayer::IsBadWeapon()
{
	return (GetWeaponID() == 42 || GetWeaponID() == 43 || GetWeaponID() == 44 || GetWeaponID() == 45 || GetWeaponID() == 46 || GetWeaponID() == 47 || GetWeaponID() == 48
		|| GetWeaponID() == 49 || GetWeaponID() == 59 || GetWeaponID() == 64 || GetWeaponID() == 500 || GetWeaponID() == 505 || GetWeaponID() == 506 || GetWeaponID() == 507 || GetWeaponID() == 508
		|| GetWeaponID() == 509 || GetWeaponID() == 512 || GetWeaponID() == 514 || GetWeaponID() == 515 || GetWeaponID() == 516) ? true : false;
}

bool CLocalPlayer::IsPistol()
{
	return (GetWeaponID() == 31 || GetWeaponID() == 1 || GetWeaponID() == 2 || GetWeaponID() == 3 || GetWeaponID() == 4 || GetWeaponID() == 30 || GetWeaponID() == 32 || GetWeaponID() == 36
		|| GetWeaponID() == 61 || GetWeaponID() == 63) ? true : false;
}

void CLocalPlayer::SetAttack()
{
	if (!GetAsyncKeyState(0x01))
	{
		Process.Write(CLIENT + Offset.m_dwForceAttack, 1);
		Sleep(65);
		Process.Write(CLIENT + Offset.m_dwForceAttack, 0);
		Sleep(65);
	}
}
