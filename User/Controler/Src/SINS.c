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
#include "SINS.h"
#include "Earth_Declination.h"
#include "math.h"
SINS NamelessQuad;
SINS Origion_NamelessQuad;
SINS FilterBefore_NamelessQuad;
SINS FilterAfter_NamelessQuad;
SINS Filter_Feedback_NamelessQuad;
float SpeedDealt[3]={0};
float Sin_Pitch=0,Sin_Roll=0,Sin_Yaw=0;
float Cos_Pitch=0,Cos_Roll=0,Cos_Yaw=0;
float Baro_Climbrate=0;
float Acceleration_Length=0;
Vector2f SINS_Accel_Body={0,0};
float Acce_History[3][100]={0};
float Declination=0;//�����ƫ��
void  SINS_Prepare(void)
{
  
  //static uint16_t Acce_Save_Cnt=0;
  //uint16_t i=0;
  Vector2f SINS_Accel_Earth={0,0};
  Vector3f Body_Frame,Earth_Frame;
  /*Z-Y-Xŷ����ת�������Ҿ���
  //Pitch Roll  Yaw �ֱ��Ӧ�� �� ��
  
  X����ת����
  R������
  {1      0        0    }
  {0      cos��    sin��}
  {0    -sin��    cos�� }
  
  Y����ת����
  R���ȣ�
  {cos��     0        -sin��}
  {0         1        0     }
  {sin��     0        cos��}
  
  Z����ת����
  R���ȣ�
  {cos��      sin��       0}
  {-sin��     cos��       0}
  {0          0           1 }
  
  ��Z-Y-X˳����:
  ��������ϵ����������ϵ����ת����R(b2n)
  R(b2n) =R(��)^T*R(��)^T*R(��)^T
  
  R=
  {cos��*cos��     -cos��*sin��+sin��*sin��*cos��        sin��*sin��+cos��*sin��*cos��}
  {cos��*sin��     cos��*cos�� +sin��*sin��*sin��       -cos��*sin��+cos��*sin��*sin��}
  {-sin��          cos��sin ��                          cos��cos��                   }
  */
  /*
  Origion_NamelessQuad.Acceleration[_YAW] =
  -Sin_Roll* Acce_Control[0]
  + Sin_Pitch *Cos_Roll * Acce_Control[1]
  + Cos_Pitch * Cos_Roll *Acce_Control[2];
  
  Origion_NamelessQuad.Acceleration[_PITCH]=
  Cos_Yaw* Cos_Roll * Acce_Control[0]
  +(Sin_Pitch*Sin_Roll*Cos_Yaw-Cos_Pitch * Sin_Yaw) * Acce_Control[1]
  +(Sin_Pitch * Sin_Yaw+Cos_Pitch * Sin_Roll * Cos_Yaw)*Acce_Control[2];
  
  Origion_NamelessQuad.Acceleration[_ROLL]=
  Sin_Yaw* Cos_Roll * Acce_Control[0]
  +(Sin_Pitch * Sin_Roll * Sin_Yaw +Cos_Pitch * Cos_Yaw) * Acce_Control[1]
  + (Cos_Pitch * Sin_Roll * Sin_Yaw - Sin_Pitch * Cos_Yaw)*Acce_Control[2];
  */
  Body_Frame.x=Acce_SINS[0];//X_Origion;//Acce_Control[0];
  Body_Frame.y=Acce_SINS[1];//Y_Origion;//Acce_Control[1];
  Body_Frame.z=Acce_SINS[2];//Z_Origion;//Acce_Control[2];
  Vector_From_BodyFrame2EarthFrame(&Body_Frame,&Earth_Frame);
  Origion_NamelessQuad.Acceleration[_YAW]=Earth_Frame.z;
  Origion_NamelessQuad.Acceleration[_PITCH]=Earth_Frame.x;
  Origion_NamelessQuad.Acceleration[_ROLL]=Earth_Frame.y;
  
  
  Origion_NamelessQuad.Acceleration[_YAW]*=AcceGravity/AcceMax;
  Origion_NamelessQuad.Acceleration[_YAW]-=AcceGravity;//��ȥ�������ٶ�
  Origion_NamelessQuad.Acceleration[_YAW]*=100;//���ٶ�cm/s^2
  
  Origion_NamelessQuad.Acceleration[_PITCH]*=AcceGravity/AcceMax;
  Origion_NamelessQuad.Acceleration[_PITCH]*=100;//���ٶ�cm/s^2
  
  Origion_NamelessQuad.Acceleration[_ROLL]*=AcceGravity/AcceMax;
  Origion_NamelessQuad.Acceleration[_ROLL]*=100;//���ٶ�cm/s^2
  
  
  Acceleration_Length=sqrt(Origion_NamelessQuad.Acceleration[_YAW]*Origion_NamelessQuad.Acceleration[_YAW]
                           +Origion_NamelessQuad.Acceleration[_PITCH]*Origion_NamelessQuad.Acceleration[_PITCH]
                             +Origion_NamelessQuad.Acceleration[_ROLL]*Origion_NamelessQuad.Acceleration[_ROLL]);
  
  /******************************************************************************/
  //�����˻��ڵ�������ϵ�µ���������������������˶����ٶ���ת����ǰ������˶����ٶ�:��ͷ(����)+���
  
  SINS_Accel_Earth.x=Origion_NamelessQuad.Acceleration[_PITCH];//�ص�������ϵ�����������˶����ٶ�,��λΪCM
  SINS_Accel_Earth.y=Origion_NamelessQuad.Acceleration[_ROLL];//�ص�������ϵ�����������˶����ٶ�,��λΪCM
  
  
  SINS_Accel_Body.x=SINS_Accel_Earth.x*Cos_Yaw+SINS_Accel_Earth.y*Sin_Yaw;  //��������˶����ٶ�  X������
  SINS_Accel_Body.y=-SINS_Accel_Earth.x*Sin_Yaw+SINS_Accel_Earth.y*Cos_Yaw; //��ͷ�����˶����ٶ�  Y������
  
  /*
  Acce_Save_Cnt++;
  if(Acce_Save_Cnt>=2)//10ms
  {
  for(i=99;i>0;i--)
  {
  Acce_History[_PITCH][i]=Acce_History[_PITCH][i-1];
  Acce_History[_ROLL][i]=Acce_History[_ROLL][i-1];
  Acce_History[_YAW][i]=Acce_History[_YAW][i-1];
}
  Acce_History[_PITCH][0]=Origion_NamelessQuad.Acceleration[_PITCH];
  Acce_History[_ROLL][0]=Origion_NamelessQuad.Acceleration[_ROLL];
  Acce_History[_YAW][0]=Origion_NamelessQuad.Acceleration[_YAW];
  Acce_Save_Cnt=0;
}
  */
}


/******************************************
ԭʼ�˶����ٶȷ���Ϊ�����췽��
Origion_NamelessQuad.Acceleration[_ROLL]
Ϊ������������������˶����ٶ�
Origion_NamelessQuad.Acceleration[_PITCH]
Ϊ������������������˶����ٶ�
Origion_NamelessQuad.Acceleration[_YAW]
Ϊ�������š��졯������˶����ٶ�

��������������E����������N�������죨U���˶�ʱ�����ٶȷ���Ϊ��
U�����졢��ѹ�߶ȡ�_YAW��
*
*
*
*
*
*
* * * * * * * * * *N��������γ�߷���_ROLL��
*
*
*
*
*
*
E�����������߷���_PITCH��
*/

/*****************�㷨�������ͽ���***************************************************
1����������ƪ֮�ߵ����ٶ�+�ٶ�+λ�����׻����ںϷ���:
http://blog.csdn.net/u011992534/article/details/61924200
2��������ߵ��ں�֮�۲⴫�����ͺ���������������˹��ͨ�˲������
����ѹ��MS5611��GPSģ��M8N����������PX4FLOW�ȣ�:
http://blog.csdn.net/u011992534/article/details/73743955
3����APMԴ�����GPS����ѹ�ƹߵ��ں�
http://blog.csdn.net/u011992534/article/details/78257684
**********************************************************************************/
float pos_correction[3]={0,0,0};
float acc_correction[3]={0,0,0};
float vel_correction[3]={0,0,0};
/****��ѹ�����׻����˲����������ο���Դ�ɿ�APM****/
//#define TIME_CONTANST_ZER       1.5f
float TIME_CONTANST_ZER=3.5f;//3.0
#define K_ACC_ZER 	        (1.0f / (TIME_CONTANST_ZER * TIME_CONTANST_ZER * TIME_CONTANST_ZER))
#define K_VEL_ZER	        (3.0f / (TIME_CONTANST_ZER * TIME_CONTANST_ZER))
#define K_POS_ZER               (3.0f / TIME_CONTANST_ZER)
#define MS5611_Sync_Cnt 10
#define SPL06_Sync_Cnt 20
#define FBM320_Sync_Cnt 10
#define HCSR04_Sync_Cnt 10//20
uint16 High_Delay_Cnt=0;

float Altitude_Dealt=0;
float Altitude_Estimate=0;
Testime SINS_High_Delta;
float Delta_T;
void Strapdown_INS_High()
{
  uint16 Cnt=0;
  static uint16_t Save_Cnt=0;
  Save_Cnt++;//���ݴ洢����
  Test_Period(&SINS_High_Delta);
  Delta_T=SINS_High_Delta.Time_Delta/1000.0;
  
  Observation_Tradeoff(HC_SR04);  
  
  //�ɹ۲�������ѹ�ƣ��õ�״̬���
  Altitude_Dealt=Altitude_Estimate-NamelessQuad.Pos_History[_YAW][High_Delay_Cnt];//��ѹ��(������)��SINS�������Ĳ��λcm
  //��·���ַ����������ߵ�
  acc_correction[_YAW] +=Altitude_Dealt* K_ACC_ZER*Delta_T ;//���ٶȽ�����
  vel_correction[_YAW] +=Altitude_Dealt* K_VEL_ZER*Delta_T ;//�ٶȽ�����
  pos_correction[_YAW] +=Altitude_Dealt* K_POS_ZER*Delta_T ;//λ�ý�����
  //���ٶȼƽ��������
  NamelessQuad.Last_Acceleration[_YAW]=NamelessQuad.Acceleration[_YAW];//��һ�μ��ٶ���
  NamelessQuad.Acceleration[_YAW]=Origion_NamelessQuad.Acceleration[_YAW]+acc_correction[_YAW];
  //�ٶ�������������£����ڸ���λ��,���ڲ���h=0.005,��Խϳ���
  //������ö����������������΢�ַ��̣��������ø��߽׶Σ���Ϊ���ٶ��źŷ�ƽ��
  SpeedDealt[_YAW]=(NamelessQuad.Last_Acceleration[_YAW]
                    +NamelessQuad.Acceleration[_YAW])*Delta_T/2.0;
  //ԭʼλ�ø���
  Origion_NamelessQuad.Position[_YAW]+=(NamelessQuad.Speed[_YAW]+0.5*SpeedDealt[_YAW])*Delta_T;
  //λ�ý��������
  NamelessQuad.Position[_YAW]=Origion_NamelessQuad.Position[_YAW]+pos_correction[_YAW];
  //ԭʼ�ٶȸ���
  Origion_NamelessQuad.Speed[_YAW]+=SpeedDealt[_YAW];
  //�ٶȽ��������
  NamelessQuad.Speed[_YAW]=Origion_NamelessQuad.Speed[_YAW]+vel_correction[_YAW];
  
  if(Save_Cnt>=1)//20ms
  {
    for(Cnt=Num-1;Cnt>0;Cnt--)//20ms����һ��
    {
      NamelessQuad.Pos_History[_YAW][Cnt]=NamelessQuad.Pos_History[_YAW][Cnt-1];
    }
    NamelessQuad.Pos_History[_YAW][0]=NamelessQuad.Position[_YAW];
    Save_Cnt=0;
  }
}




#define KALMAN_DT 0.005f
float R[2]={5.0e-4f,6.0e-4f};//float R[2]={5.0e-4f,3.0e-4f};//{5.0e-4f,3.0e-4f}
float Q=30;//100  150  30
float Q_Baro=150;
float Q_Tofsense=30;
float Acce_Bias_Gain[3]={
  0.0005,//0.001
  0.0005,//0.001
  0.0005,//0.001
};
float Pre_conv[4]=
{
  0.18,0.1,//0.001,0,
  0.1,0.18//0,0.001
};//��һ��Э����
void  KalmanFilter(float Observation,//λ�ù۲���
                   uint16 Pos_Delay_Cnt,//�۲⴫������ʱ��
                   SINS *Ins_Kf,//�ߵ��ṹ��
                   float System_drive,//ϵͳԭʼ���������ߵ����ٶ�
                   float *R,
                   float Q,
                   float dt,
                   uint16 N,
                   uint8_t update_flag)
{
  uint16 Cnt=0;
  static uint16 Speed_Sync_Cnt=0;
  float Temp_conv[4]={0};//����Э����
  float Conv_Z=0,Z_Cor=0;
  float k[2]={0};//�������
  float Ctemp=0;
	//����״̬
	Ins_Kf->Acceleration[N]=System_drive;
	Ins_Kf->Acceleration[N]=Ins_Kf->Acce_Bias[N]+Ins_Kf->Acceleration[N];
	Ins_Kf->Position[N] +=Ins_Kf->Speed[N]*dt+(Ins_Kf->Acceleration[N]*dt*dt)/2.0;
	Ins_Kf->Speed[N]+=Ins_Kf->Acceleration[N]*dt;
	if(update_flag==1)
	{
		//����Э����
		Ctemp=Pre_conv[1]+Pre_conv[3]*dt;
		Temp_conv[0]=Pre_conv[0]+Pre_conv[2]*dt+Ctemp*dt+R[0];
		Temp_conv[1]=Ctemp;
		Temp_conv[2]=Pre_conv[2]+Pre_conv[3]*dt;;
		Temp_conv[3]=Pre_conv[3]+R[1];
		//���㿨��������
		Conv_Z=Temp_conv[0]+Q;
		k[0]=Temp_conv[0]/Conv_Z;
		k[1]=Temp_conv[2]/Conv_Z;
		//�ں��������
		Z_Cor=Observation-Ins_Kf->Pos_History[N][Pos_Delay_Cnt];
		//Z_Cor=Positional-*Position;
		Ins_Kf->Position[N] +=k[0]*Z_Cor;
		Ins_Kf->Speed[N] +=k[1]*Z_Cor;
		Ins_Kf->Acce_Bias[N]+=Acce_Bias_Gain[_YAW]*Z_Cor;
		Ins_Kf->Acce_Bias[N]=constrain_float(Ins_Kf->Acce_Bias[N],-200,200);
		//����״̬Э�������
		Pre_conv[0]=(1-k[0])*Temp_conv[0];
		Pre_conv[1]=(1-k[0])*Temp_conv[1];
		Pre_conv[2]=Temp_conv[2]-k[1]*Temp_conv[0];
		Pre_conv[3]=Temp_conv[3]-k[1]*Temp_conv[1]; 
	}
  
  for(Cnt=Num-1;Cnt>0;Cnt--)//5ms����һ��
  {
    Ins_Kf->Pos_History[N][Cnt]=Ins_Kf->Pos_History[N][Cnt-1];
  }
  Ins_Kf->Pos_History[N][0]=Ins_Kf->Position[N];
  
  Speed_Sync_Cnt++;
  if(Speed_Sync_Cnt>=20)//100ms����һ��
  {
  for(Cnt=Num-1;Cnt>0;Cnt--)
  {
    Ins_Kf->Vel_History[N][Cnt]=Ins_Kf->Vel_History[N][Cnt-1];
  }
  Speed_Sync_Cnt=0;
  }
  Ins_Kf->Vel_History[N][0]=Ins_Kf->Speed[N];
}

void Alt_SINS_Init(void)
{
	uint16_t _cnt=0;
	if(Sensor_Flag.Hcsr04_Health==1)
	{
		NamelessQuad.Position[_YAW]=HC_SR04_Distance;
		for(_cnt=Num-1;_cnt>0;_cnt--){NamelessQuad.Pos_History[_YAW][_cnt]=HC_SR04_Distance;}
		NamelessQuad.Pos_History[_YAW][0]=HC_SR04_Distance;
		Total_Controller.High_Position_Control.Expect=HC_SR04_Distance;//���ߵ��߶�����Ϊ�����߶ȣ����ҽ�����һ��
		Origion_NamelessQuad.Position[_YAW]=HC_SR04_Distance;
		Origion_NamelessQuad.Speed[_YAW]=0;
		Q=Q_Tofsense;	
	}
	else
	{
		NamelessQuad.Position[_YAW]=WP_Sensor.baro_altitude;
		for(_cnt=Num-1;_cnt>0;_cnt--){NamelessQuad.Pos_History[_YAW][_cnt]=WP_Sensor.baro_altitude;}
		NamelessQuad.Pos_History[_YAW][0]=WP_Sensor.baro_altitude;
		Total_Controller.High_Position_Control.Expect=WP_Sensor.baro_altitude;//���ߵ��߶�����Ϊ�����߶ȣ����ҽ�����һ��
		Origion_NamelessQuad.Position[_YAW]=WP_Sensor.baro_altitude;
		Origion_NamelessQuad.Speed[_YAW]=0;
		Q=Q_Baro;
	}
}

uint8_t Observation_Update_Flag=0;
void Observation_Tradeoff(uint8_t HC_SR04_Enable)
{
  static uint8_t observation_flag=1,last_observation_flag=1;
  uint16 Cnt=0;
  last_observation_flag=observation_flag;
	
	if(Sensor_Flag.Hcsr04_Health==1)
	{
		Altitude_Estimate=HC_SR04_Distance*Cos_Roll*Cos_Pitch;
		High_Delay_Cnt=HCSR04_Sync_Cnt;
		observation_flag=2;
		//if(HCSR_04_Update_Flag==1)
		//{
		//	Observation_Update_Flag=HCSR_04_Update_Flag;
		//	HCSR_04_Update_Flag=0;
		//}
		Observation_Update_Flag=1;
		Q=Q_Tofsense;	
	}
	else
	{
		Altitude_Estimate=SPL06_001_Filter_high;//�߶ȹ۲���
		High_Delay_Cnt=SPL06_Sync_Cnt;
		Observation_Update_Flag=1;
		observation_flag=1;
		Q=Q_Baro;	
	} 
	
	if(observation_flag==2&&last_observation_flag==1)//��ѹ���г�����
	{
		NamelessQuad.Position[_YAW]=HC_SR04_Distance*Cos_Roll*Cos_Pitch;
		for(Cnt=Num-1;Cnt>0;Cnt--){NamelessQuad.Pos_History[_YAW][Cnt]=HC_SR04_Distance*Cos_Roll*Cos_Pitch;}
		NamelessQuad.Pos_History[_YAW][0]=HC_SR04_Distance*Cos_Roll*Cos_Pitch;
		Total_Controller.High_Position_Control.Expect=HC_SR04_Distance*Cos_Roll*Cos_Pitch;//���ߵ��߶�����Ϊ�����߶ȣ����ҽ�����һ��
		
		Origion_NamelessQuad.Position[_YAW]=HC_SR04_Distance*Cos_Roll*Cos_Pitch;
		Origion_NamelessQuad.Speed[_YAW]=0;
		acc_correction[_YAW]=0 ;//���ٶȽ�����
		vel_correction[_YAW]=0;//�ٶȽ�����
		pos_correction[_YAW]=0;
	}
	else if(observation_flag==1&&last_observation_flag==2)//����������ѹ��
	{
		NamelessQuad.Position[_YAW]=Altitude_Estimate;
		for(Cnt=Num-1;Cnt>0;Cnt--){NamelessQuad.Pos_History[_YAW][Cnt]=Altitude_Estimate;}
		NamelessQuad.Pos_History[_YAW][0]=Altitude_Estimate;
		Total_Controller.High_Position_Control.Expect=Altitude_Estimate;//���ߵ��߶�����Ϊ�����߶ȣ����ҽ�����һ��
		
		Origion_NamelessQuad.Position[_YAW]=Altitude_Estimate;
		Origion_NamelessQuad.Speed[_YAW]=0;
		acc_correction[_YAW]=0 ;//���ٶȽ�����
		vel_correction[_YAW]=0;//�ٶȽ�����
		pos_correction[_YAW]=0;
	}
}

void Strapdown_INS_High_Kalman(void)
{
  Test_Period(&SINS_High_Delta);
  Delta_T=SINS_High_Delta.Time_Delta/1000.0;
  Observation_Tradeoff(HC_SR04);
  if(Gyro_Safety_Calibration_Flag==1)
	{
		KalmanFilter(Altitude_Estimate,//λ�ù۲���
								 High_Delay_Cnt,//�۲⴫������ʱ��
								 &NamelessQuad,//�ߵ��ṹ��
								 Origion_NamelessQuad.Acceleration[_YAW],//ϵͳԭʼ���������ߵ����ٶ�
								 R,
								 Q,
								 Delta_T,//0.005f,
								 _YAW,
								 1);
	}
	else
	{
		Alt_SINS_Init();
		NamelessQuad.Acce_Bias[_YAW]=-Origion_NamelessQuad.Acceleration[_YAW];
	}
}


/*************************���¼�������ͶӰ��������Դ��APM3.2 AP.Math.c�ļ�******************************/
// constrain a value
float constrain_float(float amt, float low, float high){
  return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}

int16_t constrain_int16_t(int16_t amt, int16_t low, int16_t high){
  return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}

float longitude_scale(Location loc)
{
  static int32_t last_lat;
  static float scale = 1.0;
  //�Ƚ�����γ�����ֵ�������ظ��������Һ���
  if (ABS(last_lat - loc.lat) < 100000) {
    // we are within 0.01 degrees (about 1km) of the
    // same latitude. We can avoid the cos() and return
    // the same scale factor.
    return scale;
  }
  scale = cosf(loc.lat * 1.0e-7f * DEG_TO_RAD);
  scale = constrain_float(scale, 0.01f, 1.0f);
  last_lat = loc.lat;
  return scale;
}
/*
return the distance in meters in North/East plane as a N/E vector
from loc1 to loc2
*/
Vector2f location_diff(Location loc1,Location loc2)
{
  Vector2f Location_Delta;
  Location_Delta.x=(loc2.lat - loc1.lat) * LOCATION_SCALING_FACTOR;//���뵥λΪm
  Location_Delta.y=(loc2.lng - loc1.lng) * LOCATION_SCALING_FACTOR * longitude_scale(loc2);//���뵥λΪm
  return Location_Delta;
}
// square
float sq(float v) {return v*v;}
// 2D vector length
float pythagorous2(float a, float b) {	return sqrtf(sq(a)+sq(b));}
// 3D vector length
float pythagorous3(float a, float b, float c) {return sqrtf(sq(a)+sq(b)+sq(c));}
// return distance in meters between two locations
float get_distance(Location loc1,Location loc2){
  float dlat              = (float)(loc2.lat - loc1.lat);
  float dlong             = ((float)(loc2.lng - loc1.lng)) * longitude_scale(loc2);
  return pythagorous2(dlat, dlong) * LOCATION_SCALING_FACTOR;
}
/*************************���ϼ�������ͶӰ��������Դ��APM3.2 AP.Math.c�ļ�******************************/

Vector2i GPSData_To_XY_Home={1143637460,306276000};//����γ��
Location GPS_Home;//��ʼ��λ�ɹ�����Ϣ
Location GPS_Present;//��ǰλ�õ���Ϣ
uint8 GPS_Home_Set=0;
void Set_GPS_Home(void)//����Home��
{	
	static uint16_t gps_home_cnt=0;
  if(GPS_Home_Set==0
			&&GPS_Sate_Num>=9//�������ڵ���9
				&&Horizontal_Acc_Est<=1.5f)//ˮƽλ�ù��ƾ���С��1.5m
	 {
		 if(gps_home_cnt<=100) gps_home_cnt++;//ˢ��10hz������10S����
	 }

   if(GPS_Home_Set==0&&gps_home_cnt==100)//ȫ��ֻ����һ��
  {
    GPSData_To_XY_Home.x=Longitude_Origion;//Longitude;
    GPSData_To_XY_Home.y=Latitude_Origion;//Latitude;
    GPS_Home_Set=1;//�趨������
    GPS_Home.lng=GPSData_To_XY_Home.x;
    GPS_Home.lat=GPSData_To_XY_Home.y; 
    Strapdown_INS_Reset(&NamelessQuad,_PITCH,Earth_Frame_To_XYZ.E,0);//��λ�ߵ��ں�
    Strapdown_INS_Reset(&NamelessQuad,_ROLL,Earth_Frame_To_XYZ.N,0);//��λ�ߵ��ں�
    Declination=get_declination(0.0000001f*GPS_Home.lat,0.0000001f*GPS_Home.lng);//��ȡ���ش�ƫ��
  }
}

float Body_Frame_To_XYZ[3]={0,0,0};//��������������ϵ��������(Y��)������(X��)����λ��ƫ��
Vector3_Nav Earth_Frame_To_XYZ={0,0,0};//��������������ϵ���� ������������������λ��ƫ��
void GPSData_Sort()
{
  Vector2f location_delta={0,0};
  GPS_Present.lng=Longitude_Origion;//���µ�ǰ��γ��
  GPS_Present.lat=Latitude_Origion;
  location_delta=location_diff(GPS_Home,GPS_Present);//���ݵ�ǰGPS��λ��Ϣ��Home��λ����Ϣ������������������λ��ƫ��
  /***********************************************************************************
  ��ȷ�µ���ϵ������������������Ϊ������:
  ������������������,�����˻����home�㣬���������ƶ�ʱ����ʱGPS_Present.lng>GPS_Home.lng���õ���location_delta.x����0;
  ����������γ������,�����˻����home�㣬���������ƶ�ʱ����ʱGPS_Present.lat>GPS_Home.lat���õ���location_delta.y����0;
  ******************************************************************************/
  location_delta.x*=100;//�ص�������ϵ����������λ��ƫ��,��λΪCM
  location_delta.y*=100;//�ص�������ϵ����������λ��ƫ��,��λΪCM
  Earth_Frame_To_XYZ.E=location_delta.y;//����ϵ�����Home������λ��ƫ�ƣ���λΪCM
  Earth_Frame_To_XYZ.N=location_delta.x;//����ϵ�����Home������λ��ƫ�ƣ���λΪCM
  //�����˻��ڵ�������ϵ�µ��������������������λ��ƫ����ת����ǰ�����λ��ƫ��:��ͷ(����)+���
  Body_Frame_To_XYZ[_PITCH]=location_delta.x*Cos_Yaw+location_delta.y*Sin_Yaw;//��ͷ����λ��ƫ��  Y������
  Body_Frame_To_XYZ[_ROLL]=-location_delta.x*Sin_Yaw+location_delta.y*Cos_Yaw;  //�������λ��ƫ��  X������
}

#define TIME_CONTANST_XY      2.5f
#define K_ACC_XY	           (1.0f / (TIME_CONTANST_XY * TIME_CONTANST_XY * TIME_CONTANST_XY))
#define K_VEL_XY             (3.0f / (TIME_CONTANST_XY * TIME_CONTANST_XY))
#define K_POS_XY             (3.0f / TIME_CONTANST_XY)
float X_Delta=0,Y_Delta=0;
uint16_t GPS_Save_Period_Cnt=0;
uint16_t GPS_SINS_Delay_Cnt=40;//100ms
Testime SINS_Horizontal_Delta;
Vector2_Body Pos_Err_On_Accel={0};
Vector2_Body  Accel_Correction_BF={0};
Vector2_Earth Accel_Correction_EF={0};
void Strapdown_INS_Horizontal()
{
  uint16 Cnt=0;
  GPSData_Sort();//��ȡ���home��ˮƽƫ��
  GPS_Save_Period_Cnt++;
  if(GPS_Save_Period_Cnt>=2)//10ms
  {
    for(Cnt=Num-1;Cnt>0;Cnt--)//10ms����һ��
    {
      NamelessQuad.Pos_History[_PITCH][Cnt]=NamelessQuad.Pos_History[_PITCH][Cnt-1];
      NamelessQuad.Pos_History[_ROLL][Cnt]=NamelessQuad.Pos_History[_ROLL][Cnt-1];
    }
    NamelessQuad.Pos_History[_PITCH][0]=NamelessQuad.Position[_PITCH];
    NamelessQuad.Pos_History[_ROLL][0]=NamelessQuad.Position[_ROLL];
    GPS_Save_Period_Cnt=0;
  }
  //GPS��������ϵ�£���������������λ��ƫ����SINS�������Ĳ��λcm
  X_Delta=Earth_Frame_To_XYZ.E-NamelessQuad.Pos_History[_PITCH][GPS_SINS_Delay_Cnt];
  Y_Delta=Earth_Frame_To_XYZ.N-NamelessQuad.Pos_History[_ROLL][GPS_SINS_Delay_Cnt];
  
  
  Pos_Err_On_Accel.Rol=X_Delta*Cos_Yaw+Y_Delta*Sin_Yaw;//����ϵRoll����    X��
  Pos_Err_On_Accel.Pit=-X_Delta*Sin_Yaw+Y_Delta*Cos_Yaw;//����ϵPitch����  Y��
  
  Accel_Correction_BF.Pit+=Pos_Err_On_Accel.Pit* K_ACC_XY*CNTLCYCLE;//�������ͷ���򣬼��ٶȽ�����
  Accel_Correction_BF.Rol+=Pos_Err_On_Accel.Rol* K_ACC_XY*CNTLCYCLE;//�����������򣬼��ٶȽ�����
  
  Accel_Correction_EF.North=Accel_Correction_BF.Rol*Cos_Yaw+Accel_Correction_BF.Pit*Sin_Yaw;//�����巽���ϼ��ٶ�����������ת������ϵ����  Y Axis
  Accel_Correction_EF.East=Accel_Correction_BF.Rol*Sin_Yaw-Accel_Correction_BF.Pit*Cos_Yaw;//�����巽���ϼ��ٶ�����������ת������ϵ����   X axis
  
  acc_correction[_PITCH] += X_Delta*K_ACC_XY*CNTLCYCLE;//���ٶȽ�����
  //acc_correction[_PITCH]  = Accel_Correction_EF.East;//���ٶȽ�����
  vel_correction[_PITCH] += X_Delta* K_VEL_XY*CNTLCYCLE;//�ٶȽ�����
  pos_correction[_PITCH] += X_Delta* K_POS_XY*CNTLCYCLE;//λ�ý�����
  
  //acc_correction[_ROLL]  = Accel_Correction_EF.North;//���ٶȽ�����
  acc_correction[_ROLL] += Y_Delta* K_ACC_XY*CNTLCYCLE;//���ٶȽ�����
  vel_correction[_ROLL] += Y_Delta* K_VEL_XY*CNTLCYCLE;//�ٶȽ�����
  pos_correction[_ROLL] += Y_Delta* K_POS_XY*CNTLCYCLE;//λ�ý�����
  
  /*************************************************************/
  //ˮƽ�˶����ٶȼ�У��
  NamelessQuad.Acceleration[_PITCH]=Origion_NamelessQuad.Acceleration[_PITCH]+acc_correction[_PITCH];
  //�ٶ�������������£����ڸ���λ��
  SpeedDealt[_PITCH]=NamelessQuad.Acceleration[_PITCH]*CNTLCYCLE;
  //ԭʼλ�ø���
  Origion_NamelessQuad.Position[_PITCH]+=(NamelessQuad.Speed[_PITCH]+0.5*SpeedDealt[_PITCH])*CNTLCYCLE;
  //λ�ý��������
  NamelessQuad.Position[_PITCH]=Origion_NamelessQuad.Position[_PITCH]+pos_correction[_PITCH];
  //ԭʼ�ٶȸ���
  Origion_NamelessQuad.Speed[_PITCH]+=SpeedDealt[_PITCH];
  //�ٶȽ��������
  NamelessQuad.Speed[_PITCH]=Origion_NamelessQuad.Speed[_PITCH]+vel_correction[_PITCH];
  
  /*************************************************************/
  //ˮƽ�˶����ٶȼ�У��
  NamelessQuad.Acceleration[_ROLL]=Origion_NamelessQuad.Acceleration[_ROLL]+acc_correction[_ROLL];
  //�ٶ�������������£����ڸ���λ��
  SpeedDealt[_ROLL]=NamelessQuad.Acceleration[_ROLL]*CNTLCYCLE;
  //ԭʼλ�ø���
  Origion_NamelessQuad.Position[_ROLL]+=(NamelessQuad.Speed[_ROLL]+0.5*SpeedDealt[_ROLL])*CNTLCYCLE;
  //λ�ý��������
  NamelessQuad.Position[_ROLL]=Origion_NamelessQuad.Position[_ROLL]+pos_correction[_ROLL];
  //ԭʼ�ٶȸ���
  Origion_NamelessQuad.Speed[_ROLL]+=SpeedDealt[_ROLL];
  //�ٶȽ��������
  NamelessQuad.Speed[_ROLL]=Origion_NamelessQuad.Speed[_ROLL]+vel_correction[_ROLL];
}



void Strapdown_INS_Reset(SINS *Ins,uint8_t Axis,float Pos_Target,float Vel_Target)
{
  uint16_t Cnt=0;
  Ins->Position[Axis]=Pos_Target;//λ������
  Ins->Speed[Axis]=Vel_Target;//�ٶ�����
  Ins->Acceleration[Axis]=0.0f;//���ٶ�����
  Ins->Acce_Bias[Axis]=0.0f;
  for(Cnt=Num-1;Cnt>0;Cnt--)//��ʷλ��ֵ��ȫ��װ��Ϊ��ǰ�۲�ֵ
  {
    Ins->Pos_History[Axis][Cnt]=Pos_Target;
  }
  Ins->Pos_History[Axis][0]=Pos_Target;
  for(Cnt=Num-1;Cnt>0;Cnt--)//��ʷ�ٶ�ֵ��ȫ��װ��Ϊ��ǰ�۲�ֵ
  {
    Ins->Vel_History[Axis][Cnt]=Vel_Target;
  }
  Ins->Vel_History[Axis][0]=Vel_Target;
  pos_correction[Axis]=0;//��չߵ��ں���
  acc_correction[Axis]=0;
  vel_correction[Axis]=0;
}



#define Dealt_Update 0.1 //100ms����һ��
#define Process_Noise_Constant 1
#define Pos_Process_Noise  0.5*Process_Noise_Constant*Dealt_Update*Dealt_Update//0.005
#define Vel_Process_Noise  Process_Noise_Constant*Dealt_Update  //0.1
float R_GPS[2]={Pos_Process_Noise,Vel_Process_Noise};
//float Q_GPS[2]={0.075,3};//{0.075,5}  {0.03��3}
//float R_Acce_bias[2]={0.0001,0.000005};
//float Q_GPS[2]={0.075,1.2};//{0.075,5}  {0.03��3}
//float R_Acce_bias[2]={0.0001,0};
float   Q_GPS[2]={0.02,0.45};//{0.015,3.0}{0.075,3.0};
float   R_Acce_bias[2]={0.00025,0};//0.0001  0.001��ʼ�׷�ɢ
double Pre_conv_GPS[2][4]=
{
  0.018 ,    0.005,  0.005    , 0.5,//0.0001 ,    0.00001,  0.00001    , 0.003,
  0.018 ,    0.005,  0.005    , 0.5,
};//��һ��Э����
double K_GPS[2][2]={0};//�������
float Acce_Bias[2]={0,0.001};
void   KalmanFilter_Horizontal_GPS(float Position_GPS,float Vel_GPS,float Position_Last,float Vel_Last,
                                   float *Position,float *Vel,
                                   float *Acce,float *R,
                                   float *Q,float dt,uint8_t Axis)
{
  float Conv_Z=0;
  float Z_Delta[2]={0};
  float Conv_Temp=0;
  double Temp_conv[4]={0};//����Э����
  uint8 Label=0;
  if(Axis=='X') Label=0;
  else Label=1;
  //����״̬
  *Position +=*Vel*dt+((*Acce+Acce_Bias[Label])*dt*dt)/2.0;
  *Vel+=(*Acce+Acce_Bias[Label])*dt;
  //*Vel+=(*Acce)*dt;
  //����Э����
  Conv_Temp=Pre_conv_GPS[Label][1]+Pre_conv_GPS[Label][3]*dt;
  Temp_conv[0]=Pre_conv_GPS[Label][0]+Pre_conv_GPS[Label][2]*dt+Conv_Temp*dt+R_GPS[0];
  Temp_conv[1]=Conv_Temp;
  Temp_conv[2]=Pre_conv_GPS[Label][2]+Pre_conv_GPS[Label][3]*dt;
  //Temp_conv[1]=Conv_Temp+R_GPS[0]*0.5*0.00001;
  //Temp_conv[2]=Temp_conv[1];
  Temp_conv[3]=Pre_conv_GPS[Label][3]+R_GPS[1];
  //���㿨��������
  Conv_Z=1.0/((Temp_conv[0]+Q_GPS[0]*GPS_Quality)*(Temp_conv[3]+Q_GPS[1]*GPS_Quality)-Temp_conv[1]*Temp_conv[2]);
  //K_GPS[0][0]=( Temp_conv[0]*(Temp_conv[3]+Q_GPS[1])-Temp_conv[1]*Temp_conv[2])*Conv_Z;
  //K_GPS[0][1]=(-Temp_conv[0]*Temp_conv[1]+Temp_conv[1]*(Temp_conv[0]+Q_GPS[0]))*Conv_Z;
  //K_GPS[1][0]=( Temp_conv[2]*(Temp_conv[3]+Q_GPS[1])-Temp_conv[2]*Temp_conv[3])*Conv_Z;
  //K_GPS[1][1]=(-Temp_conv[1]*Temp_conv[2]+Temp_conv[3]*(Temp_conv[0]+Q_GPS[0]))*Conv_Z;
  //��������
  K_GPS[0][0]=( Temp_conv[0]*(Temp_conv[3]+Q_GPS[1]*GPS_Quality)-Temp_conv[1]*Temp_conv[2])*Conv_Z;
  K_GPS[0][1]=(Temp_conv[1]*Q_GPS[0]*GPS_Quality)*Conv_Z;
  K_GPS[1][0]=(Temp_conv[2]*Q_GPS[1]*GPS_Quality)*Conv_Z;
  K_GPS[1][1]=(-Temp_conv[1]*Temp_conv[2]+Temp_conv[3]*(Temp_conv[0]+Q_GPS[0]*GPS_Quality))*Conv_Z;
  //�ں��������
  Z_Delta[0]=Position_GPS-Position_Last;
  Z_Delta[1]=Vel_GPS-Vel_Last;
	
	Z_Delta[0]=constrain_float(Z_Delta[0],-10000,10000);//100m
	Z_Delta[1]=constrain_float(Z_Delta[1],-2000,2000);//20m/s
	
  *Position +=K_GPS[0][0]*Z_Delta[0]+K_GPS[0][1]*Z_Delta[1];
  *Vel +=K_GPS[1][0]*Z_Delta[0]+K_GPS[1][1]*Z_Delta[1];
  Acce_Bias[Label]+=R_Acce_bias[0]*Z_Delta[0]+R_Acce_bias[1]*Z_Delta[1];
	
	
	Acce_Bias[Label]=constrain_float(Acce_Bias[Label],-100,100);//100
	
	
  //����״̬Э�������
  Pre_conv_GPS[Label][0]=(1-K_GPS[0][0])*Temp_conv[0]-K_GPS[0][1]*Temp_conv[2];
  Pre_conv_GPS[Label][1]=(1-K_GPS[0][0])*Temp_conv[1]-K_GPS[0][1]*Temp_conv[3];
  Pre_conv_GPS[Label][2]=(1-K_GPS[1][1])*Temp_conv[2]-K_GPS[1][0]*Temp_conv[0];
  Pre_conv_GPS[Label][3]=(1-K_GPS[1][1])*Temp_conv[3]-K_GPS[1][0]*Temp_conv[1];
}


#define X_Axis  0
#define Y_Axis  1
#define NUM_BUF 50
float Position_History[2][NUM_BUF]={0};
float Vel_History[2][NUM_BUF]={0};
uint16 GPS_Vel_Delay_Cnt=20;// 200ms 20-200ms
uint16 GPS_Pos_Delay_Cnt=10;// 100ms 10-100ms
int16 GPS_Position_Cnt=0;
float Acce_bias[2]={0};
Testime SINS_Horizontal_Delta;
float Horizontal_Delta_T=0;
uint8_t Filter_Defeated_Flag=0;
void Filter_Horizontal(void)
{
  int16 i=0;
  GPSData_Sort();
  Test_Period(&SINS_Horizontal_Delta);
  Horizontal_Delta_T=SINS_Horizontal_Delta.Time_Delta/1000.0;
  
  GPS_Position_Cnt++;
  if(GPS_Position_Cnt>=2)//ÿ10ms����һ��
  {
    for(i=NUM_BUF-1;i>0;i--)
    {
      Position_History[X_Axis][i]=Position_History[X_Axis][i-1];
      Position_History[Y_Axis][i]=Position_History[Y_Axis][i-1];
      
      Vel_History[X_Axis][i]=Vel_History[X_Axis][i-1];
      Vel_History[Y_Axis][i]=Vel_History[Y_Axis][i-1];
    }
    Position_History[X_Axis][0]=NamelessQuad.Position[_PITCH];
    Position_History[Y_Axis][0]=NamelessQuad.Position[_ROLL];
    
    Vel_History[X_Axis][0]=NamelessQuad.Speed[_PITCH];
    Vel_History[Y_Axis][0]=NamelessQuad.Speed[_ROLL];
    
    GPS_Position_Cnt=0;
  }
  NamelessQuad.Acceleration[_PITCH]=Origion_NamelessQuad.Acceleration[_PITCH];
  NamelessQuad.Acceleration[_ROLL]=Origion_NamelessQuad.Acceleration[_ROLL];
  
  
  
  if(GPS_Update_finished_Correct_Flag==1)
  {
    KalmanFilter_Horizontal_GPS(Earth_Frame_To_XYZ.E,
                                GPS_Speed_Resolve[1],
                                Position_History[X_Axis][GPS_Pos_Delay_Cnt],
                                Vel_History[X_Axis][GPS_Vel_Delay_Cnt],
                                &NamelessQuad.Position[_PITCH],
                                &NamelessQuad.Speed[_PITCH],
                                &Origion_NamelessQuad.Acceleration[_PITCH],
                                R_GPS,Q_GPS,Horizontal_Delta_T,'X');
    
    
    KalmanFilter_Horizontal_GPS(Earth_Frame_To_XYZ.N,
                                GPS_Speed_Resolve[0],
                                Position_History[Y_Axis][GPS_Pos_Delay_Cnt],
                                Vel_History[Y_Axis][GPS_Vel_Delay_Cnt],
                                &NamelessQuad.Position[_ROLL],
                                &NamelessQuad.Speed[_ROLL],
                                &Origion_NamelessQuad.Acceleration[_ROLL],
                                R_GPS,Q_GPS,Horizontal_Delta_T,'Y');
    GPS_Update_finished_Correct_Flag=0;
  }
  else
  {
      NamelessQuad.Position[_PITCH] +=NamelessQuad.Speed[_PITCH]*Horizontal_Delta_T
        +((NamelessQuad.Acceleration[_PITCH]+Acce_Bias[0])*Horizontal_Delta_T*Horizontal_Delta_T)/2.0f;
      NamelessQuad.Speed[_PITCH]+=(NamelessQuad.Acceleration[_PITCH]+Acce_Bias[0])*Horizontal_Delta_T;
      
      NamelessQuad.Position[_ROLL] +=NamelessQuad.Speed[_ROLL]*Horizontal_Delta_T
        +((NamelessQuad.Acceleration[_ROLL]+Acce_Bias[1])*Horizontal_Delta_T*Horizontal_Delta_T)/2.0f;
      NamelessQuad.Speed[_ROLL]+=(NamelessQuad.Acceleration[_ROLL]+Acce_Bias[1])*Horizontal_Delta_T;
  }
  
  if(ABS(NamelessQuad.Position[_PITCH]-Earth_Frame_To_XYZ.E)>1000000
     ||ABS(NamelessQuad.Position[_ROLL]-Earth_Frame_To_XYZ.N)>1000000
       ||ABS(NamelessQuad.Speed[_PITCH]-GPS_Speed_Resolve[1])>1000000
         ||ABS(NamelessQuad.Speed[_ROLL]-GPS_Speed_Resolve[0])>1000000
           )
  {
    Filter_Defeated_Flag=1;//��ʼʱ���ں�ʧ�ܱ�־
  }
  
  
}


