#include <windows.h>
#include "iostream"
using namespace std;

int main()
{
	DWORD  file_attr;
	HANDLE hFile = CreateFile(TEXT
	("D:\\normal.dat"),   // имя файла
		GENERIC_ALL,          // чтение из файла
		0,                     // монопольный доступ к файлу
		NULL,                  // защиты нет 
		CREATE_ALWAYS,         // открываем существующий файл
		FILE_ATTRIBUTE_NORMAL, // обычный файл
		NULL                   // шаблона нет
	);

	// читаем атрибуты файла
	file_attr = GetFileAttributes(TEXT("D:\\normal.dat"));
	if (file_attr == -1)
	{
		cerr << "Get file attributes failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		cout << "Press any key to finish.";
		cin.get();
		return 0;
	}
	// проверяем, является ли файл нормальным
	if (file_attr == FILE_ATTRIBUTE_NORMAL)
		cout << "This is a normal file." << endl;
	else
	{
		cout << "This is a not normal file." << endl;
		return 0;
	}
	// устанавливаем атрибут скрытого файла
	if (!SetFileAttributes(TEXT("D:\\normal.dat"), FILE_ATTRIBUTE_HIDDEN))
	{
		cerr << "Set file attributes failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		cout << "Press any key to finish.";
		cin.get();
		return 0;
	}
	// Теперь можно проверить, что файл скрылся
	cout << "Now the file is hidden." << endl
		<< "Press any key to continue.";
	cin.get();
	// Обратно делаем файл обычным
	if (!SetFileAttributes(TEXT("D:\\normal.dat"), FILE_ATTRIBUTE_NORMAL))
	{
		cerr << "Set file attributes failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		cout << "Press any key to finish.";
		cin.get();
		return 0;
	}
	cout << "Now the file is again normal." << endl;
	return 0;
}
