
#ifndef triggerbot
#define triggerbot

#include "Engine.h"
#include <thread>

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

#endif