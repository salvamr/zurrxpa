#include "HOffsetManager.h"
#include "..\Offsets.h"

#include <sstream>
#include <fstream>
#include <iomanip>

#include "../Utilis/HUtilis.h"
#include "../NetVarManager/HNetVarManager.h"

namespace Dumper
{
    namespace OffsetManager
    {
        void COffsetManager::Dump( void )
        {
            if( !pProcess->GetModuleByName( "client.dll" ) || !pProcess->GetModuleByName( "engine.dll" ) )
                return;

			// NetVars
			
			Offset.m_iItemDefinitionIndex = pNetVarManager->GetNetVar("DT_BaseAttributableItem", "m_iItemDefinitionIndex");

			Offset.m_vecOrigin			= pNetVarManager->GetNetVar("DT_BaseEntity","m_vecOrigin");
			Offset.m_iTeamNum			= pNetVarManager->GetNetVar("DT_BaseEntity","m_iTeamNum");
			Offset.m_flFlashDuration	= pNetVarManager->GetNetVar("DT_CSPlayer","m_flFlashDuration");
			Offset.m_bGunGameImmunity	= pNetVarManager->GetNetVar("DT_CSPlayer","m_bGunGameImmunity");
			Offset.m_iCrossHairID		= pNetVarManager->GetNetVar("DT_CSPlayer", "m_bHasDefuser") + 0x5C;
			Offset.m_iShotsFired		= pNetVarManager->GetNetVar("DT_CSPlayer", "m_iShotsFired");

			Offset.m_lifeState			= pNetVarManager->GetNetVar("DT_BasePlayer", "m_lifeState");
			Offset.m_nTickBase			= pNetVarManager->GetNetVar("DT_BasePlayer", "m_nTickBase");
			Offset.m_fFlags				= pNetVarManager->GetNetVar("DT_BasePlayer", "m_fFlags");
			Offset.m_iHealth			= pNetVarManager->GetNetVar("DT_BasePlayer", "m_iHealth");
			Offset.m_hActiveWeapon		= pNetVarManager->GetNetVar("DT_BasePlayer", "m_hActiveWeapon");
			Offset.m_vecViewOffset		= pNetVarManager->GetNetVar("DT_BasePlayer", "m_vecViewOffset[0]");
			Offset.m_vecVelocity		= pNetVarManager->GetNetVar("DT_BasePlayer", "m_vecVelocity[0]");
			Offset.m_vecPunch			= pNetVarManager->GetNetVar("DT_BasePlayer", "m_Local") + 0x70;
			Offset.m_dwBoneMatrix		= pNetVarManager->GetNetVar("DT_BaseAnimating","m_nForceBone") + 0x1C;

			// Signatures
			Offset.m_bDormant			= pProcess->FindPattern("client.dll", "55 8B EC 53 8B 5D 08 56 8B F1 88 9E ? ? ? ? E8", Remote::SignatureType_t::READ, 0xC, 0x0);
			Offset.m_dwLocalPlayer		= pProcess->FindPattern("client.dll", "8D 34 85 ? ? ? ? 89 15", Remote::SignatureType_t::READ | Remote::SignatureType_t::SUBTRACT, 0x3, 0x4);
			Offset.m_dwEntityList		= pProcess->FindPattern("client.dll", "BB ? ? ? ? 83 FF 01 0F 8C ? ? ? ? 3B F8", Remote::SignatureType_t::READ | Remote::SignatureType_t::SUBTRACT, 0x1, 0x0);
			Offset.m_dwForceJump		= pProcess->FindPattern("client.dll", "89 15 ? ? ? ? 8B 15 ? ? ? ? F6 C2 03 74 03 83 CE 08", Remote::SignatureType_t::READ | Remote::SignatureType_t::SUBTRACT, 0x2, 0x0);
			Offset.m_dwForceAttack		= pProcess->FindPattern("client.dll", "89 15 ? ? ? ? 8B 15 ? ? ? ? F6 C2 03 74 03 83 CE 04", Remote::SignatureType_t::READ | Remote::SignatureType_t::SUBTRACT, 0x2, 0x0);
			Offset.m_pSensitivity		= pProcess->FindPattern("client.dll", "6A 01 51 C7 04 24 17 B7 D1 38 B9", Remote::SignatureType_t::READ | Remote::SignatureType_t::SUBTRACT, 0xB, 0x0);
			Offset.m_dwSensitivity		= pProcess->FindPattern("client.dll", "6A 01 51 C7 04 24 17 B7 D1 38 B9", Remote::SignatureType_t::READ | Remote::SignatureType_t::SUBTRACT, 0xB, 0x2C);
			Offset.m_dwClientState		= pProcess->FindPattern("engine.dll", "A1 ? ? ? ? F3 0F 11 80 ? ? ? ? D9 46 04 D9 05", Remote::SignatureType_t::READ | Remote::SignatureType_t::SUBTRACT, 0x1, 0x0);
			Offset.m_dwViewAngles		= pProcess->FindPattern("engine.dll", "F3 0F 11 80 ? ? ? ? D9 46 04 D9 05 ? ? ? ?", Remote::SignatureType_t::READ, 0x4, 0x0);	
		}

        COffsetManager* COffsetManager::Singleton( void )
        {
            static auto g_pOffsetManager = new COffsetManager();
            return g_pOffsetManager;
        }
    }
}

