// TestNoCRT.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include <windows.h>


DWORD WINAPI AppStart()
{


	LPTOP_LEVEL_EXCEPTION_FILTER DefaultFilter = SetUnhandledExceptionFilter(NULL);


	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	return AppStart();
}


