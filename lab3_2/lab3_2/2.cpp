#include <stdio.h>
#include <process.h>
#include <windows.h>
using namespace std;

volatile long int Var = 0; 

DWORD WINAPI ThreadProc1(LPVOID lpParameter)
{
	int i;
	for (i = 0; i < 100000000; i++)
	{
		*(int*)lpParameter = *(int*)lpParameter + 10;
	}
	ExitThread(0);
}
DWORD WINAPI ThreadProc2(LPVOID lpParameter)
{
	int i;	
	for (i = 0; i < 100000000; i++)
	{
		*(int*)lpParameter = *(int*)lpParameter - 10;
	}
	ExitThread(0);
}
void main()
{
	HANDLE h[20];
	int i;
	printf("Initial value Var = %d\n", Var);
	printf("Laynch childs\n");
	for (i = 0; i < 10; i++)
	{
		h[i] = CreateThread(NULL, 0, ThreadProc1, (LPVOID)&Var, 0, NULL);
		if (h[i] == NULL)  printf("CreateThread failed.");			
	}
	for (i = 10; i < 20; i++)
	{
		h[i] = CreateThread(NULL, 0, ThreadProc2, (LPVOID)&Var, 0, NULL);
		if (h[i] == NULL)  printf("CreateThread failed.");
	}	
	for (i = 0; i < 20; i++)
	{
		WaitForSingleObject(h[i], INFINITE);
		if (CloseHandle(h[i]) == 0) printf("Error closeHandle");
	}
	printf("Var = %d", Var);
	
	getchar();
}
