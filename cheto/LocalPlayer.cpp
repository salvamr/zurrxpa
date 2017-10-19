#include "Engine.h"
#include "Process.h"
#include "Offsets.h"

CLocalPlayer::CLocalPlayer() 
{}

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

bool CLocalPlayer::HasMouseEnabled()
{
	DWORD mouse_ptr = CLIENT + Offset.dwMouseEnablePtr;
	DWORD mouse_value_xored = Process.Read<DWORD>(CLIENT + Offset.dwMouseEnable);
	bool Value = mouse_ptr ^ mouse_value_xored;

	return !Value;
}

Vector CLocalPlayer::GetVecPunch()
{
	return Process.Read<Vector>(GetPlayer() + Offset.m_vecPunch);
}

bool CLocalPlayer::HasBadWeapon()
{
	switch (GetWeaponID())
	{
		case 42:
		case 43:
		case 44:
		case 45:
		case 46:
		case 47:
		case 48:
		case 49:
		case 59:
		case 64:
		case 500:
		case 505:
		case 506:
		case 507:
		case 508:
		case 509:
		case 512:
		case 514:
		case 515:
		case 516:
			return true;
		default:
			return false;
	}
}

bool CLocalPlayer::HasPistol()
{
	switch (GetWeaponID())
	{
		case 1:
		case 2:
		case 3:
		case 4:
		case 30:
		case 31:
		case 32:
		case 36:
		case 61:
		case 63:
			return true;
		default:
			return false;
	}
}

bool CLocalPlayer::IsInGame()
{
	DWORD m_dwClientState = Process.Read<DWORD>(ENGINE + Offset.m_dwClientState);
	return (Process.Read<int>(m_dwClientState + Offset.dwClientState_State) == 6);
}

void CLocalPlayer::SetAttack()
{
	if (!GetAsyncKeyState(0x01))
	{
		Process.Write(CLIENT + Offset.m_dwForceAttack, 1);
		Sleep(65);
		Process.Write(CLIENT + Offset.m_dwForceAttack, 0);
	}
}
