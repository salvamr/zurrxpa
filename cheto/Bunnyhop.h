
#ifndef bunnyhop
#define bunnyhop

#include "Engine.h"
#include <thread>

class CBunny
{
public:
	CBunny();
	~CBunny();
	void Main();
	static thread bunnyThread;
private:
	CLocalPlayer* localPlayer;

};
#endif