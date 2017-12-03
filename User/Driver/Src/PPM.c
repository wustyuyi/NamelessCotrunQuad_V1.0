#include "Headfile.h"
#include "PPM.h"
/***************************觉得不错，欢迎打赏，请小哥吃热干面：支付宝账号：1094744141@qq.com*********************************/
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
/***************************************************
函数名: void PPM_Init(void)
说明:	PPM接收初始化
入口:	无
出口:	无
备注:	上电初始化，运行一次
****************************************************/
void PPM_Init()
{
GPIO_InitTypeDef GPIO_InitStructure;
EXTI_InitTypeDef EXTI_InitStructure;
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;//GPIO_Pin_0
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//输入下拉
//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_Init(GPIOA, &GPIO_InitStructure);
GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource8);
EXTI_InitStructure.EXTI_Line = EXTI_Line8;
EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
EXTI_InitStructure.EXTI_LineCmd	= ENABLE;
EXTI_Init(&EXTI_InitStructure);

}
/***************************觉得不错，欢迎打赏，请小哥吃热干面：支付宝账号：1094744141@qq.com*********************************/
uint16 PPM_Sample_Cnt=0;
uint16 PPM_Isr_Cnt=0;
u32 Last_PPM_Time=0;
u32 PPM_Time=0;
u16 PPM_Time_Delta=0;
u16 PPM_Time_Max=0;
uint16 PPM_Start_Time=0;
uint16 PPM_Finished_Time=0;
uint16 PPM_Is_Okay=0;
uint16 PPM_Databuf[8]={0};
/***************************觉得不错，欢迎打赏，请小哥吃热干面：支付宝账号：1094744141@qq.com*********************************/
/***************************************************
函数名: void EXTI9_5_IRQHandler(void)
说明:	PPM接收中断函数
入口:	无
出口:	无
备注:	程序初始化后、始终运行
****************************************************/
void EXTI9_5_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line8) != RESET)
  {
//系统运行时间获取，单位us
    Last_PPM_Time=PPM_Time;
    PPM_Time=10000*TIME_ISR_CNT
                   +TIM2->CNT/2;//us
    PPM_Time_Delta=PPM_Time-Last_PPM_Time;
    //PPM中断进入判断
    if(PPM_Isr_Cnt<100)  PPM_Isr_Cnt++;
   //PPM解析开始
    if(PPM_Is_Okay==1)
    {
    PPM_Sample_Cnt++;
    //对应通道写入缓冲区
    PPM_Databuf[PPM_Sample_Cnt-1]=PPM_Time_Delta;
    //单次解析结束
      if(PPM_Sample_Cnt>=8)
        PPM_Is_Okay=0;
    }
    if(PPM_Time_Delta>=2050)//帧结束电平至少2ms=2000us
    {
      PPM_Is_Okay=1;
      PPM_Sample_Cnt=0;
    }
  }
  EXTI_ClearITPendingBit(EXTI_Line8);
}