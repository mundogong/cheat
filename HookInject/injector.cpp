#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>

DWORD GetProcessIDFromName(LPCWSTR szName);
DWORD GetMainThreadIdFromName(LPCWSTR szName);

typedef bool (CALLBACK* LPFNDLLFUNC1)(DWORD);

HINSTANCE hDLL;               // Handle to DLL  
LPFNDLLFUNC1 lpfnDllFunc1;    // Function pointer  
DWORD dwParam1;
bool  uReturnVal;

const wchar_t * ProcessName = L"notepad++.exe";

int main() {
	printf("%d", GetProcessIDFromName(ProcessName));
	hDLL = LoadLibrary(L"GongWg.dll");
	if (hDLL != NULL)
	{
		lpfnDllFunc1 = (LPFNDLLFUNC1)GetProcAddress(hDLL, "sethook");
		if (!lpfnDllFunc1)
		{
			// handle the error  
			FreeLibrary(hDLL);
		}
		else
		{
			// call the function  
			uReturnVal = lpfnDllFunc1(GetMainThreadIdFromName(ProcessName));
		}
	}
	return 0;
}

// �ɽ�������ȡ����ID(��Ҫͷ�ļ�tlhelp32.h)
// ʧ�ܷ���0
DWORD GetProcessIDFromName(LPCWSTR szName)
{
	DWORD id = 0;       // ����ID
	PROCESSENTRY32 pe;  // ������Ϣ
	pe.dwSize = sizeof(PROCESSENTRY32);
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); // ��ȡϵͳ�����б�
	if (Process32First(hSnapshot, &pe))      // ����ϵͳ�е�һ�����̵���Ϣ
	{
		do
		{
			if (0 == lstrcmpW(pe.szExeFile, szName)) // �����ִ�Сд�Ƚ�
			{
				id = pe.th32ProcessID;
				break;
			}
		} while (Process32Next(hSnapshot, &pe));      // ��һ������
	}
	CloseHandle(hSnapshot);     // ɾ������
	return id;
}

// �ɽ�������ȡ���߳�ID(��Ҫͷ�ļ�tlhelp32.h)
// ʧ�ܷ���0
DWORD GetMainThreadIdFromName(LPCWSTR szName)
{
	DWORD idThread = 0;         // ����ID
	DWORD idProcess = 0;        // ���߳�ID

								// ��ȡ����ID
	PROCESSENTRY32 pe;      // ������Ϣ
	pe.dwSize = sizeof(PROCESSENTRY32);
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); // ��ȡϵͳ�����б�
	if (Process32First(hSnapshot, &pe))      // ����ϵͳ�е�һ�����̵���Ϣ
	{
		do
		{
			if (0 == lstrcmpW(pe.szExeFile, szName)) // �����ִ�Сд�Ƚ�
			{
				idProcess = pe.th32ProcessID;
				break;
			}
		} while (Process32Next(hSnapshot, &pe));      // ��һ������
	}
	CloseHandle(hSnapshot); // ɾ������
	if (idProcess == 0)
	{
		return 0;
	}

	// ��ȡ���̵����߳�ID
	THREADENTRY32 te;       // �߳���Ϣ
	te.dwSize = sizeof(THREADENTRY32);
	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0); // ϵͳ�����߳̿���
	if (Thread32First(hSnapshot, &te))       // ��һ���߳�
	{
		do
		{
			if (idProcess == te.th32OwnerProcessID)      // ��Ϊ�ҵ��ĵ�һ���ý��̵��߳�Ϊ���߳�
			{
				idThread = te.th32ThreadID;
				break;
			}
		} while (Thread32Next(hSnapshot, &te));           // ��һ���߳�
	}
	CloseHandle(hSnapshot); // ɾ������
	return idThread;
}
