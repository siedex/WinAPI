// ThreadPriorityBoost.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h> 
#include <conio.h> 

using namespace std;
int main()
{
	HANDLE hProcess, hThread;
	BOOL bPriorityBoost;

	// �������� ���������������� �������� �������� 
	hProcess = GetCurrentProcess();

	// ������ ����� ������������� ��������� ����������� ��� �������� 
	if (!GetProcessPriorityBoost(hProcess, &bPriorityBoost))
	{
		_cputs("Get process priority boost failed.\n");
		_cputs("Press any key to exit.\n");
		_getch();
		return GetLastError();
	}
	_cprintf("The process priority boost = %d.\n", bPriorityBoost);

	// ��������� ����� ������������� ��������� ����������� ��� �������� 
	if (!SetProcessPriorityBoost(hProcess, TRUE))
	{
		_cputs("Set process priority boost failed.\n");
		_cputs("Press any key to exit.\n");
		_getch();
		return GetLastError();
	}

	// �������� ���������������� �������� ������ 
	hThread = GetCurrentThread();
	// ������ ����� ������������� ��������� ����������� ��� ������ 
	if (!GetThreadPriorityBoost(hThread, &bPriorityBoost))
	{
		_cputs("Get process priority boost failed.\n");
		_cputs("Press any key to exit.Xn");
		_getch();
		return GetLastError();
	}
	_cprintf("The thread priority boost = %d.\n", bPriorityBoost);

	// �������� ����� ������������� ��������� ����������� ��� ������ 
	if (!SetThreadPriorityBoost(hThread, FALSE))
	{
		_cputs("Set process priority boost failed.\n");
		_cputs("Press any key to exit.\n");
		_getch();
		return GetLastError();
	}
	_cputs("Press any key to exit.\n");

	_getch();
	return 0;
}

