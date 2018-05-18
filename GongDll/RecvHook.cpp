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
	_asm jmp RETN�հ�
	jecode :
	__asm leave
	__asm retn 8
}

void RecvAutoPlay() {
	if (RecvAutoOandC == FALSE) {
		Flag = 2;
		RecvInitAutoData();
		RecvAutoOandC = TRUE;
		HookJmp(HOOK�հ�, (int)getPacketHook, 5);
		hRecvAutoThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RecvAutoThread, NULL, 0, &RecvAutoThreadID);
		Notice(L"[ �հ��Զ� ]-[     ��     ]");
	}
	else {
		Flag = -1;
		WaitForSingleObject(hRecvAutoThread, INFINITE);
		CloseHandle(hRecvAutoThread);
		Notice(L"[ �հ��Զ� ]-[     ��     ]"); 
	}
}

DWORD WINAPI RecvAutoThread() {
	while (RecvAutoOandC) {
		Sleep(2000);
		switch (Flag)
		{
		case 1://����ɫ
			RecvDungeon.CountRole--;
			RecvDungeon.CurrentRole++;
			if (RecvDungeon.CountRole <= 0) {
				Notice(L"[Fuckintman]-[  �ر��Զ�  ]");
				Flag = 0;
			}
			else {
				Notice(L"[Fuckintman]-[   ����ɫ   ]");
				Sleep(6000);
				�˳���ɫ();
				Sleep(6000);
				ѡ���ɫ(RecvDungeon.CurrentRole);
				Sleep(6000);
				Flag = 2;
			}
			break;
		case 2://�ɻ�
			if (GetPrivateProfileIntW(L"�Զ�", L"��Ԩģʽ", 0, lpPath) == 1) {
				RecvDungeon.DungeonId = GetPrivateProfileIntW(L"�Զ�", L"��Ԩ��ͼ", 0, lpPath);
			}
			else {
				RecvDungeon.DungeonId = GetDungeonId(readInt(�ȼ���ַ));
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
		case 3://��ͼ
			���ѡͼ();
			Flag = 0;
			break;
		case -1://�˳�
			RestoreHook(HOOK�հ�, HookRecvByte, 5);
			RecvAutoOandC = FALSE;
			Flag = 0;
			break;
		case 4://�س�
			Sleep(1500);
			����س�();
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
	//�հ���ͼ������л�
	if (pHead == 0x18) {
		if (WhetherHaveTried(RecvDungeon.DungeonId) == FALSE) {
			Flag = 1;
		}
		else {
			if (RecvDungeon.DungeonCount == 0 || RecvDungeon.DungeonCount % GetPrivateProfileIntW(L"�Զ�", L"ˢͼ���", 0, lpPath) != 0) {
				���ѡͼ();
			}
		}
		return RecvDungeon.WhetherUi;
	}
	if (pHead == 0x1b) {
		if (RecvDungeon.DungeonId == 7101 || RecvDungeon.DungeonId == 7102 || RecvDungeon.DungeonId == 7103 || RecvDungeon.DungeonId == 7104 || RecvDungeon.DungeonId == 7105 || RecvDungeon.DungeonId == 7106 || RecvDungeon.DungeonId == 7107) {
			�����ͼ(RecvDungeon.DungeonId, 2, RecvDungeon.DungeonDifficulty);
		}
		else if (GetPrivateProfileIntW(L"�Զ�", L"��Ԩģʽ", 0, lpPath) == 1) {
			�����ͼ(RecvDungeon.DungeonId, RecvDungeon.DungeonDifficulty, 0, 1);
		}
		else {
			�����ͼ(RecvDungeon.DungeonId, RecvDungeon.DungeonDifficulty);
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
			��ͼȷ��();
		}
		return RecvDungeon.WhetherUi;
	}
	if (pHead == 0x1d) {
		RecvDungeon.RoleCoordinate.x = readInt(bagPointer + 16) & 0xff;
		RecvDungeon.RoleCoordinate.y = readInt(bagPointer + 17) & 0xff;
		MonsterCount = readInt(bagPointer + 34) & 0xff;
		KillCount = 0;
		if (GetPrivateProfileIntW(L"�Զ�", L"��ȡ����", 0, lpPath) == 1) {
			int gNum = readInt(bagPointer + 35 + 21 * MonsterCount) & 0xff;
			for (int i = 0; i < gNum; i++)
			{
				int BID = readInt(bagPointer + 37 + 21 * MonsterCount + 21 * i);
				���ʰȡ(BID);
			}
		}
		if (RecvDungeon.WhetherUi == TRUE) {
			for (int i = 0; i < MonsterCount; i++)
			{
				int MID = readInt(bagPointer + 41 + 21 * i) & 0xffff;
				�����ɱ(MID);
			}
		}
		return RecvDungeon.WhetherUi;
	}
	if (pHead == 0x26)
	{
		KillCount++;
		if (GetPrivateProfileIntW(L"�Զ�", L"�Զ�ʰȡ", 0, lpPath) == 1) {
			int gNum = readInt(bagPointer + 18) & 0xff;
			for (int i = 0; i < gNum; i++)
			{
				int GID = readInt(bagPointer + 19 + 127 * i);
				���ʰȡ(GID);
			}
		}
		if (KillCount == MonsterCount)
		{
			if (RecvDungeon.RoleCoordinate.x != RecvDungeon.BossCoordinate.x || RecvDungeon.RoleCoordinate.y != RecvDungeon.BossCoordinate.y) {
				if (RecvDungeon.RoleCoordinate.x == RecvDungeon.AbyssCoordinate.x && RecvDungeon.RoleCoordinate.y == RecvDungeon.AbyssCoordinate.y && GetPrivateProfileIntW(L"�Զ�", L"��Ԩģʽ", 0, lpPath) == 1) {
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
			���ͨ��();
		}
		RecvDungeon.DungeonCount++;
		WCHAR text[50];
		wsprintf(text, L"[ ˢͼ%3d��]-[ ƣ�� : %3d ]", RecvDungeon.DungeonCount, decodeInt(���ƣ��) - decodeInt(����ƣ��));
		Notice(text);
		return RecvDungeon.WhetherUi;
	}
	if (pHead == 0x23) {
		if (GetPrivateProfileIntW(L"�Զ�", L"���Ƹ���", 0, lpPath) == 0) {
			����س�();
		}
		else if (GetPrivateProfileIntW(L"�Զ�", L"���Ƹ���", 0, lpPath) == 1) {
			�������();
		}
		else if (GetPrivateProfileIntW(L"�Զ�", L"���Ƹ���", 0, lpPath) == 2) {
			�ƽ���();
		}
		return RecvDungeon.WhetherUi;
	}
	if (pHead == 0x105) {
		����س�();
		return RecvDungeon.WhetherUi;
	}
	if (pHead == 0x3e1) {
		RecvAutoPlay();
		Notice(L"�Բ�,�ɻ��ѱ�����!");
	}
	return 0;
}

void RecvInitAutoData() {
	RecvDungeon.CurrentRole = readInt(readInt(0x04D10450) + 0x154);
	RecvDungeon.CountRole = GetPrivateProfileIntW(L"�Զ�", L"��ɫ����", 0, lpPath);
	RecvDungeon.WhetherUi = GetPrivateProfileIntW(L"�Զ�", L"����UI", 0, lpPath);
}