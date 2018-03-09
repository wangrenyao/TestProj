// Win32Project1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Win32Project1.h"

#include <Windows.h>

#define WM_TESTMSG (WM_USER + 0x100)
LRESULT CALLBACK MainWndProc(IN HWND hWnd, IN UINT uMsg, IN WPARAM wParam, IN LPARAM lParam)
{
	LRESULT ret = 0;
	switch (uMsg)
	{
		case WM_CREATE:
		{
			PostMessage(hWnd, WM_TESTMSG, 0, 0);
			break;
		}

		case WM_TESTMSG:
		{
			SendMessage(hWnd, WM_TESTMSG, 0, 0);
			MessageBeep(MB_ICONERROR);	// I think the program can't run to here
			break;
		}

		case WM_CLOSE:
		{
			DestroyWindow(hWnd);
			break;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}

		default:
		{
			ret = ::DefWindowProc(hWnd, uMsg, wParam, lParam);
			break;
		}
	}

	return ret;
}



BOOL RegisterWndClass(IN HINSTANCE hInstance)
{
	WNDCLASSEX wndClassEx;

	ZeroMemory(&wndClassEx, sizeof(wndClassEx));
	wndClassEx.cbSize = sizeof (wndClassEx);
	wndClassEx.style = CS_HREDRAW | CS_VREDRAW;
	wndClassEx.lpfnWndProc = MainWndProc;
	wndClassEx.cbClsExtra = 0;
	wndClassEx.cbWndExtra = 0;
	wndClassEx.hInstance = hInstance;
	wndClassEx.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_HAND));
	wndClassEx.hCursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW));
	wndClassEx.hbrBackground = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
	wndClassEx.lpszMenuName = NULL;
	wndClassEx.lpszClassName = TEXT("MyMainWnd");
	wndClassEx.hIconSm = LoadIcon(NULL, MAKEINTRESOURCE(IDI_ERROR));

	return ::RegisterClassEx(&wndClassEx);
}


int WINAPI WinMain(IN HINSTANCE hInstance, IN HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	RegisterWndClass(hInstance);
	
	HWND hMainWnd = CreateWindowEx(0, L"MyMainWnd", L"MainWnd", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, 0, hInstance, 0);

	ShowWindow(hMainWnd, SW_SHOWNORMAL);
	UpdateWindow(hMainWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}


/*
		case WM_PAINT:
		{
			OutputDebugStringA("MainWindow WM_PAINT called.\n");
			ret = 0;
			SendMessage(hWnd, WM_PAINT, 0, 0);

			MessageBeep(MB_ICONERROR);
			//MessageBox(hWnd, L"SendMessge  returned", L"", MB_OK | MB_ICONERROR);
			//DebugBreak();
			break;
		}


INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
		break;
	}
	case WM_TIMER:
	{
		OutputDebugStringA("WM_TIMER.\n");
		break;
	}
	case WM_CLOSE:
	{
		return EndDialog(hDlg, 0);
	}

	case WM_PAINT:
	{
		OutputDebugStringA("WM_PAINT called\n");
		//RedrawWindow(hDlg, NULL, NULL, RDW_UPDATENOW);
		TCHAR buf[4096];
		SendMessage(hDlg, WM_PAINT, 0x90, 0);
		if (wParam == 0x90)
		{
			MessageBeep(MB_ICONERROR);
		}
		break;
	}

	return (INT_PTR)TRUE;
	}
	return (INT_PTR)FALSE;
}

return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DLG_TEST), NULL, DlgProc);
*/