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
#include "control_poshold.h"


Vector3_Nav Earth_Frame_Accel_Target={0,0,0};   //��������������ϵ����������������Ŀ���˶����ٶ�����
Vector3_Nav Earth_Frame_Pos_Err={0,0,0};        //��������������ϵ����������������wλ��ƫ��
Vector2_Ang Body_Frame_Accel_Target={0,0};      //��������������ϵ��������(Y��)������(X��)����Ŀ���˶����ٶ�����
Vector2_Ang Body_Frame_Speed_Feedback={0,0};    //��������������ϵ��������(Y��)������(X��)����Ŀ���˶��ٶȷ���
Vector2_Ang Body_Frame_Pos_Err={0,0};           //���巽����λ��ƫ��
Vector2_Ang Body_Frame_Brake_Speed={0,0};       //���巽����ɲ���ٶ�
uint8 GPS_Speed_Control_Mode=0;


// a faster varient of atan.  accurate to 6 decimal places for values between -1 ~ 1 but then diverges quickly
float fast_atan(float v)
{
    float v2 = v*v;
    return (v*(1.6867629106f+v2*0.4378497304f)/(1.6867633134f+v2));
}
/// accel_to_lean_angles - horizontal desired acceleration to lean angles
///    converts desired accelerations provided in lat/lon frame to roll/pitch angles
void accel_to_lean_angles(Vector2f _accel_target,Vector2f *target_angle)
{
  float accel_right, accel_forward;
  float lean_angle_max = 30;
  accel_forward=_accel_target.y;//cm/s^2
  accel_right  =_accel_target.x;//cm/s^2
  // update angle targets that will be passed to stabilize controller
  target_angle->y=constrain_float(fast_atan(accel_forward*Cos_Roll/(GRAVITY_MSS*100))*RAD2DEG,-lean_angle_max,lean_angle_max);//pitch
  target_angle->x=constrain_float(fast_atan(accel_right/(GRAVITY_MSS*100))*RAD2DEG,-lean_angle_max,lean_angle_max);//roll
}

float ncq_speed_mapping(float input,uint16_t input_max,float output_max)
{
  float output_speed=0;
  float temp_scale=(float)(input/input_max);
  temp_scale=constrain_float(temp_scale,-1.0f, 1.0f);
  if(temp_scale>=0) output_speed=(float)(output_max*temp_scale*temp_scale);
  else output_speed=(float)(-output_max*temp_scale*temp_scale); 
  return output_speed;
}

Vector2f accel_target={0},angle_target={0};
void ncq_control_poshold()
{
  static uint16 Horizontal_Pos_Control_Cnt=0;//�߶��ٶȿ��Ƽ�����
  static uint16 Horizontal_Vel_Control_Cnt=0;//�߶��ٶȿ��Ƽ�����
  
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
        if(Total_Controller.Latitude_Position_Control.Expect==0
           &&Total_Controller.Longitude_Position_Control.Expect==0)//����˻��к�ֻ����һ��
        {
          // Total_Controller.Latitude_Position_Control.Expect=NamelessQuad.Position[_ROLL];
          //Total_Controller.Longitude_Position_Control.Expect=NamelessQuad.Position[_PITCH];
          if(get_stopping_point_xy(&UAV_Cushion_Stop_Point)==1)
          {
            Total_Controller.Latitude_Position_Control.Expect=UAV_Cushion_Stop_Point.y;
            Total_Controller.Longitude_Position_Control.Expect=UAV_Cushion_Stop_Point.x;
          }
          else//ֻ�����ٶ�ɲ��
          {
            //�ٶȿ���������
            Total_Controller.Latitude_Speed_Control.Expect =0;
            Total_Controller.Longitude_Speed_Control.Expect=0;  
          }
        }
        else
        {
          //λ�÷�������Դ�ڵ�ǰ�ߵ���λ�ù���
          Total_Controller.Latitude_Position_Control.FeedBack=NamelessQuad.Position[_ROLL];
          Total_Controller.Longitude_Position_Control.FeedBack=NamelessQuad.Position[_PITCH];
          //��������ϵ��E��N������λ��ƫ��
          Earth_Frame_Pos_Err.N=Total_Controller.Latitude_Position_Control.Expect-Total_Controller.Latitude_Position_Control.FeedBack;
          Earth_Frame_Pos_Err.E=Total_Controller.Longitude_Position_Control.Expect-Total_Controller.Longitude_Position_Control.FeedBack;
          //��������ϵ�»���Pitch��Roll������λ��ƫ��
          Body_Frame_Pos_Err.Pit=-Earth_Frame_Pos_Err.E*Sin_Yaw+Earth_Frame_Pos_Err.N*Cos_Yaw;
          Body_Frame_Pos_Err.Rol=Earth_Frame_Pos_Err.E*Cos_Yaw+Earth_Frame_Pos_Err.N*Sin_Yaw;
          //��������ϵ�»���Pitch��Roll����������ɲ���ٶȣ�����Ϊ���������㲻����PID_Control()����
          Body_Frame_Pos_Err.Pit=constrain_float(Body_Frame_Pos_Err.Pit,-Total_Controller.Latitude_Position_Control.Err_Max, Total_Controller.Latitude_Position_Control.Err_Max);//λ��ƫ���޷�����λcm
          Body_Frame_Pos_Err.Rol=constrain_float(Body_Frame_Pos_Err.Rol,-Total_Controller.Longitude_Position_Control.Err_Max,Total_Controller.Longitude_Position_Control.Err_Max);//λ��ƫ���޷�����λcm
          
          Body_Frame_Brake_Speed.Pit=Total_Controller.Latitude_Position_Control.Kp*Body_Frame_Pos_Err.Pit;
          Body_Frame_Brake_Speed.Rol=Total_Controller.Longitude_Position_Control.Kp*Body_Frame_Pos_Err.Rol;
          //�ٶȿ���������
          Total_Controller.Latitude_Speed_Control.Expect =Body_Frame_Brake_Speed.Pit;
          Total_Controller.Longitude_Speed_Control.Expect=Body_Frame_Brake_Speed.Rol;  
        }
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
    }
    else //ֻ����ˮƽ�ٶȿ��ƣ���ˮƽλ�ÿ���
    {
      //�����������1����������ϵ�ĺ����ٶȿ��ƣ�
      //            2����������ϵ�����ϵ��ٶȿ���
      if(GPS_Speed_Control_Mode==Angle_Mode)//�ƶ�����ˣ���Ӧ�����Ƕ�
      {
        Total_Controller.Pitch_Angle_Control.Expect=Target_Angle[0];
        Total_Controller.Roll_Angle_Control.Expect=Target_Angle[1];
      }
      else//�ƶ�����ˣ���Ӧ������������ϵ����Pitch,Roll�����˶��ٶ�
      {
        Horizontal_Vel_Control_Cnt++;
        if(Horizontal_Vel_Control_Cnt>=2)//10ms����һ���ٶ�
        {
          Total_Controller.Latitude_Speed_Control.Expect =ncq_speed_mapping(-Target_Angle[0],Pit_Rol_Max,Max_Horvel);
          Total_Controller.Longitude_Speed_Control.Expect =ncq_speed_mapping(Target_Angle[1],Pit_Rol_Max,Max_Horvel);
          //����ϵ��ˮƽ�ٶȣ�ת������������ϵX-Y������
          //������Pitch��Roll����ˮƽ�ٶȿ���
          Body_Frame_Speed_Feedback.Pit=-NamelessQuad.Speed[_PITCH]*Sin_Yaw+NamelessQuad.Speed[_ROLL]*Cos_Yaw;
          Body_Frame_Speed_Feedback.Rol= NamelessQuad.Speed[_PITCH]*Cos_Yaw+NamelessQuad.Speed[_ROLL]*Sin_Yaw;
          
          Total_Controller.Latitude_Speed_Control.FeedBack=Body_Frame_Speed_Feedback.Pit;//��ͷPitch����Y������
          Total_Controller.Longitude_Speed_Control.FeedBack=Body_Frame_Speed_Feedback.Rol;//���Roll����X������
          
          PID_Control_Div_LPF(&Total_Controller.Latitude_Speed_Control);
          PID_Control_Div_LPF(&Total_Controller.Longitude_Speed_Control);//ˮƽ�ٶȿ������õ������˶����ٶ�
 
          
          accel_target.y=-Total_Controller.Latitude_Speed_Control.Control_OutPut;
          accel_target.x=Total_Controller.Longitude_Speed_Control.Control_OutPut;//�����˶����ٶ�
          accel_to_lean_angles(accel_target,&angle_target);//�����˶����ٶ�ת������̬���
          Total_Controller.Pitch_Angle_Control.Expect=angle_target.y;
          Total_Controller.Roll_Angle_Control.Expect=angle_target.x;  
          
          //Total_Controller.Pitch_Angle_Control.Expect=-Total_Controller.Latitude_Speed_Control.Control_OutPut;
          //Total_Controller.Roll_Angle_Control.Expect=Total_Controller.Longitude_Speed_Control.Control_OutPut;
          Horizontal_Vel_Control_Cnt=0;
        }
      }
      Total_Controller.Latitude_Position_Control.Expect=0;
      Total_Controller.Longitude_Position_Control.Expect=0;
    }
  }
  else//�����㶨����������������ˮƽ��̬
  {
    /********��GPS����ģʽλ��0��ֱ�ӽ�����̬ģʽ���ȴ�GPS�ź��ٴ���������ʱ��***********
    *********�Զ��л���GPS����ģʽ�����Controler_Mode_Select����������й���**********/
    Pos_Hold_SetFlag=0;//��0�������ص�λ��Ϊ����ģʽʱ��
    //�ڿ���ģʽ�����Լ��Ƿ������ٴν���GPS����ģʽ
    Total_Controller.Pitch_Angle_Control.Expect=Target_Angle[0];
    Total_Controller.Roll_Angle_Control.Expect=Target_Angle[1];
  }
  
}



//����ģʽ�£�ң�˻��к�����ˮƽ�ٶȿ���ɲ������ɲͣ���ٸ�ֵλ��ѡ��
uint8_t get_stopping_point_xy(Vector3f *stopping_point)
{
  Vector2f curr_pos,curr_vel,curr_accel;
  float vel_total=0,accel_total=0;   
  curr_pos.x=NamelessQuad.Position[_PITCH];
  curr_pos.y=NamelessQuad.Position[_ROLL];
  curr_vel.x=NamelessQuad.Speed[_PITCH];
  curr_vel.y=NamelessQuad.Speed[_ROLL];   
  curr_accel.x=NamelessQuad.Acceleration[_PITCH];
  curr_accel.y=NamelessQuad.Acceleration[_ROLL];
  
  vel_total=pythagorous2(curr_vel.x,curr_vel.y);
  accel_total=pythagorous2(curr_accel.x,curr_accel.y);
  
  if(vel_total <= 20.0f //��ˮƽ�ٶȵ�С�ڵ���20cm/s
     && accel_total<=40 //��ˮƽ���ٶȵ�С�ڵ���40cm/s^2
       && rMat[2][2]>=0.97)//Cos_Pitch*Cos_Roll����������ˮƽ��̬ԼΪ15deg����������ˮƽ��̬��ԼΪ10deg  
  {
    stopping_point->x = curr_pos.x;
    stopping_point->y = curr_pos.y;
    return 1;
  }
  return 0;
}

