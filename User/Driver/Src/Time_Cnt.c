#include "Headfile.h"
#include "Time_Cnt.h"
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
void TIM2_Configuration_Cnt(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    TIM_DeInit(TIM2);
    //TIM_TimeBaseStructure.TIM_Period = 60000;//30ms
    //TIM_TimeBaseStructure.TIM_Period = 20000;//10ms
    TIM_TimeBaseStructure.TIM_Period = 20000;//20ms

    TIM_TimeBaseStructure.TIM_Prescaler = 36-1; //36M/36/2=0.5us
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    TIM_ClearFlag(TIM2, TIM_FLAG_Update);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM2, ENABLE);
}
/***************************觉得不错，欢迎打赏，请小哥吃热干面：支付宝账号：1094744141@qq.com*********************************/

#define Hour         3
#define Minute       2
#define Second       1
#define MicroSecond  0
uint16 Time_Sys[4]={0};
uint16 Microsecond_Cnt=0;
u32 TIME_ISR_CNT=0;
void TIM2_IRQHandler(void)//10ms
{
 if( TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET )
 {

   TIME_ISR_CNT++;

   Microsecond_Cnt++;
   if(Microsecond_Cnt>=100)//1s
   {
     Microsecond_Cnt=0;
     Time_Sys[Second]++;
     if(Time_Sys[Second]>=60)//1min
     {
     Time_Sys[Second]=0;
     Time_Sys[Minute]++;
     if(Time_Sys[Minute]>=60)//1hour
     {
     Time_Sys[Minute]=0;
     Time_Sys[Hour]++;
     }
     }
   }
 Time_Sys[MicroSecond]=Microsecond_Cnt;
 TIM_ClearITPendingBit(TIM2,TIM_FLAG_Update);
 }
}


void Test_Period(Testime *Time_Lab)
{
   Time_Lab->Last_Time=Time_Lab->Now_Time;
   Time_Lab->Now_Time=(10000*TIME_ISR_CNT
                      +TIM2->CNT/2)/1000.0;//单位ms
   Time_Lab->Time_Delta=Time_Lab->Now_Time-Time_Lab->Last_Time;
   Time_Lab->Time_Delta_INT=(uint16)(Time_Lab->Time_Delta);
}
/***************************觉得不错，欢迎打赏，请小哥吃热干面：支付宝账号：1094744141@qq.com*********************************/