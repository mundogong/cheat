#include "Helper.h"


WCHAR lpPath[MAX_PATH];
DWORD MyThreadID;
HANDLE hMyThread;
HANDLE hProcess;
byte ChangeMonsterByte[5] = { 0x50, 0x83, 0xEC, 0x0C, 0x53 };
byte HookKillByte[6] = { 0x55, 0x8b, 0xec, 0x83, 0xec, 0x40 };
byte HookRecvByte[5] = { 0xB8, 0xC7, 0x00, 0x00, 0x00 };
byte BloodByte[5] = { 0x8B, 0x55, 0x08, 0x50, 0x51 };

void MessageLoop()
{
	MSG msg = { 0 };
	(RegisterHotKey(NULL, 1, 0, VK_HOME));
	(RegisterHotKey(NULL, 1, MOD_CONTROL, VK_F1));
	(RegisterHotKey(NULL, 1, MOD_CONTROL, VK_F2));
	(RegisterHotKey(NULL, 1, MOD_CONTROL, VK_F3));
	(RegisterHotKey(NULL, 1, MOD_CONTROL, VK_F4));
	(RegisterHotKey(NULL, 1, MOD_CONTROL, VK_F5));
	(RegisterHotKey(NULL, 1, MOD_CONTROL, VK_F6));
	(RegisterHotKey(NULL, 1, MOD_ALT, VK_LEFT));
	(RegisterHotKey(NULL, 1, MOD_ALT, VK_RIGHT));
	(RegisterHotKey(NULL, 1, MOD_ALT, VK_UP));
	(RegisterHotKey(NULL, 1, MOD_ALT, VK_DOWN));
	while (GetMessage(&msg, NULL, 0, 0))
	{
		Sleep(100);
		if (WM_HOTKEY == msg.message)
		{
			switch (msg.wParam)
			{
			case 1:
				switch (LOWORD(msg.lParam))
				{
				case 0:
					switch (HIWORD(msg.lParam))
					{
						
					case VK_HOME:
						Notice(L"[ crtl+F1  ]-[  收包自动  ]");
						Notice(L"[ crtl+F2  ]-[  组包选图  ]");
						Notice(L"[ crtl+F3  ]-[  组包回城  ]");
						Notice(L"[ crtl+F4  ]-[  完成已接  ]");
						Notice(L"[   ALT    ]-[  PASS房间  ]");
						break;
					}
					break;
				case MOD_CONTROL:
					switch (HIWORD(msg.lParam))
					{
					case VK_F1:
						RecvAutoPlay();
						break;
					case VK_F2:
						组包选图();
						break;
					case VK_F3:
						组包回城();
						break;
					case VK_F4:
						完成已接();
						break;
					case VK_F5:
						SendRecvIntercept();
						break;
					case VK_F6:
					{
						wchar_t a[20];
						wsprintf(a, L"%d", decodeInt(readInt(人物基址) + 编号偏移));
						Notice(a);
					}
						break;
					}
					break;
				case MOD_ALT:
					switch (HIWORD(msg.lParam))
					{
					case VK_LEFT:
						CoercivePassMap(0);
						break;
					case VK_RIGHT:
						CoercivePassMap(1);
						break;
					case VK_UP:
						CoercivePassMap(2);
						break;
					case VK_DOWN:
						CoercivePassMap(3);
						break;
					}
					break;
				}
			}
		}
	}
}

void InitData() {
	hProcess = GetCurrentProcess();
}

void PrimaryThread()
{
	if (hMyThread == NULL) {
		hMyThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MessageLoop, NULL, 0, &MyThreadID);
	}
}

void InitIniPath() {
	ZeroMemory(lpPath, MAX_PATH);
	SHGetSpecialFolderPathW(0, lpPath, CSIDL_DESKTOPDIRECTORY, 0);
	wcscat_s(lpPath, L"\\辅助.ini");
}

/********************************************call*************************************************/
void Notice(LPCWSTR NoticeContent, int Color) {
	_asm {
		mov ecx, 商店基址
		mov ecx, dword ptr ds : [ecx]
		mov ecx, dword ptr ds : [ecx + 0x50]
		push 0x0
		push 0x0
		push 0x0
		push 0x0
		push 35
		push Color
		push NoticeContent
		call 喇叭公告
	}
}
