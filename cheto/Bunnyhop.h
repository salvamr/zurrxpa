
#ifndef bunnyhop
#define bunnyhop

#include "Include.h"
#include "Offsets.h"
#include "Settings.h"

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