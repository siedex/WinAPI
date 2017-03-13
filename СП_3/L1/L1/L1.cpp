// L1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <tchar.h>
#include <conio.h>
int main(int argc, TCHAR *argv[])
{
	_cputts(TEXT("I am created"));
	_cputts(TEXT("\nMy name is: "));
	_cputts(argv[0]);
	_cputts(TEXT("\n"));

	for (int i = 1; i < argc; i++)
	{
		cprintf("\n My %d parameter = %s", i, argv[i]);
	}
	_cputts(TEXT("Press any key to finish..."));
	_getch();
    return 0;
}

