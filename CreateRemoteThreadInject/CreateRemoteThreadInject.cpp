#include <Windows.h>
#include <tlhelp32.h>
#include <stdio.h>
#include "shlobj.h"

DWORD GetProcessIDFromName(LPCWSTR szName);

DWORD ProcessId;
HANDLE hProcess;
HMODULE KernelHandle;
LPTHREAD_START_ROUTINE LodalibraryAddr;
HANDLE hThread;
void * DllNameMemory;
WCHAR szLibPath[MAX_PATH];

int main()
{
	ZeroMemory(szLibPath, MAX_PATH);
	SHGetSpecialFolderPathW(0, szLibPath, CSIDL_DESKTOPDIRECTORY, 0);
	wcscat_s(szLibPath, L"\\GongDll.dll");

	ProcessId = GetProcessIDFromName(L"DNF.exe");
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessId);
	if (hProcess == NULL) {
		printf("打开进程失败\n");
		return 1;
	}
	KernelHandle = GetModuleHandle(L"Kernel32"); //因为kernel32 每一个windows程序进程空间中都有 所以让他调用LOADLIBRARY不成问题
	if (KernelHandle == NULL) {
		printf("获取KernelHandle失败\n");
		return 1;
	}
	DllNameMemory = VirtualAllocEx(hProcess, 0, sizeof(szLibPath) + 1, 4096, 4);
	if (DllNameMemory == NULL) {
		printf("申请内存失败\n");
		return 1;
	}
	if (!WriteProcessMemory(hProcess, DllNameMemory, szLibPath, sizeof(szLibPath) + 1, 0)) {
		printf("写内存失败\n");
		return 1;
	}
	LodalibraryAddr = (LPTHREAD_START_ROUTINE)GetProcAddress(KernelHandle, "LoadLibraryW");
	if (LodalibraryAddr == 0) {
		printf("获取loadlibrary地址失败\n");
		return 1;
	}
	hThread = CreateRemoteThread(hProcess, NULL, 0, LodalibraryAddr, DllNameMemory, 0, NULL);
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	VirtualFree(DllNameMemory, sizeof(szLibPath) + 1, 4096);
	CloseHandle(hProcess);
	printf("注入完成，可以关闭\n");
    return 0;
}

// 由进程名获取进程ID(需要头文件tlhelp32.h)
// 失败返回0
DWORD GetProcessIDFromName(LPCWSTR szName)
{
	DWORD id = 0;       // 进程ID
	PROCESSENTRY32W pe;  // 进程信息
	pe.dwSize = sizeof(PROCESSENTRY32);
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); // 获取系统进程列表
	if (Process32FirstW(hSnapshot, &pe))      // 返回系统中第一个进程的信息
	{
		do
		{
			if (0 == lstrcmpiW(pe.szExeFile, szName)) // 不区分大小写比较
			{
				id = pe.th32ProcessID;
				break;
			}
		} while (Process32NextW(hSnapshot, &pe));      // 下一个进程
	}
	CloseHandle(hSnapshot);     // 删除快照
	return id;
}