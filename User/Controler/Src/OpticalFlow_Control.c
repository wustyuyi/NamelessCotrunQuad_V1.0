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
#include "OpticalFlow_Control.h"

extern Vector2f OpticalFlow_Position;
extern Vector2f OpticalFlow_Speed;
extern Vector2f OpticalFlow_Speed_Err;
extern Vector2f OpticalFlow_Position_Err;

Vector2f OpticalFlow_Pos_Ctrl_Expect={0};
Vector2f OpticalFlow_Pos_Ctrl_Err={0};
Vector2f OpticalFlow_Pos_Ctrl_Integrate={0};
Vector2f OpticalFlow_Pos_Ctrl_Output={0};

Vector2f OpticalFlow_Ctrl_Expect={0};
Vector2f OpticalFlow_Ctrl_Err={0};
Vector2f OpticalFlow_Ctrl_Integrate={0};
Vector2f OpticalFlow_Ctrl_Output={0};

void OpticalFlow_SINS_Reset(void)
{ 
  OpticalFlow_SINS.Position[_PITCH]=0;
  OpticalFlow_SINS.Speed[_PITCH]=0;
  OpticalFlow_SINS.Position[_ROLL]=0;
  OpticalFlow_SINS.Speed[_ROLL]=0;
  OpticalFlow_Position.x=0;
  OpticalFlow_Position.y=0;
}


void OpticalFlow_Ctrl_Reset(void)
{ 
  OpticalFlow_Ctrl_Integrate.x=0.0f;
  OpticalFlow_Ctrl_Integrate.y=0.0f;
  OpticalFlow_Pos_Ctrl_Integrate.x=0.0f;
  OpticalFlow_Pos_Ctrl_Integrate.y=0.0f;
  OpticalFlow_Pos_Ctrl_Expect.x=0;
  OpticalFlow_Pos_Ctrl_Expect.y=0;
}

float OpticalFlow_Expect_Speed_Mapping(float input,uint16_t input_max,float output_max)
{
  float output_speed=0;
  float temp_scale=(float)(input/input_max);
  temp_scale=constrain_float(temp_scale,-1.0f, 1.0f);
  if(temp_scale>=0) output_speed=(float)(output_max*temp_scale*temp_scale);
  else output_speed=(float)(-output_max*temp_scale*temp_scale); 
  return output_speed;
}

void OpticalFlow_Set_Target_Point(Vector2f target)
{
  OpticalFlow_Pos_Ctrl_Expect.x=target.x;
  OpticalFlow_Pos_Ctrl_Expect.y=target.y;
}

void OpticalFlow_Set_Target_Vel(Vector2f target)
{
  OpticalFlow_Ctrl_Expect.x=target.x;
  OpticalFlow_Ctrl_Expect.y=target.y;
}

void OpticalFlow_Control(uint8_t force_brake_flag)
{
  static uint16_t SDK_Ctrl_Cnt=0;
  if(SDK_Ctrl_Mode==0)//SDKģʽ�£������ݽ��գ���������ģʽ
  {
      if(Roll_Control==0
         &&Pitch_Control==0)//��ˮƽң��������
      {
        /**************************����λ�ÿ�����************************************/
        if(OpticalFlow_Pos_Ctrl_Expect.x==0
           &&OpticalFlow_Pos_Ctrl_Expect.y==0)
        {
          if(force_brake_flag==1||(rMat[2][2]>=0.95
             &&pythagorous2(OpticalFlow_SINS.Speed[_PITCH],OpticalFlow_SINS.Speed[_ROLL])<=40))//��˻��к󣬸��ݵ�ǰ�ٶȡ�����ж��Ƿ������ͣ
          {
            OpticalFlow_Pos_Ctrl_Expect.x=OpticalFlow_SINS.Position[_PITCH];
            OpticalFlow_Pos_Ctrl_Expect.y=OpticalFlow_SINS.Position[_ROLL];
          }
          else  //��˻���δ������ͣ����ʱ��ֻ�����ٶȿ��� 
          {
            OpticalFlow_Pos_Ctrl_Output.x=0;
            OpticalFlow_Pos_Ctrl_Output.y=0;
          }
        }
        else  OpticalFlow_Pos_Control();
       
        /***********��ֻ��Ҫ�ٶȿ���ʱ����������ע�ͣ����޵���ʱ��*************/
         //OpticalFlow_Pos_Ctrl_Output.x=0;
         //OpticalFlow_Pos_Ctrl_Output.y=0;
        /**************************����ģ�͵ļ��ٶ�-��̬��ӳ�䣬���ֱ�Ӹ���̬��������������20������************************************/
        OpticalFlow_Vel_Control(OpticalFlow_Pos_Ctrl_Output);//�ٶ�����
      }
      else
      {
        OpticalFlow_Pos_Ctrl_Output.x=OpticalFlow_Expect_Speed_Mapping(-Target_Angle[1],Pit_Rol_Max,OpticalFlow_Speed_Control_Max);
        OpticalFlow_Pos_Ctrl_Output.y=OpticalFlow_Expect_Speed_Mapping(-Target_Angle[0],Pit_Rol_Max,OpticalFlow_Speed_Control_Max); 
        if(OpticalFlow_Speed_Control_Mode==1)
        {
          OpticalFlow_Vel_Control(OpticalFlow_Pos_Ctrl_Output);//�ٶ�����
        }
        else
        {
          Total_Controller.Pitch_Angle_Control.Expect=Target_Angle[0];
          Total_Controller.Roll_Angle_Control.Expect=Target_Angle[1];      
        }
        OpticalFlow_Pos_Ctrl_Expect.x=0;
        OpticalFlow_Pos_Ctrl_Expect.y=0;
      }
      PID_LPF_Reset(&Total_Controller.SDK_Roll_Position_Control,SDK_Roll_Position_Controler);
      PID_LPF_Reset(&Total_Controller.SDK_Pitch_Position_Control,SDK_Pitch_Position_Controler);
  }
  else//SDK����ģʽ
  {
      if(Roll_Control==0
         &&Pitch_Control==0)//��ˮƽң��������
    {  
        if(SDK_Line.line_ctrl_enable==1)//�߼��
        {
          /***********��ֻ��Ҫ�ٶȿ���ʱ����������ע�ͣ����޵���ʱ��*************/
            SDK_Ctrl_Cnt++;
            if(SDK_Ctrl_Cnt>=4)//20ms
            {
              Total_Controller.SDK_Roll_Position_Control.Expect=0;
              Total_Controller.SDK_Roll_Position_Control.FeedBack=SDK_Target.x;
              PID_Control_SDK_Err_LPF(&Total_Controller.SDK_Roll_Position_Control);   
              accel_target.x=constrain_float(Total_Controller.SDK_Roll_Position_Control.Control_OutPut,
                                            -Total_Controller.Optical_Speed_Control.Control_OutPut_Limit,
                                             Total_Controller.Optical_Speed_Control.Control_OutPut_Limit);                             
              Total_Controller.Roll_Angle_Control.Expect=constrain_float(fast_atan(accel_target.x/(GRAVITY_MSS*100))*RAD2DEG,-30,30);//roll                                
              SDK_Ctrl_Cnt=0;
            }
            //if(ABS(SDK_Target_Yaw_Gyro)<=10) OpticalFlow_Y_Vel_Control(8);
            //else if(ABS(SDK_Target_Yaw_Gyro)<=20) OpticalFlow_Y_Vel_Control(5);
            //else if(ABS(SDK_Target_Yaw_Gyro)<=50) OpticalFlow_Y_Vel_Control(3);
            //else OpticalFlow_Y_Vel_Control(2);
            if(ABS(SDK_Target_Yaw_Gyro)<=10) OpticalFlow_Y_Vel_Control(5);
            else if(ABS(SDK_Target_Yaw_Gyro)<=20) OpticalFlow_Y_Vel_Control(3);
            else if(ABS(SDK_Target_Yaw_Gyro)<=50) OpticalFlow_Y_Vel_Control(2);
            else OpticalFlow_Y_Vel_Control(1);
            
            OpticalFlow_Pos_Ctrl_Expect.x=0;
            OpticalFlow_Pos_Ctrl_Expect.y=0;
            force_brake_flag=1;
        }
        else if(SDK_Point.flag==1)//���ٵ���
        {
            SDK_Ctrl_Cnt++;
            if(SDK_Ctrl_Cnt>=4)//20ms
            {
              Total_Controller.SDK_Roll_Position_Control.Expect=0;
              Total_Controller.SDK_Roll_Position_Control.FeedBack=SDK_Target.x;
              PID_Control_SDK_Err_LPF(&Total_Controller.SDK_Roll_Position_Control);
                          
              Total_Controller.SDK_Pitch_Position_Control.Expect=0;
              Total_Controller.SDK_Pitch_Position_Control.FeedBack=SDK_Target.y;
              PID_Control_SDK_Err_LPF(&Total_Controller.SDK_Pitch_Position_Control);
              
              accel_target.x=constrain_float(Total_Controller.SDK_Roll_Position_Control.Control_OutPut,
                                            -Total_Controller.Optical_Speed_Control.Control_OutPut_Limit,
                                             Total_Controller.Optical_Speed_Control.Control_OutPut_Limit);                             
              Total_Controller.Roll_Angle_Control.Expect=constrain_float(fast_atan(accel_target.x/(GRAVITY_MSS*100))*RAD2DEG,-20,20);//roll
              
              
              accel_target.y=constrain_float(Total_Controller.SDK_Pitch_Position_Control.Control_OutPut,
                                             -Total_Controller.Optical_Speed_Control.Control_OutPut_Limit,
                                              Total_Controller.Optical_Speed_Control.Control_OutPut_Limit);//450
              Total_Controller.Pitch_Angle_Control.Expect=constrain_float(fast_atan(accel_target.y*Cos_Roll/(GRAVITY_MSS*100))*RAD2DEG,-20,20);//pitch
              
              SDK_Ctrl_Cnt=0;
            }
            OpticalFlow_Pos_Ctrl_Expect.x=0;
            OpticalFlow_Pos_Ctrl_Expect.y=0;
            force_brake_flag=1;
        }
        else//SDKģʽ�£�δ����������
        {
              /**************************����λ�ÿ�����************************************/
              if(OpticalFlow_Pos_Ctrl_Expect.x==0
                 &&OpticalFlow_Pos_Ctrl_Expect.y==0)
              {
                if(force_brake_flag==1||(rMat[2][2]>=0.95
                   &&pythagorous2(OpticalFlow_SINS.Speed[_PITCH],OpticalFlow_SINS.Speed[_ROLL])<=40))//��˻��к󣬸��ݵ�ǰ�ٶȡ�����ж��Ƿ������ͣ
                {
                  OpticalFlow_Pos_Ctrl_Expect.x=OpticalFlow_SINS.Position[_PITCH];
                  OpticalFlow_Pos_Ctrl_Expect.y=OpticalFlow_SINS.Position[_ROLL];
                }
                else  //��˻���δ������ͣ����ʱ��ֻ�����ٶȿ��� 
                {
                  OpticalFlow_Pos_Ctrl_Output.x=0;
                  OpticalFlow_Pos_Ctrl_Output.y=0;
                }
              }
              else  OpticalFlow_Pos_Control();
                /**************************����ģ�͵ļ��ٶ�-��̬��ӳ�䣬���ֱ�Ӹ���̬��������������20������************************************/
              OpticalFlow_Vel_Control(OpticalFlow_Pos_Ctrl_Output);//�ٶ�����        
              PID_LPF_Reset(&Total_Controller.SDK_Roll_Position_Control,SDK_Roll_Position_Controler);
              PID_LPF_Reset(&Total_Controller.SDK_Pitch_Position_Control,SDK_Pitch_Position_Controler);
       }
    }
    else//SDKģʽ�´����ֶ���˲���ʱ����������Դ��ң��������
    {
          Total_Controller.Pitch_Angle_Control.Expect=Target_Angle[0];
          Total_Controller.Roll_Angle_Control.Expect=Target_Angle[1];
          OpticalFlow_Pos_Ctrl_Expect.x=0;
          OpticalFlow_Pos_Ctrl_Expect.y=0;
          force_brake_flag=1;
    }  
    SDK_Recieve_Flag=0; 
    OpticalFlow_Pos_Ctrl_Expect.x=0;
    OpticalFlow_Pos_Ctrl_Expect.y=0;
  }
}


void OpticalFlow_Control_Pure(uint8_t force_brake_flag)
{
		/////////////////////////////////SDKλ�ÿ��ƿ�ʼ////////////////////////////////////////						
	if(ngs_sdk.update_flag==true)
	{
			if(ngs_sdk.move_flag.sdk_front_flag==true||ngs_sdk.move_flag.sdk_behind_flag==true)//ǰ��/����
			{
					OpticalFlow_Pos_Ctrl_Expect.x=OpticalFlow_SINS.Position[_PITCH];										//���ұ���
					OpticalFlow_Pos_Ctrl_Expect.y=OpticalFlow_SINS.Position[_ROLL]+ngs_sdk.f_distance;	//ǰ�����		
					Total_Controller.High_Position_Control.Expect=NamelessQuad.Position[_YAW];	 				//���±���																
			}
			
			if(ngs_sdk.move_flag.sdk_left_flag==true||ngs_sdk.move_flag.sdk_right_flag==true)//����/����
			{
				  OpticalFlow_Pos_Ctrl_Expect.x=OpticalFlow_SINS.Position[_PITCH]+ngs_sdk.f_distance;//���ҵ���
					OpticalFlow_Pos_Ctrl_Expect.y=OpticalFlow_SINS.Position[_ROLL];										 //ǰ�󱣳�			
					Total_Controller.High_Position_Control.Expect=NamelessQuad.Position[_YAW];			 	 //���±���														
			}
			
			if(ngs_sdk.move_flag.sdk_up_flag==true||ngs_sdk.move_flag.sdk_down_flag==true)//����/�½�
			{
					OpticalFlow_Pos_Ctrl_Expect.x=OpticalFlow_SINS.Position[_PITCH];															//ǰ�󱣳�
					OpticalFlow_Pos_Ctrl_Expect.y=OpticalFlow_SINS.Position[_ROLL];																//���ұ���
				  Total_Controller.High_Position_Control.Expect=NamelessQuad.Position[_YAW]+ngs_sdk.f_distance; //���µ���										
			}
			ngs_sdk.move_flag.sdk_front_flag=false;
			ngs_sdk.move_flag.sdk_behind_flag=false;
			ngs_sdk.move_flag.sdk_left_flag=false;
			ngs_sdk.move_flag.sdk_right_flag=false;
			ngs_sdk.move_flag.sdk_up_flag=false;
			ngs_sdk.move_flag.sdk_down_flag=false;							
			ngs_sdk.update_flag=false;
	}
	
      if(Roll_Control==0
         &&Pitch_Control==0)//��ˮƽң��������
      {
        /**************************����λ�ÿ�����************************************/
        if(OpticalFlow_Pos_Ctrl_Expect.x==0
           &&OpticalFlow_Pos_Ctrl_Expect.y==0)
        {
          if(force_brake_flag==1||(rMat[2][2]>=0.95
             &&pythagorous2(OpticalFlow_SINS.Speed[_PITCH],OpticalFlow_SINS.Speed[_ROLL])<=40))//��˻��к󣬸��ݵ�ǰ�ٶȡ�����ж��Ƿ������ͣ
          {
            OpticalFlow_Pos_Ctrl_Expect.x=OpticalFlow_SINS.Position[_PITCH];
            OpticalFlow_Pos_Ctrl_Expect.y=OpticalFlow_SINS.Position[_ROLL];
          }
          else  //��˻���δ������ͣ����ʱ��ֻ�����ٶȿ��� 
          {
            OpticalFlow_Pos_Ctrl_Output.x=0;
            OpticalFlow_Pos_Ctrl_Output.y=0;
          }
        }
        else  OpticalFlow_Pos_Control();
       
        /***********��ֻ��Ҫ�ٶȿ���ʱ����������ע�ͣ����޵���ʱ��*************/
         //OpticalFlow_Pos_Ctrl_Output.x=0;
         //OpticalFlow_Pos_Ctrl_Output.y=0;
        /**************************����ģ�͵ļ��ٶ�-��̬��ӳ�䣬���ֱ�Ӹ���̬��������������20������************************************/
        OpticalFlow_Vel_Control(OpticalFlow_Pos_Ctrl_Output);//�ٶ�����
      }
      else
      {
        OpticalFlow_Pos_Ctrl_Output.x=OpticalFlow_Expect_Speed_Mapping(-Target_Angle[1],Pit_Rol_Max,OpticalFlow_Speed_Control_Max);
        OpticalFlow_Pos_Ctrl_Output.y=OpticalFlow_Expect_Speed_Mapping(-Target_Angle[0],Pit_Rol_Max,OpticalFlow_Speed_Control_Max); 
        if(OpticalFlow_Speed_Control_Mode==1)
        {
          OpticalFlow_Vel_Control(OpticalFlow_Pos_Ctrl_Output);//�ٶ�����
        }
        else
        {
          Total_Controller.Pitch_Angle_Control.Expect=Target_Angle[0];
          Total_Controller.Roll_Angle_Control.Expect=Target_Angle[1];      
        }
        OpticalFlow_Pos_Ctrl_Expect.x=0;
        OpticalFlow_Pos_Ctrl_Expect.y=0;
      }
      PID_LPF_Reset(&Total_Controller.SDK_Roll_Position_Control,SDK_Roll_Position_Controler);
      PID_LPF_Reset(&Total_Controller.SDK_Pitch_Position_Control,SDK_Pitch_Position_Controler);
}


void OpticalFlow_Pos_Control(void)
{
  static uint16_t OpticalFlow_Pos_Ctrl_Cnt=0;
  OpticalFlow_Pos_Ctrl_Cnt++;
  if(OpticalFlow_Pos_Ctrl_Cnt>=10)//50ms����һ���ٶȣ���������Ƶ�ʹ���ϵͳ��Ӧ������
  {
    //����λ��ƫ��  
    OpticalFlow_Pos_Ctrl_Err.x=OpticalFlow_Pos_Ctrl_Expect.x-OpticalFlow_SINS.Position[_PITCH];
    OpticalFlow_Pos_Ctrl_Err.y=OpticalFlow_Pos_Ctrl_Expect.y-OpticalFlow_SINS.Position[_ROLL];
    //����λ�ÿ������
    OpticalFlow_Pos_Ctrl_Output.x=Total_Controller.Optical_Position_Control.Kp*OpticalFlow_Pos_Ctrl_Err.x;
    OpticalFlow_Pos_Ctrl_Output.y=Total_Controller.Optical_Position_Control.Kp*OpticalFlow_Pos_Ctrl_Err.y;
    OpticalFlow_Pos_Ctrl_Cnt=0;
  }
}


void OpticalFlow_Vel_Control(Vector2f target)
{ 
  static uint16_t OpticalFlow_Vel_Ctrl_Cnt=0;
  OpticalFlow_Ctrl_Expect.x= target.x;//�ٶ�����
  OpticalFlow_Ctrl_Expect.y= target.y;
  OpticalFlow_Vel_Ctrl_Cnt++;
  if(OpticalFlow_Vel_Ctrl_Cnt>=4)//20ms����һ���ٶȣ���������Ƶ�ʹ���ϵͳ��Ӧ������
  {
    OpticalFlow_Ctrl_Err.x=constrain_float(OpticalFlow_Ctrl_Expect.x-OpticalFlow_SINS.Speed[_PITCH],-Total_Controller.Optical_Speed_Control.Err_Max,Total_Controller.Optical_Speed_Control.Err_Max);//30
    OpticalFlow_Ctrl_Err.y=constrain_float(OpticalFlow_Ctrl_Expect.y-OpticalFlow_SINS.Speed[_ROLL] ,-Total_Controller.Optical_Speed_Control.Err_Max,Total_Controller.Optical_Speed_Control.Err_Max);
    
    //if(ABS(OpticalFlow_Ctrl_Err.x)<=Total_Controller.Optical_Speed_Control.Integrate_Separation_Err)  
      OpticalFlow_Ctrl_Integrate.x+=Total_Controller.Optical_Speed_Control.Ki*OpticalFlow_Ctrl_Err.x;//0.1  15
    //if(ABS(OpticalFlow_Ctrl_Err.y)<=Total_Controller.Optical_Speed_Control.Integrate_Separation_Err)  
      OpticalFlow_Ctrl_Integrate.y+=Total_Controller.Optical_Speed_Control.Ki*OpticalFlow_Ctrl_Err.y;
    
    OpticalFlow_Ctrl_Integrate.x=constrain_float(OpticalFlow_Ctrl_Integrate.x,-Total_Controller.Optical_Speed_Control.Integrate_Max,Total_Controller.Optical_Speed_Control.Integrate_Max);
    OpticalFlow_Ctrl_Integrate.y=constrain_float(OpticalFlow_Ctrl_Integrate.y,-Total_Controller.Optical_Speed_Control.Integrate_Max,Total_Controller.Optical_Speed_Control.Integrate_Max);
    
    OpticalFlow_Ctrl_Output.x=OpticalFlow_Ctrl_Integrate.x+Total_Controller.Optical_Speed_Control.Kp*OpticalFlow_Ctrl_Err.x;//4.5
    OpticalFlow_Ctrl_Output.y=OpticalFlow_Ctrl_Integrate.y+Total_Controller.Optical_Speed_Control.Kp*OpticalFlow_Ctrl_Err.y;

    accel_target.y=-constrain_float(OpticalFlow_Ctrl_Output.y,-Total_Controller.Optical_Speed_Control.Control_OutPut_Limit,Total_Controller.Optical_Speed_Control.Control_OutPut_Limit);//450
    accel_target.x=-constrain_float(OpticalFlow_Ctrl_Output.x,-Total_Controller.Optical_Speed_Control.Control_OutPut_Limit,Total_Controller.Optical_Speed_Control.Control_OutPut_Limit);//�����˶����ٶ�
    accel_to_lean_angles(accel_target,&angle_target);//�����˶����ٶ�ת������̬���
    Total_Controller.Pitch_Angle_Control.Expect=angle_target.y;
    Total_Controller.Roll_Angle_Control.Expect=angle_target.x;
    OpticalFlow_Vel_Ctrl_Cnt=0;
  }
}

void OpticalFlow_Y_Vel_Control(float target_y)
{ 
  static uint16_t OpticalFlow_Vel_Ctrl_Cnt=0;
  OpticalFlow_Ctrl_Expect.y= target_y;
  OpticalFlow_Vel_Ctrl_Cnt++;
  if(OpticalFlow_Vel_Ctrl_Cnt>=4)//20ms����һ���ٶȣ���������Ƶ�ʹ���ϵͳ��Ӧ������
  {
    OpticalFlow_Ctrl_Err.y=constrain_float(OpticalFlow_Ctrl_Expect.y-OpticalFlow_SINS.Speed[_ROLL] ,-Total_Controller.Optical_Speed_Control.Err_Max,Total_Controller.Optical_Speed_Control.Err_Max);
    
    OpticalFlow_Ctrl_Integrate.y+=Total_Controller.Optical_Speed_Control.Ki*OpticalFlow_Ctrl_Err.y;
    
    OpticalFlow_Ctrl_Integrate.y=constrain_float(OpticalFlow_Ctrl_Integrate.y,-Total_Controller.Optical_Speed_Control.Integrate_Max,Total_Controller.Optical_Speed_Control.Integrate_Max);
    
    OpticalFlow_Ctrl_Output.y=OpticalFlow_Ctrl_Integrate.y+Total_Controller.Optical_Speed_Control.Kp*OpticalFlow_Ctrl_Err.y;

    accel_target.y=-constrain_float(OpticalFlow_Ctrl_Output.y,-Total_Controller.Optical_Speed_Control.Control_OutPut_Limit,Total_Controller.Optical_Speed_Control.Control_OutPut_Limit);//450
    accel_to_lean_angles(accel_target,&angle_target);//�����˶����ٶ�ת������̬���
    Total_Controller.Pitch_Angle_Control.Expect=angle_target.y;
    OpticalFlow_Vel_Ctrl_Cnt=0;
  }
}

