#include"Helper.h"

BOOL RecvAutoOandC = FALSE;
DWORD RecvAutoThreadID;
HANDLE hRecvAutoThread;

dungeon RecvDungeon;
int MonsterCount = 0;
int KillCount = 0;
int Flag = 0;

void RecvInitAutoData();
DWORD WINAPI RecvAutoThread();
int getPacketData();

__declspec(naked) void getPacketHook() {
	_asm pushad
	_asm pushfd
	getPacketData();
	_asm cmp eax, 1
	_asm je jecode
	_asm popfd
	_asm popad
	_asm mov eax, 0xc7
	_asm jmp RETN收包
	jecode :
	__asm leave
	__asm retn 8
}

void RecvAutoPlay() {
	if (RecvAutoOandC == FALSE) {
		Flag = 2;
		RecvInitAutoData();
		RecvAutoOandC = TRUE;
		HookJmp(HOOK收包, (int)getPacketHook, 5);
		hRecvAutoThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RecvAutoThread, NULL, 0, &RecvAutoThreadID);
		Notice(L"[ 收包自动 ]-[     开     ]");
	}
	else {
		Flag = -1;
		WaitForSingleObject(hRecvAutoThread, INFINITE);
		CloseHandle(hRecvAutoThread);
		Notice(L"[ 收包自动 ]-[     关     ]"); 
	}
}

DWORD WINAPI RecvAutoThread() {
	while (RecvAutoOandC) {
		Sleep(2000);
		switch (Flag)
		{
		case 1://换角色
			RecvDungeon.CountRole--;
			RecvDungeon.CurrentRole++;
			if (RecvDungeon.CountRole <= 0) {
				Notice(L"[Fuckintman]-[  关闭自动  ]");
				Flag = 0;
			}
			else {
				Notice(L"[Fuckintman]-[   换角色   ]");
				Sleep(6000);
				退出角色();
				Sleep(6000);
				选择角色(RecvDungeon.CurrentRole);
				Sleep(6000);
				Flag = 2;
			}
			break;
		case 2://飞机
			if (GetPrivateProfileIntW(L"自动", L"深渊模式", 0, lpPath) == 1) {
				RecvDungeon.DungeonId = GetPrivateProfileIntW(L"自动", L"深渊地图", 0, lpPath);
			}
			else {
				RecvDungeon.DungeonId = GetDungeonId(readInt(等级基址));
			}
			RecvDungeon.DungeonDifficulty = GetDungeonMaxDifficulty(RecvDungeon.DungeonId);
			if (WhetherHaveTried(RecvDungeon.DungeonId) == FALSE) {
				Flag = 1;
			}
			else {
				GetPlaneRoute(RecvDungeon.DungeonId);
				Flag = 0;
			}
			break;
		case 3://进图
			组包选图();
			Flag = 0;
			break;
		case -1://退出
			RestoreHook(HOOK收包, HookRecvByte, 5);
			RecvAutoOandC = FALSE;
			Flag = 0;
			break;
		case 4://回城
			Sleep(1500);
			组包回城();
			Flag = 0;
			break;

		default:
			Flag = 0;
			break;
		}
	}
	return 0;
}

int getPacketData() {
	int bagPointer;
	_asm mov bagPointer, ebx;
	int pHead = readInt(bagPointer + 1) & 0xffff;
	int pLength = readInt(bagPointer + 3);
	//收包：图外界面切换
	if (pHead == 0x18) {
		if (WhetherHaveTried(RecvDungeon.DungeonId) == FALSE) {
			Flag = 1;
		}
		else {
			if (RecvDungeon.DungeonCount == 0 || RecvDungeon.DungeonCount % GetPrivateProfileIntW(L"自动", L"刷图间隔", 0, lpPath) != 0) {
				组包选图();
			}
		}
		return RecvDungeon.WhetherUi;
	}
	if (pHead == 0x1b) {
		if (RecvDungeon.DungeonId == 7101 || RecvDungeon.DungeonId == 7102 || RecvDungeon.DungeonId == 7103 || RecvDungeon.DungeonId == 7104 || RecvDungeon.DungeonId == 7105 || RecvDungeon.DungeonId == 7106 || RecvDungeon.DungeonId == 7107) {
			组包进图(RecvDungeon.DungeonId, 2, RecvDungeon.DungeonDifficulty);
		}
		else if (GetPrivateProfileIntW(L"自动", L"深渊模式", 0, lpPath) == 1) {
			组包进图(RecvDungeon.DungeonId, RecvDungeon.DungeonDifficulty, 0, 1);
		}
		else {
			组包进图(RecvDungeon.DungeonId, RecvDungeon.DungeonDifficulty);
		}
		return RecvDungeon.WhetherUi;
	}
	if (pHead == 0x1c)
	{
		RecvDungeon.BossCoordinate.x = readInt(bagPointer + 24) & 0xff;
		RecvDungeon.BossCoordinate.y = readInt(bagPointer + 25) & 0xff;
		RecvDungeon.AbyssCoordinate.x = readInt(bagPointer + 26) & 0xff;
		RecvDungeon.AbyssCoordinate.y = readInt(bagPointer + 27) & 0xff;
		if (RecvDungeon.WhetherUi == TRUE) {
			进图确认();
		}
		return RecvDungeon.WhetherUi;
	}
	if (pHead == 0x1d) {
		RecvDungeon.RoleCoordinate.x = readInt(bagPointer + 16) & 0xff;
		RecvDungeon.RoleCoordinate.y = readInt(bagPointer + 17) & 0xff;
		MonsterCount = readInt(bagPointer + 34) & 0xff;
		KillCount = 0;
		if (GetPrivateProfileIntW(L"自动", L"提取建筑", 0, lpPath) == 1) {
			int gNum = readInt(bagPointer + 35 + 21 * MonsterCount) & 0xff;
			for (int i = 0; i < gNum; i++)
			{
				int BID = readInt(bagPointer + 37 + 21 * MonsterCount + 21 * i);
				组包拾取(BID);
			}
		}
		if (RecvDungeon.WhetherUi == TRUE) {
			for (int i = 0; i < MonsterCount; i++)
			{
				int MID = readInt(bagPointer + 41 + 21 * i) & 0xffff;
				组包秒杀(MID);
			}
		}
		return RecvDungeon.WhetherUi;
	}
	if (pHead == 0x26)
	{
		KillCount++;
		if (GetPrivateProfileIntW(L"自动", L"自动拾取", 0, lpPath) == 1) {
			int gNum = readInt(bagPointer + 18) & 0xff;
			for (int i = 0; i < gNum; i++)
			{
				int GID = readInt(bagPointer + 19 + 127 * i);
				组包拾取(GID);
			}
		}
		if (KillCount == MonsterCount)
		{
			if (RecvDungeon.RoleCoordinate.x != RecvDungeon.BossCoordinate.x || RecvDungeon.RoleCoordinate.y != RecvDungeon.BossCoordinate.y) {
				if (RecvDungeon.RoleCoordinate.x == RecvDungeon.AbyssCoordinate.x && RecvDungeon.RoleCoordinate.y == RecvDungeon.AbyssCoordinate.y && GetPrivateProfileIntW(L"自动", L"深渊模式", 0, lpPath) == 1) {
					Flag = 4;
				}
				else {
					GotoNextRoom(RecvDungeon.DungeonId, RecvDungeon.RoleCoordinate);
				}
			}
		}
		return RecvDungeon.WhetherUi;
	}
	if (pHead == 0x1f) {
		if (RecvDungeon.WhetherUi == TRUE) {
			组包通关();
		}
		RecvDungeon.DungeonCount++;
		WCHAR text[50];
		wsprintf(text, L"[ 刷图%3d次]-[ 疲劳 : %3d ]", RecvDungeon.DungeonCount, decodeInt(最大疲劳) - decodeInt(已用疲劳));
		Notice(text);
		return RecvDungeon.WhetherUi;
	}
	if (pHead == 0x23) {
		if (GetPrivateProfileIntW(L"自动", L"翻牌个数", 0, lpPath) == 0) {
			组包回城();
		}
		else if (GetPrivateProfileIntW(L"自动", L"翻牌个数", 0, lpPath) == 1) {
			组包翻牌();
		}
		else if (GetPrivateProfileIntW(L"自动", L"翻牌个数", 0, lpPath) == 2) {
			黄金翻牌();
		}
		return RecvDungeon.WhetherUi;
	}
	if (pHead == 0x105) {
		组包回城();
		return RecvDungeon.WhetherUi;
	}
	if (pHead == 0x3e1) {
		RecvAutoPlay();
		Notice(L"卧槽,飞机已被击毁!");
	}
	return 0;
}

void RecvInitAutoData() {
	RecvDungeon.CurrentRole = readInt(readInt(0x04D10450) + 0x154);
	RecvDungeon.CountRole = GetPrivateProfileIntW(L"自动", L"角色个数", 0, lpPath);
	RecvDungeon.WhetherUi = GetPrivateProfileIntW(L"自动", L"屏蔽UI", 0, lpPath);
}