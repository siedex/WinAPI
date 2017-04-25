// ParentProcessHandleInfo.cpp : Defines the entry point for the console application.
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
	char lpszComLine[80]; 			// для командной строки 

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	HANDLE hThread;
	DWORD IDThread;

	_cputs("Press any key to start the count-thread.\n");
	_getch(); 

										// запускаем поток-счетчик 
	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread, NULL, 0, &IDThread);
	if (hThread == NULL) 	return GetLastError();

	// устанавливаем атрибуты нового процесса 
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	
	if (!SetHandleInformation(hThread, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT))
	{
		_cputs("The inheritance is not changed.\n");
		_cputs("Press any char to finish.\n");
		_getch();
		return GetLastError();
	}

	// формируем командную строку 
	std::stringstream ssCommand;
	ssCommand << "c:\\ChildProcess.exe " << reinterpret_cast<int>(hThread);
	std::string strCmd = ssCommand.str();

	// запускаем новый консольный процесс 
	if (!CreateProcess(
		NULL, 				// имя процесса 
		&strCmd[0], 			// адрес командной строки 
		NULL, 				// атрибуты защиты процесса по умолчанию 
		NULL, 				// атрибуты защиты первичного потока по умолчанию 
		TRUE, 				// наследуемые дескрипторы текущего процесса 
							// наследуются новым процессом 
		CREATE_NEW_CONSOLE, 	// новая консоль 
		NULL, 				// используем среду окружения процесса предка 
		NULL, 				// текущий диск и каталог, как и в процессе-предке 
		&si, 					// вид главного окна - по умолчанию 
		&pi 					// здесь будут дескрипторы и идентификаторы 
								// нового процесса и его первичного потока 
	))
	{
		_cputs("The new process is not created.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return GetLastError();
	}
	// закрываем дескрипторы нового процесса 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	// ждем закрытия потока-счетчика 
	WaitForSingleObject(hThread, INFINITE);
	_cputs("Press any key to exit.\n");
	_getch();
	// закрываем дескриптор потока 
	CloseHandle(hThread);
	return 0;
}




