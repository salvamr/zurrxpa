#include "Printing.h"

CPrinClass Print;

void CPrinClass::standar_exclamation(string msg, int color, bool tab)
{
	if (tab == true)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), defaultColor);
		cout << "[ ! ] ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
		cout << "\t" << msg << endl;
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), defaultColor);
		cout << "[ ! ] ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
		cout << msg << endl;
	}
}

void CPrinClass::standar_plus(string msg, int color, bool tab)
{
	if (tab == true)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), defaultColor);
		cout << "[ + ] ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
		cout << "\t" << msg << endl;
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), defaultColor);
		cout << "[ + ] ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
		cout << msg << endl;
	}
}

void CPrinClass::error(string msg)
{
	MessageBox(NULL, msg.c_str(), NULL, MB_ICONERROR | MB_OK);
	CloseHandle(Process.HandleProcess);
	ExitProcess(EXIT_SUCCESS);
}

void CPrinClass::it(string msg, bool tab, int color)
{
	if (tab == true)
	{
		standar_plus(msg, color, tab);
	}
	else
	{
		standar_plus(msg, color);
	}
}

void CPrinClass::warning(string msg, bool tab, int color)
{
	if (tab == true)
	{
		standar_exclamation(msg, color, tab);
	}
	else
	{
		standar_exclamation(msg, color);
	}
}

void CPrinClass::succes(string msg, bool tab, int color)
{
	if (tab == true)
	{
		standar_exclamation(msg, color, tab);
	}
	else
	{
		standar_exclamation(msg, color);
	}
}