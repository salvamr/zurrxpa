#include "Include.h"
#include "ini.h"
#include "INIReader.h"

using std::string;

INIReader::INIReader(string filename)
{
	_error = ini_parse(filename.c_str(), ValueHandler, this);
}

int INIReader::ParseError()
{
	return _error;
}

string INIReader::GetString(string section, string name, string default_value)
{
	string key = MakeKey(section, name);
	return _values.count(key) ? _values[key] : default_value;
}

int INIReader::GetInteger(string section, string name, int default_value)
{
	string valstr = GetString(section, name, "");
	const char* value = valstr.c_str();
	char* end;
	int n = strtol(value, &end, 0);
	return end > value ? n : default_value;
}

float INIReader::GetFloat(string section, string name, float default_value)
{
	string valstr = GetString(section, name, "");
	const char* value = valstr.c_str();
	char* end;
	float n = strtof(value, &end);
	return end > value ? n : default_value;
}

string INIReader::MakeKey(string section, string name)
{
	string key = section + decode(/*.*/"Lg") + name;
	std::transform(key.begin(), key.end(), key.begin(), ::tolower);
	return key;
}

int INIReader::ValueHandler(void* user, const char* section, const char* name, const char* value)
{
	INIReader* reader = (INIReader*)user;
	string key = MakeKey(section, name);
	if (reader->_values[key].size() > 0)
		reader->_values[key] += "\n";
	reader->_values[key] += value;
	return 1;
}