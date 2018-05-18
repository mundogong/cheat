// dllmain.cpp : 定义 DLL 应用程序的入口点。
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
		Notice(L"[ 注入成功  ]-[  HOME呼出  ]");
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

