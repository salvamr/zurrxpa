#ifndef _H_PRINTING
#define _H_PRINTING

#include <Windows.h>
#include <iostream>
#include "Process.h"

using namespace std;

class  CPrinClass
{
public:
	void error(string msg);

	void it(string msg, bool tab = false, int color = 7); //Lightgray
	void succes(string msg, bool tab = false, int color = 10); //Green
	void warning(string msg, bool tab = false, int color = 14); //Yellow
private:
	void standar_exclamation(string msg, int color, bool tab = false);
	void standar_plus(string msg, int color, bool tab = false);
	const int defaultColor = 7;
}; extern CPrinClass Print;

#endif