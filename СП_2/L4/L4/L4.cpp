// L4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>

using namespace std;

volatile UINT nCount;

void thread()
{
	while (true)
	{
		nCount++;
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
		cout << "Input :" << endl;
		cout << "\t'n' to exit" << endl;
		cout << "\t'y' to display the count" << endl;
		cout << "\t's' to suspend thread" << endl;
		cout << "\t'r' to resume thread" << endl;
		cin >> c;

		if (c == 'n')
			break;

		switch (c)
		{
		case 'y':
			cout << "count == " << nCount << endl;
			break;
		case 's':
		{
			DWORD dwCount = SuspendThread(hThread);
			cout << "Thread suspend count == " << dwCount << endl;
			break;
		}
		case 'r':
		{
			DWORD dwCount = ResumeThread(hThread);
			cout << "Thread suspend count == " << dwCount << endl;
			break;
		}
		}
	}

	TerminateThread(hThread, 0);
	CloseHandle(hThread);
    return 0;
}

