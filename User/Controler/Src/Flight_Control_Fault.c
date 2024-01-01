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
#include "Flight_Control_Fault.h"

Flight_Control_Fault_State  State_Breakdown;


#define DIVIDER_RES_MAX  100//��ѹ����1
#define DIVIDER_RES_MIN  10//��ѹ����2
#define DIVIDER_RES_SCALE (DIVIDER_RES_MAX+DIVIDER_RES_MIN)/DIVIDER_RES_MIN

float Battery_Valtage=0;
void Battery_Fault_Check(void)
{
  static uint16_t battery_fault_cnt=0;
  Battery_Valtage=(DIVIDER_RES_SCALE*ADC_Value[1]*3.3f)/4096;
  if(Battery_Valtage<Safe_Vbat/1000.0f)
  {
    battery_fault_cnt++;
    if(battery_fault_cnt>=100)//����100*5ms=500ms
    {
      State_Breakdown.Low_Voltage_Fault_Flag=true;
    }
  }
  else
  {
    battery_fault_cnt/=2;
    if(battery_fault_cnt==0)  State_Breakdown.Low_Voltage_Fault_Flag=false; 
  }
}

void Baro_Fault_Check(float baropress)
{
  static uint16_t baro_fault_cnt=0;
  static float last_baropress=0;
  static uint16_t baro_gap_cnt=0;
  baro_gap_cnt++;
  if(baro_gap_cnt>=40)//ÿ200ms���һ�Σ���Ϊ��ѹ�Ƹ������ڴ���5ms
  {
    baro_gap_cnt=0;
    if(last_baropress==baropress)
    {
      baro_fault_cnt++;
      if(baro_fault_cnt>5)  State_Breakdown.Baro_Fault_Flag=true;   
    }
    else
    {
      baro_fault_cnt/=2;
      if(baro_fault_cnt==0)  State_Breakdown.Baro_Fault_Flag=false; 
    }
    last_baropress=baropress; 
  }
}

void Accel_Fault_Check(Vector3f accel)
{
  static uint16_t accel_fault_cnt=0;
  static Vector3f last_accel={0};
  if(last_accel.x==accel.x
     &&last_accel.y==accel.y
       &&last_accel.z==accel.z)
  {
    accel_fault_cnt++;
    if(accel_fault_cnt>20)  State_Breakdown.Accel_Fault_Flag=true;   
  }
  else
  {
    accel_fault_cnt/=2;
    if(accel_fault_cnt==0)  State_Breakdown.Accel_Fault_Flag=false; 
  }
  last_accel=accel; 
}


void Gyro_Fault_Check(Vector3f gyro)
{
  static uint16_t gyro_fault_cnt=0;
  static Vector3f last_gyro={0};
  if(last_gyro.x==gyro.x
     &&last_gyro.y==gyro.y
       &&last_gyro.z==gyro.z)
  {
    gyro_fault_cnt++;
    if(gyro_fault_cnt>20)  State_Breakdown.Gyro_Fault_Flag=true;   
  }
  else
  {
    gyro_fault_cnt/=2;
    if(gyro_fault_cnt==0)  State_Breakdown.Gyro_Fault_Flag=false; 
  }
  last_gyro=gyro; 
}


void Compass_Fault_Check(Vector3f compass)
{
  static uint16_t compass_fault_cnt=0;
  static Vector3f last_compass={0};
  static uint16_t compass_gap_cnt=0;
  compass_gap_cnt++;
  if(compass_gap_cnt>=40)//ÿ200ms���һ�Σ���Ϊ�����Ƹ������ڴ���5ms
  {
    compass_gap_cnt=0;
    if(last_compass.x==compass.x
       &&last_compass.y==compass.y
         &&last_compass.z==compass.z)
    {
      compass_fault_cnt++;
      if(compass_fault_cnt>10)  State_Breakdown.Compass_Fault_Flag=true;   
    }
    else
    {
      compass_fault_cnt/=2;
      if(compass_fault_cnt==0)  State_Breakdown.Compass_Fault_Flag=false; 
    }
    last_compass=compass;
  }
}



void Ultrasonic_Fault_Check(float ultrasonic)
{
  static uint16_t ultrasonic_fault_cnt=0;
  static float last_ultrasonic;
  if(last_ultrasonic==ultrasonic)
  {
    ultrasonic_fault_cnt++;
    if(ultrasonic_fault_cnt>20)  State_Breakdown.Ultrasonic_Fault_Flag=true;   
  }
  else
  {
    ultrasonic_fault_cnt/=2;
    if(ultrasonic_fault_cnt==0)  State_Breakdown.Ultrasonic_Fault_Flag=false; 
  }
  last_ultrasonic=ultrasonic; 
}



void Opticalflow_Fault_Check(int16_t opticalflow_x,int16_t opticalflow_y)
{
  static uint16_t opticalflow_fault_cnt=0;
  static uint16_t opticalflow_fault_zero_cnt=0; 
  static int16_t last_opticalflow_x,last_opticalflow_y;
  if(last_opticalflow_x==opticalflow_x
     &&last_opticalflow_y==opticalflow_y
       &&last_opticalflow_x!=0
         &&last_opticalflow_y!=0)
  {
    opticalflow_fault_cnt++;
    if(opticalflow_fault_cnt>20)  State_Breakdown.Opticalflow_Fault_Flag=true;   
  }
  else if(last_opticalflow_x==opticalflow_x
          &&last_opticalflow_y==opticalflow_y
            &&last_opticalflow_x==0
              &&last_opticalflow_y==0)
  {
    opticalflow_fault_zero_cnt++;
    if(opticalflow_fault_zero_cnt>100)  State_Breakdown.Opticalflow_Fault_Flag=true;   
  }
  else
  {
    opticalflow_fault_cnt/=2;
    opticalflow_fault_zero_cnt/=2;
    if(opticalflow_fault_cnt==0)  State_Breakdown.Opticalflow_Fault_Flag=false; 
  }
  last_opticalflow_x=opticalflow_x;
  last_opticalflow_y=opticalflow_y;
}


Vector3f Accel,Gyro,Compass;
void Flight_Control_Fault_ALL(void)
{
  Battery_Fault_Check();
  Baro_Fault_Check(Altitude_Estimate);
  Accel_Fault_Check(Accel);
  Gyro_Fault_Check(Gyro);
  Compass_Fault_Check(Compass);
}


