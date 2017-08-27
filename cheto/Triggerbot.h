
#ifndef triggerbot
#define triggerbot

#include "Include.h"
#include "Offsets.h"
#include "WeaponConfig.h"

class CTrigger
{
public:
	CTrigger();
	~CTrigger();
	void	Main();
private:
	CLocalPlayer* localPlayer;
	CEntity* entityList;
	int crossId;
}; 

extern CTrigger Triggerbot;

#endif