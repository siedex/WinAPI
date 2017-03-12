// L6.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <tchar.h>
#include <iostream>

void ErrorMessageBox()
{
	TCHAR* lpMsgBuf = NULL;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (TCHAR*)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, lpMsgBuf, TEXT("Ошибка Win32 API"), MB_OK | MB_ICONHAND);
	LocalFree(lpMsgBuf);

}

int main()
{
	HANDLE hHandle = NULL;
	if (!CloseHandle(hHandle))
		ErrorMessageBox();
	return 0;
}

