// dllmain.cpp : ���� DLL Ӧ�ó������ڵ㡣
#include<Windows.h>
#include "Helper.h"
#include"HideDLL.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		Hide(hModule);
		Notice(L"[ ע��ɹ�  ]-[  HOME����  ]");
		InitData();
		InitIniPath();
		PrimaryThread();
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

