
#ifndef offsets
#define offsets

#include <Windows.h>

class COffsets
{
public:

	DWORD m_iItemDefinitionIndex,
		m_vecOrigin,
		m_iTeamNum,
		m_flFlashDuration,
		m_bGunGameImmunity,
		m_iShotsFired,
		m_lifeState,
		m_fFlags,
		m_iHealth,
		m_hActiveWeapon,
		m_vecViewOffset,
		m_vecPunch,
		m_iCrossHairID,
		m_dwBoneMatrix,
		m_bDormant,
		m_dwClientState,
		m_dwViewAngles,
		m_dwLocalPlayer,
		m_dwEntityList,
		m_dwForceJump,
		m_dwForceAttack,
		m_pSensitivity,
		m_dwSensitivity,
		m_dwMaxPlayers,
		dwClientState_State,
		dwMouseEnable,
		dwMouseEnablePtr,
		m_vecVelocity ;

	void	Load();
}; 

extern COffsets Offset;

#endif