#include "Headfile.h"
#include "US_100.h"
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
float US_Distance=0;
float US_100_Distance(uint8 MSB,uint8 LSB)
{
  return (256*(MSB)+(LSB))/1.0;
}

float US_100_Temperature(uint8 data)
{
  return (data-45)/1.0;
}

uint8 HC_SR04_StartFlag=0;
float HC_SR04_Distance=0;
uint16 HC_SR04_RSSI=1;
void HC_SR04_Start(void)
{
  if(HC_SR04_StartFlag==0)
  {
    HC_SR04_OUT_HIGH;
    delay_us(20);
    HC_SR04_OUT_LOW;
    EXTI->IMR |=EXTI_Line1;
    HC_SR04_StartFlag=1;
    HC_SR04_RSSI=255;
  }
   HC_SR04_RSSI--;
}

void HC_SR04_Init(void)
{
      GPIO_InitTypeDef  GPIO_InitStructure;
      EXTI_InitTypeDef EXTI_InitStructure;

      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
      GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_Init(GPIOB, &GPIO_InitStructure);

      GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//下拉输入
      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_Init(GPIOA, &GPIO_InitStructure);

      GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource1);
      EXTI_InitStructure.EXTI_Line = EXTI_Line1;
      EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
      EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
      EXTI_InitStructure.EXTI_LineCmd	= ENABLE;
      EXTI_Init(&EXTI_InitStructure);

      //EXTI->IMR &=~EXTI_Line1;//关闭外部中断
}

void HC_SR04_UP()
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//下拉输入
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);


  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource1);
  EXTI_InitStructure.EXTI_Line = EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd= ENABLE;
  EXTI_Init(&EXTI_InitStructure);
}
/***************************觉得不错，欢迎打赏，请小哥吃热干面：支付宝账号：1094744141@qq.com*********************************/
void HC_SR04_DN()
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//上拉输入
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);


  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource1);
  EXTI_InitStructure.EXTI_Line = EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd= ENABLE;
  EXTI_Init(&EXTI_InitStructure);
}

u32 Test_Cnt1,Test_Cnt2=0,Test_Delta=0;
uint16 Exti_Cnt=0;
uint16 Sample_Cnt=0;
void EXTI1_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line1) != RESET)
  {
   Sample_Cnt++;
   if(Sample_Cnt==1)//先上升沿
   {
    Exti_Cnt++;
    Test_Cnt1=10000*TIME_ISR_CNT
                      +TIM2->CNT/2;
    HC_SR04_DN();
   }
   else//后下降沿
   {
   Test_Cnt2=10000*TIME_ISR_CNT
                      +TIM2->CNT/2;
   HC_SR04_StartFlag=0;
   HC_SR04_UP();
   //EXTI->IMR &=~EXTI_Line1;//关闭外部中断
   Sample_Cnt=0;
   Test_Delta=(Test_Cnt2-Test_Cnt1);
   HC_SR04_Distance=(Test_Cnt2-Test_Cnt1)*(325)/20000.0;
   }

  }
  EXTI_ClearITPendingBit(EXTI_Line1);
}
/***************************觉得不错，欢迎打赏，请小哥吃热干面：支付宝账号：1094744141@qq.com*********************************/




