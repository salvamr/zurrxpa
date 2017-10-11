
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
	static thread miscThread;
private:
	CLocalPlayer* localPlayer;

	void featureNoFlash();
	void featurePanicKey();
	void featureReloadKey();
	void featureHideWindow();
	void featureMarioBrosSong();
};

#endif