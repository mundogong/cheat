#include "helper.h"
void CoercivePassMap(int direction) {
	_asm
	{
		mov ecx, �̵��ַ
		sub ecx, 8
		mov ecx, dword ptr ds : [ecx]
		mov ecx, dword ptr ds : [ecx + 0x20A028]
		mov ecx, dword ptr ds : [ecx + 0x8C]
		push - 0x1
		push - 0x1
		push 0x0
		push 0x0
		push 0x0
		push 0x0
		push 0x0
		push direction
		mov eax, ��ͼCALL
		call eax
	}
}

void CoordinateCall(int personaddress, int x, int y, int z) {
	_asm {
		mov esi, personaddress
		mov eax, [esi]
		mov edi, eax
		mov eax, [eax + 0xcc]
		mov ecx, esi
		call eax
		mov eax, z
		mov ecx, y
		mov edx, x
		push eax
		push ecx
		push edx
		mov eax, [edi + 0xa8]
		mov ecx, esi
		call eax
	}
}

void CoordinatePassMap(int direction) {
	int һ��ƫ��, ����ƫ��, ��ʱ����, ����ṹ, x, y, xF, yF, cx, cy;
	һ��ƫ�� = readInt(�����ַ);
	����ƫ�� = readInt(һ��ƫ�� + 184);
	��ʱ���� = readInt(�̵��ַ - 8);
	��ʱ���� = readInt(��ʱ���� + 0x20A028);
	��ʱ���� = readInt(��ʱ���� + 140);
	����ṹ = ��ʱ���� + (direction + direction * 8) * 4 + 5200;
	x = readInt(����ṹ + 0);
	y = readInt(����ṹ + 4);
	xF = readInt(����ṹ + 8);
	yF = readInt(����ṹ + 12);
	if (direction == 0) {
		cx = x + xF + 20;
		cy = y + yF / 2;
	}
	if (direction == 1) {
		cx = x - 20;
		cy = y + yF / 2;
	}
	if (direction == 2) {
		cx = x + xF / 2;
		cy = y + yF + 20;
	}
	if (direction == 3) {
		cx = x + xF / 2;
		cy = y - 20;
	}
	CoordinateCall(һ��ƫ��, cx, cy, 0);
	Sleep(150);
	CoordinateCall(һ��ƫ��, x + xF / 2, y, 0);
}
