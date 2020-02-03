#include "Bunnyhop.h"

#include "Process.h"
#include "Settings.h"
#include "Offsets.h"

#include <Windows.h>

CBunny::CBunny()
{
	localPlayer = new CLocalPlayer();
}

CBunny::~CBunny()
{

}

void CBunny::Main()
{
	while (FindWindow(NULL, "Counter-Strike: Global Offensive"))
	{
		Sleep(1);

 		if (GetForegroundWindow() == FindWindow(NULL, "Counter-Strike: Global Offensive") && localPlayer->IsInGame())
		{
			if (!localPlayer->HasMouseEnabled() && GetAsyncKeyState(Settings.BunnyHopKey))
			{		
				if (localPlayer->GetStatus() & (1 << 0) && localPlayer->IsMoving())
				{
					Process.Write<DWORD>(CLIENT + Offset.m_dwForceJump, 5);
				}
				else
				{
					Process.Write<DWORD>(CLIENT + Offset.m_dwForceJump, 4);
					Process.Write<DWORD>(CLIENT + Offset.m_dwForceJump, 5);
					Process.Write<DWORD>(CLIENT + Offset.m_dwForceJump, 4);
				}
			}
		}
	}
}
