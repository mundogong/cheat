#include"Address.h"
//[基址]
int 人物基址 = 0x04E08638;
int 商店基址 = 0x04D1190C;
int 背包基址 = 0x04D11910;
int 等级基址 = 0x04CF4E64;
int 加密基址 = 0x04E49170;
int 解密基址 = 0x04E49110;
int 加密参数一 = 0x045A39E0;
int 加密参数二 = 0x045A3BE0;
int 喇叭公告 = 0x0249DCA0;
int 时间基址 = 0x20A028;
int 已用疲劳 = 0x04E0889C;
int 最大疲劳 = 0x04E088A4;
int 评分基址 = 0x04D0FDE4;
//[HOOK]
int HOOK收包 = 0x01FE39F3;
int RETN收包 = 0x01FE39F8;
//[CALL]
int 过图CALL = 0x01567130;
//[偏移]
int x偏移 = 0x1c4;
int y偏移 = 0x1c8;
int z偏移 = 0x1cc;
int 开始偏移 = 0xC0;
int 结束偏移 = 0xC4;
int 地图偏移 = 0xBc;
int 类型偏移 = 0x98;
int 阵营偏移 = 0x828;
int 编号偏移 = 0xa0;
int 代码偏移 = 0x3d4;
int 名称偏移 = 0x3d8;

//[组包]
int 发包基址 = 0x04E3C1F8;
int 缓冲CALL = 0x031C3BD0;
int 秘钥CALL = 0x0332A790;
int 发包CALL = 0x031C5470;
int 加密包CALL = 0x031C3CE0;
//[任务]
int 任务基址 = 0x04D11940;
int 完成CALL = 0x019E75F0;

/*
HOOKJMP TenRPCS.dll+207132 - 8D 64 24 08 - lea esp,[esp+08]
*/