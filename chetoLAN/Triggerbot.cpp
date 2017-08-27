#include "Triggerbot.h"

CTrigger::CTrigger()
{
	localPlayer = new CLocalPlayer();
	entityList = new CEntity();
	crossId = 0;
}

CTrigger::~CTrigger()
{
}

void CTrigger::doTrigger()
{
	if (GameStatus.Status && Settings.TriggerKey && GetAsyncKeyState(Settings.TriggerKey) & 0x8000 && !localPlayer->IsBadWeapon())
	{
		crossId = localPlayer->GetCrosshairID();

		if ((Settings.TriggerDisableForPistols && localPlayer->IsPistol()))
		{
			return;
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

void CTrigger::Main()
{
	while (FindWindow(NULL, "Counter-Strike: Global Offensive"))
	{
		doTrigger();
		Sleep(1);
	}
}
