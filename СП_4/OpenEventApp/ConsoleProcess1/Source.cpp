#include <windows.h> 
#include <iostream>

using namespace std;
HANDLE hlnEvent;
CHAR lpEventName[] = "EventName";
int main()
{
	char c;
	hlnEvent = OpenEvent(EVENT_MODIFY_STATE, FALSE, lpEventName);
	if (hlnEvent == NULL)
	{
		cout << "Open event failed." << endl;
		cout << "Input any char to exit." << endl;
		cin.get();
		return GetLastError();
	}
	cout << "Input any char: ";
	cin >> c;
	// устанавливаем событие о вводе символа 
	SetEvent(hlnEvent);
	// закрываем дескриптор события в текущем процессе 
	CloseHandle(hlnEvent);
	cin.get();
	cout << "Press any key to exit." << endl;
	cin.get();
	return 0;
}
