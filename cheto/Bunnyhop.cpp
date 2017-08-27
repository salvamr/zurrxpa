#include "Bunnyhop.h"

CBunny Bunnyhop;

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
		if (Settings.BunnyHopKey != 0 && GameStatus.Status && GetAsyncKeyState(Settings.BunnyHopKey) & 0x8000)
		{
			if (localPlayer->GetSpeed() > 0.003f)
			{
				if (localPlayer->GetStatus() & (1 << 0))
				{
					Process.Write<DWORD>(CLIENT + Offset.m_dwForceJump, 5);
					Process.Write<DWORD>(CLIENT + Offset.m_dwForceJump, 4);
					Process.Write<DWORD>(CLIENT + Offset.m_dwForceJump, 5);
				}
				else
				{
					Process.Write<DWORD>(CLIENT + Offset.m_dwForceJump, 4);
				}
			}
		}
		Sleep(1);
	}
}