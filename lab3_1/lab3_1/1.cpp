#include <stdio.h>
#include <windows.h>
using namespace std;

void main() 
{	
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));

	LPCTSTR lpApplicationName = "C:/Windows/notepad.exe";
	LPTSTR lpCommandLine = NULL;							// командная строка
	LPSECURITY_ATTRIBUTES lpProcessAttributes = NULL;		// SD (дескриптор безопасности
	LPSECURITY_ATTRIBUTES lpThreadAttributes = NULL;		// SD
	BOOL bInheritHandles = false;							// дескриптор параметра наследования
	DWORD dwCreationFlags = 0;								// флажки создания
	LPVOID lpEnvironment = NULL;							// новый блок конфигурации
	LPCTSTR lpCurrentDirectory = NULL;						// имя текущего каталога
	LPSTARTUPINFO lpStartupInfo = &si;						// информация предустановки
	LPPROCESS_INFORMATION lpProcessInformation = &pi;		// информация о процессе

	
	if (!CreateProcess(lpApplicationName, lpCommandLine, lpProcessAttributes, lpThreadAttributes, bInheritHandles,
						dwCreationFlags, lpEnvironment, lpCurrentDirectory, lpStartupInfo, lpProcessInformation))
			throw ("CreateProcess failed.");
	// Ждать до тех пор, пока дочерний процесс не выйдет из работы.
	WaitForSingleObject(pi.hProcess, INFINITE);
	// Закроем дескрипторы процесса и потока.
	if (CloseHandle(pi.hProcess) == 0) throw ("Error CloseHandle");
	if (CloseHandle(pi.hThread) == 0) throw ("Error CloseHandle");
}