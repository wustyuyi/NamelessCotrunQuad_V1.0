/*----------------------------------------------------------------------------------------------------------------------/
        *               本程序只供购买者学习使用，版权著作权属于无名科创团队，
        *               无名科创团队将飞控程序源码提供给购买者，
        *               购买者要为无名科创团队提供保护，
        *               未经作者许可，不得将源代码提供给他人
        *               不得将源代码放到网上供他人免费下载，
        *               更不能以此销售牟利，如发现上述行为，
        *               无名科创团队将诉之以法律解决！！！
-----------------------------------------------------------------------------------------------------------------------/
        *               生命不息、奋斗不止；前人栽树，后人乘凉！！！
        *               开源不易，且学且珍惜，祝早日逆袭、进阶成功！！！
-----------------------------------------------------------------------------------------------------------------------/
	*		无名科创开源飞控 V1.1	武汉科技大学  By.YuYi
	*		CSDN博客: http://blog.csdn.net/u011992534
	*               优酷ID：NamelessCotrun无名小哥
	*               无名科创开源飞控QQ群：540707961
        *               https://shop348646912.taobao.com/?spm=2013.1.1000126.2.5ce78a88ht1sO2
        *               百度贴吧:无名科创开源飞控
        *               修改日期:2017/10/30
        *               版本：V1.1
        *               版权所有，盗版必究。
        *               Copyright(C) 武汉科技大学无名科创团队 2017-2019
        *               All rights reserved
----------------------------------------------------------------------------------------------------------------------*/
/*
#include "Headfile.h"
#include "delay.h"
u8   fac_us;
u16  fac_ms;
void delay_init(u8 SYSCLK)
{
	SysTick->CTRL &= 0xfffffffb;
	fac_us=SYSCLK/8;
	fac_ms=(u16)fac_us*1000;
}
void delay_us(u32 nus)
{
	u32 temp;
	SysTick->LOAD = nus*fac_us;
	SysTick->VAL = 0x00;
	SysTick->CTRL = 0x01;
	temp = SysTick->CTRL;
	while((temp&0x01)&&(!(temp&(1<<16))))temp = SysTick->CTRL;
	SysTick->CTRL=0x00;
  	SysTick->VAL =0X00;

}
void delay_ms(u16 nms)
{
	u32 temp;
	SysTick->LOAD = (u32)nms*fac_ms;
	SysTick->VAL = 0x00;
	SysTick->CTRL = 0x01;
	temp = SysTick->CTRL;
	while((temp&0x01)&&(!(temp&(1<<16)))) temp = SysTick->CTRL;
	SysTick->CTRL=0x00;
  	SysTick->VAL =0X00;
}
*/
#include "Headfile.h"
#include "delay.h"
u8   fac_us;
u16  fac_ms;
void delay_init(u8 SYSCLK)
{
  SysTick->CTRL &= 0xfffffffb;
  fac_us=SYSCLK/8;
  fac_ms=(u16)fac_us*1000;
}

void delay_ms(uint16_t nms)
{
    uint32_t t0=micros();
    while(micros() - t0 < nms * 1000);
}
void delay_us(u32 nus)
{
    uint32_t t0=micros();
    while(micros() - t0 < nus);
}
/***************************觉得不错，欢迎打赏，请小哥吃热干面：支付宝账号：1094744141@qq.com*********************************/