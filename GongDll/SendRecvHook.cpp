#include"Helper.h"

int head = 0;
int param = 0;
int callfrom = 0;
int count = 0;
BOOL WhetherIntercept = FALSE;
BOOL SendOandC = FALSE;

int buffer = 缓冲CALL;
int bufferreturn = 缓冲CALL + 5;
byte BufferHookByte[5] = { 0x55, 0x8B, 0xEC, 0x6A, 0xFF };

int encrypt1 = 加密包CALL;
int encrypt2 = encrypt1 + 0x30;
int encrypt3 = encrypt1 + 0x60;
int encrypt4 = encrypt1 + 0x90;
int encryptreturn1 = encrypt1 + 7;
int encryptreturn2 = encrypt2 + 7;
int encryptreturn3 = encrypt3 + 7;
int encryptreturn4 = encrypt4 + 7;
byte EncryptHookByte[7] = { 0x55, 0x8b, 0xec, 0x80, 0x79, 0x08, 0x00 };

int sendpacket = 发包CALL;
int sendpacketreturn = 发包CALL + 8;
byte SendHookByte[8] = { 0x55, 0x8B, 0xEC, 0xB8, 0x50, 0x00, 0x04, 0x00 };

int recvpacket = HOOK收包 - 11;
int recvreturn = recvpacket + 7;
byte RecvHookByte[7] = { 0xC6, 0x05, 0xB0, 0x17, 0xC8, 0x04, 0x00 };


void BufferOperation();

void EncryptOperation1();
void EncryptOperation2();
void EncryptOperation3();
void EncryptOperation4();

void SendOperation();

void RevcOperation();

__declspec(naked) void BufferFunc1() {
	_asm push ebp
	_asm mov ebp, esp
	_asm push - 1
	_asm pushad;
	_asm mov eax, [ebp + 0x4]
		_asm mov callfrom, eax
	_asm mov eax, [ebp + 0x8]
		_asm mov head, eax
	BufferOperation();
	_asm popad
	_asm jmp bufferreturn
}

void BufferOperation() {
	wchar_t Str[100];
	GetPrivateProfileStringW(L"自动", L"过滤发包包头", L" ", Str, 200, lpPath);

	std::vector<int> route = SplitStr(Str, L" ");
	for (unsigned i = 0; i < route.size(); i++) {
		if (head == route[i]) {
			return;
		}
	}
	WhetherIntercept = TRUE;
	WCHAR context[100];
	wsprintf(context, L"Send_缓冲Call(%d); /*callfrom:%x*/ ", head, callfrom);
	WCHAR charcount[15];
	wsprintf(charcount, L"/*%d*/", count);
	WritePrivateProfileStringW(L"sendrecv", charcount, context, lpPath);
	count++;
}


__declspec(naked) void EncryptFunc1() {
	_asm push ebp
	_asm mov ebp, esp
	_asm pushad;
	_asm mov eax, [ebp + 0x4]
		_asm mov callfrom, eax
	_asm mov eax, [ebp + 0x8]
		_asm mov param, eax
	EncryptOperation1();
	_asm popad
	_asm cmp byte ptr[ecx + 0x8], 00
	_asm jmp encryptreturn1
}

__declspec(naked) void EncryptFunc2() {
	_asm push ebp
	_asm mov ebp, esp
	_asm pushad;
	_asm mov eax, [ebp + 0x4]
		_asm mov callfrom, eax
	_asm mov eax, [ebp + 0x8]
		_asm mov param, eax
	EncryptOperation2();
	_asm popad
	_asm cmp byte ptr[ecx + 0x8], 00
	_asm jmp encryptreturn2
}

__declspec(naked) void EncryptFunc3() {
	_asm push ebp
	_asm mov ebp, esp
	_asm pushad;
	_asm mov eax, [ebp + 0x4]
		_asm mov callfrom, eax
	_asm mov eax, [ebp + 0x8]
		_asm mov param, eax
	EncryptOperation3();
	_asm popad
	_asm cmp byte ptr[ecx + 0x8], 00
	_asm jmp encryptreturn3
}

__declspec(naked) void EncryptFunc4() {
	_asm push ebp
	_asm mov ebp, esp
	_asm pushad;
	_asm mov eax, [ebp + 0x4]
		_asm mov callfrom, eax
	_asm mov eax, [ebp + 0x8]
		_asm mov param, eax
	EncryptOperation4();
	_asm popad
	_asm cmp byte ptr[ecx + 0x8], 00
	_asm jmp encryptreturn4
}

void EncryptOperation1() {
	if (WhetherIntercept == TRUE) {
		WCHAR context[100];
		wsprintf(context, L"Send_加密Call(%d, 1); /*callfrom:%x*/ ", param, callfrom);
		WCHAR charcount[15];
		wsprintf(charcount, L"/*%d*/", count);
		WritePrivateProfileStringW(L"sendrecv", charcount, context, lpPath);
		count++;
	}
}

void EncryptOperation2() {
	if (WhetherIntercept == TRUE) {
		WCHAR context[100];
		wsprintf(context, L"Send_加密Call(%d, 2); /*callfrom:%x*/ ", param, callfrom);
		WCHAR charcount[15];
		wsprintf(charcount, L"/*%d*/", count);
		WritePrivateProfileStringW(L"sendrecv", charcount, context, lpPath);
		count++;
	}
}

void EncryptOperation3() {
	if (WhetherIntercept == TRUE) {
		WCHAR context[100];
		wsprintf(context, L"Send_加密Call(%d, 4); /*callfrom:%x*/ ", param, callfrom);
		WCHAR charcount[15];
		wsprintf(charcount, L"/*%d*/", count);
		WritePrivateProfileStringW(L"sendrecv", charcount, context, lpPath);
		count++;
	}
}

void EncryptOperation4() {
	if (WhetherIntercept == TRUE) {
		WCHAR context[100];
		wsprintf(context, L"Send_加密Call(%d, 8); /*callfrom:%x*/ ", param, callfrom);
		WCHAR charcount[15];
		wsprintf(charcount, L"/*%d*/", count);
		WritePrivateProfileStringW(L"sendrecv", charcount, context, lpPath);
		count++;
	}
}

__declspec(naked) void SendFunc() {
	_asm push ebp
	_asm mov ebp, esp
	_asm mov eax, 0x00040050
	_asm pushad;
	_asm mov eax, [ebp + 0x4]
		_asm mov callfrom, eax
	SendOperation();
	_asm popad
	_asm jmp sendpacketreturn
}

void SendOperation() {
	if (WhetherIntercept == TRUE) {
		WCHAR context[100];
		wsprintf(context, L"Send_发包Call(); /*callfrom:%x*/ ", callfrom);
		WCHAR charcount[15];
		wsprintf(charcount, L"/*%d*/", count);
		WritePrivateProfileStringW(L"sendrecv", charcount, context, lpPath);
		count++;
		wsprintf(charcount, L"/*%d*/", count);
		WritePrivateProfileStringW(L"sendrecv", charcount, L"", lpPath);
		count++;
		WhetherIntercept = FALSE;
	}
}

void writepacket(int bagPointer, int pLength) {
	wchar_t * monster = new wchar_t[3 * pLength + 50];
	BYTE * buffer = new BYTE[pLength];
	ReadProcessMemory(hProcess, (LPCVOID)bagPointer, buffer, pLength, NULL);
	memset(monster, 0, (3 * pLength + 50) * sizeof(wchar_t));
	for (int i = 0; i < pLength; i++) {
		wchar_t * num = new wchar_t[5];
		if (buffer[i] > 0xf) {
			wsprintf(num, L"%x ", buffer[i]);
			lstrcatW(monster, num);
		}
		else {
			wsprintf(num, L"0%x ", buffer[i]);
			lstrcatW(monster, num);
		}
	}
	wchar_t * num = new wchar_t[15];
	wsprintf(num, L"/*%d*/", count);
	count++;
	WritePrivateProfileStringW(L"sendrecv", num, monster, lpPath);
}
int temp = 0;
__declspec(naked) void RecvFunc() {
	_asm mov temp, 0x04CB6CE0
	_asm mov byte ptr[temp], 0
	_asm pushad;
	RevcOperation();
	_asm popad
	_asm jmp recvreturn
}

void RevcOperation() {
	int bagPointer;
	_asm mov bagPointer, ebx;
	int pHead = readInt(bagPointer + 1) & 0xffff;
	int pLength = readInt(bagPointer + 3);
	wchar_t Str[100];;
	GetPrivateProfileStringW(L"自动", L"过滤收包包头", L" ", Str, 200, lpPath);

	std::vector<int> route = SplitStr(Str, L" ");
	for (unsigned i = 0; i < route.size(); i++) {
		if (pHead == route[i]) {
			return;
		}
	}
	writepacket(bagPointer, pLength);
}


void SendRecvIntercept() {
	if (SendOandC == FALSE) {
		SendOandC = TRUE;
		HookJmp(buffer, (int)BufferFunc1, 5);
		HookJmp(encrypt1, (int)EncryptFunc1, 7);
		HookJmp(encrypt2, (int)EncryptFunc2, 7);
		HookJmp(encrypt3, (int)EncryptFunc3, 7);
		HookJmp(encrypt4, (int)EncryptFunc4, 7);
		HookJmp(sendpacket, (int)SendFunc, 8);
		HookJmp(recvpacket, (int)RecvFunc, 7);
		Notice(L"[收发包拦截]-[     开     ]");
	}
	else {
		SendOandC = FALSE;
		RestoreHook(buffer, BufferHookByte, 5);
		RestoreHook(encrypt1, EncryptHookByte, 7);
		RestoreHook(encrypt2, EncryptHookByte, 7);
		RestoreHook(encrypt3, EncryptHookByte, 7);
		RestoreHook(encrypt4, EncryptHookByte, 7);
		RestoreHook(sendpacket, SendHookByte, 8);
		RestoreHook(recvpacket, RecvHookByte, 7);
		Notice(L"[收发包拦截]-[     关     ]");
	}
}