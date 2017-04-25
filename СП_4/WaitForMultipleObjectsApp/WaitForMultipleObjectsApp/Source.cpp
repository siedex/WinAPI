﻿#include <windows.h> 
#include <iostream> 

using namespace std;
void thread_0()
{
	int i;
	for (i = 0; i < 5; ++i)
	{
		cout << i << ' '  << flush;
		Sleep(7);
	}
	cout << endl;
}

void thread_l()
{
	int i;
	for (i = 5; i < 10; ++i)
	{
		cout << i << ' ' << flush;
		Sleep(7);
	}
	cout << endl;
}
int main()
{
	HANDLE hThread[2];
	DWORD dwThread[2];
	// запускаем первый поток
	hThread[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_0, NULL, 0, &dwThread[0]);
	if (hThread[0] == NULL) return GetLastError();
	// запускаем второй поток 
	hThread[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_l, NULL, 0, &dwThread[1]);
	if (hThread[1] == NULL) return GetLastError();
	// ждем завершения потоков thread_l и thread_2 
	if (WaitForMultipleObjects(2, hThread, TRUE, INFINITE) == WAIT_FAILED)
	{
		cout << "Wait for multiple objects failed." << endl;
		cout << "Input any char to exit." << endl;
		cin.get();
	}
	// закрываем дескрипторы потоков thread_0 и thread_l 
	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);
	return 0;
}
