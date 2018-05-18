
#ifndef   MY_H_FILE       //如果没有定义这个宏  
#define   MY_H_FILE       //定义这个宏
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

/********************************************组包*************************************************/
void Send_缓冲Call(int cdov);
void Send_加密Call(int wtud, int taya);
void Send_发包Call();
void 组包接受任务(int 任务ID);
void 组包完成任务(int 任务ID);
void 组包提交任务(int 任务ID);
void 完成任务CALL(int 任务ID);
void 完成已接();

void 退出角色();
void 选择角色(int count);
void 组包移动(int dMap, int xMap, int fdMap, int fxMap, int x, int y);
void 组包选图();
void 组包进图(int mapId, int grade, int taskId = 0, int abyss = 0);
void 进图确认();
void 组包秒杀(int 怪物ID);
void 组包拾取(int 物品指针);
void 组包过图(int rX, int rY);
void 组包通关();
void 组包翻牌();
void 黄金翻牌();
void 组包回城();
void 整理背包();
void 组包卖物(int addr);
void 组包分解(int addr);
/********************************************组包*************************************************/

/********************************************加密解密*************************************************/
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
/********************************************加密解密*************************************************/

/********************************************自动*************************************************/
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
/********************************************自动*************************************************/
#endif