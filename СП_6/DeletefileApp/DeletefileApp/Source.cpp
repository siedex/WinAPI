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
	fileName,   // ��� �����
		GENERIC_WRITE,         // ������ � ����
		0,                     // ����������� ������ � �����
		NULL,                  // ������ ��� 
		CREATE_ALWAYS,            // ������� ����� ����
		FILE_ATTRIBUTE_NORMAL, // ������� ����
		NULL                   // ������� ���
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
	// ������� ����
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
