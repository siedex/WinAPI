
#include <windows.h>
#include "iostream"
using namespace std;

int main()
{
	// копируем файл
	if (!CopyFile(TEXT("D:\\demo_file.dat"), TEXT("D:\\new_file.dat"), FALSE))
	{
		cerr << "Copy file failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		cout << "Press any key to finish.";
		cin.get();
		return 0;
	}
	cout << "The file is copied." << endl;
	return 0;
}
