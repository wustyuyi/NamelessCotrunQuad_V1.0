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
#include "US_100.h"
float US_100_Distance(uint8 MSB,uint8 LSB)
{
  return (256*(MSB)+(LSB))/1.0;
}

float US_100_Temperature(uint8 data)
{
  return (data-45)/1.0;
}


Butter_BufferData Butter_Buffer_HCSR04;
Butter_Parameter Butter_2HZ_Parameter_HCSR04;
u32 Test_Cnt1[2]={0},Test_Cnt2[2]={0},Test_Delta=0;
uint8 HC_SR04_StartFlag=0;
float HC_SR04_Distance_Temp=0,HC_SR04_Distance=0,HC_SR04_Distance_Filter=0,HC_SR04_Bubble_Distance=0;
float HC_SR04_Distance_Record[5]={0};
float HC_SR04_Distance_Div[5]={0};
float HCSR04_Data[5];
uint16 HC_SR04_RSSI=1;
uint16 Sample_Cnt=0;
void HC_SR04_Start(void)
{
  float tempa,tempb,tempc,max,min;//���ڷ������˲�
  HC_SR04_RSSI--;
  if(HC_SR04_RSSI<=254&&HC_SR04_StartFlag==1)//ͨѶ�쳣���ж���ռ��ʱ����·�Ӵ�������
  {
    HC_SR04_StartFlag=0;
    Sample_Cnt=0;
    HC_SR04_OUT_LOW;//��ǿ������һ��ʱ��
    //EXTI->IMR &=~EXTI_Line1;//�ر��ⲿ�ж�
    EXTI_ClearITPendingBit(EXTI_Line1);
    Delay_Us(10);
  }
  else//��������
  {   
    if(Test_Delta<=Effective_Height_Time_Max)  //�޷�Լ24000->400cm,15000->250cm��11765->200cm  5882->100
    {
      HC_SR04_Distance_Temp=Test_Delta*(340)/20000.0;
    }
    
    for(int16 i=5;i>0;i--)
    {
      HCSR04_Data[i]=HCSR04_Data[i-1];
    }
    HCSR04_Data[0]=HC_SR04_Distance_Temp;
    
    /******************************************/
    //��ֵ�˲�����֤�õ����ݲ����䣬����������Ծʱ��΢������쳣
    HC_SR04_Distance_Record[0]=HC_SR04_Distance_Temp;
    tempa=HC_SR04_Distance_Record[2];
    tempb=HC_SR04_Distance_Record[1];
    tempc=HC_SR04_Distance_Record[0];
    max = tempa > tempb ? tempa:tempb;
    max = max > tempc ? max:tempc;
    min = tempa < tempb ? tempa:tempb;
    min = min < tempc ? min:tempc;
    if(tempa > min && tempa < max)    HC_SR04_Distance_Record[0] = tempa;
    if(tempb > min  && tempb < max )  HC_SR04_Distance_Record[0] = tempb;
    if(tempc > min  &&  tempc < max)  HC_SR04_Distance_Record[0] = tempc;
    for(int16 i=5;i>0;i--)
    {
      HC_SR04_Distance_Record[i] = HC_SR04_Distance_Record[i-1];  
    }
       
    HC_SR04_Distance_Div[0]=HCSR04_Data[4]-HCSR04_Data[3];
    HC_SR04_Distance_Div[1]=HCSR04_Data[3]-HCSR04_Data[2];
    HC_SR04_Distance_Div[2]=HCSR04_Data[2]-HCSR04_Data[1];
    HC_SR04_Distance_Div[3]=HCSR04_Data[1]-HCSR04_Data[0];
    //if(ABS(HC_SR04_Distance_Div[0])<15
    //   &&ABS(HC_SR04_Distance_Div[1])<15
    //     &&ABS(HC_SR04_Distance_Div[2])<15
    //       &&ABS(HC_SR04_Distance_Div[3])<15
     //       &&ABS(HC_SR04_Distance_Div[0])<=1.0*ABS(NamelessQuad.Speed[_YAW])) 
    //{
        HC_SR04_Bubble_Distance=HC_SR04_Distance_Temp;
        HC_SR04_Distance=HC_SR04_Bubble_Distance;
    //}
    
    HC_SR04_Distance_Filter=LPButterworth(HC_SR04_Distance,&Butter_Buffer_HCSR04,&Butter_2HZ_Parameter_HCSR04);
    if(HC_SR04_Distance<=User_Height_Max&&HC_SR04_Distance>0)  Sensor_Flag.Hcsr04_Health=1;
    else  Sensor_Flag.Hcsr04_Health=0; 
  }
  
  if(HC_SR04_StartFlag==0)
  {
    HC_SR04_OUT_HIGH;
    Delay_Us(20);//������10us,�����ʱʱ��Լ����15us
    HC_SR04_OUT_LOW;
    HC_SR04_StartFlag=1;
    Sample_Cnt=0;
    HC_SR04_UP();
    HC_SR04_RSSI=255;
  }
}

void HC_SR04_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  //EXTI_InitTypeDef EXTI_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//��������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  GPIO_SetBits(GPIOA,GPIO_Pin_0);//��ʼ����
  delay_ms(10);//��ʼ��������һ��ʱ��
  HC_SR04_StartFlag=0;
  Sample_Cnt=0;
  
  Set_Cutoff_Frequency(10, 4 ,&Butter_2HZ_Parameter_HCSR04);
}

void HC_SR04_UP()
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//��������
  //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource1);
  EXTI_InitStructure.EXTI_Line = EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd= ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  
  EXTI->IMR |=EXTI_Line1;//�ر��ⲿ�ж�
  
}

void HC_SR04_DN()
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
  //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource1);
  EXTI_InitStructure.EXTI_Line = EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd= ENABLE;
  EXTI_Init(&EXTI_InitStructure);
}


uint8_t HCSR_04_Update_Flag=0;
void EXTI1_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line1) != RESET)
  {   
    if(Sample_Cnt==0)//��������
    {
      //Test_Cnt1=10000*TIME_ISR_CNT+TIM2->CNT/2;
      Test_Cnt1[0]=TIME_ISR_CNT;//10ms
      Test_Cnt1[1]=TIM2->CNT;//us
      HC_SR04_DN();
      Sample_Cnt++;
    }
    else if(Sample_Cnt==1)//���½���
    {
      //Test_Cnt2=10000*TIME_ISR_CNT+TIM2->CNT/2;
      Test_Cnt2[0]=TIME_ISR_CNT;//10ms
      Test_Cnt2[1]=TIM2->CNT;//us
      HC_SR04_StartFlag=0;
      Test_Delta=10000*(Test_Cnt2[0]-Test_Cnt1[0])+(Test_Cnt2[1]-Test_Cnt1[1]);//us
      EXTI->IMR &=~EXTI_Line1;//�ر��ⲿ�ж�
      HCSR_04_Update_Flag=1;
    }
    EXTI_ClearITPendingBit(EXTI_Line1);
  }
}


uint8 HC_SR04_Cnt=0;
void HC_SR04_Statemachine(void)
{
  HC_SR04_Cnt++;
  if(HC_SR04_Cnt>=20)//100ms
  {
    HC_SR04_Start();//�������������������ⲿ�ж����洦��
    HC_SR04_Cnt=0;
  }
}

