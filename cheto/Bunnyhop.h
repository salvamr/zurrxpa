
#ifndef bunnyhop
#define bunnyhop

#include "Engine.h"

class CBunny
{
public:
	CBunny();
	~CBunny();
	void Main();
private:
	CLocalPlayer* localPlayer;

};

extern CBunny Bunnyhop;
#endif