/* Copyright (c)  2019-2025 Wuhan Nameless Innovation Technology Co.,Ltd. All rights reserved.*/
/*----------------------------------------------------------------------------------------------------------------------/
                ��Դ����������ѣ������ߵ���ʷ�Ѿ�֤�����ڹ�����������£���������Ŀ�Դ������������˰����ߣ��Է��ز�����
								Ŀ���Ƶķ�ʽ�в�ͨ���õĿ�Դ��Ŀ��Ҫ��רְ��Ա�����ۺ�����ְ��ֽ�ѧ��ͳ���û�����������ʵ������ɶԲ�
								Ʒ��һ�δ���������������������ۺϿ��ǣ������ɿؿ�Դ�����У������������˾���漤��ܴ��룬�汾������ʵ��
								���ܣ����ڹ�˾��Ʒ���������������Ӱ��ͻ�ѧϰ���������ȫ�����Ÿ��ͻ�ѧϰ���ͻ���ֲ�Ͷ��ο��������뱣����
								���Ȩ��
-----------------------------------------------------------------------------------------------------------------------/
*               ������ֻ��������ѧϰʹ�ã���Ȩ����Ȩ���������ƴ��Ŷӣ������ƴ��Ŷӽ��ɿس���Դ���ṩ�������ߣ�
*               ������ҪΪ�����ƴ��Ŷ��ṩ������δ��������ɣ����ý�Դ�����ṩ�����ˣ����ý�Դ����ŵ����Ϲ�����������أ� 
*               �������Դ�����Ĳ�����緢��������Ϊ�������ƴ��Ŷӽ���֮�Է��ɽ��������
-----------------------------------------------------------------------------------------------------------------------
*                                                 Ϊʲôѡ���������£�
*                                         �ж����ļ۸�������׵Ŀ�Դ�ɿأ�
*                                         ����ҵ������֮������µ��ۺ����
*                                         ׷�����û����飬��Ч����ѧϰ֮·��
*                                         ���²��ٹµ�������������տ�Դ�߶ȣ�
*                                         ��Ӧ���ҷ�ƶ���٣��ٽ��������ƹ�ƽ��
*                                         ��ʱ���ܶ�����ʣ����������˹�ͬ�塣 
-----------------------------------------------------------------------------------------------------------------------
*               ������Ϣ���ܶ���ֹ��ǰ�����������˳���������
*               ��Դ���ף���ѧ����ϧ��ף������Ϯ�����׳ɹ�������
*               ѧϰ�����ߣ��������Ƽ���DJI��ZEROTECH��XAG��AEE��GDU��AUTEL��EWATT��HIGH GREAT�ȹ�˾��ҵ
*               ��ְ�����뷢�ͣ�15671678205@163.com���豸ע��ְ����λ����λ��������
*               �����ƴ���Դ�ɿ�QQȺ��2��Ⱥ465082224��1��Ⱥ540707961����Ա������
*               CSDN���ͣ�http://blog.csdn.net/u011992534
*               �ſ�ID��NamelessCotrun����С��
*               Bվ��ѧ��Ƶ��https://space.bilibili.com/67803559/#/video
*               �ͻ�ʹ���ĵá��Ľ������������http://www.openedv.com/forum.php?mod=viewthread&tid=234214&extra=page=1
*               �Ա����̣�https://shop348646912.taobao.com/?spm=2013.1.1000126.2.5ce78a88ht1sO2
*               �ٶ�����:�����ƴ���Դ�ɿ�
*               ��˾����:www.nameless.tech
*               �������¹����׿�TI��Դ�ɿ���Ƴ��ԡ�֪��ר��:https://zhuanlan.zhihu.com/p/54471146
*               �޸�����:2019/11/27                    
*               �汾���۷���PRO����WisdomPilot_Pro_V1.0.0
*               ��Ȩ���У�����ؾ���
*               Copyright(C) 2019-2025 �人�������¿Ƽ����޹�˾ 
*               All rights reserved
-----------------------------------------------------------------------------------------------------------------------
*               ��Ҫ��ʾ��
*               �����Ա�����ת�ֵķɿء��������ѡ�����ѧ�ܵĶ����Խ��ۺ�Ⱥѧϰ������
*               ����ֱ�����������������������ϣ��������´�����������Ȩ�����˲��ý�
*               ���ϴ��봫���Ϲ��������أ�������ı��ΪĿ���������ϴ��룬�����д˲�
*               ���ߣ���˾����ǰ��֪����1���ڼ�ʱ�����������ѧУ����λ����������
*               ������ַ��Ϣ�ᱻ�����ڹ�˾�������ٷ�΢�Ź���ƽ̨���ٷ��������͡�֪��
*               ר���Լ��Ա�������ҳ���Թ�ʾ���棬����������Ϊ�����Ϊ�����۵㣬Ӱ��
*               ��ѧ���ҹ���������������ܿ�ͺ������˻����������������ء�
*               �����Ϊ����˾����ش���ʧ�ߣ����Է���;���������л���ĺ�����лл������
----------------------------------------------------------------------------------------------------------------------*/
#include "Headfile.h"
#include "PPM.h"

/***************************************************
������: void PPM_Init(void)
˵��:	PPM���ճ�ʼ��
���:	��
����:	��
��ע:	�ϵ��ʼ��������һ��
****************************************************/
void PPM_Init()
{
  GPIO_InitTypeDef GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;//GPIO_Pin_0
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//��������
  //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource8);
  EXTI_InitStructure.EXTI_Line = EXTI_Line8;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd	= ENABLE;
  EXTI_Init(&EXTI_InitStructure);
}

void PPM_UP()
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//��������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource8);
  EXTI_InitStructure.EXTI_Line = EXTI_Line8;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd= ENABLE;
  EXTI_Init(&EXTI_InitStructure);
}

void PPM_DN()
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
    
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource8);
  EXTI_InitStructure.EXTI_Line = EXTI_Line8;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd= ENABLE;
  EXTI_Init(&EXTI_InitStructure);
}

static uint16_t PPM_buf[8]={0};
uint16_t PPM_Databuf[10]={0};
uint8_t ppm_update_flag=0;
uint32_t now_ppm_time_send=0;
/***************************************************
������: void EXTI9_5_IRQHandler(void)
˵��:	PPM�����жϺ���
���:	��
����:	��
��ע:	�����ʼ����ʼ������
****************************************************/
void EXTI9_5_IRQHandler(void)
{
	static uint32_t last_ppm_time=0,now_ppm_time=0;
	static uint8_t ppm_ready=0,ppm_sample_cnt=0;
	static uint16_t ppm_time_delta=0;
  if(EXTI_GetITStatus(EXTI_Line8) != RESET)
  {
    //ϵͳ����ʱ���ȡ����λus
    last_ppm_time=now_ppm_time;
    now_ppm_time_send=now_ppm_time=10000*TIME_ISR_CNT+TIM2->CNT;//us
    ppm_time_delta=now_ppm_time-last_ppm_time;
    //PPM������ʼ
    if(ppm_ready==1)
    {
			if(ppm_time_delta>=2200)//֡������ƽ����2ms=2000us�����ڲ����ϰ汾ң������
				//���ջ����PPM�źŲ���׼�������ֽ����쳣ʱ�����Ը�С��ֵ�������������һ����ʹ����ط��ϰ汾ң����
			{
				//memcpy(PPM_Databuf,PPM_buf,ppm_sample_cnt*sizeof(uint16));
				ppm_ready = 1;
				ppm_sample_cnt=0;
				ppm_update_flag=1;
			}
			else if(ppm_time_delta>=900&&ppm_time_delta<=2100)
      {         
        PPM_buf[ppm_sample_cnt++]=ppm_time_delta;//��Ӧͨ��д�뻺����       
        if(ppm_sample_cnt>=8)//���ν�������
        {
          memcpy(PPM_Databuf,PPM_buf,ppm_sample_cnt*sizeof(uint16));
          //ppm_ready=0;
					ppm_sample_cnt=0;
        }
      }
      else  ppm_ready=0;
    }
    else if(ppm_time_delta>=2200)//֡������ƽ����2ms=2000us
    {
      ppm_ready=1;
      ppm_sample_cnt=0;
			ppm_update_flag=0;
    }
  }
  EXTI_ClearITPendingBit(EXTI_Line8);
}


