#include"Helper.h"

void HookJmp(int base, int Hook, int HookByteNum) {
	byte * Jmp = new byte(HookByteNum);
	memset(Jmp, 0x90, HookByteNum);
	*(byte *)Jmp = 0xe9;
	*(int *)(Jmp + 1) = Hook - base - 5;
	write(base, Jmp, HookByteNum);
}

void HookCall(int base, int Hook, int HookByteNum) {
	byte * Call = new byte(HookByteNum);
	memset(Call, 0x90, HookByteNum);
	*(byte *)Call = 0xe8;
	*(int *)(Call + 1) = Hook - base - 5;
	write(base, Call, HookByteNum);
}

void RestoreHook(int base, byte *RestoreByte, int RestoreByteNum) {
	write(base, RestoreByte, RestoreByteNum);
}