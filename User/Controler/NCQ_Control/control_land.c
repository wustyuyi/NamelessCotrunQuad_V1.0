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
#include "control_config.h"
#include "control_land.h"

enum fixed_state{Faraway,Near,Arrive};
Vector2_Nav land_pos_target,land_pos_now,land_home_pos;
float target_yaw_rate=0,target_yaw_alt=0;
bool land_althold(float taret_climb_rate,float target_climb_alt)
{
  static uint16 High_Pos_Control_Cnt=0;//�߶�λ�ÿ��Ƽ�����
  static uint16 High_Vel_Control_Cnt=0;//�߶��ٶȿ��Ƽ�����
  static uint8_t move_flag=0;
  bool handmove_flag=false;
  float step_mapping=0,scale_mapping=0;
  Thr_Scale_Set(&RC_Calibration[2]);
  High_Hold_Throttle=Thr_Hover_Default;
  /*�߶ȿ�������1��*/
  /********
      **
      **
      **
      **
      **
  ********/
  /*******************************�߶ȿ�������ʼ****************************************/
  /****************���ߣ��߶�λ�û�+�ٶȻ�+���ٶȻ����������ڷֱ�Ϊ8ms��4ms��4ms*******************/
  if(target_climb_alt==0)
  {
    Total_Controller.High_Position_Control.Expect=NamelessQuad.Position[_YAW];//һֱ���¸߶�����
  }
  else
  {
    Total_Controller.High_Position_Control.Expect=target_climb_alt;//���¸߶�����
  }
  if(RC_NewData[0]>=Deadzone_Min
     &&RC_NewData[0]<=Deadzone_Max)
  {
    //�߶�λ�û���������ٶ�����
    High_Pos_Control_Cnt++;
    if(High_Pos_Control_Cnt>=2)//��ֱ�߶ȿ�������2*5=10ms
    {
      High_Pos_Control_Cnt=0;
      Total_Controller.High_Position_Control.FeedBack=NamelessQuad.Position[_YAW];//����
      PID_Control(&Total_Controller.High_Position_Control);//���θ߶�λ�ÿ�����
      //�ڻ��ٶ�����
      if(target_climb_alt==0) Yaw_Vel_Target=taret_climb_rate;//�����ٶ�������Դ���ⲿֱ�Ӹ���
      else Yaw_Vel_Target=Total_Controller.High_Position_Control.Control_OutPut;//�����ٶ�������Դ��λ�ÿ��������
#ifdef YAW_VEL_FEEDFORWARD  //�ٶ�ǰ��������
      Yaw_Vel_Feedforward_Delta=(Yaw_Vel_Target-Last_Yaw_Vel_Target)/(2*Delta);//�ٶ������仯��
      Yaw_Vel_Feedforward_Output=Yaw_Vel_Feedforward_Rate*Yaw_Vel_Feedforward_Delta;
      Last_Yaw_Vel_Target=Yaw_Vel_Target;//�ϴ��ٶ�����
#endif
      Total_Controller.High_Speed_Control.Expect=Yaw_Vel_Target;
    }
    handmove_flag=false;
    move_flag=0;
  }
  else if(RC_NewData[0]>Deadzone_Max)//���������ٶ�����
  {
    //���Ÿ����ơ������ٶ�����
    step_mapping=(float)(RC_NewData[0]-Deadzone_Max)/(Thr_Top-Deadzone_Max);//��Χ0~1
    scale_mapping=constrain_float(step_mapping*step_mapping,0,1);
    Total_Controller.High_Speed_Control.Expect=Max_Upvel*scale_mapping;//��������ٶ�50cm/s
    handmove_flag=true;
    move_flag=1;
  }
  else if(RC_NewData[0]<Deadzone_Min)//�����½��ٶ�����
  {
    //���Ÿ����ơ������ٶ�����
    step_mapping=(float)(RC_NewData[0]-Deadzone_Min)/(Deadzone_Min-Thr_Buttom);//��Χ0~-1
    scale_mapping=constrain_float(step_mapping*step_mapping,0,1);
    Total_Controller.High_Speed_Control.Expect=-Max_Downvel*scale_mapping;//����½��ٶ�40cm/s
    handmove_flag=true;
    move_flag=2;
  }
  /*�߶ȿ�������2��*/
  /********
          *
          *
   * * * *
  *
  *
  ********/
  /*******************************��ֱ�ٶȿ�������ʼ*******************************************************************/
  High_Vel_Control_Cnt++;
  if(High_Vel_Control_Cnt>=1)//��ֱ�߶ȿ�������5*1=5ms
  {
    High_Vel_Control_Cnt=0;
    Total_Controller.High_Speed_Control.FeedBack=NamelessQuad.Speed[_YAW];//�ߵ��ٶȹ��Ƹ��ٶȷ���
    PID_Control_Div_LPF(&Total_Controller.High_Speed_Control);//���θ߶��ٶȿ���
  }
  /*******************************�����½��������������ٶ��޷���������*******************************************************************/     
  if(move_flag==1)//�������Ƹ�ʱ���ٶȿ�����������������������½����ٶȽ��зֱ��޷���ȷ�������½�ʱ��̬ƽ��
  {
    Total_Controller.High_Speed_Control.Control_OutPut=constrain_float(Total_Controller.High_Speed_Control.Control_OutPut,
                                                                       -Climb_Up_Acceleration_Max,Climb_Up_Acceleration_Max);                                                                
  }
  else if(move_flag==2)
  {
    Total_Controller.High_Speed_Control.Control_OutPut=constrain_float(Total_Controller.High_Speed_Control.Control_OutPut,
                                                                       -Climb_Down_Acceleration_Max,Climb_Down_Acceleration_Max);
  }    
  /*******************************��ֱ�ٶȿ���������******************************************************************/
  /*�߶ȿ�������3��*/
  /********
         **
       **
     **
       **
         **
  ********/
  
  /*******************************��ֱ���ٶȿ�������ʼ******************************************************************/
  Total_Controller.High_Acce_Control.Expect=Total_Controller.High_Speed_Control.Control_OutPut;//���ٶ�����
#ifdef YAW_VEL_FEEDFORWARD  //�ٶ�ǰ��������
  Total_Controller.High_Acce_Control.Expect+=Yaw_Vel_Feedforward_Output;//����ǰ�����������
#endif
  Total_Controller.High_Acce_Control.FeedBack=Filter_Feedback_NamelessQuad.Acceleration[_YAW];//���ٶȷ���
  //PID_Control_Err_LPF(&Total_Controller.High_Acce_Control);//���θ߶ȼ��ٶȿ���
	PID_Control_Div_LPF(&Total_Controller.High_Acce_Control);//���θ߶ȼ��ٶȿ���
  /**************************************
  ���ٶȻ�ǰ������������ʱ��ע������
  ��ͣ���� = ���ٶȻ�����ֵ + ��׼��ͣ����
  ��ʱ����� F = mg
  ����Ҫ���a�ļ��ٶ�ʱ������� F1=m(g+a)
  F1/F = 1 + a/g
  ��˴�ʱӦ�������ͣ����*(1 + a/g)
  **************************************/
  Total_Controller.High_Acce_Control.Control_OutPut+=(High_Hold_Throttle+Total_Controller.High_Acce_Control.Integrate-Thr_Start)*
    (Total_Controller.High_Acce_Control.Expect/980);
  /*******************************��ֱ���ٶȿ���������******************************************************************/
  if(YAW_Pos_Control_Accel_Disable==0)
  {
    Throttle=Int_Sort(High_Hold_Throttle+Total_Controller.High_Acce_Control.Control_OutPut);//������Դ�ڸ߶ȼ��ٶȿ��������
  }
  else
  {
    Throttle=Int_Sort(High_Hold_Throttle+Total_Controller.High_Speed_Control.Control_OutPut);//������Դ�ڸ߶��ٶȿ��������
  }
  /*****************************************�߶ȿ������������������ſ�����***********************************************************/
  return handmove_flag;
}



Vector2f_Nav land_pos_sort(Vector2_Nav target_pos,Vector2_Nav now_pos)//�õ����Ŀ������Pit��Rol����ƫ��
{
  Vector2f_Nav earth_pos_delta;
  //Vector2_Body body_pos_delta;
  static int32_t last_land_lat;
  static float land_scale = 1.0;
  //�Ƚ�����γ�����ֵ�������ظ��������Һ���
  if(ABS(last_land_lat - target_pos.lat) < 100000)
  {
    // we are within 0.01 degrees (about 1km) of the
    // same latitude. We can avoid the cos() and return
    // the same scale factor.
    //land_scale;
  }
  else
  {
    land_scale = cosf(target_pos.lat * 1.0e-7f * DEG_TO_RAD);
    land_scale = constrain_float(land_scale, 0.01f, 1.0f);
  }
  last_land_lat= target_pos.lat;
  earth_pos_delta.N=(target_pos.lat-now_pos.lat) * LOCATION_SCALING_FACTOR;//���뵥λΪm
  earth_pos_delta.E=(target_pos.lng-now_pos.lng) * LOCATION_SCALING_FACTOR * land_scale;//���뵥λΪm
  /***********************************************************************************
  ��ȷ�µ���ϵ������������������Ϊ������:
  ������������������,�����˻����home�㣬���������ƶ�ʱ����ʱGPS_Present.lng>GPS_Home.lng���õ���location_delta.x����0;
  ����������γ������,�����˻����home�㣬���������ƶ�ʱ����ʱGPS_Present.lat>GPS_Home.lat���õ���location_delta.y����0;
  ******************************************************************************/
  earth_pos_delta.N*=100;//�ص�������ϵ����������λ��ƫ��,��λΪCM
  earth_pos_delta.E*=100;//�ص�������ϵ����������λ��ƫ��,��λΪCM
  return earth_pos_delta;
}

bool alt_handmove_check(void)
{
  bool alt_handmove=false;
  alt_handmove=(bool)((RC_NewData[0]<=Deadzone_Min) || (RC_NewData[0]>=Deadzone_Max));
  return alt_handmove;
}

bool pos_handmove_check(void)
{
  bool pos_handmove=false;
  pos_handmove=(bool)(Roll_Control!=0||Pitch_Control!=0);//��ˮƽң��������
  return pos_handmove;
}

bool land_poshold(Vector2_Nav target_pos,Vector2_Nav now_pos,uint8_t fixed_state)
{
  static uint16 Horizontal_Pos_Control_Cnt=0;//�߶��ٶȿ��Ƽ�����
  static uint16 Horizontal_Vel_Control_Cnt=0;//�߶��ٶȿ��Ƽ�����
  bool handmove_flag=false;
  float max_nav_speed=0;
  Vector2f_Nav earth_frame_distance={0,0};
  earth_frame_distance=land_pos_sort(target_pos,land_home_pos);//�õ����Ŀ���N��E����ƫ�ƣ�������λ��ƫ��
  if(Landon_Earth_Flag==0)
  {
    /*******************************ˮƽλ�ÿ�������ʼ***********************************************************/
    //������������ͣ�������GPS��������������ԭ��ǳ�� http://blog.csdn.net/u011992534/article/details/79408187
    if(GPS_ok()==true)
    {
      if(Roll_Control==0
         &&Pitch_Control==0)//��ˮƽң��������
      {
        Horizontal_Pos_Control_Cnt++;
        if(Horizontal_Pos_Control_Cnt>4)//20ms����һ��
        {
          //λ������,��γ�������ٶȡ��߶�
          Total_Controller.Latitude_Position_Control.Expect=NamelessQuad.Position[_ROLL];//��ֲ����ˮƽĿ��λ�ã�Ŀ�����лض���ģʽ����ͣ��
          Total_Controller.Longitude_Position_Control.Expect=NamelessQuad.Position[_PITCH];
          //��������ϵ��E��N������λ��ƫ��
          Earth_Frame_Pos_Err.N=earth_frame_distance.N-NamelessQuad.Position[_ROLL];
          Earth_Frame_Pos_Err.E=earth_frame_distance.E-NamelessQuad.Position[_PITCH];
          //��������ϵ�»���Pitch��Roll������λ��ƫ��
          Body_Frame_Pos_Err.Pit=-Earth_Frame_Pos_Err.E*Sin_Yaw+Earth_Frame_Pos_Err.N*Cos_Yaw;
          Body_Frame_Pos_Err.Rol=Earth_Frame_Pos_Err.E*Cos_Yaw+Earth_Frame_Pos_Err.N*Sin_Yaw;
          //��������ϵ�»���Pitch��Roll����������ɲ���ٶȣ�����Ϊ���������㲻����PID_Control()����
          if(fixed_state==Faraway)   max_nav_speed=First_Nav_Rate;
          else if(fixed_state==Near)   max_nav_speed=Second_Nav_Rate;
          else if(fixed_state==Arrive)   max_nav_speed=Third_Nav_Rate;
          else   max_nav_speed=Default_Nav_rate;
          Body_Frame_Brake_Speed.Pit=constrain_float(Total_Controller.Latitude_Position_Control.Kp*Body_Frame_Pos_Err.Pit,-max_nav_speed, max_nav_speed);//λ��ƫ���޷�����λcm
          Body_Frame_Brake_Speed.Rol=constrain_float(Total_Controller.Latitude_Position_Control.Kp*Body_Frame_Pos_Err.Rol,-max_nav_speed, max_nav_speed);//λ��ƫ���޷�����λcm
          
          //�ٶȿ���������
          Total_Controller.Latitude_Speed_Control.Expect =Body_Frame_Brake_Speed.Pit;
          Total_Controller.Longitude_Speed_Control.Expect=Body_Frame_Brake_Speed.Rol;
          Horizontal_Pos_Control_Cnt=0;//λ�ÿ�������������������ɲ���ٶ�
        }
        //����ϵ��ˮƽ�ٶȣ�ת������������ϵX-Y������
        //������Pitch��Roll����ˮƽ�ٶȿ���
        Horizontal_Vel_Control_Cnt++;
        if(Horizontal_Vel_Control_Cnt>=2)//10ms����һ��λ��
        {
          Body_Frame_Speed_Feedback.Pit=-NamelessQuad.Speed[_PITCH]*Sin_Yaw+NamelessQuad.Speed[_ROLL]*Cos_Yaw;
          Body_Frame_Speed_Feedback.Rol=NamelessQuad.Speed[_PITCH]*Cos_Yaw+NamelessQuad.Speed[_ROLL]*Sin_Yaw;
          //�����巽���ٶȷ�����
          Total_Controller.Latitude_Speed_Control.FeedBack=Body_Frame_Speed_Feedback.Pit;//��ͷPitch����Y������
          Total_Controller.Longitude_Speed_Control.FeedBack=Body_Frame_Speed_Feedback.Rol;//���Roll����X������
          //�����巽���ٶȿ�����
          PID_Control_Div_LPF(&Total_Controller.Latitude_Speed_Control);
          PID_Control_Div_LPF(&Total_Controller.Longitude_Speed_Control);
          
          accel_target.y=-Total_Controller.Latitude_Speed_Control.Control_OutPut;
          accel_target.x=Total_Controller.Longitude_Speed_Control.Control_OutPut;//�����˶����ٶ�
          accel_to_lean_angles(accel_target,&angle_target);//�����˶����ٶ�ת������̬���
          Total_Controller.Pitch_Angle_Control.Expect=angle_target.y;
          Total_Controller.Roll_Angle_Control.Expect=angle_target.x;  
          //Total_Controller.Pitch_Angle_Control.Expect=-Total_Controller.Latitude_Speed_Control.Control_OutPut;
          //Total_Controller.Roll_Angle_Control.Expect=Total_Controller.Longitude_Speed_Control.Control_OutPut;
          Horizontal_Vel_Control_Cnt=0;
        }
        /*******************************ˮƽλ�ÿ���������***********************************************************/
        handmove_flag=false;
      }
      else //ֻ����ˮƽ�ٶȿ��ƣ���ˮƽλ�ÿ���
      {
        Horizontal_Vel_Control_Cnt++;
        if(Horizontal_Vel_Control_Cnt>=2)//10ms����һ���ٶ�
        {
          Total_Controller.Latitude_Speed_Control.Expect=ncq_speed_mapping(-Target_Angle[0],Pit_Rol_Max,Max_Horvel);
          Total_Controller.Longitude_Speed_Control.Expect=ncq_speed_mapping(Target_Angle[1],Pit_Rol_Max,Max_Horvel);
          //����ϵ��ˮƽ�ٶȣ�ת������������ϵX-Y������
          //������Pitch��Roll����ˮƽ�ٶȿ���
          Body_Frame_Speed_Feedback.Pit=-NamelessQuad.Speed[_PITCH]*Sin_Yaw+NamelessQuad.Speed[_ROLL]*Cos_Yaw;
          Body_Frame_Speed_Feedback.Rol=NamelessQuad.Speed[_PITCH]*Cos_Yaw+NamelessQuad.Speed[_ROLL]*Sin_Yaw;
          
          Total_Controller.Latitude_Speed_Control.FeedBack=Body_Frame_Speed_Feedback.Pit;//��ͷPitch����Y������
          Total_Controller.Longitude_Speed_Control.FeedBack=Body_Frame_Speed_Feedback.Rol;//���Roll����X������
          
          PID_Control_Div_LPF(&Total_Controller.Latitude_Speed_Control);
          PID_Control_Div_LPF(&Total_Controller.Longitude_Speed_Control);
          
          accel_target.y=-Total_Controller.Latitude_Speed_Control.Control_OutPut;
          accel_target.x=Total_Controller.Longitude_Speed_Control.Control_OutPut;//�����˶����ٶ�
          accel_to_lean_angles(accel_target,&angle_target);//�����˶����ٶ�ת������̬���
          Total_Controller.Pitch_Angle_Control.Expect=angle_target.y;
          Total_Controller.Roll_Angle_Control.Expect=angle_target.x;  
          //Total_Controller.Pitch_Angle_Control.Expect=-Total_Controller.Latitude_Speed_Control.Control_OutPut;
          //Total_Controller.Roll_Angle_Control.Expect=Total_Controller.Longitude_Speed_Control.Control_OutPut;
          Horizontal_Vel_Control_Cnt=0;
        }
        handmove_flag=true;
      }
    }
  }
  else
  {
    Total_Controller.Pitch_Angle_Control.Expect=0;//ˮƽ������̬�Ǹ�0
    Total_Controller.Roll_Angle_Control.Expect=0;
    Take_Off_Reset();//��ջ��ֿ�����
  }
  return handmove_flag;
}



#define Minimal_Thrust_Threshold 1150//��½���������Сֵ
uint16_t Landon_Earth_Cnt=0;
uint8_t Last_Landon_Earth_Flag=0,Landon_Earth_Flag=0;
uint8_t Landon_Earth_Flag_Set=0;

void landon_earth_check(void)//�Լ촥�ؽ��뵡��ģʽ
{
  Last_Landon_Earth_Flag=Landon_Earth_Flag;
  //���ſ��ƴ��ڽϵ��г̣�
  //1����̬ģʽ�£����Ÿ˴��ڵ�λ
  //2������ģʽ�£������ٶ����£������ٶȻ�����Ϊ��Сֵ��
  //���ٶȿ���������ڳ�ʱ����֣������Ľϴ�ֵ��ʹ�����ſ��ƽϵ�
  if(Throttle_Output<=Minimal_Thrust_Threshold
     &&Gyro_Length<=35.0//���غ�����ת���Ͻ��ٶ�С��20deg/s
       &&ABS(NamelessQuad.Speed[_YAW])<=30.0//�ߵ���ֱ���ٶ�+-20cm/s
         &&Unwanted_Lock_Flag==0
           &&pos_handmove_check()==false)//��ˮƽ�ֶ�����
    Landon_Earth_Cnt++;
  else Landon_Earth_Cnt/=2;
  
  if(Landon_Earth_Cnt>=1000)  Landon_Earth_Cnt=1000;//��ֹ���
  if(Landon_Earth_Cnt>=200*2.0)//����2.0S
  {
    Landon_Earth_Flag=1;//��½��־λ
    //Landon_Earth_Cnt=0;
  }
  else
  {
    Landon_Earth_Flag=0;//��½��־λ
  }
  /*
  if(ABS(Throttle_Rate)>=1.0E-5f)//ֻҪ���ű仯�ʲ�Ϊ0���������½��־λ
  {
  Landon_Earth_Flag=0;
  Landon_Earth_Cnt=0;
}
  */
  
  
}

// land_nogps_run - runs the land controller
//      pilot controls roll and pitch angles
//      should be called at 100hz or more
void land_nogps_run()
{
  if(Landon_Earth_Flag==0)//δ���أ�����̬���Ʋ���
  {
    Total_Controller.Pitch_Angle_Control.Expect=Target_Angle[0];//ˮƽ������̬����Դ��ң�˸���
    Total_Controller.Roll_Angle_Control.Expect=Target_Angle[1];
    
    if(NamelessQuad.Position[_YAW]<=Safe_Height)//��Գ�ʼ�߶�10M����,��ʱ����Ư��
      target_yaw_rate=Nav_Decline_Rate;//��Nav_Decline_rate�ٶ��½�
    else target_yaw_rate=Nav_Rapid_Decline_Rate;//��Nav_Rapid_Decline_rate�ٶ��½�
    
    target_yaw_alt=0;
    
    land_althold(target_yaw_rate,target_yaw_alt);
  }
  else
  {
    Total_Controller.Pitch_Angle_Control.Expect=0;//ˮƽ������̬�Ǹ�0
    Total_Controller.Roll_Angle_Control.Expect=0;
    Take_Off_Reset();//��ջ��ֿ�����
    target_yaw_rate=2*Nav_Rapid_Decline_Rate;//��2*Nav_Rapid_Decline_rate�ٶ��½�,ʹ��������Ѹ�����㵡������
    target_yaw_alt=0;
    land_althold(target_yaw_rate,target_yaw_alt);
  }
}



uint8_t last_handmove_change_mode=1,handmove_change_mode=1;
uint16 nav_transition_cnt=0;
uint16 nav_transition_flag=0;
uint16 nav_climb_rate_cnt=0;
int16 nav_decline_rate_cnt=0;
uint16 first_switch_flag=1;
uint8_t distance_land_mode=0,last_distance_land_mode=0;
uint8_t climb_safe_alt_flag=0,home_fixed_flag=0;
bool check_pos_handmove=false;
bool check_alt_handmove=false;

void land_reset()//��½�����д��ڸ��ֱ�־λ����һ�η��й����У����ܻ�Ƶ���л�����Ҫ����ϴ�δ������ϵı�־λ�����л�ʱ��ȫ�����
{
  //��λ�����е����б�־λ������Ӧ�Խ�Ϊ���ӵ��߼����̵ıر���̼��ɣ�һ��Ҫ���պ�
  last_handmove_change_mode=0;
  
  nav_transition_cnt=0;
  nav_transition_flag=0;
  nav_climb_rate_cnt=0;
  distance_land_mode=0;
  last_distance_land_mode=0;//���Զ�����ģʽ��־λ��0����һ��ѭ���������ж�
  climb_safe_alt_flag=0;
  first_switch_flag=1;
  home_fixed_flag=0;
  handmove_change_mode=2;//ˮƽλ���ֶ�ģʽ
  first_switch_flag=1;//׼�����´λ���ʱ�̵��л�
  
  /*
  last_handmove_change_mode=1;
  handmove_change_mode=1;
  nav_transition_cnt=0;
  nav_transition_flag=0;
  nav_climb_rate_cnt=0;
  nav_decline_rate_cnt=0;
  first_switch_flag=1;
  distance_land_mode=0;
  last_distance_land_mode=0;
  climb_safe_alt_flag=0;
  home_fixed_flag=0;
  check_pos_handmove=false;
  check_alt_handmove=false;
  */
}


void land_state_check(void)
{
  float distance_to_home=100*get_distance(GPS_Home,GPS_Present);//��λcm
  last_distance_land_mode=distance_land_mode;
  if(distance_to_home>=Faraway_Distance)//����ɵ�ˮƽ���볬��Faraway_Distance�뾶
  {
    distance_land_mode=1;//��ԭ����������ȫ�߶��ٷ�����ˮƽ�����Ϸ�
    home_fixed_flag=Faraway;//Զ��home��
  }
  else if(distance_to_home>=Near_Distance)//����ɵ�ˮƽ����Near_Distance~Faraway_Distance�뾶
  {
    distance_land_mode=2;//�ȱ��ֵ�ǰ�߶ȣ�ˮƽ�˶���home�����Ϸ������½�
    home_fixed_flag=Near;//�ӽ�home��
  }
  else//��home�����С�ڵ���Near_Distance�뾶���ѵ���home��
  {
    distance_land_mode=3;//ˮƽλ�ñ���Ϊhome�㣬��ֱ���½�
    home_fixed_flag=Arrive;//������home��
  }
  
  check_pos_handmove=pos_handmove_check();//ˮƽλ�÷����ֶ�
  check_alt_handmove=alt_handmove_check();//��ֱ�߶ȷ����ֶ�
  
  last_handmove_change_mode=handmove_change_mode;
  if(check_pos_handmove==true)//��ˮƽλ���Զ����ƹ����У����ֶ�����
  {
    last_distance_land_mode=0;//���Զ�����ģʽ��־λ��0����һ��ѭ���������ж�
    //distance_land_mode=0;
    climb_safe_alt_flag=0;
    home_fixed_flag=0;
    handmove_change_mode=2;//ˮƽλ���ֶ�ģʽ
    first_switch_flag=1;//׼�����´λ���ʱ�̵��л�
    /**************ϣ�����������У�ˮƽ��ʱ�޸߶��������½���������ˮƽ���ʱ���߶ȱ��ּ���**************/
  }
  else handmove_change_mode=1;
  
  if(check_alt_handmove==true)//���߶��Զ����ƹ����У����ֶ�����
  {
    last_distance_land_mode=0;//���Զ�����ģʽ��־λ��0����һ��ѭ���������ж�
    //distance_land_mode=0;
    climb_safe_alt_flag=0;
    home_fixed_flag=0;
    first_switch_flag=1;//׼�����´λ���ʱ�̵��л�
  }
}
// land_run - runs the land controller
//      horizontal position controlled with loiter controller
//      should be called at 100hz or more
void land_gps_run()
{
  static uint16_t land_gap_cnt=0;
  land_home_pos.lat=GPS_Home.lat;
  land_home_pos.lng=GPS_Home.lng;
  land_pos_now.lat=GPS_Present.lat;
  land_pos_now.lng=GPS_Present.lng;
  
  land_state_check();
  
  if(Landon_Earth_Flag==0)//δ���أ�����̬���Ʋ���
  {
    if(check_pos_handmove==false)//��ˮƽ��˶���λ
    {
      if(distance_land_mode==1&&first_switch_flag==1)//�״��з���ģʽ������home��Զʱ
      {
        if(NamelessQuad.Position[_YAW]<Safe_Height)//���з���˲��ĸ߶�С�ڰ�ȫ�߶�ʱ�����ֵ�ǰˮƽλ�ã���������ȫ�߶��ٷ���
        {
          land_pos_target.lat=GPS_Present.lat;
          land_pos_target.lng=GPS_Present.lng;
          //target_yaw_rate=Nav_climb_rate;//��Nav_climb_rate�ٶ�������Nav_Safety_Height��ȫ�߶�
          nav_climb_rate_cnt=Nav_Climb_Rate;
          target_yaw_rate=Nav_Climb_Rate-nav_climb_rate_cnt;//�ٶ����ε������������ſ�����ͻ��
          land_gap_cnt=0;//����ʱ�䲽��������
          //����ɼ򵥼���һ�µ�΢�ֲ���Ϊ1.5ʱ
          //1.5*50=75���ſ�����˲�����75��ͻ�䣬���ܵ��·ɻ����ȶ�
          target_yaw_alt=0;//Ŀ��߶���0
          climb_safe_alt_flag=0;
        }
        else//���з���˲��ĸ߶ȴ��ڰ�ȫ�߶�ʱ�����ֵ�ǰ�߶ȣ�ִ�з���
        {
          land_pos_target.lat=GPS_Home.lat;
          land_pos_target.lng=GPS_Home.lng;
          target_yaw_rate=0;//Ŀ���ٶ���0
          target_yaw_alt=NamelessQuad.Position[_YAW];//Ŀ�걣�ֵ�ǰ�߶�
          climb_safe_alt_flag=1;//�Ѿ��ﵽ��ȫ�߶�
        }
        first_switch_flag=0;
        last_distance_land_mode=1;//ȷ����˳��������һ�׶�
      }
      else if(distance_land_mode==1&&last_distance_land_mode==1)//��������Զ��home���Զλ��
      {
        if(NamelessQuad.Position[_YAW]>=Safe_Height//�������ĸ߶ȳ�����ȫ�߶�ʱ�����ֵ�ǰ�߶ȣ�����home���Ϸ�����
           &&climb_safe_alt_flag==0)//��δ���ﰲȫ�߶�
        {
          climb_safe_alt_flag=1;//�ѵ��ﰲȫ�߶�
          nav_transition_cnt=Nav_Transition_Period;//���ù��ɻ���ʱ��Nav_Transition_Period������
          nav_transition_flag=0;
        }
        else if(climb_safe_alt_flag==0)//��home��Զ��δ�ﵽ��ȫ�߶ȣ���Ȼ���ڱ���ԭ��λ�ã����������
        {
          //ˮƽfixedλ�ò����ٴ����ã���Ϊ�ڳ�ʼ�з���ʱ������
          //target_yaw_rate=Nav_climb_rate;//��Nav_climb_rate�ٶ�������Nav_Safety_Height��ȫ�߶�
          land_gap_cnt++;
          if(land_gap_cnt>=8)//ÿ8*5=40ms�ݼ�
          {
            if(nav_climb_rate_cnt>=1)  nav_climb_rate_cnt--;
            else nav_climb_rate_cnt=0;
            land_gap_cnt=0;
          }
          
          target_yaw_rate=Nav_Climb_Rate-nav_climb_rate_cnt;//�ٶ����ε������������ſ�����ͻ��
          //����ɼ򵥼���һ�µ�΢�ֲ���Ϊ1.5ʱ
          //1.5*50=75���ſ�����˲�����75��ͻ�䣬�ɻ����²��ȶ�
          target_yaw_alt=0;//Ŀ��߶���0
        }
        
        if(climb_safe_alt_flag==1)//ֻ����һ��
        {
          if(nav_transition_cnt>=1)  nav_transition_cnt--;//˥����0
          else nav_transition_cnt=0;
          
          if(nav_transition_cnt==0)//����ʱ���ѽ��������÷�����
          {
            land_pos_target.lat=GPS_Home.lat;
            land_pos_target.lng=GPS_Home.lng;
            target_yaw_rate=0;//Ŀ���ٶ���0
            target_yaw_alt=NamelessQuad.Position[_YAW];//Ŀ�걣�ֵ�ǰ�߶�
            climb_safe_alt_flag++;//climb_safe_alt_flag==2
          }
          else//�����ڼ�
          {
            if(nav_transition_flag==0)//δ���û���״̬
            {
              nav_transition_flag=1;//���ҽ�����1�Σ�����Ϊ��ԭ����ͣnav_transition_cnt������
              land_pos_target.lat=GPS_Present.lat;
              land_pos_target.lng=GPS_Present.lng;
              target_yaw_rate=0;
              target_yaw_alt=NamelessQuad.Position[_YAW];
            }
          }
        }
      }
      else if(distance_land_mode==2&&last_distance_land_mode!=2)//�״��з���ģʽ������home�Ͻ�ʱ�����ֵ�ǰ�߶ȣ���Home����ΪĿ��㣬����home���Ϸ�
      {
        land_pos_target.lat=GPS_Home.lat;
        land_pos_target.lng=GPS_Home.lng;
        target_yaw_rate=0;//Ŀ���ٶ���0
        target_yaw_alt=NamelessQuad.Position[_YAW];//��Ŀ��߶�����Ϊ��ǰ�߶�
        climb_safe_alt_flag=2;
        //����������������1��A->B  2��C->B
        //ִ�еĲ�����ͬ���������ֵ�ǰ�߶ȣ���home����
        last_distance_land_mode=2;//ȷ����˳��������һ�׶�
      }
      else if(distance_land_mode==2&&last_distance_land_mode==2)
      {
        //ˮƽfixedλ�ò����ٴ����ã���Ϊ����һ״̬������
        land_pos_target.lat=GPS_Home.lat;
        land_pos_target.lng=GPS_Home.lng;
        target_yaw_rate=0;//Ŀ���ٶ���0
        climb_safe_alt_flag=2;
      }
      else if(distance_land_mode==3&&last_distance_land_mode!=3)//�״ν���home�����Ϸ�
      {
        land_pos_target.lat=GPS_Home.lat;
        land_pos_target.lng=GPS_Home.lng;
        //target_yaw_rate=Nav_Decline_Rate;//��Nav_Decline_rateĿ���ٶ��½�
        nav_decline_rate_cnt=Nav_Decline_Rate;
        target_yaw_rate=Nav_Decline_Rate-nav_decline_rate_cnt;
        land_gap_cnt=0;//����ʱ�䲽��������
        
        target_yaw_alt=0;//��Ŀ��߶�����Ϊ��ǰ�߶�
        climb_safe_alt_flag=2;
        
        //�������ҽ���һ�������1��B->A
        //ִ�еĲ���Ϊ��ˮƽ��������Ϊhome�㣬���½�
      }
      else if(distance_land_mode==3&&last_distance_land_mode==3)//����home�����Ϸ�
      {
        land_pos_target.lat=GPS_Home.lat;
        land_pos_target.lng=GPS_Home.lng;
        //target_yaw_rate=Nav_Decline_Rate;//��Nav_Decline_rateĿ���ٶ��½�
        
        land_gap_cnt++;
        if(land_gap_cnt>=8)//ÿ8*5=40ms�ݼ�
        {
          if(nav_decline_rate_cnt<=-1)  nav_decline_rate_cnt++;
          else nav_decline_rate_cnt=0;
          land_gap_cnt=0;
        }
        target_yaw_rate=Nav_Decline_Rate-nav_decline_rate_cnt;//�½��ٶ����ε������������ſ�����ͻ��
        
        target_yaw_alt=0;//��Ŀ��߶�����Ϊ��ǰ�߶�
        climb_safe_alt_flag=2;
      }
      /*************************************************************/
      land_poshold(land_pos_target,land_pos_now,home_fixed_flag);
      land_althold(target_yaw_rate,target_yaw_alt);
    }
    else//����ˮƽ�ֶ�����
    {
      land_poshold(land_pos_target,land_pos_now,home_fixed_flag);
      if(handmove_change_mode==2&&last_handmove_change_mode==1)
      {
        target_yaw_rate=0;//Ŀ���ٶ���0
        target_yaw_alt=NamelessQuad.Position[_YAW];//��Ŀ��߶�����Ϊ��ǰ�߶�
      }
      else if(handmove_change_mode==2&&last_handmove_change_mode==2)
      {
        target_yaw_rate=0;//Ŀ���ٶ���0
        //target_yaw_alt=NamelessQuad.Position[_YAW];//��Ŀ��߶�����Ϊ��ǰ�߶�
      }
      land_althold(target_yaw_rate,target_yaw_alt);
    }
  }
  else
  {
    Total_Controller.Pitch_Angle_Control.Expect=0;//ˮƽ������̬�Ǹ�0
    Total_Controller.Roll_Angle_Control.Expect=0;
    Take_Off_Reset();//��ջ��ֿ�����
    target_yaw_rate=2*Nav_Rapid_Decline_Rate;//��2*Nav_Rapid_Decline_rate�ٶ��½�,ʹ��������Ѹ�����㵡������
    target_yaw_alt=0;
    land_althold(target_yaw_rate,target_yaw_alt);
  }
}


bool GPS_ok()// returns true if the GPS is ok and home position is set
{
  if(GPS_Sate_Num>=7//��λ���ǳ���7��
     &&GPS_Quality<=3.5f//ˮƽ�������Ӵ���6������
       &&GPS_Home_Set==1
         &&Filter_Defeated_Flag==0)
  {
    return true;
  }
  else
  {
    return false;
  }
}


// land_run - runs the land controller
// should be called at 100hz or more
void land_run()
{
  if (GPS_ok()==true)
  {
    land_gps_run();//GPS��Чʱ��ִ��һ����������
  }
  else
  {
    land_nogps_run();//GPS��Чʱ��ִ��һ����½����
  }
}


