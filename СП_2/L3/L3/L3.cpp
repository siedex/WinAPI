// L3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>

using namespace std;

volatile UINT counter;

void thread()
{
	while (true)
	{
		counter++;
		Sleep(100);
	}
}

int main()
{
	HANDLE hThread;
	DWORD IdThread;
	char c;

	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread, NULL, 0, &IdThread);
	if (hThread == NULL)
		return GetLastError();

	while (true)
	{
		cout << "Input 'y' to display the count or any char to finish: ";
		cin >> c;
		if (c == 'y')
			cout << "count == " << counter << endl;
		else
			break;
	}

	TerminateThread(hThread, 0);
	CloseHandle(hThread);
    return 0;
}

