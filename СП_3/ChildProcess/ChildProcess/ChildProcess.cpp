// ChildProcess.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h> 
#include <conio.h> 
#include "iostream"
#include <string>
#include <sstream>
using namespace std;

int main(int argc, char *argv[])
{
	HANDLE hThread;
	std::string str = argv[1];
	int code = std::stoi(str);
	// преобразуем символьное представление дескриптора в число 
	hThread = reinterpret_cast<HANDLE>(code);

	char c;
	// ждем команды о завершении потока 
	while (true)
	{
		_cputs("Input 't' to terminate the thread: ");
		c = _getch();
		if (c == 't')
		{
			_cputs("t\n");
			break;
		}
	}
	TerminateThread(hThread, 0);
	// закрываем дескриптор потока 
	CloseHandle(hThread);

	_cputs("Press any key to exit.\n");
	_getch();
	return 0;
}


