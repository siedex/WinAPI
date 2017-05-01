#include <windows.h>
#include <tchar.h>
#include <ctime>

#define MAXLENGTH 256
#define THREADS_COUNT 16
#define TIMER_ELLAPSE 500

struct threadArgs
	
{
	unsigned int seed;
	unsigned int threadID;
	HDC hdc;
	threadArgs(unsigned int tid, HDC _hdc)	
	{
		threadID = tid;
		seed = (unsigned int)rand() * RAND_MAX;	
		hdc = _hdc;
	}
};


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void CalculateArea(int, int);
void Thread(void*);

RECT areas[THREADS_COUNT];
HANDLE mutex;
bool isFirst = true;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("Threads16");
	MSG msg;
	WNDCLASS wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = TEXT("MENU");
	wndclass.lpszClassName = szAppName;

	RegisterClass(&wndclass);
	
	HWND hwnd = CreateWindow(szAppName, TEXT("16 Threads"), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, nullptr, nullptr, hInstance, nullptr);
	SetTimer(hwnd, 1, TIMER_ELLAPSE, NULL);

	mutex = CreateMutex(NULL, FALSE, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	

	switch (message)
	{
	case WM_SIZE:
	{
		CalculateArea(LOWORD(lParam), HIWORD(lParam));
		return 0;
	}
	case WM_PAINT:
	{
		HDC hdc = BeginPaint(hwnd, &ps);
		threadArgs *array[THREADS_COUNT] = { 0 };
		HANDLE hThreads[THREADS_COUNT];
		for (int i = 0; i < THREADS_COUNT; i++)
		{
			DWORD idThread;
			array[i] = new threadArgs(i, hdc);
			hThreads[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread, (LPVOID)array[i], 0, &idThread);
			WaitForSingleObject(hThreads[i],INFINITE);
		}
		//WaitForMultipleObjects(THREADS_COUNT, hThreads, TRUE, INFINITE);
		EndPaint(hwnd, &ps);

		for (int i = 0; i < THREADS_COUNT; i++)
		{
			CloseHandle(hThreads[i]);
			delete(array[i]);
		}
		return 0;
	}
	case WM_CLOSE:
	{
		DestroyWindow(hwnd);
		return 0;
	}
	case WM_TIMER:
		InvalidateRect(hwnd, NULL, TRUE);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		break;
	}
	return DefWindowProc(hwnd,message,wParam,lParam);
}

void CalculateArea(int width, int height)
{
	int stepX = width / (THREADS_COUNT);
	
	int index = 0;
	for (int x = 0; x <= width - stepX; x += stepX)
	{
			areas[index].left = x;
			areas[index].top = 0;
			areas[index].right = x + stepX;
			areas[index].bottom = height;
			index++;
	}

	return;
}

void Thread(void *pIndex)
{
	
	WaitForSingleObject(mutex, INFINITE);
	
	threadArgs* args = (threadArgs*)pIndex;

	srand(args->seed);

	RECT rect = areas[args->threadID];
	HBRUSH brush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
	FillRect(args->hdc, &rect, brush);

	DeleteObject(brush);
	ReleaseMutex(mutex);
}

