// L3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <conio.h>

int main()
{
	char lpszCommandLine[] = "c:\\L1.exe pi p2 p3";

	STARTUPINFO startupInfo;
	PROCESS_INFORMATION processInformation;

	ZeroMemory(&startupInfo, sizeof(startupInfo));
	startupInfo.cb = sizeof(startupInfo);

	if (!CreateProcess(NULL, lpszCommandLine, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &startupInfo, &processInformation))
	{
		cputs("The new process is not created.\n");
		_cputs("Check a name of the process.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return 0;
	}

	while (true)
	{
		char c;
		_cputs("Input 't' to terminate the new console process: ");
		c = _getch();
		if (c == 't')
		{
			_cputs("t\n");
			
			TerminateProcess(processInformation.hProcess, 0);
			break;
		}
	}

	CloseHandle(processInformation.hProcess);
	CloseHandle(processInformation.hThread);

	cputs("Press any key to finish.\n");
	_getch();

    return 0;
}

