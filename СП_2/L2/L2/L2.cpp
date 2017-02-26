﻿// L2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h> 
#include <iostream> 
#include <string.h> 
#include <process.h> 

using namespace std;

HANDLE hMutex;

UINT WINAPI thread(void *pString)
{
	int i = 1;
	char *pLexema;
	pLexema = strtok((char*)pString, " ");
	while (pLexema != NULL)
	{
		WaitForSingleObject(hMutex, INFINITE);
		cout << "Thread find the lexema " << i << " : " << pLexema << endl;
		ReleaseMutex(hMutex);

		pLexema = strtok(NULL, " ");
		i++;
	}
	return 0;
}

int main()
{
	char sentence[80];
	int i, j, k = 0;
	HANDLE hThread;
	UINT IDThread;

	hMutex = CreateMutex(NULL, FALSE, NULL);

	cout << "Input string: ";
	cin.getline(sentence, 80);
	j = strlen(sentence);

	// создаем поток для подсчета лексем 
	hThread = (HANDLE)
		_beginthreadex(NULL, 0, thread, sentence, 0, &IDThread);
	if (hThread == NULL)
		return GetLastError();

	// сами подсчитываем количество букв "а" в строке 
	for (i = 0; i<j; i++)
		if (sentence[i] == 'a')
			k++;
	
	WaitForSingleObject(hMutex, INFINITE);
	cout << "Number of symbols 'a' in the string = " << k << endl;
	ReleaseMutex(hMutex);

	// ждем окончания разбора на лексемы 
	WaitForSingleObject(hThread, INFINITE);
	// закрываем дескриптор потока thread 
	CloseHandle(hThread);
	return 0;
}


