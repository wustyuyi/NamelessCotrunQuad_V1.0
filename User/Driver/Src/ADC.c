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
#include "headfile.h"
#include "ADC.h"
#include "stm32f10x_adc.h"


float MCU_TEPERATE = 0.0;
unsigned short average = 0;
unsigned short ADC_Value[10];
float mcu_current_temperate=0; 
/******************************************************************************
* ��������       : DMA_Configuraiton
* ����           : DMA ģ������
* ����           : ��
* ���           : ��
* ����           : ��
*******************************************************************************/
void DMA_Configuration (void)
{
  DMA_InitTypeDef DMA_InitStructure;
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
  DMA_DeInit(DMA1_Channel1);//��DMA��ͨ��1�Ĵ�������Ϊȱʡֵ
  DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)( &(ADC1->DR));//DMA����ADC����ַ
  DMA_InitStructure.DMA_MemoryBaseAddr = (unsigned long)&ADC_Value;//DMA�ڴ����ַ
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//�ڴ���Ϊ���ݴ����Ŀ�ĵ�
  DMA_InitStructure.DMA_BufferSize = 2;//DMAͨ����DMA����Ĵ�С
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//�����ַ�Ĵ�������
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//�ڴ��ַ�Ĵ�������
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //���ݿ��Ϊ16λ
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//���ݿ��Ϊ16λ
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//������ѭ������ģʽ
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;//DMAͨ�� xӵ�и����ȼ�
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);//����DMA_InitStruct��ָ���Ĳ�����ʼ��DMA��ͨ��
  DMA_ITConfig(DMA1_Channel1,DMA1_IT_TC1,ENABLE);//����DMAͨ��1��������ж�
  DMA_Cmd(DMA1_Channel1, ENABLE);
}

/******************************************************************************
* ��������       : ADC_GPIO_Init
* ����           : ADC GPIO������
* ����           : ��
* ���           : ��
* ����           : ��
*******************************************************************************/
void ADC_GPIO_Init (void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}


/******************************************************************************
* ��������       : ADC_Configuraiton
* ����           : ADC ģ������
* ����           : ��
* ���           : ��
* ����           : ��
*******************************************************************************/
void ADC_Configuration (void)
{
  ADC_InitTypeDef ADC_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
  RCC_ADCCLKConfig(RCC_PCLK2_Div6);//ADC���ʱ��Ƶ��Ϊ14M
  ADC_DeInit(ADC1); //������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
  ADC_InitStructure.ADC_ScanConvMode = ENABLE; //ģ��ת��������ɨ��ģʽ
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//ģ��ת������������ת��ģʽ
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;  //�ⲿ�������������
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//ADC�����Ҷ���
  ADC_InitStructure.ADC_NbrOfChannel = 2;//˳����й���ת����ADCͨ������Ŀ
  ADC_Init(ADC1, &ADC_InitStructure);//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���
  ADC_TempSensorVrefintCmd(ENABLE);//�����ڲ��¶ȴ�����
  /***����ָ��ADC�Ĺ�����ͨ�����������ǵ�ת��˳��Ͳ���ʱ��;ADC1,ADCͨ��x,�������˳��ֵΪy,����ʱ��Ϊ239.5����  */
  ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 1, ADC_SampleTime_239Cycles5);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 2, ADC_SampleTime_239Cycles5);
  
  ADC_DMACmd(ADC1, ENABLE);// ����ADC��DMA֧�֣�Ҫʵ��DMA���ܣ������������DMAͨ���Ȳ�����  
  ADC_Cmd(ADC1, ENABLE);//ʹ��ָ����ADC1
  ADC_ResetCalibration(ADC1);//��λָ����ADC1��У׼�Ĵ���
  while(ADC_GetResetCalibrationStatus(ADC1)); //��ȡADC1��λУ׼�Ĵ�����״̬,����״̬��ȴ�
  ADC_StartCalibration(ADC1); //��ʼָ��ADC1��У׼״̬
  while(ADC_GetCalibrationStatus(ADC1));//��ȡָ��ADC1��У׼����,����״̬��ȴ�
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
  ADC_ITConfig(ADC1,ADC_IT_EOC,ENABLE);//ʹ��ADC�ж�
  ADC_ExternalTrigConvCmd(ADC1, ENABLE); //ʹ��ADC���ⲿ��������ת������
}


/*******************************************************************************
* ��������: calculate_MCU_temperate
* ��������: ���㵱ǰ��Ƭ���ڲ����¶�
* �������: Value                   -- �ڲ��¶ȴ�����AD����ֵ
* �������: mcu_current_temperate   -- MCU��ǰ�¶Ȳ���ֵ
* ����˵������
*******************************************************************************/
float adc4_temp = 0.0;
float calculate_MCU_temperate (float Value)
{ 
  static const float mcu_25_temperate = 1.43;// MCU��25�ȵĵ���ֵ Ϊ1.43��
  static const float avg_slope = 0.0043;//��Ƭ���¶����ѹֵ���ߵ�ƽ��б��  4.3mV/���϶�
  adc4_temp = 3.3*Value/4096.0f;
  mcu_current_temperate = (((mcu_25_temperate-adc4_temp)/avg_slope) + 25.0);
  return (mcu_current_temperate); 
}

//����Ϊ�жϴ���������ʱ��2�ṩ500ns�Ķ�ʱ��500ns�ڲ�ADȡ40��mcu�¶ȴ������ϵ�ֵ��
/*******************************************************************************
* ��������: DMAChannel1_IRQHandler
* ��������: DMA�жϴ�����
* �������: ��
* �������: ��
* ����˵������
*******************************************************************************/
void DMA1_Channel1_IRQHandler(void)
{    
  //unsigned char i;
  //unsigned short sum;
  if(DMA_GetITStatus(DMA1_IT_TC1))  //��DMAͨ��1��������ж��н��м��
  {
    //for(i=0;i<1;i++)
    //{
    //    sum = ADC_Value[i];
    //}
  }
  //average = sum / 1;
  DMA_ClearITPendingBit(DMA1_IT_GL1);//��DMAͨ��1��
}


void Chip_ADC_Init()
{
  NVIC_InitTypeDef NVIC_InitStructure;
  ADC_GPIO_Init();
  ADC_Configuration();
  DMA_Configuration();
  /* Configure one bit for preemption priority */ 
  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;         
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;   
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;         
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            
  NVIC_Init(&NVIC_InitStructure);
}

