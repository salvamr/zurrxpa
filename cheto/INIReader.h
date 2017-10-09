#ifndef __INIREADER_H__
#define __INIREADER_H__

#include <string>
#include <map>

using namespace std;

class INIReader
{
public:
	INIReader(string filename);
	int ParseError();
	string GetString(string section, string name, string default_value);
	int GetInteger(string section, string name, int default_value);
	float GetFloat(string section, string name, float default_value);

private:
	int _error;
	map<string, string> _values;
	static string MakeKey(string section, string name);
	static int ValueHandler(void* user, const char* section, const char* name, const char* value);
};
#endif