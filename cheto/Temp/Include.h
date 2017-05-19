#ifndef _INCLUDE_H_
#define _INCLUDE_H_

//===== CHANGE_THIS =====//
#define DiskLetter "C:\\"
#define HWID 2619271064
 
#define URLSub		"https://www.dropbox.com/s/roj68j0qaykpddl/Pani.ini?raw=1"   //..?dl=0 cambiarlo por ?raw=1

#define URLSettings "https://www.dropbox.com/s/efoihobnhaukuef/Settings.ini?raw=1"
#define URLOffsets	"https://www.dropbox.com/s/oo07q44yrd604vm/Offsets.ini?raw=1"
#define URLInstructions "https://www.dropbox.com/s/i955irxfhns15yc/README.ini?raw=1"

#define CLIENT		Process->Client.Base
#define CLIENT_SIZE Process->Client.Size
#define ENGINE		Process->Engine.Base
#define ENGINE_SIZE Process->Engine.Size

#include <Windows.h>
#include <fstream> 
#include <TlHelp32.h>
#include <iostream>
#include <tchar.h>
#include <ctype.h>
#include "urlmon.h"
#include <wininet.h>
#include <algorithm>
#include <map>
#include <thread>

#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "winmm.lib" )
#pragma comment(lib, "Wininet.lib")

using namespace std;

#include "Vector.h"
#include "Process.h"
#include "Engine.h"

#define M_PI			3.14159265358979323846
#define M_PI_F			( ( float )( M_PI ) )
#define RAD2DEG( x )	( ( float )( x ) * ( float )( 180.0f / M_PI_F ) )

//Set your color for the string
class CColor
{
public:
	void Number(int ColorNumber)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ColorNumber);
	}
}; extern CColor* p_Color;

class CRandom
{
public:
	float Float(float Start, float End)
	{
		return Start + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (End - Start)));
	}
}; extern CRandom* Random;

#endif

