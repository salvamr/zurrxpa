#include "Triggerbot.h"

CTrigger Triggerbot;

void CTrigger::Main()
{
	if (Settings.TriggerKey && Game.Status && !Weapon.IsBadWeapon())
	{
		if (Settings.TriggerDisableForPistols && Weapon.IsPistol())
			return;

		Entity.GetEntity(Local.GetCrosshairID());

		if (!Entity.IsDormant() && GetAsyncKeyState(Settings.TriggerKey) & 0x8000)
		{
			if (Entity.GetHealth() > 100 || Entity.IsInvisible())
				return;
			else
			{
				if (GetAsyncKeyState(Settings.TriggerKey))
				{
					if (Local.GetCrosshairID() > 0 && Entity.GetHealth() != 0 && Local.GetTeam() != Entity.GetTeam())
					{
						Sleep(Settings.TriggerDelay);
						Local.SetAttack();
						Sleep(Settings.TriggerDelay);
					}
				}
			}
		}
		else
		{
			Entity.GetEntity(Local.GetCrosshairID());
		}
	}
}
