#pragma once
#ifndef include
#define include

#define CLIENT		(DWORD)Process.Client
#define ENGINE		(DWORD)Process.Engine

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
#include "Psapi.h"
#include "Shlwapi.h"
#include <list>

#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "winmm.lib" )
#pragma comment(lib, "Wininet.lib")
#pragma comment(lib,"psapi")
#pragma comment(lib, "Shlwapi.lib")

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
}; 
extern CGameStatus GameStatus;
#endif
