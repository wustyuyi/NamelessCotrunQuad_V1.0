/* Copyright (c)  2019-2025 Wuhan Nameless Innovation Technology Co.,Ltd. All rights reserved.*/
/*----------------------------------------------------------------------------------------------------------------------/
开源并不等于免费，先驱者的历史已经证明，在国内这个环境下，毫无收益的开源，单靠坊间个人爱好者，自发地参与项
目完善的方式行不通，好的开源项目需要请专职人员做好售后服务、手把手教学、统计用户反馈需求、在实践中完成对产
品的一次次完善与迭代升级。经过综合考虑，无名飞控开源代码中，程序仅保留公司正版激活功能代码，版本激活无实际
功能，属于公司产品常规出厂操作，不影响客户学习，其余代码全部开放给客户学习，客户移植和二次开发代码请保留代
码版权。
-----------------------------------------------------------------------------------------------------------------------/
*               本程序只供购买者学习使用，版权著作权属于无名科创团队，无名科创团队将飞控程序源码提供给购买者，
*               购买者要为无名科创团队提供保护，未经作者许可，不得将源代码提供给他人，不得将源代码放到网上供他人免费下载， 
*               更不能以此销售牟利，如发现上述行为，无名科创团队将诉之以法律解决！！！
-----------------------------------------------------------------------------------------------------------------------
*                                                 为什么选择无名创新？
*                                         感动人心价格厚道，最靠谱的开源飞控；
*                                         国内业界良心之作，最精致的售后服务；
*                                         追求极致用户体验，高效进阶学习之路；
*                                         萌新不再孤单求索，合理把握开源尺度；
*                                         响应国家扶贫号召，促进教育体制公平；
*                                         新时代奋斗最出彩，建人类命运共同体。 
-----------------------------------------------------------------------------------------------------------------------
*               生命不息、奋斗不止；前人栽树，后人乘凉！！！
*               开源不易，且学且珍惜，祝早日逆袭、进阶成功！！！
*               学习优秀者，简历可推荐到DJI、ZEROTECH、XAG、AEE、GDU、AUTEL、EWATT、HIGH GREAT等公司就业
*               求职简历请发送：15671678205@163.com，需备注求职意向单位、岗位、待遇等
*               无名科创开源飞控QQ群：2号群465082224、1号群540707961（人员已满）
*               CSDN博客：http://blog.csdn.net/u011992534
*               优酷ID：NamelessCotrun无名小哥
*               B站教学视频：https://space.bilibili.com/67803559/#/video
*               客户使用心得、改进意见征集贴：http://www.openedv.com/forum.php?mod=viewthread&tid=234214&extra=page=1
*               淘宝店铺：https://shop348646912.taobao.com/?spm=2013.1.1000126.2.5ce78a88ht1sO2
*               百度贴吧:无名科创开源飞控
*               公司官网:www.nameless.tech
*               无名创新国内首款TI开源飞控设计初衷、知乎专栏:https://zhuanlan.zhihu.com/p/54471146
*               修改日期:2019/11/27                    
*               版本：慧飞者PRO——WisdomPilot_Pro_V1.0.0
*               版权所有，盗版必究。
*               Copyright(C) 2019-2025 武汉无名创新科技有限公司 
*               All rights reserved
-----------------------------------------------------------------------------------------------------------------------
*               重要提示：
*               正常淘宝咸鱼转手的飞控、赠送朋友、传给学弟的都可以进售后群学习交流，
*               不得直接在网上销售无名创新资料，无名创新代码有声明版权，他人不得将
*               资料代码传网上供他人下载，不得以谋利为目的销售资料代码，发现有此操
*               作者，公司会提前告知，请1天内及时处理，否则你的学校、单位、姓名、电
*               话、地址信息会被贴出在公司官网、官方微信公众平台、官方技术博客、知乎
*               专栏以及淘宝店铺首页予以公示公告，此种所作所为，会成为个人污点，影响
*               升学、找工作、社会声誉、很快就很在无人机界出名，后果很严重。
*               因此行为给公司造成重大损失者，会以法律途径解决，感谢您的合作，谢谢！！！
----------------------------------------------------------------------------------------------------------------------*/
#include "Headfile.h"
#include "NamelessCotrun_SDK.h"

bool auto_altland(float taret_climb_rate,float target_climb_alt)
{
  return land_althold(taret_climb_rate,target_climb_alt);
}
//SDK本模式需要在光流模式下使用
uint8_t move_with_speed_target(float x_target,float y_target,float delta,SDK_Status *Status,uint16_t number)
{
  static float end_time=0;
  Vector2f vel_target;
  Testime dt;
  vel_target.x=x_target;
  vel_target.y=y_target;
  Test_Period(&dt);
  ncq_control_althold();//高度控制依然进行
  if(Status->Status[number].Start_Flag==1
     &&Status->Status[number].Execute_Flag==1
       &&Status->Status[number].End_flag==1)
  {
    OpticalFlow_Control_Pure(0);//完成之后，进行光流悬停
    return 1;
  }
  else
  {
    if(Status->Status[number].Start_Flag==0) 
    {
      end_time=dt.Now_Time+delta;//单位ms 
      Status->Status[number].Start_Flag=1;
    } 
    if(dt.Now_Time>end_time)
    {
      Status->Status[number].Execute_Flag=1;
      Status->Status[number].End_flag=1;
      OpticalFlow_Control_Pure(1);//完成之后，进行光流悬停
      OpticalFlow_Pos_Ctrl_Expect.x=0;
      OpticalFlow_Pos_Ctrl_Expect.y=0;
      end_time=0;
      Status->Transition_Time[number]=200;
      return 1;//返回完成
    }
    else
    { 
      OpticalFlow_Pos_Ctrl_Expect.x=0;
      OpticalFlow_Pos_Ctrl_Expect.y=0;
      Status->Status[number].Execute_Flag=1;
      OpticalFlow_Vel_Control(vel_target);//给定速度期望
      return 0;
    }
  }
}


uint8_t move_with_xy_target(float pos_x_target,float pos_y_target,SDK_Status *Status,uint16_t number)
{
  ncq_control_althold();//高度控制依然进行
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
    OpticalFlow_Control_Pure(0);//完成之后，进行光流悬停
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
      OpticalFlow_Control_Pure(1);//完成之后，进行光流悬停
      OpticalFlow_Pos_Ctrl_Expect.x=0;
      OpticalFlow_Pos_Ctrl_Expect.y=0;
      return 1;
    }
    else
    { 
      Status->Status[number].Execute_Flag=1; 
      OpticalFlow_Pos_Control();//光流位置控制
      OpticalFlow_Vel_Control(OpticalFlow_Pos_Ctrl_Output);//光流速度控制 
      return 0;
    }
  }
}


uint8_t move_with_target(float pos_x_target,float pos_y_target,Duty_Status *Status,uint8_t *Start_flag)
{
  ncq_control_althold();//高度控制依然进行
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
    OpticalFlow_Control_Pure(0);//完成之后，进行光流悬停
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
      OpticalFlow_Control_Pure(1);//完成之后，进行光流悬停
      OpticalFlow_Pos_Ctrl_Expect.x=0;
      OpticalFlow_Pos_Ctrl_Expect.y=0;
      return 1;
    }
    else
    { 
      Status->Execute_Flag=1; 
      OpticalFlow_Pos_Control();//光流位置控制
      OpticalFlow_Vel_Control(OpticalFlow_Pos_Ctrl_Output);//光流速度控制 
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
  OpticalFlow_Control_Pure(0);//水平位置控制依然进行
  
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
      if(z_target==0)//速度控制，一次任务中只设置一次
      {
        target_rate=z_vel;
        target_alt=0;
        end_flag=1;
      }
      else//位置控制，一次任务中只设置一次
      {
        target_rate=0;
        target_alt=NamelessQuad.Position[_YAW]+z_target;
        end_flag=2;
      }
      end_time=dt.Now_Time+delta;//单位ms 
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
        return 1;//返回完成
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
    //ncq_control_althold();//高度控制
    OpticalFlow_Control(0);//位置控制
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
    OpticalFlow_Control(0);//结束后的水平位置控制
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
  //if(!(sum==*(data_buf+num-1)))	return;	                //不满足和校验条件	
  if(!(*(data_buf)==0xAA && *(data_buf+1)==0xAF))	return;//不满足帧头条件		   
  if(*(data_buf+2)==0XC0)//色块检测
  {
    SDK_Recieve_Flag=1;
  }
  else if(*(data_buf+2)==0XF3)//线检测
  {
    SDK_Now_Mode=0x02;
    SDK_Line.x=*(data_buf+4)<<8|*(data_buf+5);
    SDK_Line.line_angle=(*(data_buf+6)<<8)|*(data_buf+7);
    SDK_Line.flag=*(data_buf+8);        
    //line.flag从低位到高位分别对应镜头视野中上下左右四个区域，检测到有直线为1，否则为0
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
  else if(*(data_buf+2)==0XF2)//点检测
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
  else if(*(data_buf+2)==0XC3)//二维码
  {
    SDK_Recieve_Flag=1;
  }
  //串口数传SDK模式
  else if(*(data_buf+2)==0X01)//高度位置控制
  {
    if(*(data_buf+4)==0X01)//上升  
    {
      Total_Controller.High_Position_Control.Expect+=*(data_buf+5);
      Unwanted_Lock_Flag=0;
    }
    else if(*(data_buf+4)==0X02)//下降
    {
      Total_Controller.High_Position_Control.Expect-=*(data_buf+5);
    }
    else if(*(data_buf+4)==0X03)//地面起飞，上升到目标高度
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
  if(state==0&&data==0xAA)//帧头1
  {
    state=1;
    RxBuffer[0]=data;
  }
  else if(state==1&&data==0xAF)//帧头2
  {
    state=2;
    RxBuffer[1]=data;
  }
  else if(state==2&&data<0XFF)//功能字节
  {
    state=3;
    RxBuffer[2]=data;
  }
  else if(state==3&&data<50)//数据长度
  {
    state = 4;
    RxBuffer[3]=data;
    _data_len = data;
    _data_cnt = 0;
  }
  else if(state==4&&_data_len>0)//有多少数据长度，就存多少个
  {
    _data_len--;
    RxBuffer[4+_data_cnt++]=data;
    if(_data_len==0) state = 5;
  }
  else if(state==5)//最后接收数据校验和
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
  SDK_Line_DT_Reset();//复位SDK线检测数据
  SDK_Point_DT_Reset();//复位SDK点检测数据
  if(ReadFlashParameterOne(SDK_MODE_DEFAULT,&sdk_mode_default))
  {
    SDK_Mode_Set=(uint8_t)(sdk_mode_default);
    SDK_DT_Send_Check(SDK_Mode_Set);//初始化opemmv工作模式，默认以上次工作状态配置
  } 
}

