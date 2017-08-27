
#ifndef misc
#define misc

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

	void featureNoFlash();
	void featurePanicKey();
	void featureReloadKey();
	void featureHideWindow();
	void featureMarioBrosSong();
};

extern CMisc Misc;

#endif