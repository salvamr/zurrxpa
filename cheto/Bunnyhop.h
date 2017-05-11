#ifndef _BUNNY_H_
#define _BUNNY_H_

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

#endif