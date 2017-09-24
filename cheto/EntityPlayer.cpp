#include "Engine.h"

CEntity::CEntity() 
{}

DWORD CEntity::GetEntity(int Index)
{
	return Process.Read<DWORD>(CLIENT + Offset.m_dwEntityList + (Index - 1) * 0x10);
}

bool CEntity::IsAlive(int Index)
{
	return Process.Read<bool>(GetEntity(Index) + Offset.m_lifeState);
}

bool CEntity::IsInvisible(int Index)
{
	return Process.Read<bool>(GetEntity(Index) + Offset.m_bGunGameImmunity);
}

bool CEntity::IsDormant(int Index)
{
	return Process.Read<bool>( GetEntity(Index) + Offset.m_bDormant);
}

int CEntity::GetHealth(int Index)
{
	return Process.Read<int>( GetEntity(Index) + Offset.m_iHealth);
}

int CEntity::GetTeam(int Index)
{
	return Process.Read<int>( GetEntity(Index) + Offset.m_iTeamNum);
}

DWORD CEntity::GetBoneMatrix(int Index)
{
	return Process.Read<DWORD>( GetEntity(Index) + Offset.m_dwBoneMatrix);
}

list<int> CEntity::GetMaxPlayers()
{
	int maxPlayers = 0;
	list<int> totalPlayers;

	maxPlayers = Process.Read<int>(Process.Read<DWORD>(ENGINE + Offset.m_dwClientState) + Offset.m_dwMaxPlayers);

	for (int i = 0; i < maxPlayers; i++)
	{
		if (this->GetEntity(i) && 
			!this->IsAlive(i) && 
			!this->IsDormant(i) && 
			this->GetBoneMatrix(i) && 
			this->GetHealth(i) > 0 &&
			!this->IsInvisible(i) &&
			!this->GetBone(i, Settings.AimbotBone).IsZero())
			totalPlayers.push_back(i);
	}

	return totalPlayers; 
}

Vector CEntity::GetBone(int Index, int BoneID )
{
	Vector temp;

	temp.x = Process.Read<vec_t>(GetBoneMatrix(Index) + 0x30 * BoneID + 0x0C);
	temp.y = Process.Read<vec_t>(GetBoneMatrix(Index) + 0x30 * BoneID + 0x1C);
	temp.z = Process.Read<vec_t>(GetBoneMatrix(Index) + 0x30 * BoneID + 0x2C);

	return temp;
}