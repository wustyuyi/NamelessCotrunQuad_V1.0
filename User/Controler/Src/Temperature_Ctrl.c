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
#include "Temperature_Ctrl.h"

#define Temperature_Ctrl_Enable   1

#define Temperature_Setpoint   50//IMU���¿���50���϶�
const float Temp_Control_Unit[20]=
{1  ,1 ,1 ,0 ,0 ,0 , 0 ,50    ,30  ,0 ,80,  20.00  ,3.0   ,100.0  ,0    ,0 ,100 , 1 ,  1 ,  1 };//ˮƽά�ȷ�����ٶȿ����� 20 3 50  //  10  3  80
/*
1ƫ���޷���־��  2�����޷���־��3���ַ����־��   4������
5����            6ƫ�        7�ϴ�ƫ�       8ƫ���޷�ֵ��
9���ַ���ƫ��ֵ��10����ֵ       11�����޷�ֵ��    12���Ʋ���Kp��
13���Ʋ���Ki��   14���Ʋ���Kd�� 15�������������  16�ϴο����������
17������޷��ȣ� 18����ֿ���ʱ�Ļ�������
*/		
void Temperature_Ctrl_Init(void)
{
  Total_Controller.IMU_Temperature_Control.Err_Limit_Flag=(uint8)(Temp_Control_Unit[0]);//1ƫ���޷���־
  Total_Controller.IMU_Temperature_Control.Integrate_Limit_Flag=(uint8)(Temp_Control_Unit[1]);//2�����޷���־
  Total_Controller.IMU_Temperature_Control.Integrate_Separation_Flag=(uint8)(Temp_Control_Unit[2]);//3���ַ����־
  Total_Controller.IMU_Temperature_Control.Expect=Temp_Control_Unit[3];//4����
  Total_Controller.IMU_Temperature_Control.FeedBack=Temp_Control_Unit[4];//5����ֵ
  Total_Controller.IMU_Temperature_Control.Err=Temp_Control_Unit[5];//6ƫ��
  Total_Controller.IMU_Temperature_Control.Last_Err=Temp_Control_Unit[6];//7�ϴ�ƫ��
  Total_Controller.IMU_Temperature_Control.Err_Max=Temp_Control_Unit[7];//8ƫ���޷�ֵ
  Total_Controller.IMU_Temperature_Control.Integrate_Separation_Err=Temp_Control_Unit[8];//9���ַ���ƫ��ֵ
  Total_Controller.IMU_Temperature_Control.Integrate=Temp_Control_Unit[9];//10����ֵ
  Total_Controller.IMU_Temperature_Control.Integrate_Max=Temp_Control_Unit[10];//11�����޷�ֵ
  Total_Controller.IMU_Temperature_Control.Kp=Temp_Control_Unit[11];//12���Ʋ���Kp
  Total_Controller.IMU_Temperature_Control.Ki=Temp_Control_Unit[12];//13���Ʋ���Ki
  Total_Controller.IMU_Temperature_Control.Kd=Temp_Control_Unit[13];//14���Ʋ���Ki
  Total_Controller.IMU_Temperature_Control.Control_OutPut=Temp_Control_Unit[14];//15�����������
  Total_Controller.IMU_Temperature_Control.Last_Control_OutPut=Temp_Control_Unit[15];//16�ϴο����������
  Total_Controller.IMU_Temperature_Control.Control_OutPut_Limit=Temp_Control_Unit[16];//17�ϴο����������
  Total_Controller.IMU_Temperature_Control.Scale_Kp=Temp_Control_Unit[17];
  Total_Controller.IMU_Temperature_Control.Scale_Ki=Temp_Control_Unit[18];
  Total_Controller.IMU_Temperature_Control.Scale_Kd=Temp_Control_Unit[19];  
}

void Simulation_PWM_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin    = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode   = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed  = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);
}

#define Simulation_PWM_Period_MAX  100//100*1ms=0.1S
void Simulation_PWM_Output(uint16_t width)
{
#if Temperature_Ctrl_Enable
	uint16_t static cnt=0;
	cnt++;
	if(cnt>=Simulation_PWM_Period_MAX)  cnt=0;
  if(cnt<=width) GPIO_SetBits(GPIOA,GPIO_Pin_5);
	else GPIO_ResetBits(GPIOA,GPIO_Pin_5);
#else
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);
#endif
	
}


void Temperature_Ctrl(void)
{
#if Temperature_Ctrl_Enable
 uint16_t static cnt=0;
 cnt++;
 Total_Controller.IMU_Temperature_Control.Expect=Temperature_Setpoint;
 Total_Controller.IMU_Temperature_Control.FeedBack=WP_Sensor.temperature;
 if(cnt>=10)  //10*1ms=0.01S
 {
	 PID_Control(&Total_Controller.IMU_Temperature_Control);
	 Total_Controller.IMU_Temperature_Control.Control_OutPut=constrain_float(Total_Controller.IMU_Temperature_Control.Control_OutPut,0,Simulation_PWM_Period_MAX);
	 cnt=0;
 }
#else
	Total_Controller.IMU_Temperature_Control.Control_OutPut=0;
#endif
}

uint8_t Temperature_State_Check(void)
{
#if Temperature_Ctrl_Enable
  return (ABS(Total_Controller.IMU_Temperature_Control.Err))<=2.0f?1:0;
#else
	return 1;
#endif	
}


void Temperature_Ctrl_Run(void)
{
	Temperature_Ctrl();	
	Simulation_PWM_Output(Total_Controller.IMU_Temperature_Control.Control_OutPut);
}

