#include <iostream>
#include <Windows.h>
#include <tlHelp32.h>
#include <stdio.h>
#include <string>
using namespace std;
int main()
{
	cout << R"(                                                                                                
88  888b      88          88  88888888888  ,ad8888ba,  888888888888  ,ad8888ba,    88888888ba   
88  8888b     88          88  88          d8"'    `"8b      88      d8"'    `"8b   88      "8b  
88  88 `8b    88          88  88         d8'                88     d8'        `8b  88      ,8P  
88  88  `8b   88          88  88aaaaa    88                 88     88          88  88aaaaaa8P'  
88  88   `8b  88          88  88"""""    88                 88     88          88  88""""88'    
88  88    `8b 88          88  88         Y8,                88     Y8,        ,8P  88    `8b    
88  88     `8888  88,   ,d88  88          Y8a.    .a8P      88      Y8a.    .a8P   88     `8b   
88  88      `888   "Y8888P"   88888888888  `"Y8888Y"'       88       `"Y8888Y"'    88      `8b  
                                                                                                
                                                                                                twitter: yafesonofnoah)" << endl;
	int a;
	int pid;
	string address;
	string dlladdress;
	cout << "1.) Hedef Processin PID'si ile devam etmek istiyorsaniz 1 girin." << endl;
	cout << "2.) Hedef Processin Adi ile devam etmek istiyorsaniz 2 girin." << endl;
	cin >> a;

	switch (a) {
	case 1:
	{
		cout << "Processin PID Değerini Giriniz." << endl;
		cin >> pid;
		cout << "Dll Path Addresini Giriniz. " << endl;
		cin >> address;
		cout << "Islem Basarili. " << endl;
		{
			LPCSTR DllPath = address.c_str();
			HANDLE hProcess = OpenProcess(
				PROCESS_ALL_ACCESS,
				FALSE,
				pid);
			LPVOID pDllPath = VirtualAllocEx(
				hProcess,
				0,
				strlen(DllPath) + 1,
				MEM_COMMIT,
				PAGE_READWRITE
			);
			WriteProcessMemory(
				hProcess,
				pDllPath,
				(LPVOID)DllPath,
				strlen(DllPath) + 1,
				0
			);
			HANDLE hLoadThread = CreateRemoteThread(
				hProcess,
				0,
				0,
				(LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleA("Kernel32.dll"),
					"LoadLibraryA"),
				pDllPath,
				0,
				0
			);
			WaitForSingleObject(
				hLoadThread,
				INFINITE
			);
			VirtualFreeEx(
				hProcess,
				pDllPath,
				strlen(DllPath) + 1,
				MEM_RELEASE
			);
		}
		break;
	}
	case 2:
	{

		{
			HANDLE hProcess;
			string address;
			cout << "Hedef Processin Adını Giriniz." << endl;
			cin >> address;
			cout << "Dll Path Addresini Giriniz. " << endl;
			cin >> dlladdress;
			LPSTARTUPINFOA si = new STARTUPINFOA();
			LPPROCESS_INFORMATION pi = new PROCESS_INFORMATION();
			LPCSTR DllPath = address.c_str();
			DWORD dwProcessId = 0;
			//ZeroMemory(&si, sizeof(si));
			//ZeroMemory(&pi, sizeof(pi));
			BOOL bCreateProcess = NULL;
			bCreateProcess = CreateProcessA(
				DllPath,
				NULL,
				NULL,
				NULL,
				FALSE,
				0,
				NULL,
				NULL,
				si,
				pi
			);
			if (bCreateProcess == FALSE)
			{
				cout << " Error - " << GetLastError << endl;
			}
			cout << "Process Olusturma Basarili." << endl;
			//cout << "Process ID -> " << pi->dwProcessId << endl;
			cout << "Process ID ->" << GetProcessId(pi->hProcess) << endl;
			DllPath = dlladdress.c_str();
			hProcess = OpenProcess(
				PROCESS_ALL_ACCESS,
				FALSE,
				pi->dwProcessId
			);
			LPVOID pDllPath = VirtualAllocEx(
				hProcess,
				0,
				strlen(DllPath) + 1,
				MEM_COMMIT,
				PAGE_READWRITE
			);
			WriteProcessMemory(
				hProcess,
				pDllPath,
				(LPVOID)DllPath,
				strlen(DllPath) + 1,
				0
			);
			HANDLE hLoadThread = CreateRemoteThread(
				hProcess,
				0,
				0,
				(LPTHREAD_START_ROUTINE)GetProcAddress(
					GetModuleHandleA("Kernel32.dll"),
					"LoadLibraryA"),
				pDllPath,
				0,
				0
			);
			WaitForSingleObject(
				hLoadThread,
				INFINITE
			);
			VirtualFreeEx(
				hProcess,
				pDllPath,
				strlen(DllPath) + 1,
				MEM_RELEASE);
			CloseHandle(pi->hProcess);
			system("PAUSE");
			return 0;
		}
		break;
	}
	default:
		cout << "1 Veya 2 Gir ";
	}

}