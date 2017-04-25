// ParentProcessDuplicate.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include <windows.h> 
#include <conio.h> 
#include <string>
#include <sstream>

using namespace std;
volatile int counter;

void thread()
{
	for (;;)
	{
		counter++;
		Sleep(100);
		_cprintf("count = %d\n", counter);
	}
}

int main()
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	HANDLE hThread, hInheritThread;
	DWORD IDThread;

	_cputs("Press any key to start the count-thread.\n");
	_getch();

	// ��������� �����-������� 
	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread, NULL, 0, &IDThread);
	if (hThread == NULL) 	return GetLastError();

	// ������������� �������� ������ �������� 
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);

	if (!DuplicateHandle(GetCurrentProcess(), hThread, GetCurrentProcess(), &hInheritThread, 0, TRUE, DUPLICATE_SAME_ACCESS))
	{
		_cputs("The handle is not duplicated.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return GetLastError();
	}

	// ��������� ��������� ������ 
	std::stringstream ssCommand;
	ssCommand << "c:\\ChildProcess.exe " << reinterpret_cast<int>(hInheritThread);
	std::string strCmd = ssCommand.str();

	// ��������� ����� ���������� ������� 
	if (!CreateProcess(
		NULL, 				// ��� �������� 
		&strCmd[0], 			// ����� ��������� ������ 
		NULL, 				// �������� ������ �������� �� ��������� 
		NULL, 				// �������� ������ ���������� ������ �� ��������� 
		TRUE, 				// ����������� ����������� �������� �������� 
							// ����������� ����� ��������� 
		CREATE_NEW_CONSOLE, 	// ����� ������� 
		NULL, 				// ���������� ����� ��������� �������� ������ 
		NULL, 				// ������� ���� � �������, ��� � � ��������-������ 
		&si, 					// ��� �������� ���� - �� ��������� 
		&pi 					// ����� ����� ����������� � �������������� 
								// ������ �������� � ��� ���������� ������ 
	))
	{
		_cputs("The new process is not created.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return GetLastError();
	}
	// ��������� ����������� ������ �������� 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	// ���� �������� ������-�������� 
	WaitForSingleObject(hThread, INFINITE);
	_cputs("Press any key to exit.\n");
	_getch();
	// ��������� ���������� ������ 
	CloseHandle(hThread);
	CloseHandle(hInheritThread);
	return 0;
}






