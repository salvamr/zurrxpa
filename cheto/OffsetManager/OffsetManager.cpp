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
			Offset.m_fFlags				= pNetVarManager->GetNetVar("DT_BasePlayer", "m_fFlags");
			Offset.m_iHealth			= pNetVarManager->GetNetVar("DT_BasePlayer", "m_iHealth");
			Offset.m_hActiveWeapon		= pNetVarManager->GetNetVar("DT_BasePlayer", "m_hActiveWeapon");
			Offset.m_vecViewOffset		= pNetVarManager->GetNetVar("DT_BasePlayer", "m_vecViewOffset[0]");
			Offset.m_vecVelocity		= pNetVarManager->GetNetVar("DT_BasePlayer", "m_vecVelocity[0]");
			Offset.m_vecPunch			= pNetVarManager->GetNetVar("DT_BasePlayer", "m_Local") + 0x70;
			Offset.m_dwBoneMatrix		= pNetVarManager->GetNetVar("DT_BaseAnimating","m_nForceBone") + 0x1C;

			// Signatures
			Offset.m_bDormant = 0xE9;//= pProcess->FindPattern("client.dll", "55 8B EC 53 8B 5D 08 56 8B F1 88 9E ? ? ? ? E8", Remote::SignatureType_t::READ, 0xC, 0x0);
			Offset.m_dwLocalPlayer		= pProcess->FindPattern("client.dll", "8D 34 85 ? ? ? ? 89 15", Remote::SignatureType_t::READ | Remote::SignatureType_t::SUBTRACT, 0x3, 0x4);
			Offset.m_dwEntityList		= pProcess->FindPattern("client.dll", "BB ? ? ? ? 83 FF 01 0F 8C ? ? ? ? 3B F8", Remote::SignatureType_t::READ | Remote::SignatureType_t::SUBTRACT, 0x1, 0x0);
			Offset.m_dwForceJump		= pProcess->FindPattern("client.dll", "89 0D ? ? ? ? 8B 0D ? ? ? ? 8B F2 8B C1 83 CE 08", Remote::SignatureType_t::READ | Remote::SignatureType_t::SUBTRACT, 0x2, 0x0);
			Offset.m_dwForceAttack		= pProcess->FindPattern("client.dll", "89 0D ? ? ? ? 8B 0D ? ? ? ? 8B F2 8B C1 83 CE 04", Remote::SignatureType_t::READ | Remote::SignatureType_t::SUBTRACT, 0x2, 0x0);
			Offset.m_pSensitivity		= pProcess->FindPattern("client.dll", "6A 01 51 C7 04 24 17 B7 D1 38 B9", Remote::SignatureType_t::READ | Remote::SignatureType_t::SUBTRACT, 0xB, 0x0);
			Offset.m_dwSensitivity		= pProcess->FindPattern("client.dll", "6A 01 51 C7 04 24 17 B7 D1 38 B9", Remote::SignatureType_t::READ | Remote::SignatureType_t::SUBTRACT, 0xB, 0x2C);
			Offset.m_dwClientState		= pProcess->FindPattern("engine.dll", "8B 3D ? ? ? ? 8A F9", Remote::SignatureType_t::READ | Remote::SignatureType_t::SUBTRACT, 0x2, 0x0);
			Offset.m_dwViewAngles		= pProcess->FindPattern("engine.dll", "F3 0F 11 80 ? ? ? ? D9 46 04 D9 05 ? ? ? ?", Remote::SignatureType_t::READ, 0x4, 0x0);	

			//cout << "m_iItemDefinitionIndex 0x" << hex << Offset.m_iItemDefinitionIndex << endl;
			//cout << "m_vecOrigin 0x" << hex << Offset.m_vecOrigin << endl;
			//cout << "m_iTeamNum 0x" << hex << Offset.m_iTeamNum << endl;
			//cout << "m_flFlashDuration 0x" << hex << Offset.m_flFlashDuration << endl;
			//cout << "m_bGunGameImmunity 0x" << hex << Offset.m_bGunGameImmunity << endl;
			//cout << "m_iCrossHairID 0x" << hex << Offset.m_iCrossHairID << endl;
			//cout << "m_iShotsFired 0x" << hex << Offset.m_iShotsFired << endl;
			//cout << "m_lifeState 0x" << hex << Offset.m_lifeState << endl;
			//cout << "m_fFlags 0x" << hex << Offset.m_fFlags << endl;
			//cout << "m_iHealth 0x" << hex << Offset.m_iHealth << endl;
			//cout << "m_hActiveWeapon 0x" << hex << Offset.m_hActiveWeapon << endl;
			//cout << "m_vecViewOffset 0x" << hex << Offset.m_vecViewOffset << endl;
			//cout << "m_vecVelocity 0x" << hex << Offset.m_vecVelocity << endl;
			//cout << "m_vecPunch 0x" << hex << Offset.m_vecPunch << endl;
			//cout << "m_dwBoneMatrix 0x" << hex << Offset.m_dwBoneMatrix << endl;
			//cout << "m_bDormant 0x" << hex << Offset.m_bDormant << endl;
			//cout << "m_dwLocalPlayer 0x" << hex << Offset.m_dwLocalPlayer << endl;
			//cout << "m_dwEntityList 0x" << hex << Offset.m_dwEntityList << endl;
			//cout << "m_dwForceJump 0x" << hex << Offset.m_dwForceJump << endl;
			//cout << "m_dwForceAttack 0x" << hex << Offset.m_dwForceAttack << endl;
			//cout << "m_pSensitivity 0x" << hex << Offset.m_pSensitivity << endl;
			//cout << "m_dwSensitivity 0x" << hex << Offset.m_dwSensitivity << endl;
			//cout << "m_dwClientState 0x" << hex << Offset.m_dwClientState << endl;
			//cout << "m_dwViewAngles 0x" << hex << Offset.m_dwViewAngles << endl;
		}

        COffsetManager* COffsetManager::Singleton( void )
        {
            static auto g_pOffsetManager = new COffsetManager();
            return g_pOffsetManager;
        }
    }
}

