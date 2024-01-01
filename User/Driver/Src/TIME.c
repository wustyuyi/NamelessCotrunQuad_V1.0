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
#include "Time.h"
void Timer1_Configuration(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_DeInit(TIM1);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
  TIM_TimeBaseStructure.TIM_Period=5000;
  TIM_TimeBaseStructure.TIM_Prescaler= (72-1);
  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
  TIM_ClearFlag(TIM1, TIM_FLAG_Update);
  TIM_ITConfig(TIM1,TIM_IT_Update|TIM_IT_Trigger,ENABLE);
  TIM_Cmd(TIM1, ENABLE);
}

Sensor WP_Sensor; 
Sensor_Health Sensor_Flag;
_Baro Baro_Show;
Testime Time1_Delta;
Testime T11;
Testime T22;
float ty=0;
uint16_t High_Okay_flag=0;
/***************************************************
������: void TIM1_UP_IRQHandler(void)
˵��:	ϵͳ���ȶ�ʱ��
���:	��
����:	��
��ע:	���Ĳ��֣��������ɼ����˲���
        ��̬���㡢���Ե��������Ƶȶ����������      
ע���ߣ�����С��
****************************************************/
void TIM1_UP_IRQHandler(void)//5msˢ��һ��
{
  if( TIM_GetITStatus(TIM1,TIM_IT_Update)!=RESET )
  {
		Test_Period(&T11);
    Test_Period(&Time1_Delta);//ϵͳ����ʱ�������
    NRF24L01_RC();//ң������ѯ���գ����ж˷�ʽ
    /*************���ٶȼơ��������������ɼ�***********/
    GET_MPU_DATA();//1.4ms
    /*************������+��ѹ��״̬������***********/
    Compass_Tradeoff();//����ʹ�����ô����ƣ�Ĭ�����ã�ʹ������ʱע��������ת��ϵ
    SPL06_001_StateMachine();
    /*************��̬����***********/
    AHRSUpdate_GraDes_TimeSync(X_w_av,Y_w_av,Z_w_av,X_g_av,Y_g_av,Z_g_av);
    //DirectionConsineMatrix(DCM_Gyro,DCM_Acc,MagN);//DCM��̬���㣬�ο�APM
    Optflow_Statemachine();//����״̬������ʼ��ʱ���ڹ�������
    SINS_Prepare();//�õ�������Ե���ϵ�������˶����ٶ�
    if(High_Okay_flag==1)//�߶ȹߵ��ں�
    {
      /*
      �����ڳ�����ʱ���õڶ����ںϷ�ʽ��
      ��Ϊ���۲⴫��������ѹ�ơ����������л�ʱ�����׻����˲����м����
      ��Ҫ�ں�һ��ʱ�䣬�������������������˲�����ֱ���л�
      */  
      //Strapdown_INS_High();//1�����׻����˲��ߵ��ں�
      Strapdown_INS_High_Kalman();//2���������˲��ߵ��ں�
    } 
    if(GPS_ISR_CNT>=300&&GPS_Update_finished==1)//GPS_PVT��������Ϻ󣬿�ʼ����
    {
      GPS_PVT_Parse();//GPS��������֡����
      Set_GPS_Home();//����Home��
			GPS_Update_finished=0;
    }  
    if(GPS_Home_Set==1)//Home��������
    {
      Filter_Horizontal();//ˮƽ����ߵ��ں�
    }
    Total_Control();//�ܿ�������ˮƽλ��+ˮƽ�ٶ�+��̬���Ƕ�+���ٶȣ����������߶�λ��+�߶��ٶ�+�߶ȼ��ٶȿ�����
    Control_Output();//�����������
		Temperature_Ctrl_Run();		
		Accel_Calibration_Check();//���ٶȱ궨���
		Mag_Calibration_Check();//�����Ʊ궨���
		ESC_Calibration_Check();//���У׼��⣬�������Ҫ�ε���غ����
		Horizontal_Calibration_Check();//����ˮƽУ׼��⣬ȷ�����ܷ�����ˮƽ������ٲ���
    Angle_Calculate();//���ٶȼ�ŷ���Ǽ��㣬��û��ת̨ƽ̨ʱ��������Ϊ��̬����Ĺ۲�Ƕ�
    Bling_Working(Bling_Mode);//״ָ̬ʾ��		
    Usb_Hid_Receive();//USB���⴮�ڲ�ѯ����
    NCLink_SEND_StateMachine();//�������µ���վ����״̬��		
    /*
		DMA_Send_Vcan(NamelessQuad.Position[_YAW],
									NamelessQuad.Speed[_YAW],
									NamelessQuad.Acceleration[_YAW],
									WP_Sensor.baro_altitude,
									0,Roll_Gyro,
									0,0);//DMA���䣬ֻʹ��ɽ����λ��
   */		
    Flight_Control_Fault_ALL();//�ɿ�״̬���
		
		Test_Period(&T22);	
		ty=T22.Now_Time-T11.Now_Time;
		
		
    TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
  }
}
