#ifndef __INIREADER_H__
#define __INIREADER_H__

#include "Include.h"

class INIReader
{
public:
	INIReader(string filename);
	int ParseError();
	string GetString(string section, string name, string default_value);
	long GetInteger(string section, string name, long default_value);
	double GetDouble(string section, string name, double default_value);
	bool GetBoolean(string section, string name, bool default_value);

private:
	int _error;
	map<string, string> _values;
	static string MakeKey(string section, string name);
	static int ValueHandler(void* user, const char* section, const char* name, const char* value);
};
#endif
