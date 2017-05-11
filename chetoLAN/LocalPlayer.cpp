#include "Engine.h"

CLocalPlayer Local;

DWORD CLocalPlayer::GetPlayer()
{
	return Process.Read<DWORD>(CLIENT + Offset.m_dwLocalPlayer);
}

bool CLocalPlayer::IsShooting()
{
	return Process.Read<bool>(GetPlayer() + Offset.m_iShotsFired);
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
	DWORD CurrentWeapon = Process.Read<DWORD>(GetPlayer() + Offset.m_hActiveWeapon) & 0xFFF;
	DWORD WeaponEntity	= Process.Read<DWORD>(CLIENT + Offset.m_dwEntityList + (CurrentWeapon - 1) * 0x10);

	return Process.Read<int>(WeaponEntity + Offset.m_iItemDefinitionIndex);
}

Vector CLocalPlayer::GetEyePosition()
{ 
	Vector	temp	= Process.Read<Vector>(GetPlayer() + Offset.m_vecViewOffset);
	Vector	temp2	= Process.Read<Vector>(GetPlayer() + Offset.m_vecOrigin);
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

void CLocalPlayer::SetAttack()
{
	if (Settings.AimbotMouse == true && !GetAsyncKeyState(0x01))
	{
		int temp = Settings.AimbotKey;
		Settings.AimbotKey = 0;

		mouse_event(MOUSEEVENTF_LEFTDOWN, NULL, NULL, NULL, NULL);
		Sleep(60);
		mouse_event(MOUSEEVENTF_LEFTUP, NULL, NULL, NULL, NULL);

		Settings.AimbotKey = temp;
	}
	else if (Settings.AimbotMouse == false && !GetAsyncKeyState(0x01))
	{
		Process.Write(CLIENT + Offset.m_dwForceAttack, 1);
		Sleep(10);
		Process.Write(CLIENT + Offset.m_dwForceAttack, 0);
	}
}
