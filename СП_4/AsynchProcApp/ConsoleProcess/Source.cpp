#include <windows.h> 
#include <iostream>

using namespace std;
int main()
{
	HANDLE hMutex;

	hMutex = OpenMutex(SYNCHRONIZE, FALSE, "DemoMutex");
	int i,j;
	for (j = 10; j < 20; ++j)
	{
		WaitForSingleObject(hMutex, INFINITE);
		for (i = 0; i < 10; ++i)
		{
			cout << j << ' ' << flush;
			Sleep(5);
		}
		cout << endl;
		ReleaseMutex(hMutex);
	}
	return 0;
}
