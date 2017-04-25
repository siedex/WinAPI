﻿#include <windows.h>
#include <iostream>
#include <conio.h>
#include <tchar.h>
using namespace std;

int _tmain(int argc, TCHAR* argv[])
{
	LPVOID  lp;
	const int size = 1000;

	// распределяем виртуальную память
	lp = VirtualAlloc(
		(LPVOID)0x00890000,
		size,
		MEM_RESERVE | MEM_COMMIT,
		PAGE_READWRITE);

	if (!lp)
	{
		cout << "Virtual allocation failed." << endl;
		return GetLastError();
	}
	cout << "Virtual memory address: " << lp << endl;

	// освобождаем виртуальную память
	if (!VirtualFree(lp, 0, MEM_RELEASE))
	{
		cout << "Memory release failed." << endl;
		return GetLastError();
	}
	getch();
	return 0;
}
