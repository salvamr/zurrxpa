#include "Engine.h"

CEntity* Entity = new CEntity();

CEntity::CEntity()
{}

CEntity::~CEntity()
{}

void CEntity::GetEntity(int Index)
{
	EntityList = Process->Read<DWORD>(CLIENT + Offset->m_dwEntityList + (Index - 1) * 0x10);
}

bool CEntity::IsAlive()
{
	return Process->Read<bool>(EntityList + Offset->m_lifeState);
}

bool CEntity::IsInvisible()
{
	return Process->Read<bool>(EntityList + Offset->m_bGunGameImmunity);
}

bool CEntity::IsDormant( )
{
	return Process->Read<bool>(EntityList + Offset->m_bDormant);
}

int CEntity::GetHealth( )
{
	return Process->Read<int>(EntityList + Offset->m_iHealth);
}

int CEntity::GetTeam( )
{
	return Process->Read<int>(EntityList + Offset->m_iTeamNum);
}

DWORD CEntity::GetBoneMatrix( )
{
	return Process->Read<DWORD>(EntityList + Offset->m_dwBoneMatrix);
}

Vector CEntity::GetBone( int BoneID )
{
	Vector temp;

	temp.x = Process->Read<vec_t>(GetBoneMatrix() + 0x30 * BoneID + 0x0C);
	temp.y = Process->Read<vec_t>(GetBoneMatrix() + 0x30 * BoneID + 0x1C);
	temp.z = Process->Read<vec_t>(GetBoneMatrix() + 0x30 * BoneID + 0x2C);

	return temp;
}
