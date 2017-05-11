#ifndef _MISC_H_
#define _MISC_H

#include "Include.h"
#include "Offsets.h"
#include "Settings.h"
#include "Aimbot.h"

class CMisc
{
public:
	void Main();
private:

	void featurePanicKey();
	void featureReloadKey();

}; extern CMisc Misc;

#endif