#ifndef _INCLUDE_H_
#define _INCLUDE_H_

#define CLIENT		Process.Client.Base
#define ENGINE		Process.Engine.Base

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
#include <string>

#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "winmm.lib" )
#pragma comment(lib, "Wininet.lib")

using namespace std;

#include "Vector.h"
#include "Process.h"
#include "Engine.h"
#include "INIReader.h"
#include "Printing.h"

#define M_PI			3.14159265358979323846f
#define M_PI_F			( ( float )( M_PI ) )
#define RAD2DEG( x )	( ( float )( x ) * ( float )( 180.0f / M_PI_F ) )

class  CGameStatus
{
public:
	bool Status;
}; extern CGameStatus GameStatus;

#endif
