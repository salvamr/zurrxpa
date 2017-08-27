#ifndef _MISC_H_
#define _MISC_H

#include "Include.h"
#include "Offsets.h"
#include "Settings.h"
#include "Aimbot.h"

class CMisc
{
public:
	CMisc();
	~CMisc();
	void Main();
private:
	CLocalPlayer* localPlayer;

	void featurePanicKey();
	void featureReloadKey();
};

#endif