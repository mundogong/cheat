// wg.cpp : ���� DLL Ӧ�ó���ĵ���������
//
#include<Windows.h>

HHOOK hook = NULL;

extern "C" _declspec(dllexport) LRESULT CALLBACK keyboardProc(int code, WPARAM wParam, LPARAM lParam) {
	if ((lParam &(1 << 31)) == 0) {
		switch (wParam)
		{
		case VK_HOME:
			MessageBoxW(NULL, L"1", L"1", MB_OK);
			UnhookWindowsHookEx(hook);
			break;
		}
	}
	return CallNextHookEx(hook, code, wParam, lParam);
}

extern "C" _declspec(dllexport)bool sethook(DWORD ThreadID) {
	hook = SetWindowsHookEx(WH_KEYBOARD,(HOOKPROC)keyboardProc, GetModuleHandle(L"GongWg.dll"), ThreadID);
	if(!hook){
		MessageBox(NULL,TEXT("HOOKʧ�ܣ�"),TEXT("error"),MB_OK);
		return false;
	}
	else {
		MessageBox(NULL, TEXT("HOOK�ɹ���"), TEXT("OK"), MB_OK);
		return true;
	}
}
