#ifndef _INCLUDE_H_
#define _INCLUDE_H_

#define CLIENT		(DWORD)Process.Client
#define ENGINE		(DWORD)Process.Engine

#include <Windows.h>
#include <fstream> 
#include <TlHelp32.h>
#include <stdint.h>
#include <iostream>
#include <cstdint>
#include <tchar.h>
#include <Wtsapi32.h>
#include <vector>
#include <ctype.h>
#include "urlmon.h"
#include <Psapi.h>
#include <Userenv.h>
#include <wininet.h>
#include <algorithm>
#include <map>
#include <thread>
#include <string>
#include "Subauth.h"
#include "Shlwapi.h"

#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "winmm.lib" )
#pragma comment(lib, "Wininet.lib")
#pragma comment(lib,"Wtsapi32")
#pragma comment(lib,"Userenv")
#pragma comment(lib,"psapi")
#pragma comment(lib, "Shlwapi.lib")

using namespace std;

#include "Vector.h"
#include "Process.h"
#include "Engine.h"
#include "INIReader.h"

#define M_PI			3.14159265358979323846f
#define M_PI_F			( ( float )( M_PI ) )
#define RAD2DEG( x )	( ( float )( x ) * ( float )( 180.0f / M_PI_F ) )

class  CGameStatus
{
public:
	bool Status;
}; extern CGameStatus GameStatus;

#endif
