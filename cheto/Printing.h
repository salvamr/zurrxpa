#ifndef printing
#define printing

#include <iostream>

using namespace std;

class Print
{
public:
	static void error(string msg);

	static void it(string msg, bool tab = false, int color = 7); //Lightgray

	static void warning(string msg, bool tab = false, int color = 14); //Yellow

	static void success(string msg, bool tab = false, int color = 14); //Yellow
private:
	static void standar_exclamation(string msg, int color, bool tab = false);
	static void standar_plus(string msg, int color, bool tab = false);
	static const int defaultColor = 7;
}; 

#endif