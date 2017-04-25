// Priority.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include <windows.h> 
#include <conio.h> 

using namespace std;
int main()
{
	HANDLE hProcess;
	DWORD dwPriority;

	// �������� ���������������� �������� ������ 
	hProcess = GetCurrentProcess();

	// ������ ��������� �������� �������� 
	dwPriority = GetPriorityClass(hProcess);
	_cprintf("The priority of the process = %d.\n", dwPriority);

	// ������������� ������� ��������� �������� �������� 
	if (!SetPriorityClass(hProcess, IDLE_PRIORITY_CLASS))
	{
		_cputs("Set priority class failed.\n");
		_cputs("Press any key to exit.\n");
		_getch();
		return GetLastError();
	}
	dwPriority = GetPriorityClass(hProcess);
	_cprintf("The priority of the process = %d.\n", dwPriority);

	// ������������� ������� ��������� �������� �������� 
	if (!SetPriorityClass(hProcess, HIGH_PRIORITY_CLASS))
	{
		_cputs("Set priority class failed.\n");
		_cputs("Press any key to exit.\n");
		_getch();
		return GetLastError();
	}
	dwPriority = GetPriorityClass(hProcess);
	_cprintf("The priority of the process = %d.\n", dwPriority);

	_cputs("Press any key to exit.\n");
	_getch();

	return 0;
}


