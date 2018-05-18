#include"Helper.h"

std::vector<int> SplitStr(wchar_t * text, const wchar_t * separator) {
	std::vector<int> IntVector;
	wchar_t *inttoken = NULL;
	wchar_t *next_inttoken = NULL;
	inttoken = wcstok_s(text, separator, &next_inttoken);
	while (inttoken != NULL)
	{
		int temp = _wtoi(inttoken);
		IntVector.push_back(temp);
		inttoken = wcstok_s(NULL, separator, &next_inttoken);
	}
	return IntVector;
}
void writeivectofile(int head, std::vector<int> ivec) {
	wchar_t str[300];
	memset(str, 0, 300 * sizeof(wchar_t));
	for (unsigned int i = 0; i < ivec.size(); i++) {
		wchar_t * num = new wchar_t[10];
		memset(num, 0, 10 * sizeof(wchar_t));
		wsprintf(num, L"%d ", ivec[i]);
		lstrcatW(str, num);
	}
	wchar_t * num = new wchar_t[10];
	memset(num, 0, 10 * sizeof(wchar_t));
	wsprintf(num, L"%d", head);
	WritePrivateProfileStringW(L"send", num, str, lpPath);
}
std::vector<GoodInfo> SearchMap(int type, int camp) {
	std::vector<GoodInfo> temp;
	temp.clear();
	GoodInfo tempMap;
	int person_addr = readInt(人物基址);
	if (person_addr == 0) {
		return temp;
	}
	int map_addr = readInt(person_addr + 地图偏移);
	if (map_addr == 0) {
		return temp;
	}
	int map_start = readInt(map_addr + 开始偏移);
	int map_end = readInt(map_addr + 结束偏移);
	int monsterNum = (map_end - map_start) / 4;
	if (monsterNum <= 0 && monsterNum > 200) {
		return temp;
	}
	for (int i = 0; i < monsterNum; i++) {
		tempMap.point = map_start + i * 4;
		tempMap.address = readInt(tempMap.point);
		tempMap.x = (int)readDecimal(tempMap.address + x偏移);
		tempMap.y = (int)readDecimal(tempMap.address + y偏移);
		tempMap.z = (int)readDecimal(tempMap.address + z偏移);
		tempMap.type = readInt(tempMap.address + 类型偏移);
		tempMap.camp = readInt(tempMap.address + 阵营偏移);
		tempMap.code = readInt(tempMap.address + 代码偏移);
		tempMap.number = decodeInt(tempMap.address + 编号偏移);
		readWchar(readInt(tempMap.address + 名称偏移), tempMap.name, 20);

		if ((type == tempMap.type && tempMap.camp == camp) || (type == tempMap.type && camp == -1) || (type == -1)) {
			temp.push_back(tempMap);
		}
	}
	return temp;
}
void ErgodicRoom() {
	std::vector<GoodInfo> temp = SearchMap();
	for (unsigned int i = 0; i < temp.size(); i++) {
		wchar_t Monster[200];
		wchar_t num[5];
		wsprintf(num, L"%d", i);
		wsprintf(Monster, L"%10x%15d%15d%15d%15d%15d%15d%15d%20ls.", temp[i].address, temp[i].x, temp[i].y, temp[i].z, temp[i].type, temp[i].camp, temp[i].code, temp[i].number, temp[i].name);
		WritePrivateProfileStringW(L"map", num, Monster, lpPath);
	}
	wchar_t num[5];
	wsprintf(num, L"%d", temp.size());
	WritePrivateProfileStringW(L"map", num, L" ", lpPath);
}
void EquipHandle() {
	for (int i = 0; i < 56; i++) {
		int pGoods = readInt(readInt(readInt(背包基址) + 0x58) + 0x24 + i * 4);
		if (pGoods != 0) {
			int pQulity = readInt(pGoods + 0x170);
			if (pQulity == 0 || pQulity == 1 || pQulity == 2) {
				switch (GetPrivateProfileIntW(L"自动", L"装备处理", 0, lpPath))
				{
				case 1:
					组包卖物(i + 9);
					break;
				case 2:
					组包分解(i + 9);
					break;
				default:
					break;
				}
				Sleep(500);
			}
		}
	}
}

void GotoNextRoom(int DungeonId, POINT RoleCoordinate) {
	POINT direction;
	wchar_t DungeonIdStr[10];
	wchar_t RouteStr[100];
	wsprintf(DungeonIdStr, L"%d", DungeonId);
	GetPrivateProfileStringW(L"路径", DungeonIdStr, L" ", RouteStr, 100, lpPath);
	std::vector<int> route = SplitStr(RouteStr, L" ");
	for (unsigned int i = 0; i < route.size(); i++) {
		if ((RoleCoordinate.x * 10 + RoleCoordinate.y) == route[i] && (i + 1 < route.size())) {
			direction.x = route[i + 1] / 10;
			direction.y = route[i + 1] % 10;
			组包过图(direction.x, direction.y);
		}
	}
}
int GetDungeonId(int level) {
	if (level >= 47 && level < 51) {
		return 7146;
	}
	else if (level >= 51 && level < 55) {
		return 7147;
	}
	else if (level >= 55 && level < 60) {
		return 7148;
	}
	else if (level >= 60 && level < 65) {
		return 7149;
	}
	else if (level >= 65 && level < 72) {
		return 7150;
	}
	else if (level >= 72 && level < 77) {
		return 7151;
	}
	else if (level >= 77 && level < 81) {
		return 7152;
	}
	else if (level >= 81 && level < 85) {
		return 7152;
	}
	else {
		return GetPrivateProfileIntW(L"自动", L"副本ID", 0, lpPath);
	}

}
void GetPlaneRoute(int DungeonId) {
	switch (DungeonId)
	{
	case 3:
	case 5:
	case 6:
	case 9:
	case 7:
	case 8:
	case 1000:
		组包移动(38, 2, 38, 0, 1085, 249);
		break;
	case 10:
	case 12:
	case 13:
	case 14:
	case 17:
	case 15:
		组包移动(40, 3, 40, 0, 55, 231);
		break; 
	case 21:
	case 22:
	case 23:
	case 24:
	case 25:
	case 26:
	case 27:
		组包移动(40, 4, 40, 1, 55, 285);
		break;
	case 31:
	case 32:
	case 150:
	case 151:
	case 35:
	case 34:
	case 36:
		组包移动(41, 2, 41, 1, 55, 223);
		break;
	case 152:
	case 153:
	case 154:
		组包移动(42, 3, 42, 0, 55, 201);
		break;
	case 40:
	case 41:
	case 42:
	case 43:
	case 141:
		组包移动(43, 1, 43, 0, 860, 418);
		break;
	case 61:
	case 50:
	case 51:
	case 52:
	case 53:
	case 7146:
		组包移动(39, 5, 39, 3, 860, 285);
		break;
	case 144:
	case 145:
	case 146:
	case 148:
	case 7147:
		组包移动(46, 6, 46, 3, 861, 347);
		break;
	case 156:
	case 157:
	case 158:
	case 159:
	case 160:
	case 7148:
		组包移动(46, 5, 46, 2, 861, 241);
		break;
	case 161:
	case 162:
	case 163:
	case 164:
	case 7149:
		组包移动(46, 4, 46, 1, 55, 254);
		break;
	case 80:
	case 81:
	case 82:
	case 88:
	case 89:
	case 83:
	case 84:
	case 85:
	case 7150:
		组包移动(6, 1, 6, 0, 1085, 276);
		break;
	case 86:
	case 87:
	case 92:
	case 93:
	case 7151:
		组包移动(9, 1, 9, 0, 55, 242);
		break;
	case 70:
	case 71:
	case 72:
	case 73:
	case 74:
	case 75:
	case 76:
	case 77:
	case 7152:
		组包移动(12, 0, 11, 0, 661, 183);
		break;
	case 101:
	case 102:
	case 103:
	case 104:
	case 7153:
		组包移动(14, 2, 14, 1, 55, 271);
		break;
	case 190:
	case 191:
	case 192:
	case 193:
	case 194:
	case 7154:
		组包移动(22, 2, 22, 1, 55, 342);
		break;
	case 310:
	case 311:
	case 312:
	case 313:
	case 314:
	case 7155:
		组包移动(30, 2, 30, 1, 55, 350);
		break;
	case 7101:
	case 7102:
	case 7103:
	case 7104:
	case 7105:
	case 7106:
	case 7107:
		组包移动(17, 5, 17, 3, 157, 182);
		break;
	default:
		break;
	}
}
int GetDungeonMaxDifficulty(int DungeonId) {
	int MaxDifficulty = 0;
	switch (DungeonId)
	{
	case 3:
	case 5:
	case 6:
	case 9:
	case 7:
	case 8:
	case 1000:
		MaxDifficulty = 0;
		break;
	case 10:
	case 12:
	case 13:
	case 14:
	case 17:
	case 15:
		MaxDifficulty = 1;
		break;
	case 21:
	case 22:
	case 23:
	case 24:
	case 25:
	case 26:
	case 27:
		MaxDifficulty = 1;
		break;
	case 31:
	case 32:
	case 150:
	case 151:
	case 35:
	case 34:
	case 36:
		MaxDifficulty = 1;
		break;
	case 152:
	case 153:
	case 154:
		MaxDifficulty = 2;
		break;
	case 40:
	case 41:
	case 42:
	case 43:
	case 141:
		MaxDifficulty = 2;
		break;
	case 61:
	case 50:
	case 51:
	case 52:
	case 53:
		MaxDifficulty = 2;
		break;
	case 144:
	case 145:
	case 146:
	case 148:
		MaxDifficulty = 3;
		break;
	case 156:
	case 157:
	case 158:
	case 159:
	case 160:
		MaxDifficulty = 3;
		break;
	case 161:
	case 162:
	case 163:
	case 164:
		MaxDifficulty = 3;
		break;
	case 80:
	case 81:
	case 82:
	case 88:
	case 89:
	case 83:
	case 84:
	case 85:
		MaxDifficulty = 3;
		break;
	case 86:
	case 87:
	case 92:
	case 93:
		MaxDifficulty = 3;
		break;
	case 70:
	case 71:
	case 72:
	case 73:
	case 74:
	case 75:
	case 76:
	case 77:
		MaxDifficulty = 4;
		break;
	case 101:
	case 102:
	case 103:
	case 104:
		MaxDifficulty = 4;
		break;
	case 190:
	case 191:
	case 192:
	case 193:
	case 194:
		MaxDifficulty = 4;
		break;
	case 310:
	case 311:
	case 312:
	case 313:
	case 314:
		MaxDifficulty = 4;
		break;
	case 7101:
	case 7102:
	case 7103:
	case 7104:
	case 7105:
	case 7106:
	case 7107:
		MaxDifficulty = 3;
		break;
	case 7146:
	case 7147:
	case 7148:
	case 7149:
	case 7150:
	case 7151:
	case 7152:
	case 7153:
	case 7154:
	case 7155:
		MaxDifficulty = 0;
		break;
	default:
		break;
	}
	return MaxDifficulty;
}
bool WhetherHaveTried(int DungeonId) {
	int maxTried = decodeInt(最大疲劳);
	int usedTried = decodeInt(已用疲劳);
	int residualTried = maxTried - usedTried;
	if (DungeonId >= 7101 && DungeonId <= 7107) {
		if (maxTried - usedTried >= 6) {
			return TRUE;
		}
		else {
			return FALSE;
		}
	}
	else if (DungeonId >= 7146 && DungeonId <= 7155) {
		if (maxTried - usedTried >= 8) {
			return TRUE;
		}
		else {
			return FALSE;
		}
	}
	else {
		if (maxTried - usedTried >= 1) {
			return TRUE;
		}
		else {
			return FALSE;
		}
	}
}
