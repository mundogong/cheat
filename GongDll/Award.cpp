#include "helper.h"
void Send_����Call(int cdov)
{
	__asm push cdov
	__asm mov ecx, ������ַ
	__asm mov ecx, [ecx]
	__asm call ����CALL
}
void Send_����Call(int wtud, int taya) {
	__asm mov ecx, ������ַ
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
	__asm call ��ԿCALL
	return;
}
void Send_����Call()
{
	__asm call ����CALL
}

void �����������(int ����ID) {
	Send_����Call(31);
	Send_����Call(31, 2);
	Send_����Call(����ID, 2);
	Send_����Call();
}
void ����������(int ����ID) {
	Send_����Call(33); //19b53ea
	Send_����Call(33, 2); //19b53f8
	Send_����Call(����ID, 2); //19b5408
	Send_����Call(0, 1); //19b5434
	Send_����Call(0, 1); //19b5442
	Send_����Call(); //19b5447
}
void ����ύ����(int ����ID) {
	Send_����Call(34);
	Send_����Call(34, 2);
	Send_����Call(����ID, 2);
	Send_����Call(-1, 2);
	Send_����Call(1, 2);
	Send_����Call(65535, 2);
	Send_����Call();
}
void �������CALL(int ����ID)
{
	__asm
	{
		push -1
		push 0xFF
		push ����ID
		call ���CALL
	}
}
void ����ѽ�() {
	int ��ַ, Ŀ���ַ, ��������, �׵�ַ, β��ַ, ����ID;
	��ַ = *(int *)�����ַ;
	�׵�ַ = *(int *)(��ַ + 8);
	β��ַ = *(int *)(��ַ + 12);
	�������� = (β��ַ - �׵�ַ) / 0xc;

	for (int i = 0; i < ��������; i++) {
		Ŀ���ַ = *(int *)(�׵�ַ + i * 0xc);
		����ID = *(int *)Ŀ���ַ;
		�������CALL(����ID);
	}
}

void �˳���ɫ() {
	Send_����Call(7);
	Send_����Call();
}
void ѡ���ɫ(int count) {
	Send_����Call(4);
	Send_����Call(count, 2);
	Send_����Call();
}
void ����ƶ�(int dMap, int xMap, int fdMap, int fxMap,int x, int y) {
	Send_����Call(36);
	Send_����Call(dMap, 1);
	Send_����Call(xMap, 1);
	Send_����Call(x, 2);
	Send_����Call(y, 2);
	Send_����Call(5, 1);
	Send_����Call(fdMap, 2);
	Send_����Call(fxMap, 2);
	Send_����Call(0, 4);
	Send_����Call(0, 1);
	Send_����Call();
}
void ���ѡͼ() {
	Send_����Call(15);
	Send_����Call(0, 4);
	Send_����Call();
}
void �����ͼ(int mapId, int grade, int taskId, int abyss) {
	Send_����Call(16);
	Send_����Call(mapId, 4);		//��ͼID
	Send_����Call(grade, 1);		//��ͼ�Ѷ�
	Send_����Call(taskId, 2);		//Զ���Ѷ�
	Send_����Call(abyss, 1);		//1��Ԩ 0��ͨ
	Send_����Call(0, 1);
	Send_����Call(65535, 2);
	Send_����Call(0, 4);
	Send_����Call(0, 1);
	Send_����Call(0, 4);
	Send_����Call();
}
void ��ͼȷ��() {
	Send_����Call(37);
	Send_����Call(0, 4);
	Send_����Call(0, 4);
	Send_����Call();
}
//δȷ��
void �����ɱ(int ����ID) {
	//decodeInt(readInt(�����ַ) + ���ƫ��)
	/*3205*/Send_����Call(39); /*callfrom:22edcb9*/
	/*3206*/Send_����Call(����ID, 4); /*callfrom:22edccf*/
	/*3207*/Send_����Call(decodeInt(readInt(�����ַ) + ���ƫ��), 2); /*callfrom:22edcdf*/
	/*3208*/Send_����Call(0, 4); /*callfrom:22edcf7*/
	/*3209*/Send_����Call(0, 4); /*callfrom:22edd0f*/
	/*3210*/Send_����Call(2414490, 4); /*callfrom:22ede60*/
	/*3211*/Send_����Call(8, 4); /*callfrom:22ede75*/
	/*3212*/Send_����Call(1, 1); /*callfrom:22ee043*/
	/*3213*/Send_����Call(273, 2); /*callfrom:22ee074*/
	/*3214*/Send_����Call(decodeInt(readInt(�����ַ) + ���ƫ��), 2); /*callfrom:22ee098*/
	/*3215*/Send_����Call(2356047, 4); /*callfrom:22ee0c1*/
	/*3216*/Send_����Call(2, 2); /*callfrom:22ee0e5*/
	/*3217*/Send_����Call(293, 2); /*callfrom:22ee101*/
	/*3218*/Send_����Call(323, 2); /*callfrom:22ee111*/
	/*3219*/Send_����Call(0, 1); /*callfrom:22ee125*/
	/*3220*/Send_����Call(0, 1); /*callfrom:22ee13c*/
	/*3221*/Send_����Call(0, 1); /*callfrom:22ee14a*/
	/*3222*/Send_����Call(0, 1); /*callfrom:22ee252*/
	/*3223*/Send_����Call(15466, 2); /*callfrom:22ee2e7*/
	/*3224*/Send_����Call(0, 1); /*callfrom:1ff653b*/
	/*3225*/Send_����Call(84, 4); /*callfrom:1ff654c*/
	/*3226*/Send_����Call(2234200, 8); /*callfrom:1ff656b*/
	/*3227*/Send_����Call(519, 2); /*callfrom:1ff657b*/
	/*3228*/Send_����Call(292, 2); /*callfrom:1ff658c*/
	/*3229*/Send_����Call(293, 2); /*callfrom:1ff659d*/
	/*3230*/Send_����Call(323, 2); /*callfrom:1ff65ae*/
	/*3231*/Send_����Call(11, 2); /*callfrom:1ff65bf*/
	/*3232*/Send_����Call(32, 2); /*callfrom:1ff65d0*/
	/*3233*/Send_����Call(3, 2); /*callfrom:1ff65e1*/
	/*3234*/Send_����Call(0, 1); /*callfrom:22ee3ab*/
	/*3235*/Send_����Call(0, 1); /*callfrom:22ee3d2*/
	/*3236*/Send_����Call(); /*callfrom:22ee3d7*/
}
void ���ʰȡ(int ��Ʒָ��) {	//Ʒ�� 0��ͨ 1�� 2�� 3�� 4��˵ 5ss
	/*1626*/Send_����Call(43); /*callfrom:20ada29*/
	/*1627*/Send_����Call(��Ʒָ��, 4); /*callfrom:20ada79*/
	/*1628*/Send_����Call(0, 1); /*callfrom:20ada87*/
	/*1629*/Send_����Call(1, 1); /*callfrom:20ada94*/
	/*1630*/Send_����Call(165, 2); /*callfrom:20adb53*/
	/*1631*/Send_����Call(213, 2); /*callfrom:20adb79*/
	/*1632*/Send_����Call(16870, 2); /*callfrom:20adc62*/
	/*1633*/Send_����Call(208, 2); /*callfrom:20adc79*/
	/*1634*/Send_����Call(220, 2); /*callfrom:20adc8d*/
	/*1635*/Send_����Call(21091, 2); /*callfrom:20adcba*/
	/*1636*/Send_����Call(13124, 2); /*callfrom:20adce6*/
	/*1637*/Send_����Call(); /*callfrom:20adceb*/
}
void �����ͼ(int rX, int rY) {
	/*3416*/Send_����Call(45); /*callfrom:1567229*/
	/*3417*/Send_����Call(rX, 1); /*callfrom:1567236*/
	/*3418*/Send_����Call(rY, 1); /*callfrom:1567246*/
	/*3419*/Send_����Call(780, 4); /*callfrom:156729f*/
	/*3420*/Send_����Call(263, 4); /*callfrom:15672c9*/
	/*3421*/Send_����Call(-256, 1); /*callfrom:15672e7*/
	/*3422*/Send_����Call(59430, 2); /*callfrom:156741a*/
	/*3423*/Send_����Call(0, 2); /*callfrom:156755c*/
	/*3424*/Send_����Call(0, 2); /*callfrom:156755c*/
	/*3425*/Send_����Call(0, 2); /*callfrom:156755c*/
	/*3426*/Send_����Call(0, 2); /*callfrom:156755c*/
	/*3427*/Send_����Call(0, 2); /*callfrom:156755c*/
	/*3428*/Send_����Call(0, 2); /*callfrom:156755c*/
	/*3429*/Send_����Call(0, 2); /*callfrom:156755c*/
	/*3430*/Send_����Call(0, 2); /*callfrom:156755c*/
	/*3431*/Send_����Call(4, 4); /*callfrom:1567611*/
	/*3432*/Send_����Call(0, 4); /*callfrom:1567611*/
	/*3433*/Send_����Call(0, 4); /*callfrom:1567611*/
	/*3434*/Send_����Call(0, 4); /*callfrom:1567611*/
	/*3435*/Send_����Call(0, 4); /*callfrom:1567611*/
	/*3436*/Send_����Call(0, 4); /*callfrom:1567611*/
	/*3437*/Send_����Call(0, 4); /*callfrom:1567611*/
	/*3438*/Send_����Call(0, 4); /*callfrom:1567611*/
	/*3439*/Send_����Call(7, 2); /*callfrom:156764f*/
	/*3440*/Send_����Call(30, 2); /*callfrom:156544a*/
	/*3441*/Send_����Call(10, 2); /*callfrom:156550f*/
	/*3442*/Send_����Call(0, 2); /*callfrom:15655d4*/
	/*3443*/Send_����Call(30, 2); /*callfrom:1565699*/
	/*3444*/Send_����Call(0, 2); /*callfrom:156575e*/
	/*3445*/Send_����Call(13, 2); /*callfrom:1565823*/
	/*3446*/Send_����Call(0, 4); /*callfrom:156590d*/
	/*3447*/Send_����Call(40, 2); /*callfrom:1565959*/
	/*3448*/Send_����Call(43, 2); /*callfrom:15659a5*/
	/*3449*/Send_����Call(1, 2); /*callfrom:15659bd*/
	/*3450*/Send_����Call(49167, 8); /*callfrom:15659f9*/
	/*3451*/Send_����Call(34141, 4); /*callfrom:1565a83*/
	/*3452*/Send_����Call(0, 2); /*callfrom:1565b27*/
	/*3453*/Send_����Call(-256, 1); /*callfrom:156767b*/
	/*3454*/Send_����Call(); /*callfrom:1567680*/
}
void ���ͨ��() {
	//decodeInt(readInt(�����ַ) + ���ƫ��)
	/*3593*/Send_����Call(46); /*callfrom:235f38f*/
	/*3594*/Send_����Call(0, 1); /*callfrom:235f39c*/
	/*3595*/Send_����Call(0, 2); /*callfrom:235f447*/
	/*3596*/Send_����Call(1, 1); /*callfrom:235f46e*/
	/*3597*/Send_����Call(decodeInt(readInt(�����ַ) + ���ƫ��), 2); /*callfrom:235f4a3*/
	/*3598*/Send_����Call(3, 4); /*callfrom:235f4ec*/
	/*3599*/Send_����Call(99, 1); /*callfrom:235f51c*/
	/*3600*/Send_����Call(99, 1); /*callfrom:235f539*/
	/*3601*/Send_����Call(4, 4); /*callfrom:235f575*/
	/*3602*/Send_����Call(1, 4); /*callfrom:235f61d*/
	/*3603*/Send_����Call(-3, 4); /*callfrom:235f70b*/
	/*3604*/Send_����Call(11780, 4); /*callfrom:235f71e*/
	/*3605*/Send_����Call(19704, 4); /*callfrom:235f731*/
	/*3606*/Send_����Call(71933, 4); /*callfrom:235f73e*/
	/*3607*/Send_����Call(35293, 4); /*callfrom:235f74b*/
	/*3608*/Send_����Call(19465, 1); /*callfrom:235f787*/
	/*3609*/Send_����Call(0, 4); /*callfrom:235f7ae*/
	/*3610*/Send_����Call(0, 4); /*callfrom:235f7bb*/
	/*3611*/Send_����Call(); /*callfrom:235f9d9*/
}

void �ƽ���() {
	Send_����Call(69);
	Send_����Call();
	Send_����Call(70);
	Send_����Call();
	Send_����Call(71);
	Send_����Call(0, 1);
	Send_����Call(0, 1);
	Send_����Call();
	Send_����Call(71);
	Send_����Call(1, 1);
	Send_����Call(0, 1);
	Send_����Call();
}
void �������() {
	Send_����Call(69);
	Send_����Call();
	Send_����Call(70);
	Send_����Call();
	Send_����Call(71); //643f2e0
	Send_����Call(0, 1); //648f8ee
	Send_����Call(0, 1); //6464c63
	Send_����Call(); //646dc45
	Send_����Call(1438);
	Send_����Call();
}
void ����س�() {
	Send_����Call(42);
	Send_����Call();
}
void ������() {
	Send_����Call(20);
	Send_����Call(6, 4);
	Send_����Call(16, 1);
	Send_����Call(0, 1);
	Send_����Call(24, 1);
	Send_����Call(1, 1);
	Send_����Call(32, 1);
	Send_����Call(0, 1);
	Send_����Call();
}
void �������(int addr) {
	Send_����Call(22);
	Send_����Call(0, 1);
	Send_����Call(addr, 2);
	Send_����Call(1, 4);
	Send_����Call(2, 4);
	Send_����Call(2 * addr + 3, 4);
	Send_����Call();
}
void ����ֽ�(int addr) {
	Send_����Call(26);
	Send_����Call(addr, 2);
	Send_����Call(0, 1);
	Send_����Call(65535, 2);
	Send_����Call(319, 4);
	Send_����Call();
}