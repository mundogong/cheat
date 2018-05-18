
#ifndef   MY_H_FILE       //���û�ж��������  
#define   MY_H_FILE       //���������
#include <windows.h>
#include "shlobj.h"
#include"address.h"
#include<vector>
#include<string.h>
#include<math.h>
#include <time.h>

struct GoodInfo
{
	int point;
	int address;
	int x;
	int y;
	int z;
	int type;
	int camp;
	int code;
	int number;
	WCHAR name[20] = { 0 };
};

struct MemoryInfo
{
	int Point;
	int Value;
	int Integer;
	float Decimal;
	int DecodeInteger;
	float DecodeDecimal;
	WCHAR Unicode[20];
};

struct dungeon {
	int CurrentRole;
	int CountRole;
	int DungeonCount;
	int DungeonId;
	int DungeonDifficulty;
	POINT BossCoordinate;
	POINT RoleCoordinate;
	POINT AbyssCoordinate;
	BOOL WhetherUi;
};

extern WCHAR lpPath[MAX_PATH];
extern HANDLE hProcess;
extern DWORD ProcessID;
extern HWND hGameWindow;
extern DWORD ThreadID;
extern DWORD MyThreadID;
extern HANDLE hMyThread;
extern HMODULE hdll;
extern byte HookKillByte[6];
extern byte ChangeMonsterByte[5];
extern byte HookRecvByte[5];
extern byte BloodByte[5];

void PrimaryThread();
void MessageLoop();
void InitData();
void InitIniPath();
/********************************************call*************************************************/
void Notice(LPCWSTR NoticeContent, int Color = 0xFF00FFFF);
void CoercivePassMap(int direction);
void CoordinateCall(int personaddress, int x, int y, int z);
void CoordinatePassMap(int direction);
/********************************************call*************************************************/

/********************************************���*************************************************/
void Send_����Call(int cdov);
void Send_����Call(int wtud, int taya);
void Send_����Call();
void �����������(int ����ID);
void ����������(int ����ID);
void ����ύ����(int ����ID);
void �������CALL(int ����ID);
void ����ѽ�();

void �˳���ɫ();
void ѡ���ɫ(int count);
void ����ƶ�(int dMap, int xMap, int fdMap, int fxMap, int x, int y);
void ���ѡͼ();
void �����ͼ(int mapId, int grade, int taskId = 0, int abyss = 0);
void ��ͼȷ��();
void �����ɱ(int ����ID);
void ���ʰȡ(int ��Ʒָ��);
void �����ͼ(int rX, int rY);
void ���ͨ��();
void �������();
void �ƽ���();
void ����س�();
void ������();
void �������(int addr);
void ����ֽ�(int addr);
/********************************************���*************************************************/

/********************************************���ܽ���*************************************************/
void read(int address, byte * temp, int count = 4);
void write(int address, byte * temp, int count = 4);
int readInt(int address);
void writeInt(int address, int temp);
float readDecimal(int address);
void writeDecimal(int address, float value);
LPVOID applyMemory(int count, DWORD protect = PAGE_EXECUTE_READWRITE, DWORD type = MEM_COMMIT);
void freeMemory(LPVOID address, DWORD protect = PAGE_EXECUTE_READWRITE, DWORD type = MEM_COMMIT);
void readWchar(int address, LPVOID temp, int count);
int decodeInt(int address);
void encryptInt(int address, int value);
float decodeDecimal(int address);
void encryptDecimal(int address, float value);
void HookJmp(int base, int Hook, int HookByteNum);
void HookCall(int base, int Hook, int HookByteNum);
void RestoreHook(int base, byte *RestoreByte, int RestoreByteNum);
std::vector<int> SplitStr(wchar_t * text, const wchar_t * separator);
void writeivectofile(int head, std::vector<int> ivec);
std::vector<int> SearchConditioncode(std::vector<byte> Conditioncode);
std::vector<MemoryInfo> traverseMemory();
MemoryInfo readAddrInfo(int noAddress);
/********************************************���ܽ���*************************************************/

/********************************************�Զ�*************************************************/
std::vector<GoodInfo> SearchMap(int type = -1, int camp = -1);
void ErgodicRoom();

void RecvAutoPlay();

int GetDungeonId(int level);
int GetDungeonMaxDifficulty(int DungeonId);
void GetPlaneRoute(int DungeonId);
bool WhetherHaveTried(int DungeonId);
void GotoNextRoom(int DungeonId, POINT RoleCoordinate);
void EquipHandle();

void SendRecvIntercept();
/********************************************�Զ�*************************************************/
#endif