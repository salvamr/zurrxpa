#include "Printing.h"
#include "Process.h"

#include <Windows.h>

void Print::standar_exclamation(string msg, int color, bool tab)
{
	if (tab == true)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), defaultColor);
		cout << "[ ! ] ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
		cout << "\t" << msg.c_str() << endl;
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), defaultColor);
		cout << "[ ! ] ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
		cout << msg.c_str() << endl;
	}
}

void Print::standar_plus(string msg, int color, bool tab)
{
	if (tab == true)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), defaultColor);
		cout << "[ + ] ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
		cout << "\t" << msg.c_str() << endl;
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), defaultColor);
		cout << "[ + ] ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
		cout << msg.c_str() << endl;
	}
}

void Print::error(string msg)
{
	MessageBox(NULL, msg.c_str(), NULL, MB_ICONERROR | MB_OK);
	CloseHandle(Process.HandleProcess);
	ExitProcess(EXIT_SUCCESS);
}

void Print::it(string msg, bool tab, int color)
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

void Print::success(string msg, bool tab, int color)
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

void Print::warning(string msg, bool tab, int color)
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