#include "helper.h"
void CoercivePassMap(int direction) {
	_asm
	{
		mov ecx, 商店基址
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
		mov eax, 过图CALL
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
	int 一级偏移, 二级偏移, 临时数据, 坐标结构, x, y, xF, yF, cx, cy;
	一级偏移 = readInt(人物基址);
	二级偏移 = readInt(一级偏移 + 184);
	临时数据 = readInt(商店基址 - 8);
	临时数据 = readInt(临时数据 + 0x20A028);
	临时数据 = readInt(临时数据 + 140);
	坐标结构 = 临时数据 + (direction + direction * 8) * 4 + 5200;
	x = readInt(坐标结构 + 0);
	y = readInt(坐标结构 + 4);
	xF = readInt(坐标结构 + 8);
	yF = readInt(坐标结构 + 12);
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
	CoordinateCall(一级偏移, cx, cy, 0);
	Sleep(150);
	CoordinateCall(一级偏移, x + xF / 2, y, 0);
}
