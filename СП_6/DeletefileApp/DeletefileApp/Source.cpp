#include <windows.h>
#include "iostream"
#include <winnt.h>
#include <tchar.h>
using namespace std;

int main()
{
	TCHAR* fileName = TEXT("D:\\demo_file.dat");
	int x;
	HANDLE hFile = CreateFile(
	fileName,   // имя файла
		GENERIC_WRITE,         // запись в файл
		0,                     // монопольный доступ к файлу
		NULL,                  // защиты нет 
		CREATE_ALWAYS,            // создаем новый файл
		FILE_ATTRIBUTE_NORMAL, // обычный файл
		NULL                   // шаблона нет
	);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		cerr << "Error" << endl;
		return GetLastError();
	}

	cout << "File created." << endl;
	cout << "To delete file press any key..." << endl;

	CloseHandle(hFile);
	getchar();
	// удаляем файл
	if (!DeleteFile(fileName))
	{
		cerr << "Delete file failed." << endl << "The last error code: " << GetLastError() << endl;
		cout << "Press any key to finish.";
		cin.get();
		return 0;
	}
	cout << "The file is deleted." << endl;
	x = getchar();
	return 0;
}
