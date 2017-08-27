#ifndef _TRIGGER_H_
#define _TRIGGER_H_

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
	void doTrigger();
	CLocalPlayer* localPlayer;
	CEntity* entityList;
	int crossId;
}; 

#endif