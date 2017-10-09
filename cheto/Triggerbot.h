
#ifndef triggerbot
#define triggerbot

#include "Engine.h"

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