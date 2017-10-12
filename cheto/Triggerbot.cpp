#include "Triggerbot.h"

#include "Settings.h"
#include <Windows.h>

CTrigger::CTrigger()
{
	localPlayer = new CLocalPlayer();
	entityList = new CEntity();
	crossId = 0;
}

CTrigger::~CTrigger()
{
}

void CTrigger::Main()
{
	while (FindWindow(NULL, "Counter-Strike: Global Offensive"))
	{
		Sleep(1);

		if (GetForegroundWindow() == FindWindow(NULL, "Counter-Strike: Global Offensive") && !localPlayer->HasMouseEnabled() && GetAsyncKeyState(Settings.TriggerKey) & 0x8000 && !localPlayer->HasBadWeapon())
		{
			crossId = localPlayer->GetCrosshairID();

			if ((Settings.TriggerDisableForPistols && localPlayer->HasPistol()))
			{
				continue;
			}

			if (entityList->GetHealth(crossId) < 100 || !entityList->IsInvisible(crossId) || !entityList->IsDormant(crossId))
			{
				if (crossId != 0 && entityList->GetHealth(crossId) > 0 && entityList->GetTeam(crossId) != localPlayer->GetTeam())
				{
					Sleep(Settings.TriggerDelay);
					localPlayer->SetAttack();
					Sleep(Settings.TriggerDelay);
				}
			}

			crossId = 0;
		}
	}
}

