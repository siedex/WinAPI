// L8.cpp : Defines the entry point for the console application.
//

#include <windows.h> 
#include <iostream> 

using namespace std;
void CoutErrorMessage()
{
	char prefix[] = "Ошибка Win32 API: ";
	LPVOID lpMsgBuf;

	CharToOem(prefix, prefix); // перекодируем заголово

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // язык по умолчанию 
		(LPTSTR)&lpMsgBuf,
		0,
		NULL
	);
	// перекодируем русские буквы 
	CharToOem((char*)lpMsgBuf, (char*)lpMsgBuf);
	// выводим сообщение об ошибке на консоль
	cout << prefix << (char*)lpMsgBuf << endl;
	// освобождаем буфер 
	LocalFree(lpMsgBuf);
}


int main()
{
	HANDLE hHandle = NULL;

	// неправильный вызов функции закрытия дескриптора 
	if (!CloseHandle(hHandle))
		CoutErrorMessage();
	return 0;

}

