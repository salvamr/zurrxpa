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
			if (!localPlayer->HasMouseEnabled())
			{		
				if (localPlayer->GetStatus() == 257 && GetAsyncKeyState(Settings.BunnyHopKey) & 0x8000)
				{
					Process.Write<DWORD>(CLIENT + Offset.m_dwForceJump, 5);
				}
				else
				{
					Process.Write<DWORD>(CLIENT + Offset.m_dwForceJump, 4);
				}
			}
		}
	}
}
