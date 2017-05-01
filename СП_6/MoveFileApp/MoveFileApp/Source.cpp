#include <windows.h>
#include "iostream"
using namespace std;
int main()
{
	// ןונולושאול פאיכ
	if (!MoveFile(TEXT("D:\\demo_file.dat"), TEXT("D:\\folder\\new_file.dat")))
	{
		cerr << "Move file failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		cout << "Press any key to finish.";
		cin.get();
		return 0;
	}
	cout << "The file is moved." << endl;
	return 0;
}
