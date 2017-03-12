// L5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h> 
#include <iostream> 

using namespace std;
int main()
{
	HANDLE hThread;

	// получаем псевдодескриптор текущего потока 
	hThread = GetCurrentThread();

	// выводим псевдодескриптор на консоль 
	cout << hThread << endl;

	cin.get();

	return 0;
}


