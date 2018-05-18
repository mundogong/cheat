#include "helper.h"


int readInt(int address) {
	int temp = 0;
	ReadProcessMemory(hProcess, (LPCVOID)address, &temp, 4, 0);
	return temp;
}

void writeInt(int address, int temp) {
	WriteProcessMemory(hProcess, (LPVOID)address, &temp, 4, 0);
}

void read(int address, byte * temp, int count) {
	ReadProcessMemory(hProcess, (LPCVOID)address, temp, count, 0);
}

void write(int address, byte * temp, int count) {
	WriteProcessMemory(hProcess, (LPVOID)address, temp, count, 0);
}

float readDecimal(int address) {
	float temp;
	ReadProcessMemory(hProcess, (LPCVOID)address, &temp, 4, 0);
	return temp;
}

void writeDecimal(int address, float value) {
	WriteProcessMemory(hProcess, (LPVOID)address, &value, 4, 0);
}

LPVOID applyMemory(int count, DWORD protect, DWORD type) {
	return VirtualAllocEx(hProcess, NULL, count, type, protect);
}

void freeMemory(LPVOID address, DWORD Size, DWORD type) {
	VirtualFreeEx(hProcess, address, Size, type);
}

void readWchar(int address, LPVOID temp, int count) {
	int tempCount = 0;
	wchar_t tempWchar = L'\0';
	while (true)
	{
		wchar_t tempWchar = WORD(readInt(address + tempCount * 2));
		*((WORD *)temp + tempCount) = tempWchar;
		tempCount++;
		if (tempWchar == L'\0' || tempCount == count - 1) {
			*((WORD *)temp + tempCount) = L'\0';
			break;
		}
	}
}

int decodeInt(int address) {
	int eax, esi, edx;
	eax = readInt(address);
	esi = readInt(解密基址);
	edx = eax;
	edx >>= 16;
	edx = readInt(esi + edx * 4 + 36);
	eax = eax & 0xffff;
	eax = readInt(edx + eax * 4 + 8468);
	edx = WORD(eax);
	esi = edx;
	esi <<= 16;
	esi = esi ^ edx;
	edx = readInt(address + 4);
	eax = esi ^ edx;
	return eax;
}

void encryptInt(int address, int value) {
	int ecx, eax, esi, edx, si;
	eax = readInt(加密基址);
	eax = eax + 1;
	writeInt(加密基址, eax);
	edx = (eax >> 8) & 255;
	ecx = readInt(edx * 2 + 加密参数一) & 65535;
	eax = eax & 255;
	eax = readInt(eax * 2 + 加密参数二) & 65535;
	eax = (ecx ^ eax) & 65535;
	si = address & 15;

	if (si == 0)
	{
		ecx = value >> 16;
		ecx = ecx - eax;
		ecx = ecx + (value & 65535);
	}
	else if (si == 4)
	{
		ecx = value & 65535;
		ecx = ecx - (value >> 16);
	}
	else if (si == 8)
	{
		ecx = value >> 16;
		ecx = ecx * (value & 65535);
	}
	else if (si == 12)
	{
		ecx = value >> 16;
		ecx = ecx + (value & 65535);
		ecx = ecx + eax;
	}
	else {
		ecx = value >> 16;
		ecx = ecx + (value & 65535);
	}

	esi = (ecx ^ eax) & 65535;
	ecx = eax;
	eax = (eax << 16) | ecx;
	eax = (eax^ value);
	writeInt(address + 4, eax);
	eax = readInt(address);
	edx = esi << 16;
	esi = readInt(解密基址);
	edx = edx | ecx;
	ecx = eax >> 16;
	ecx = readInt(esi + ecx * 4 + 36);
	eax = eax & 65535;
	writeInt(ecx + eax * 4 + 8468, edx);
}

float decodeDecimal(int address) {
	int tempInt = decodeInt(address);
	float tempFloat;
	memcpy(&tempFloat, &tempInt, 4);
	return tempFloat;
}

void encryptDecimal(int address, float value) {
	int tempInt;
	memcpy(&tempInt, &value, 4);
	encryptInt(address, tempInt);
}

std::vector<int> SearchConditioncode(std::vector<byte> Conditioncode) {
	unsigned long SearchBegin = 0x400000;
	unsigned long SearchEnd = 0x7fffffff;
	int tempcount = 0;
	BYTE * Conditioncode_array = new BYTE[Conditioncode.size()];
	memset(Conditioncode_array, 0, Conditioncode.size());
	for (unsigned int i = 0; i < Conditioncode.size(); i++) {
		Conditioncode_array[i] = Conditioncode[i];
	}
	int Conditioncode_num = Conditioncode.size();
	unsigned int i, j;
	std::vector<int> temp;
	MEMORY_BASIC_INFORMATION mbInfo = { 0 };
	const SIZE_T BaseInfoLen = sizeof(MEMORY_BASIC_INFORMATION);
	BYTE *lpBuf = new BYTE[1];
	DWORD dwBufSize = 1;

	for (i = SearchBegin; i < SearchEnd;) {
		VirtualQueryEx(hProcess, (LPCVOID)i, &mbInfo, BaseInfoLen);
		if (lpBuf != NULL) {
			delete[] lpBuf;
			lpBuf = NULL;
		}
		if ((mbInfo.State == MEM_COMMIT) && (mbInfo.Protect == PAGE_EXECUTE_READ || mbInfo.Protect == PAGE_READWRITE) && (mbInfo.Type == MEM_PRIVATE)) {
			dwBufSize = mbInfo.RegionSize;
			lpBuf = new BYTE[dwBufSize];
			if (ReadProcessMemory(hProcess, (LPCVOID)i, lpBuf, dwBufSize, 0)) {
				for (j = 0; j <= mbInfo.RegionSize - Conditioncode_num; j++) {
					for (int k = 0; k < Conditioncode_num; k++) {
						if (lpBuf[j + k] != Conditioncode_array[k]) {
							goto s;
						}
					}
					temp.push_back(i + j);
				s:;
				}
			}
		}
		i = (int)mbInfo.BaseAddress + mbInfo.RegionSize;
	}
	if (lpBuf != NULL) {
		delete[] lpBuf;
		lpBuf = NULL;
	}
	delete[]Conditioncode_array;
	return temp;
}

MemoryInfo readAddrInfo(int noAddress) {
	MemoryInfo temp;
	temp.Value = noAddress;
	temp.Integer = readInt(noAddress);
	temp.Decimal = readDecimal(noAddress);
	temp.DecodeInteger = decodeInt(noAddress);
	temp.DecodeDecimal = decodeDecimal(noAddress);
	readWchar(noAddress, temp.Unicode, 20);
	return temp;
}

std::vector<MemoryInfo> traverseMemory() {
	std::vector<MemoryInfo> myaddrInfomation;
	int addrAndoffset[8];
	WCHAR num[10];

	GetPrivateProfileStringW(L"Memory", L"address", L"-1", num, 10, lpPath);
	swscanf_s(num, L"%x", &addrAndoffset[0]);

	GetPrivateProfileStringW(L"Memory", L"oneLevel", L"-1", num, 10, lpPath);
	swscanf_s(num, L"%x", &addrAndoffset[1]);

	GetPrivateProfileStringW(L"Memory", L"twoLevel", L"-1", num, 10, lpPath);
	swscanf_s(num, L"%x", &addrAndoffset[2]);

	GetPrivateProfileStringW(L"Memory", L"threeLevel", L"-1", num, 10, lpPath);
	swscanf_s(num, L"%x", &addrAndoffset[3]);

	GetPrivateProfileStringW(L"Memory", L"fourLevel", L"-1", num, 10, lpPath);
	swscanf_s(num, L"%x", &addrAndoffset[4]);

	GetPrivateProfileStringW(L"Memory", L"fiveLevel", L"-1", num, 10, lpPath);
	swscanf_s(num, L"%x", &addrAndoffset[5]);

	GetPrivateProfileStringW(L"Memory", L"sixLevel", L"-1", num, 10, lpPath);
	swscanf_s(num, L"%x", &addrAndoffset[6]);

	addrAndoffset[7] = -1;

	int Time = 0, Size = 0, index = 0;

	GetPrivateProfileStringW(L"Memory", L"Time", L"-1", num, 10, lpPath);
	swscanf_s(num, L"%x", &Time);

	GetPrivateProfileStringW(L"Memory", L"Size", L"-1", num, 10, lpPath);
	swscanf_s(num, L"%x", &Size);

	index = GetPrivateProfileIntW(L"Memory", L"index", 0, lpPath);

	int * tempAddr = new int[Time];

	std::fill(tempAddr, tempAddr + Time, addrAndoffset[0]);
	MemoryInfo tempaddrInfomation;
	for (int i = 1; i < 8; i++) {
		switch (addrAndoffset[i])
		{
		case -1:
			for (int j = 0; j < Time; j++) {
				tempaddrInfomation = readAddrInfo(tempAddr[j]);
				myaddrInfomation.push_back(tempaddrInfomation);
			}
			delete[]tempAddr;
			return myaddrInfomation;
			break;
		default:
			if (i == index) {
				for (int j = 0; j < Time; j++) {
					tempAddr[j] = readInt(tempAddr[j]) + addrAndoffset[i] + j * Size;
				}
			}
			else {
				for (int j = 0; j < Time; j++) {
					tempAddr[j] = readInt(tempAddr[j]) + addrAndoffset[i];
				}
			}
			break;
		}
	}
	return myaddrInfomation;
}