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
#include "NamelessCotrun_SDK.h"

bool auto_altland(float taret_climb_rate,float target_climb_alt)
{
  return land_althold(taret_climb_rate,target_climb_alt);
}
//SDK��ģʽ��Ҫ�ڹ���ģʽ��ʹ��
uint8_t move_with_speed_target(float x_target,float y_target,float delta,SDK_Status *Status,uint16_t number)
{
  static float end_time=0;
  Vector2f vel_target;
  Testime dt;
  vel_target.x=x_target;
  vel_target.y=y_target;
  Test_Period(&dt);
  ncq_control_althold();//�߶ȿ�����Ȼ����
  if(Status->Status[number].Start_Flag==1
     &&Status->Status[number].Execute_Flag==1
       &&Status->Status[number].End_flag==1)
  {
    OpticalFlow_Control_Pure(0);//���֮�󣬽��й�����ͣ
    return 1;
  }
  else
  {
    if(Status->Status[number].Start_Flag==0) 
    {
      end_time=dt.Now_Time+delta;//��λms 
      Status->Status[number].Start_Flag=1;
    } 
    if(dt.Now_Time>end_time)
    {
      Status->Status[number].Execute_Flag=1;
      Status->Status[number].End_flag=1;
      OpticalFlow_Control_Pure(1);//���֮�󣬽��й�����ͣ
      OpticalFlow_Pos_Ctrl_Expect.x=0;
      OpticalFlow_Pos_Ctrl_Expect.y=0;
      end_time=0;
      Status->Transition_Time[number]=200;
      return 1;//�������
    }
    else
    { 
      OpticalFlow_Pos_Ctrl_Expect.x=0;
      OpticalFlow_Pos_Ctrl_Expect.y=0;
      Status->Status[number].Execute_Flag=1;
      OpticalFlow_Vel_Control(vel_target);//�����ٶ�����
      return 0;
    }
  }
}


uint8_t move_with_xy_target(float pos_x_target,float pos_y_target,SDK_Status *Status,uint16_t number)
{
  ncq_control_althold();//�߶ȿ�����Ȼ����
  if(Status->Status[number].Start_Flag==0) 
  {
    OpticalFlow_Pos_Ctrl_Expect.x=OpticalFlow_SINS.Position[_PITCH]+pos_x_target;
    OpticalFlow_Pos_Ctrl_Expect.y=OpticalFlow_SINS.Position[_ROLL]+pos_y_target;
    Status->Status[number].Start_Flag=1;
  }
  
  if(Status->Status[number].Start_Flag==1
     &&Status->Status[number].Execute_Flag==1
       &&Status->Status[number].End_flag==1)
  {
    OpticalFlow_Control_Pure(0);//���֮�󣬽��й�����ͣ
    return 1;
  }
  else
  {    
    if(pythagorous2(OpticalFlow_Pos_Ctrl_Expect.x-OpticalFlow_SINS.Position[_PITCH],
                    OpticalFlow_Pos_Ctrl_Expect.y-OpticalFlow_SINS.Position[_ROLL])<=10.0f)
    {
      Status->Status[number].Execute_Flag=1;
      Status->Status[number].End_flag=1;
      OpticalFlow_Pos_Ctrl_Expect.x=0;
      OpticalFlow_Pos_Ctrl_Expect.y=0;
      Status->Transition_Time[number]=200;
      OpticalFlow_Control_Pure(1);//���֮�󣬽��й�����ͣ
      OpticalFlow_Pos_Ctrl_Expect.x=0;
      OpticalFlow_Pos_Ctrl_Expect.y=0;
      return 1;
    }
    else
    { 
      Status->Status[number].Execute_Flag=1; 
      OpticalFlow_Pos_Control();//����λ�ÿ���
      OpticalFlow_Vel_Control(OpticalFlow_Pos_Ctrl_Output);//�����ٶȿ��� 
      return 0;
    }
  }
}


uint8_t move_with_target(float pos_x_target,float pos_y_target,Duty_Status *Status,uint8_t *Start_flag)
{
  ncq_control_althold();//�߶ȿ�����Ȼ����
  if(*Start_flag==1)
  {
    *Start_flag=0;
  }
  
  if(Status->Start_Flag==0) 
  {
    OpticalFlow_Pos_Ctrl_Expect.x=OpticalFlow_SINS.Position[_PITCH]+pos_x_target;
    OpticalFlow_Pos_Ctrl_Expect.y=OpticalFlow_SINS.Position[_ROLL]+pos_y_target;
    Status->Start_Flag=1;
  }
  
  if(Status->Start_Flag==1
     &&Status->Execute_Flag==1
       &&Status->End_flag==1)
  {
    OpticalFlow_Control_Pure(0);//���֮�󣬽��й�����ͣ
    return 1;
  }
  else
  {    
    if(pythagorous2(OpticalFlow_Pos_Ctrl_Expect.x-OpticalFlow_SINS.Position[_PITCH],
                    OpticalFlow_Pos_Ctrl_Expect.y-OpticalFlow_SINS.Position[_ROLL])<=8.0f)
    {
      Status->Execute_Flag=1;
      Status->End_flag=1;
      //pos_base.x=0;
      //pos_base.y=0;
      OpticalFlow_Control_Pure(1);//���֮�󣬽��й�����ͣ
      OpticalFlow_Pos_Ctrl_Expect.x=0;
      OpticalFlow_Pos_Ctrl_Expect.y=0;
      return 1;
    }
    else
    { 
      Status->Execute_Flag=1; 
      OpticalFlow_Pos_Control();//����λ�ÿ���
      OpticalFlow_Vel_Control(OpticalFlow_Pos_Ctrl_Output);//�����ٶȿ��� 
      return 0;
    }
  }
}


uint8_t move_with_z_target(float z_target,float z_vel,float delta,SDK_Status *Status,uint16_t number)
{
  static float target_rate=0;
  static float target_alt=0;
  static uint8_t end_flag=0;
  static float end_time=0;
  Testime dt;
  Test_Period(&dt);
  OpticalFlow_Control_Pure(0);//ˮƽλ�ÿ�����Ȼ����
  
  if(Status->Status[number].Start_Flag==1
     &&Status->Status[number].Execute_Flag==1
       &&Status->Status[number].End_flag==1)
  {   
    auto_altland(target_rate,target_alt); 
    return 1;
  }
  else
  {
    if(Status->Status[number].Start_Flag==0) 
    {  
      if(z_target==0)//�ٶȿ��ƣ�һ��������ֻ����һ��
      {
        target_rate=z_vel;
        target_alt=0;
        end_flag=1;
      }
      else//λ�ÿ��ƣ�һ��������ֻ����һ��
      {
        target_rate=0;
        target_alt=NamelessQuad.Position[_YAW]+z_target;
        end_flag=2;
      }
      end_time=dt.Now_Time+delta;//��λms 
      Status->Status[number].Start_Flag=1;
    }
    
    
    if(end_flag==1)
    {  
      auto_altland(target_rate,target_alt);
      if(dt.Now_Time>end_time)
      { 
        end_flag=0;
        target_rate=0;
        target_alt=0;
        end_flag=0;
        end_time=0;
        Status->Status[number].Execute_Flag=1;
        Status->Status[number].End_flag=1;
        Status->Transition_Time[number]=200;
        return 1;//�������
      }
      Status->Status[number].Execute_Flag=1;
    }
    else 
    {
      auto_altland(target_rate,target_alt);    
      if(ABS(target_alt-NamelessQuad.Position[_YAW])<=5.0f)
      {
        end_flag=0;
        target_rate=0;
        target_alt=0;
        end_flag=0;
        end_time=0;
        Status->Status[number].Execute_Flag=1;
        Status->Status[number].End_flag=1;
        Status->Transition_Time[number]=200;
        return 1;
      }
      Status->Status[number].Execute_Flag=1;
    } 
  }
  return 0;
}

#define NCQ_SDK_DUTY1 move_with_speed_target(15,0,4000 ,&SDK_Duty_Status,1-1)
#define NCQ_SDK_DUTY2 move_with_speed_target(0,15,4000 ,&SDK_Duty_Status,2-1)
#define NCQ_SDK_DUTY3 move_with_speed_target(-15,0,4000,&SDK_Duty_Status,3-1)
#define NCQ_SDK_DUTY4 move_with_speed_target(0,-15,4000,&SDK_Duty_Status,4-1)
/*
#define NCQ_SDK_DUTY5 move_with_z_target(-20,0,0,&SDK_Duty_Status,5-1)
#define NCQ_SDK_DUTY6 move_with_z_target(0,20,2000,&SDK_Duty_Status,6-1)

#define NCQ_SDK_DUTY1 move_with_xy_target(-100,0,&SDK_Duty_Status,1-1)
#define NCQ_SDK_DUTY2 move_with_xy_target(0,100,&SDK_Duty_Status,2-1)
#define NCQ_SDK_DUTY3 move_with_xy_target(100,0,&SDK_Duty_Status,3-1)
#define NCQ_SDK_DUTY4 move_with_xy_target(0,-100,&SDK_Duty_Status,4-1)
*/
SDK_Status SDK_Duty_Status;
uint16_t SDK_Duty_Cnt=0;
uint16_t SDK_Transition_Time=0;
void NCQ_SDK_Run(void)
{
  if(SDK_Duty_Status.Transition_Time[SDK_Duty_Cnt]>=1) 
    SDK_Duty_Status.Transition_Time[SDK_Duty_Cnt]--;
  
  if(SDK_Duty_Status.Status[SDK_Duty_Cnt].Start_Flag==1
     &&SDK_Duty_Status.Status[SDK_Duty_Cnt].Execute_Flag==1
       &&SDK_Duty_Status.Status[SDK_Duty_Cnt].End_flag==1
         &&SDK_Duty_Status.Transition_Time[SDK_Duty_Cnt]==0)
    SDK_Duty_Cnt++;
  
  
  
  if(SDK_Duty_Cnt>=4) SDK_Duty_Cnt=4;
  
  if(SDK_Duty_Cnt==0)        NCQ_SDK_DUTY1;
  else if(SDK_Duty_Cnt==1)   NCQ_SDK_DUTY2;
  else if(SDK_Duty_Cnt==2)   NCQ_SDK_DUTY3;
  else if(SDK_Duty_Cnt==3)   NCQ_SDK_DUTY4;
  //else if(SDK_Duty_Cnt==4)   NCQ_SDK_DUTY5;
  //else if(SDK_Duty_Cnt==5)   NCQ_SDK_DUTY6;
  //else if(SDK_Duty_Cnt==6)   NCQ_SDK_DUTY7;
  else
  {
    //ncq_control_althold();//�߶ȿ���
    OpticalFlow_Control(0);//λ�ÿ���
  }
}


void NCQ_SDK_Reset(void)
{
  uint16_t i=0;
  for(i=0;i<SDK_Duty_Max;i++)
  {
    SDK_Duty_Status.Status[i].Start_Flag=0;
    SDK_Duty_Status.Status[i].Execute_Flag=0;
    SDK_Duty_Status.Status[i].End_flag=0;
  }
  SDK_Duty_Cnt=0;
}

#define Circle_Piont_Max  24
#define Circle_R  50
static Duty_Status circle_status[Circle_Piont_Max+1];
static uint8_t Circle_Start_Flag=1;
float circle_pos_x_delta[Circle_Piont_Max+1]={0},circle_pos_y_delta[Circle_Piont_Max+1]={0};
static Vector2f circle_pos_base; 
uint8_t NCQ_SDK_Circle(void)
{
  static uint16_t circle_cnt=0;
  static float circle_angle=0;
  uint16_t i=0;
  
  if(Circle_Start_Flag==1)
  {
    circle_pos_base.x=OpticalFlow_SINS.Position[_PITCH];
    circle_pos_base.y=OpticalFlow_SINS.Position[_ROLL];
    for(i=0;i<Circle_Piont_Max+1;i++)
    {
      circle_angle=15*i;
      circle_pos_x_delta[i]=circle_pos_base.x+(1-cos(circle_angle*DEG2RAD))*Circle_R;
      circle_pos_y_delta[i]=circle_pos_base.y+sin(circle_angle*DEG2RAD)*Circle_R;
    }
  }
  else if(Circle_Start_Flag==2)
  {
    ncq_control_althold();
    OpticalFlow_Control(0);//�������ˮƽλ�ÿ���
    return 1;
  }
  
  if(move_with_target(circle_pos_x_delta[circle_cnt],circle_pos_y_delta[circle_cnt],&circle_status[circle_cnt],&Circle_Start_Flag))
  {
    circle_cnt++;
    if(circle_cnt==Circle_Piont_Max+1)
    {
      circle_cnt=0;
      for(uint16_t i=0;i<Circle_Piont_Max+1;i++)
      {
        circle_status[i].End_flag=0;
        circle_status[i].Execute_Flag=0;
        circle_status[i].Start_Flag=0;
        //circle_pos_x_delta[i]=0;
        //circle_pos_y_delta[i]=0;
        circle_angle=0;
      }
      Circle_Start_Flag=2;
      return 1;
    }
  }
  return 0;
}


unsigned char sdk_data_to_send[50];
void SDK_DT_Send_Data(unsigned char *dataToSend , unsigned char length)
{
  UART3_Send(sdk_data_to_send, length);
}

void SDK_DT_Send_Check(unsigned char mode)
{
  sdk_data_to_send[0]=0xAA;
  sdk_data_to_send[1]=0xAF;
  sdk_data_to_send[2]=0xFC;
  sdk_data_to_send[3]=2;
  sdk_data_to_send[4]=mode;
  sdk_data_to_send[5]=0
    ;
  u8 sum = 0;
  for(u8 i=0;i<6;i++) sum += sdk_data_to_send[i];
  sdk_data_to_send[6]=sum;
  SDK_DT_Send_Data(sdk_data_to_send, 7);
}

uint8_t SDK_Now_Mode=0x00;
uint8_t SDK_Mode_Set=0x02;
#define SDK_TARGET_X_OFFSET  0
#define SDK_TARGET_Y_OFFSET  0//-4.2
Line  SDK_Line;
Point SDK_Point;
uint8_t SDK_Recieve_Flag=0;
Vector2f SDK_Target,SDK_Target_Offset;
float SDK_Target_Yaw_Gyro=0;
#define  Pixel_Size    0.0048
#define  Focal_Length  0.42

void SDK_Line_DT_Reset()
{
  SDK_Line.data=0;  
  SDK_Line.x=0;
  SDK_Line.y=0;
  SDK_Line.data=0;
  SDK_Line.line_angle=0;
  SDK_Line.up_ok=0;
  SDK_Line.down_ok=0;
  SDK_Line.left_ok=0;
  SDK_Line.right_ok=0;
  SDK_Line.flag=0;
  SDK_Line.line_ctrl_enable=0;
}

void SDK_Point_DT_Reset()
{
  SDK_Point.x=0;
  SDK_Point.y=0;
  SDK_Point.Pixel=0;
  SDK_Point.flag=0;
}
void Openmv_Data_Receive_Anl(u8 *data_buf,u8 num)
{
  //for(u8 i=0;i<(num-1);i++)  sum += *(data_buf+i);
  //if(!(sum==*(data_buf+num-1)))	return;	                //�������У������	
  if(!(*(data_buf)==0xAA && *(data_buf+1)==0xAF))	return;//������֡ͷ����		   
  if(*(data_buf+2)==0XC0)//ɫ����
  {
    SDK_Recieve_Flag=1;
  }
  else if(*(data_buf+2)==0XF3)//�߼��
  {
    SDK_Now_Mode=0x02;
    SDK_Line.x=*(data_buf+4)<<8|*(data_buf+5);
    SDK_Line.line_angle=(*(data_buf+6)<<8)|*(data_buf+7);
    SDK_Line.flag=*(data_buf+8);        
    //line.flag�ӵ�λ����λ�ֱ��Ӧ��ͷ��Ұ�����������ĸ����򣬼�⵽��ֱ��Ϊ1������Ϊ0
    SDK_Line.up_ok    = (SDK_Line.flag & 0x01)>>0;
    SDK_Line.down_ok  = (SDK_Line.flag & 0x02)>>1;
    SDK_Line.left_ok  = (SDK_Line.flag & 0x04)>>2;
    SDK_Line.right_ok = (SDK_Line.flag & 0x08)>>3;
    
    if(SDK_Line.up_ok==1||SDK_Line.down_ok==1)
    {
      SDK_Line.line_ctrl_enable=1;
      SDK_Target.x=(Pixel_Size*(40-SDK_Line.x)*NamelessQuad.Position[_YAW])/Focal_Length
        +NamelessQuad.Position[_YAW]*tan(Roll* DEG2RAD);
      if(SDK_Line.line_angle>0&&SDK_Line.line_angle<90)
        SDK_Target_Yaw_Gyro=-SDK_Line.line_angle;
      if(SDK_Line.line_angle<180&&SDK_Line.line_angle>90)
        SDK_Target_Yaw_Gyro=180-SDK_Line.line_angle;
      
      SDK_Recieve_Flag=1;
    }
    
    SDK_Point_DT_Reset();
  }
  else if(*(data_buf+2)==0XF2)//����
  {
    SDK_Now_Mode=0x01;
    SDK_Point.x=*(data_buf+4)<<8|*(data_buf+5);
    SDK_Point.y=*(data_buf+6)<<8|*(data_buf+7);
    SDK_Point.Pixel=*(data_buf+8)<<8|*(data_buf+9);
    SDK_Point.flag=*(data_buf+10);
    SDK_Recieve_Flag=1;
    
    SDK_Target_Offset.x=SDK_TARGET_X_OFFSET;
    SDK_Target_Offset.y=SDK_TARGET_Y_OFFSET;
    
    SDK_Target.x=(Pixel_Size*(40-SDK_Point.x)*NamelessQuad.Position[_YAW])/Focal_Length
      +NamelessQuad.Position[_YAW]*tan(Roll* DEG2RAD)-SDK_Target_Offset.x;
    SDK_Target.y=(Pixel_Size*(30-SDK_Point.y)*NamelessQuad.Position[_YAW])/Focal_Length
      +NamelessQuad.Position[_YAW]*tan(Pitch* DEG2RAD)-SDK_Target_Offset.y;  
    SDK_Line_DT_Reset(); 
  }
  else if(*(data_buf+2)==0XC3)//��ά��
  {
    SDK_Recieve_Flag=1;
  }
  //��������SDKģʽ
  else if(*(data_buf+2)==0X01)//�߶�λ�ÿ���
  {
    if(*(data_buf+4)==0X01)//����  
    {
      Total_Controller.High_Position_Control.Expect+=*(data_buf+5);
      Unwanted_Lock_Flag=0;
    }
    else if(*(data_buf+4)==0X02)//�½�
    {
      Total_Controller.High_Position_Control.Expect-=*(data_buf+5);
    }
    else if(*(data_buf+4)==0X03)//������ɣ�������Ŀ��߶�
    {
      Total_Controller.High_Position_Control.Expect+=*(data_buf+5);
      Unwanted_Lock_Flag=0;
      Reserve_Mode_Fast_Exchange_Flag=1;
    }
    SDK_Recieve_Flag=1;
  }
  else
  {
    SDK_Recieve_Flag=0;
  }
}


static u8 state = 0;
static u8 RxBuffer[50];
void SDK_Data_Receive_Prepare(u8 data)
{
  static u8 _data_len = 0,_data_cnt = 0;
  if(state==0&&data==0xAA)//֡ͷ1
  {
    state=1;
    RxBuffer[0]=data;
  }
  else if(state==1&&data==0xAF)//֡ͷ2
  {
    state=2;
    RxBuffer[1]=data;
  }
  else if(state==2&&data<0XFF)//�����ֽ�
  {
    state=3;
    RxBuffer[2]=data;
  }
  else if(state==3&&data<50)//���ݳ���
  {
    state = 4;
    RxBuffer[3]=data;
    _data_len = data;
    _data_cnt = 0;
  }
  else if(state==4&&_data_len>0)//�ж������ݳ��ȣ��ʹ���ٸ�
  {
    _data_len--;
    RxBuffer[4+_data_cnt++]=data;
    if(_data_len==0) state = 5;
  }
  else if(state==5)//����������У���
  {
    state = 0;
    RxBuffer[4+_data_cnt]=data;
    Openmv_Data_Receive_Anl(RxBuffer,_data_cnt+5);
  }
  else state = 0;
}


void SDK_Init(void)
{
  float sdk_mode_default=0;
  SDK_Line_DT_Reset();//��λSDK�߼������
  SDK_Point_DT_Reset();//��λSDK��������
  if(ReadFlashParameterOne(SDK_MODE_DEFAULT,&sdk_mode_default))
  {
    SDK_Mode_Set=(uint8_t)(sdk_mode_default);
    SDK_DT_Send_Check(SDK_Mode_Set);//��ʼ��opemmv����ģʽ��Ĭ�����ϴι���״̬����
  } 
}

