#include <Windows.h>
#include "Game.h"

/*prototype function*/
bool GenerateWindow(HINSTANCE hInstance, int nCmdShow, LPCSTR className, LPCSTR windowTitle, int width, int height, HWND& hWnd);
bool GenerateWindow(HINSTANCE hInstance, int nCmdShow, LPCSTR className, LPCSTR windowTitle, int x, int y, int width, int height, HWND& hWnd);
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

//Game *myGame = new Game; dfsgsdfgdsaffasfsda
/* WinMain */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd;
	if (GenerateWindow(hInstance, nCmdShow, "MyWindow", "MyGame", WND_WIDTH, WND_HEIGHT, hWnd))
	{
		if(myGame->Init(hWnd, hInstance))
		{

			MSG msg;
			ZeroMemory(&msg, sizeof(msg));
			while (true)
			{
				while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				if (msg.message == WM_QUIT)
					break;
				else
				{
					// run game in here
					myGame->Run();
				}

			}
		}
		delete myGame;
	}
	return 1;
}

bool GenerateWindow(HINSTANCE hInstance, int nCmdShow, LPCSTR className, LPCSTR windowTitle, int x, int y, int width, int height, HWND& hWnd)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = WinProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = className;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = NULL;
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	if (!RegisterClassEx(&wc))
	{
		return false;
	}
	hWnd = CreateWindowEx(NULL, className, windowTitle, WS_OVERLAPPEDWINDOW, x, y, width, height, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return true;
}

bool GenerateWindow(HINSTANCE hInstance, int nCmdShow, LPCSTR className, LPCSTR windowTitle, int width, int height, HWND& hWnd)
{
	return GenerateWindow(hInstance, nCmdShow, className, windowTitle, GetSystemMetrics(SM_CXSCREEN) / 2 - width / 2,
		GetSystemMetrics(SM_CYSCREEN) / 2 - height / 2, width, height, hWnd);
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	default:
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}



