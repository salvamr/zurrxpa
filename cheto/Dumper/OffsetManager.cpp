#include "HOffsetManager.h"
#include "..\Offsets.h"

#include <sstream>
#include <fstream>
#include <iomanip>

#include "HUtilis.h"
#include "HNetVarManager.h"

namespace Dumper
{
    namespace OffsetManager
    {
        void COffsetManager::Dump( void )
        {
            if( dDumper->GetModuleByName( "client.dll" ) == nullptr || dDumper->GetModuleByName( "engine.dll" ) == nullptr)
                return;
			
			// NetVars
			
			Offset.m_iItemDefinitionIndex = pNetVarManager->GetNetVar("DT_BaseAttributableItem", "m_iItemDefinitionIndex");

			Offset.m_vecOrigin			= pNetVarManager->GetNetVar("DT_BasePlayer","m_vecOrigin");
			Offset.m_iTeamNum			= pNetVarManager->GetNetVar("DT_BaseEntity","m_iTeamNum");

			Offset.m_bGunGameImmunity	= pNetVarManager->GetNetVar("DT_CSPlayer","m_bGunGameImmunity");
			Offset.m_iCrossHairID		= pNetVarManager->GetNetVar("DT_CSPlayer", "m_bHasDefuser") + 0x5C;
			Offset.m_iShotsFired		= pNetVarManager->GetNetVar("DT_CSPlayer", "m_iShotsFired");
			Offset.m_vecVelocity 		= pNetVarManager->GetNetVar("DT_CSPlayer", "m_vecVelocity[0]");

			Offset.m_lifeState			= pNetVarManager->GetNetVar("DT_BasePlayer", "m_lifeState");
			Offset.m_fFlags				= pNetVarManager->GetNetVar("DT_BasePlayer", "m_fFlags");
			Offset.m_iHealth			= pNetVarManager->GetNetVar("DT_BasePlayer", "m_iHealth");
			Offset.m_hActiveWeapon		= pNetVarManager->GetNetVar("DT_BasePlayer", "m_hActiveWeapon");
			Offset.m_vecViewOffset		= pNetVarManager->GetNetVar("DT_BasePlayer", "m_vecViewOffset[0]");
			Offset.m_vecPunch			= pNetVarManager->GetNetVar("DT_BasePlayer", "m_Local") + 0x70;

			Offset.m_dwBoneMatrix		= pNetVarManager->GetNetVar("DT_BaseAnimating","m_nForceBone") + 0x1C;

			// Signatures
			Offset.m_bDormant = 0xE9;//= dDumper->FindPattern("client.dll", "55 8B EC 53 8B 5D 08 56 8B F1 88 9E ? ? ? ? E8", Remote::SignatureType_t::READ, 0xC, 0x0);
			Offset.m_dwLocalPlayer		= dDumper->FindPattern("client.dll", "A3 ? ? ? ? C7 05 ? ? ? ? ? ? ? ? E8 ? ? ? ? 59 C3 6A ?", Remote::SignatureType_t::READ | Remote::SignatureType_t::SUBTRACT, 0x1, 0x10);
			Offset.m_dwEntityList		= dDumper->FindPattern("client.dll", "BB ? ? ? ? 83 FF 01 0F 8C ? ? ? ? 3B F8", Remote::SignatureType_t::READ | Remote::SignatureType_t::SUBTRACT, 0x1, 0x0);
			Offset.m_dwForceJump		= dDumper->FindPattern("client.dll", "8B 0D ? ? ? ? 8B D6 8B C1 83 CA 02", Remote::SignatureType_t::READ | Remote::SignatureType_t::SUBTRACT, 0x2, 0x0);
			Offset.m_dwForceAttack		= dDumper->FindPattern("client.dll", "89 0D ? ? ? ? 8B 0D ? ? ? ? 8B F2 8B C1 83 CE 04", Remote::SignatureType_t::READ | Remote::SignatureType_t::SUBTRACT, 0x2, 0x0);
			Offset.m_pSensitivity		= dDumper->FindPattern("client.dll", "81 F9 ? ? ? ? 75 1D F3 0F 10 05 ? ? ? ? F3 0F 11 44 24 ? 8B 44 24 18 35 ? ? ? ? 89 44 24 0C EB 0B", Remote::SignatureType_t::READ | Remote::SignatureType_t::SUBTRACT, 0x2, 0x0);
			Offset.m_dwSensitivity		= dDumper->FindPattern("client.dll", "81 F9 ? ? ? ? 75 1D F3 0F 10 05 ? ? ? ? F3 0F 11 44 24 ? 8B 44 24 18 35 ? ? ? ? 89 44 24 0C EB 0B", Remote::SignatureType_t::READ | Remote::SignatureType_t::SUBTRACT, 0x2, 0x2C);
			Offset.m_dwClientState		= dDumper->FindPattern("engine.dll", "A1 ? ? ? ? 33 D2 6A 00 6A 00 33 C9 89 B0", Remote::SignatureType_t::READ | Remote::SignatureType_t::SUBTRACT, 0x1, 0x0);
			Offset.m_dwViewAngles		= dDumper->FindPattern("engine.dll", "F3 0F 11 80 ? ? ? ? D9 46 04 D9 05", Remote::SignatureType_t::READ, 0x4, 0x0);
			Offset.m_dwMaxPlayers		= dDumper->FindPattern("engine.dll", "A1 ? ? ? ? 8B 80 ? ? ? ? C3 CC CC CC CC 55 8B EC 8A 45 08", Remote::SignatureType_t::READ, 0x7, 0x0);
			Offset.dwClientState_State	= dDumper->FindPattern("engine.dll", "83 B8 ? ? ? ? ? 0F 94 C0 C3", Remote::SignatureType_t::READ, 0x2, 0x0);
			Offset.dwMouseEnable		= dDumper->FindPattern("client.dll", "B9 ? ? ? ? FF 50 34 85 C0 75 10", Remote::SignatureType_t::READ | Remote::SignatureType_t::SUBTRACT, 0x1, 0x30);
			Offset.dwMouseEnablePtr		= dDumper->FindPattern("client.dll", "B9 ? ? ? ? FF 50 34 85 C0 75 10", Remote::SignatureType_t::READ | Remote::SignatureType_t::SUBTRACT, 0x1, 0x0);
		}

        COffsetManager* COffsetManager::Singleton( void )
        {
            static auto g_pOffsetManager = new COffsetManager();
            return g_pOffsetManager;
        }
    }
}