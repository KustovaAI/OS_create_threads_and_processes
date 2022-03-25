#include <stdio.h>
#include <windows.h>
using namespace std;

void main() 
{	
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));

	LPCTSTR lpApplicationName = "C:/Windows/notepad.exe";
	LPTSTR lpCommandLine = NULL;							// ��������� ������
	LPSECURITY_ATTRIBUTES lpProcessAttributes = NULL;		// SD (���������� ������������
	LPSECURITY_ATTRIBUTES lpThreadAttributes = NULL;		// SD
	BOOL bInheritHandles = false;							// ���������� ��������� ������������
	DWORD dwCreationFlags = 0;								// ������ ��������
	LPVOID lpEnvironment = NULL;							// ����� ���� ������������
	LPCTSTR lpCurrentDirectory = NULL;						// ��� �������� ��������
	LPSTARTUPINFO lpStartupInfo = &si;						// ���������� �������������
	LPPROCESS_INFORMATION lpProcessInformation = &pi;		// ���������� � ��������

	
	if (!CreateProcess(lpApplicationName, lpCommandLine, lpProcessAttributes, lpThreadAttributes, bInheritHandles,
						dwCreationFlags, lpEnvironment, lpCurrentDirectory, lpStartupInfo, lpProcessInformation))
			throw ("CreateProcess failed.");
	// ����� �� ��� ���, ���� �������� ������� �� ������ �� ������.
	WaitForSingleObject(pi.hProcess, INFINITE);
	// ������� ����������� �������� � ������.
	if (CloseHandle(pi.hProcess) == 0) throw ("Error CloseHandle");
	if (CloseHandle(pi.hThread) == 0) throw ("Error CloseHandle");
}