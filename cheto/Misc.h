
#ifndef misc
#define misc

#include "Engine.h"
#include <thread>

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

#endif