// L5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>

volatile UINT counter;

using namespace std;

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
	DWORD IdThread;
	HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread, NULL, 0, &IdThread);

	if (hThread == NULL) 
		return GetLastError();

	char c;
	while (true)
	{
		cout << "Input 'y' to display the count or any char to exit: ";
		cin >> c;
		if (c == 'y')
			cout << "count = " << counter << endl;
		else
			ExitProcess(1);
	}

    return 0;
}

