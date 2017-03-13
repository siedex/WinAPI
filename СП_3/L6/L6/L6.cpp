// L6.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h> 
#include <conio.h> 
#include "iostream"
using namespace std;

int main()
{
	char IpszCommandLine[] = "c:\\L5.exe";
	STARTUPINFO si;
	PROCESS_INFORMATION piCom;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);

	// создаем новый консольный процесс 
	if (!CreateProcess(NULL, IpszCommandLine, NULL, NULL, FALSE,
		CREATE_NEW_CONSOLE, NULL, NULL, &si, &piCom))
	{
		_cputs("The new process is not created.\n");
		_cputs("Check a name of the process.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return 0;
	}

	_cputs("The new process is created.\n");
	while (true)
	{
		char c;
		_cputs("Input 't' to terminate the new console process: ");
		c = _getch();
		if (c == 't')
		{
			_cputs("t\n");
			// завершаем новый процесс 
			TerminateProcess(piCom.hProcess, 1);
			break;
		}
	}
	// закрываем дескрипторы нового процесса в текущем процессе 
	CloseHandle(piCom.hThread);
	CloseHandle(piCom.hProcess);
	return 0;
}


