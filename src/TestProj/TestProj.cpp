// TestProj.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "TestProj.h"


template<class T>
class CTask
{
public:
	CTask()
	{
		printf("This is a normal template.\n");
	}

private:
	T m_task;
};

template<class T>
class CTask<T*>
{
public:
	CTask()
	{
		printf("This is a pointer template.\n");
	}

private:
	T *m_task;
};


int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	AllocConsole();

	CTask<int> t1;
	CTask<int*> t2;

	return 0;
}