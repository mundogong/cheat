#include "helper.h"
void Send_缓冲Call(int cdov)
{
	__asm push cdov
	__asm mov ecx, 发包基址
	__asm mov ecx, [ecx]
	__asm call 缓冲CALL
}
void Send_加密Call(int wtud, int taya) {
	__asm mov ecx, 发包基址
	__asm mov ecx, [ecx]
	__asm cmp byte ptr[ecx + 0x00000008], 00
	__asm jne jecode
	__asm mov eax, 0x80000054
	return;
	jecode:
	__asm mov eax, [ebp + 0x0000000C]
	__asm add [ecx + 0x002BCC2C], eax
	__asm push eax
	__asm lea eax, [ebp + 0x00000008]
	__asm push eax
	__asm call 秘钥CALL
	return;
}
void Send_发包Call()
{
	__asm call 发包CALL
}

void 组包接受任务(int 任务ID) {
	Send_缓冲Call(31);
	Send_加密Call(31, 2);
	Send_加密Call(任务ID, 2);
	Send_发包Call();
}
void 组包完成任务(int 任务ID) {
	Send_缓冲Call(33); //19b53ea
	Send_加密Call(33, 2); //19b53f8
	Send_加密Call(任务ID, 2); //19b5408
	Send_加密Call(0, 1); //19b5434
	Send_加密Call(0, 1); //19b5442
	Send_发包Call(); //19b5447
}
void 组包提交任务(int 任务ID) {
	Send_缓冲Call(34);
	Send_加密Call(34, 2);
	Send_加密Call(任务ID, 2);
	Send_加密Call(-1, 2);
	Send_加密Call(1, 2);
	Send_加密Call(65535, 2);
	Send_发包Call();
}
void 完成任务CALL(int 任务ID)
{
	__asm
	{
		push -1
		push 0xFF
		push 任务ID
		call 完成CALL
	}
}
void 完成已接() {
	int 地址, 目标基址, 任务数量, 首地址, 尾地址, 任务ID;
	地址 = *(int *)任务基址;
	首地址 = *(int *)(地址 + 8);
	尾地址 = *(int *)(地址 + 12);
	任务数量 = (尾地址 - 首地址) / 0xc;

	for (int i = 0; i < 任务数量; i++) {
		目标基址 = *(int *)(首地址 + i * 0xc);
		任务ID = *(int *)目标基址;
		完成任务CALL(任务ID);
	}
}

void 退出角色() {
	Send_缓冲Call(7);
	Send_发包Call();
}
void 选择角色(int count) {
	Send_缓冲Call(4);
	Send_加密Call(count, 2);
	Send_发包Call();
}
void 组包移动(int dMap, int xMap, int fdMap, int fxMap,int x, int y) {
	Send_缓冲Call(36);
	Send_加密Call(dMap, 1);
	Send_加密Call(xMap, 1);
	Send_加密Call(x, 2);
	Send_加密Call(y, 2);
	Send_加密Call(5, 1);
	Send_加密Call(fdMap, 2);
	Send_加密Call(fxMap, 2);
	Send_加密Call(0, 4);
	Send_加密Call(0, 1);
	Send_发包Call();
}
void 组包选图() {
	Send_缓冲Call(15);
	Send_加密Call(0, 4);
	Send_发包Call();
}
void 组包进图(int mapId, int grade, int taskId, int abyss) {
	Send_缓冲Call(16);
	Send_加密Call(mapId, 4);		//地图ID
	Send_加密Call(grade, 1);		//地图难度
	Send_加密Call(taskId, 2);		//远古难度
	Send_加密Call(abyss, 1);		//1深渊 0普通
	Send_加密Call(0, 1);
	Send_加密Call(65535, 2);
	Send_加密Call(0, 4);
	Send_加密Call(0, 1);
	Send_加密Call(0, 4);
	Send_发包Call();
}
void 进图确认() {
	Send_缓冲Call(37);
	Send_加密Call(0, 4);
	Send_加密Call(0, 4);
	Send_发包Call();
}
//未确认
void 组包秒杀(int 怪物ID) {
	//decodeInt(readInt(人物基址) + 编号偏移)
	/*3205*/Send_缓冲Call(39); /*callfrom:22edcb9*/
	/*3206*/Send_加密Call(怪物ID, 4); /*callfrom:22edccf*/
	/*3207*/Send_加密Call(decodeInt(readInt(人物基址) + 编号偏移), 2); /*callfrom:22edcdf*/
	/*3208*/Send_加密Call(0, 4); /*callfrom:22edcf7*/
	/*3209*/Send_加密Call(0, 4); /*callfrom:22edd0f*/
	/*3210*/Send_加密Call(2414490, 4); /*callfrom:22ede60*/
	/*3211*/Send_加密Call(8, 4); /*callfrom:22ede75*/
	/*3212*/Send_加密Call(1, 1); /*callfrom:22ee043*/
	/*3213*/Send_加密Call(273, 2); /*callfrom:22ee074*/
	/*3214*/Send_加密Call(decodeInt(readInt(人物基址) + 编号偏移), 2); /*callfrom:22ee098*/
	/*3215*/Send_加密Call(2356047, 4); /*callfrom:22ee0c1*/
	/*3216*/Send_加密Call(2, 2); /*callfrom:22ee0e5*/
	/*3217*/Send_加密Call(293, 2); /*callfrom:22ee101*/
	/*3218*/Send_加密Call(323, 2); /*callfrom:22ee111*/
	/*3219*/Send_加密Call(0, 1); /*callfrom:22ee125*/
	/*3220*/Send_加密Call(0, 1); /*callfrom:22ee13c*/
	/*3221*/Send_加密Call(0, 1); /*callfrom:22ee14a*/
	/*3222*/Send_加密Call(0, 1); /*callfrom:22ee252*/
	/*3223*/Send_加密Call(15466, 2); /*callfrom:22ee2e7*/
	/*3224*/Send_加密Call(0, 1); /*callfrom:1ff653b*/
	/*3225*/Send_加密Call(84, 4); /*callfrom:1ff654c*/
	/*3226*/Send_加密Call(2234200, 8); /*callfrom:1ff656b*/
	/*3227*/Send_加密Call(519, 2); /*callfrom:1ff657b*/
	/*3228*/Send_加密Call(292, 2); /*callfrom:1ff658c*/
	/*3229*/Send_加密Call(293, 2); /*callfrom:1ff659d*/
	/*3230*/Send_加密Call(323, 2); /*callfrom:1ff65ae*/
	/*3231*/Send_加密Call(11, 2); /*callfrom:1ff65bf*/
	/*3232*/Send_加密Call(32, 2); /*callfrom:1ff65d0*/
	/*3233*/Send_加密Call(3, 2); /*callfrom:1ff65e1*/
	/*3234*/Send_加密Call(0, 1); /*callfrom:22ee3ab*/
	/*3235*/Send_加密Call(0, 1); /*callfrom:22ee3d2*/
	/*3236*/Send_发包Call(); /*callfrom:22ee3d7*/
}
void 组包拾取(int 物品指针) {	//品级 0普通 1蓝 2紫 3粉 4传说 5ss
	/*1626*/Send_缓冲Call(43); /*callfrom:20ada29*/
	/*1627*/Send_加密Call(物品指针, 4); /*callfrom:20ada79*/
	/*1628*/Send_加密Call(0, 1); /*callfrom:20ada87*/
	/*1629*/Send_加密Call(1, 1); /*callfrom:20ada94*/
	/*1630*/Send_加密Call(165, 2); /*callfrom:20adb53*/
	/*1631*/Send_加密Call(213, 2); /*callfrom:20adb79*/
	/*1632*/Send_加密Call(16870, 2); /*callfrom:20adc62*/
	/*1633*/Send_加密Call(208, 2); /*callfrom:20adc79*/
	/*1634*/Send_加密Call(220, 2); /*callfrom:20adc8d*/
	/*1635*/Send_加密Call(21091, 2); /*callfrom:20adcba*/
	/*1636*/Send_加密Call(13124, 2); /*callfrom:20adce6*/
	/*1637*/Send_发包Call(); /*callfrom:20adceb*/
}
void 组包过图(int rX, int rY) {
	/*3416*/Send_缓冲Call(45); /*callfrom:1567229*/
	/*3417*/Send_加密Call(rX, 1); /*callfrom:1567236*/
	/*3418*/Send_加密Call(rY, 1); /*callfrom:1567246*/
	/*3419*/Send_加密Call(780, 4); /*callfrom:156729f*/
	/*3420*/Send_加密Call(263, 4); /*callfrom:15672c9*/
	/*3421*/Send_加密Call(-256, 1); /*callfrom:15672e7*/
	/*3422*/Send_加密Call(59430, 2); /*callfrom:156741a*/
	/*3423*/Send_加密Call(0, 2); /*callfrom:156755c*/
	/*3424*/Send_加密Call(0, 2); /*callfrom:156755c*/
	/*3425*/Send_加密Call(0, 2); /*callfrom:156755c*/
	/*3426*/Send_加密Call(0, 2); /*callfrom:156755c*/
	/*3427*/Send_加密Call(0, 2); /*callfrom:156755c*/
	/*3428*/Send_加密Call(0, 2); /*callfrom:156755c*/
	/*3429*/Send_加密Call(0, 2); /*callfrom:156755c*/
	/*3430*/Send_加密Call(0, 2); /*callfrom:156755c*/
	/*3431*/Send_加密Call(4, 4); /*callfrom:1567611*/
	/*3432*/Send_加密Call(0, 4); /*callfrom:1567611*/
	/*3433*/Send_加密Call(0, 4); /*callfrom:1567611*/
	/*3434*/Send_加密Call(0, 4); /*callfrom:1567611*/
	/*3435*/Send_加密Call(0, 4); /*callfrom:1567611*/
	/*3436*/Send_加密Call(0, 4); /*callfrom:1567611*/
	/*3437*/Send_加密Call(0, 4); /*callfrom:1567611*/
	/*3438*/Send_加密Call(0, 4); /*callfrom:1567611*/
	/*3439*/Send_加密Call(7, 2); /*callfrom:156764f*/
	/*3440*/Send_加密Call(30, 2); /*callfrom:156544a*/
	/*3441*/Send_加密Call(10, 2); /*callfrom:156550f*/
	/*3442*/Send_加密Call(0, 2); /*callfrom:15655d4*/
	/*3443*/Send_加密Call(30, 2); /*callfrom:1565699*/
	/*3444*/Send_加密Call(0, 2); /*callfrom:156575e*/
	/*3445*/Send_加密Call(13, 2); /*callfrom:1565823*/
	/*3446*/Send_加密Call(0, 4); /*callfrom:156590d*/
	/*3447*/Send_加密Call(40, 2); /*callfrom:1565959*/
	/*3448*/Send_加密Call(43, 2); /*callfrom:15659a5*/
	/*3449*/Send_加密Call(1, 2); /*callfrom:15659bd*/
	/*3450*/Send_加密Call(49167, 8); /*callfrom:15659f9*/
	/*3451*/Send_加密Call(34141, 4); /*callfrom:1565a83*/
	/*3452*/Send_加密Call(0, 2); /*callfrom:1565b27*/
	/*3453*/Send_加密Call(-256, 1); /*callfrom:156767b*/
	/*3454*/Send_发包Call(); /*callfrom:1567680*/
}
void 组包通关() {
	//decodeInt(readInt(人物基址) + 编号偏移)
	/*3593*/Send_缓冲Call(46); /*callfrom:235f38f*/
	/*3594*/Send_加密Call(0, 1); /*callfrom:235f39c*/
	/*3595*/Send_加密Call(0, 2); /*callfrom:235f447*/
	/*3596*/Send_加密Call(1, 1); /*callfrom:235f46e*/
	/*3597*/Send_加密Call(decodeInt(readInt(人物基址) + 编号偏移), 2); /*callfrom:235f4a3*/
	/*3598*/Send_加密Call(3, 4); /*callfrom:235f4ec*/
	/*3599*/Send_加密Call(99, 1); /*callfrom:235f51c*/
	/*3600*/Send_加密Call(99, 1); /*callfrom:235f539*/
	/*3601*/Send_加密Call(4, 4); /*callfrom:235f575*/
	/*3602*/Send_加密Call(1, 4); /*callfrom:235f61d*/
	/*3603*/Send_加密Call(-3, 4); /*callfrom:235f70b*/
	/*3604*/Send_加密Call(11780, 4); /*callfrom:235f71e*/
	/*3605*/Send_加密Call(19704, 4); /*callfrom:235f731*/
	/*3606*/Send_加密Call(71933, 4); /*callfrom:235f73e*/
	/*3607*/Send_加密Call(35293, 4); /*callfrom:235f74b*/
	/*3608*/Send_加密Call(19465, 1); /*callfrom:235f787*/
	/*3609*/Send_加密Call(0, 4); /*callfrom:235f7ae*/
	/*3610*/Send_加密Call(0, 4); /*callfrom:235f7bb*/
	/*3611*/Send_发包Call(); /*callfrom:235f9d9*/
}

void 黄金翻牌() {
	Send_缓冲Call(69);
	Send_发包Call();
	Send_缓冲Call(70);
	Send_发包Call();
	Send_缓冲Call(71);
	Send_加密Call(0, 1);
	Send_加密Call(0, 1);
	Send_发包Call();
	Send_缓冲Call(71);
	Send_加密Call(1, 1);
	Send_加密Call(0, 1);
	Send_发包Call();
}
void 组包翻牌() {
	Send_缓冲Call(69);
	Send_发包Call();
	Send_缓冲Call(70);
	Send_发包Call();
	Send_缓冲Call(71); //643f2e0
	Send_加密Call(0, 1); //648f8ee
	Send_加密Call(0, 1); //6464c63
	Send_发包Call(); //646dc45
	Send_缓冲Call(1438);
	Send_发包Call();
}
void 组包回城() {
	Send_缓冲Call(42);
	Send_发包Call();
}
void 整理背包() {
	Send_缓冲Call(20);
	Send_加密Call(6, 4);
	Send_加密Call(16, 1);
	Send_加密Call(0, 1);
	Send_加密Call(24, 1);
	Send_加密Call(1, 1);
	Send_加密Call(32, 1);
	Send_加密Call(0, 1);
	Send_发包Call();
}
void 组包卖物(int addr) {
	Send_缓冲Call(22);
	Send_加密Call(0, 1);
	Send_加密Call(addr, 2);
	Send_加密Call(1, 4);
	Send_加密Call(2, 4);
	Send_加密Call(2 * addr + 3, 4);
	Send_发包Call();
}
void 组包分解(int addr) {
	Send_缓冲Call(26);
	Send_加密Call(addr, 2);
	Send_加密Call(0, 1);
	Send_加密Call(65535, 2);
	Send_加密Call(319, 4);
	Send_发包Call();
}