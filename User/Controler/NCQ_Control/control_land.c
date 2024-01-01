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
#include "control_config.h"
#include "control_land.h"

enum fixed_state{Faraway,Near,Arrive};
Vector2_Nav land_pos_target,land_pos_now,land_home_pos;
float target_yaw_rate=0,target_yaw_alt=0;
bool land_althold(float taret_climb_rate,float target_climb_alt)
{
  static uint16 High_Pos_Control_Cnt=0;//高度位置控制计数器
  static uint16 High_Vel_Control_Cnt=0;//高度速度控制计数器
  static uint8_t move_flag=0;
  bool handmove_flag=false;
  float step_mapping=0,scale_mapping=0;
  Thr_Scale_Set(&RC_Calibration[2]);
  High_Hold_Throttle=Thr_Hover_Default;
  /*高度控制器第1步*/
  /********
      **
      **
      **
      **
      **
  ********/
  /*******************************高度控制器开始****************************************/
  /****************定高：高度位置环+速度环+加速度环，控制周期分别为8ms、4ms、4ms*******************/
  if(target_climb_alt==0)
  {
    Total_Controller.High_Position_Control.Expect=NamelessQuad.Position[_YAW];//一直更新高度期望
  }
  else
  {
    Total_Controller.High_Position_Control.Expect=target_climb_alt;//更新高度期望
  }
  if(RC_NewData[0]>=Deadzone_Min
     &&RC_NewData[0]<=Deadzone_Max)
  {
    //高度位置环输出给定速度期望
    High_Pos_Control_Cnt++;
    if(High_Pos_Control_Cnt>=2)//竖直高度控制周期2*5=10ms
    {
      High_Pos_Control_Cnt=0;
      Total_Controller.High_Position_Control.FeedBack=NamelessQuad.Position[_YAW];//反馈
      PID_Control(&Total_Controller.High_Position_Control);//海拔高度位置控制器
      //内环速度期望
      if(target_climb_alt==0) Yaw_Vel_Target=taret_climb_rate;//本次速度期望来源于外部直接给定
      else Yaw_Vel_Target=Total_Controller.High_Position_Control.Control_OutPut;//本次速度期望来源于位置控制器输出
#ifdef YAW_VEL_FEEDFORWARD  //速度前馈控制器
      Yaw_Vel_Feedforward_Delta=(Yaw_Vel_Target-Last_Yaw_Vel_Target)/(2*Delta);//速度期望变化率
      Yaw_Vel_Feedforward_Output=Yaw_Vel_Feedforward_Rate*Yaw_Vel_Feedforward_Delta;
      Last_Yaw_Vel_Target=Yaw_Vel_Target;//上次速度期望
#endif
      Total_Controller.High_Speed_Control.Expect=Yaw_Vel_Target;
    }
    handmove_flag=false;
    move_flag=0;
  }
  else if(RC_NewData[0]>Deadzone_Max)//给定上升速度期望
  {
    //油门杆上推、给定速度期望
    step_mapping=(float)(RC_NewData[0]-Deadzone_Max)/(Thr_Top-Deadzone_Max);//范围0~1
    scale_mapping=constrain_float(step_mapping*step_mapping,0,1);
    Total_Controller.High_Speed_Control.Expect=Max_Upvel*scale_mapping;//最大上升速度50cm/s
    handmove_flag=true;
    move_flag=1;
  }
  else if(RC_NewData[0]<Deadzone_Min)//给定下降速度期望
  {
    //油门杆下推、给定速度期望
    step_mapping=(float)(RC_NewData[0]-Deadzone_Min)/(Deadzone_Min-Thr_Buttom);//范围0~-1
    scale_mapping=constrain_float(step_mapping*step_mapping,0,1);
    Total_Controller.High_Speed_Control.Expect=-Max_Downvel*scale_mapping;//最大下降速度40cm/s
    handmove_flag=true;
    move_flag=2;
  }
  /*高度控制器第2步*/
  /********
          *
          *
   * * * *
  *
  *
  ********/
  /*******************************竖直速度控制器开始*******************************************************************/
  High_Vel_Control_Cnt++;
  if(High_Vel_Control_Cnt>=1)//竖直高度控制周期5*1=5ms
  {
    High_Vel_Control_Cnt=0;
    Total_Controller.High_Speed_Control.FeedBack=NamelessQuad.Speed[_YAW];//惯导速度估计给速度反馈
    PID_Control_Div_LPF(&Total_Controller.High_Speed_Control);//海拔高度速度控制
  }
  /*******************************上升下降过程中期望加速度限幅单独处理*******************************************************************/     
  if(move_flag==1)//在上下推杆时对速度控制器输出，对期望上升、下降加速度进行分别限幅，确保快速下降时姿态平稳
  {
    Total_Controller.High_Speed_Control.Control_OutPut=constrain_float(Total_Controller.High_Speed_Control.Control_OutPut,
                                                                       -Climb_Up_Acceleration_Max,Climb_Up_Acceleration_Max);                                                                
  }
  else if(move_flag==2)
  {
    Total_Controller.High_Speed_Control.Control_OutPut=constrain_float(Total_Controller.High_Speed_Control.Control_OutPut,
                                                                       -Climb_Down_Acceleration_Max,Climb_Down_Acceleration_Max);
  }    
  /*******************************竖直速度控制器结束******************************************************************/
  /*高度控制器第3步*/
  /********
         **
       **
     **
       **
         **
  ********/
  
  /*******************************竖直加速度控制器开始******************************************************************/
  Total_Controller.High_Acce_Control.Expect=Total_Controller.High_Speed_Control.Control_OutPut;//加速度期望
#ifdef YAW_VEL_FEEDFORWARD  //速度前馈控制器
  Total_Controller.High_Acce_Control.Expect+=Yaw_Vel_Feedforward_Output;//加上前馈控制器输出
#endif
  Total_Controller.High_Acce_Control.FeedBack=Filter_Feedback_NamelessQuad.Acceleration[_YAW];//加速度反馈
  //PID_Control_Err_LPF(&Total_Controller.High_Acce_Control);//海拔高度加速度控制
	PID_Control_Div_LPF(&Total_Controller.High_Acce_Control);//海拔高度加速度控制
  /**************************************
  加速度环前馈补偿，引用时请注明出处
  悬停油门 = 加速度环积分值 + 基准悬停油门
  此时输出力 F = mg
  当需要输出a的加速度时，输出力 F1=m(g+a)
  F1/F = 1 + a/g
  因此此时应输出：悬停油门*(1 + a/g)
  **************************************/
  Total_Controller.High_Acce_Control.Control_OutPut+=(High_Hold_Throttle+Total_Controller.High_Acce_Control.Integrate-Thr_Start)*
    (Total_Controller.High_Acce_Control.Expect/980);
  /*******************************竖直加速度控制器结束******************************************************************/
  if(YAW_Pos_Control_Accel_Disable==0)
  {
    Throttle=Int_Sort(High_Hold_Throttle+Total_Controller.High_Acce_Control.Control_OutPut);//油门来源于高度加速度控制器输出
  }
  else
  {
    Throttle=Int_Sort(High_Hold_Throttle+Total_Controller.High_Speed_Control.Control_OutPut);//油门来源于高度速度控制器输出
  }
  /*****************************************高度控制器结束，给定油门控制量***********************************************************/
  return handmove_flag;
}



Vector2f_Nav land_pos_sort(Vector2_Nav target_pos,Vector2_Nav now_pos)//得到相对目标点机体Pit、Rol方向偏移
{
  Vector2f_Nav earth_pos_delta;
  //Vector2_Body body_pos_delta;
  static int32_t last_land_lat;
  static float land_scale = 1.0;
  //比较两次纬度相差值，避免重复运算余弦函数
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
  earth_pos_delta.N=(target_pos.lat-now_pos.lat) * LOCATION_SCALING_FACTOR;//距离单位为m
  earth_pos_delta.E=(target_pos.lng-now_pos.lng) * LOCATION_SCALING_FACTOR * land_scale;//距离单位为m
  /***********************************************************************************
  明确下导航系方向，这里正北、正东为正方向:
  沿着正东，经度增加,当无人机相对home点，往正东向移动时，此时GPS_Present.lng>GPS_Home.lng，得到的location_delta.x大于0;
  沿着正北，纬度增加,当无人机相对home点，往正北向移动时，此时GPS_Present.lat>GPS_Home.lat，得到的location_delta.y大于0;
  ******************************************************************************/
  earth_pos_delta.N*=100;//沿地理坐标系，正北方向位置偏移,单位为CM
  earth_pos_delta.E*=100;//沿地理坐标系，正东方向位置偏移,单位为CM
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
  pos_handmove=(bool)(Roll_Control!=0||Pitch_Control!=0);//无水平遥控量给定
  return pos_handmove;
}

bool land_poshold(Vector2_Nav target_pos,Vector2_Nav now_pos,uint8_t fixed_state)
{
  static uint16 Horizontal_Pos_Control_Cnt=0;//高度速度控制计数器
  static uint16 Horizontal_Vel_Control_Cnt=0;//高度速度控制计数器
  bool handmove_flag=false;
  float max_nav_speed=0;
  Vector2f_Nav earth_frame_distance={0,0};
  earth_frame_distance=land_pos_sort(target_pos,land_home_pos);//得到相对目标点N、E方向偏移，即期望位置偏移
  if(Landon_Earth_Flag==0)
  {
    /*******************************水平位置控制器开始***********************************************************/
    //技术讲解见博客：四旋翼GPS定点流程梳理与原理浅析 http://blog.csdn.net/u011992534/article/details/79408187
    if(GPS_ok()==true)
    {
      if(Roll_Control==0
         &&Pitch_Control==0)//无水平遥控量给定
      {
        Horizontal_Pos_Control_Cnt++;
        if(Horizontal_Pos_Control_Cnt>4)//20ms控制一次
        {
          //位置期望,经纬、航行速度、高度
          Total_Controller.Latitude_Position_Control.Expect=NamelessQuad.Position[_ROLL];//移植更新水平目标位置，目的是切回定点模式赋悬停点
          Total_Controller.Longitude_Position_Control.Expect=NamelessQuad.Position[_PITCH];
          //导航坐标系下E、N方向上位置偏差
          Earth_Frame_Pos_Err.N=earth_frame_distance.N-NamelessQuad.Position[_ROLL];
          Earth_Frame_Pos_Err.E=earth_frame_distance.E-NamelessQuad.Position[_PITCH];
          //导航坐标系下机体Pitch、Roll方向上位置偏差
          Body_Frame_Pos_Err.Pit=-Earth_Frame_Pos_Err.E*Sin_Yaw+Earth_Frame_Pos_Err.N*Cos_Yaw;
          Body_Frame_Pos_Err.Rol=Earth_Frame_Pos_Err.E*Cos_Yaw+Earth_Frame_Pos_Err.N*Sin_Yaw;
          //导航坐标系下机体Pitch、Roll方向上期望刹车速度，这里为单比例运算不调用PID_Control()函数
          if(fixed_state==Faraway)   max_nav_speed=First_Nav_Rate;
          else if(fixed_state==Near)   max_nav_speed=Second_Nav_Rate;
          else if(fixed_state==Arrive)   max_nav_speed=Third_Nav_Rate;
          else   max_nav_speed=Default_Nav_rate;
          Body_Frame_Brake_Speed.Pit=constrain_float(Total_Controller.Latitude_Position_Control.Kp*Body_Frame_Pos_Err.Pit,-max_nav_speed, max_nav_speed);//位置偏差限幅，单位cm
          Body_Frame_Brake_Speed.Rol=constrain_float(Total_Controller.Latitude_Position_Control.Kp*Body_Frame_Pos_Err.Rol,-max_nav_speed, max_nav_speed);//位置偏差限幅，单位cm
          
          //速度控制器期望
          Total_Controller.Latitude_Speed_Control.Expect =Body_Frame_Brake_Speed.Pit;
          Total_Controller.Longitude_Speed_Control.Expect=Body_Frame_Brake_Speed.Rol;
          Horizontal_Pos_Control_Cnt=0;//位置控制器结束，给出期望刹车速度
        }
        //导航系的水平速度，转化到机体坐标系X-Y方向上
        //沿载体Pitch、Roll方向水平速度控制
        Horizontal_Vel_Control_Cnt++;
        if(Horizontal_Vel_Control_Cnt>=2)//10ms控制一次位置
        {
          Body_Frame_Speed_Feedback.Pit=-NamelessQuad.Speed[_PITCH]*Sin_Yaw+NamelessQuad.Speed[_ROLL]*Cos_Yaw;
          Body_Frame_Speed_Feedback.Rol=NamelessQuad.Speed[_PITCH]*Cos_Yaw+NamelessQuad.Speed[_ROLL]*Sin_Yaw;
          //沿载体方向速度反馈量
          Total_Controller.Latitude_Speed_Control.FeedBack=Body_Frame_Speed_Feedback.Pit;//机头Pitch方向，Y轴正向
          Total_Controller.Longitude_Speed_Control.FeedBack=Body_Frame_Speed_Feedback.Rol;//横滚Roll方向，X轴正向
          //沿载体方向速度控制器
          PID_Control_Div_LPF(&Total_Controller.Latitude_Speed_Control);
          PID_Control_Div_LPF(&Total_Controller.Longitude_Speed_Control);
          
          accel_target.y=-Total_Controller.Latitude_Speed_Control.Control_OutPut;
          accel_target.x=Total_Controller.Longitude_Speed_Control.Control_OutPut;//期望运动加速度
          accel_to_lean_angles(accel_target,&angle_target);//期望运动加速度转期望姿态倾角
          Total_Controller.Pitch_Angle_Control.Expect=angle_target.y;
          Total_Controller.Roll_Angle_Control.Expect=angle_target.x;  
          //Total_Controller.Pitch_Angle_Control.Expect=-Total_Controller.Latitude_Speed_Control.Control_OutPut;
          //Total_Controller.Roll_Angle_Control.Expect=Total_Controller.Longitude_Speed_Control.Control_OutPut;
          Horizontal_Vel_Control_Cnt=0;
        }
        /*******************************水平位置控制器结束***********************************************************/
        handmove_flag=false;
      }
      else //只进行水平速度控制，无水平位置控制
      {
        Horizontal_Vel_Control_Cnt++;
        if(Horizontal_Vel_Control_Cnt>=2)//10ms控制一次速度
        {
          Total_Controller.Latitude_Speed_Control.Expect=ncq_speed_mapping(-Target_Angle[0],Pit_Rol_Max,Max_Horvel);
          Total_Controller.Longitude_Speed_Control.Expect=ncq_speed_mapping(Target_Angle[1],Pit_Rol_Max,Max_Horvel);
          //导航系的水平速度，转化到机体坐标系X-Y方向上
          //沿载体Pitch、Roll方向水平速度控制
          Body_Frame_Speed_Feedback.Pit=-NamelessQuad.Speed[_PITCH]*Sin_Yaw+NamelessQuad.Speed[_ROLL]*Cos_Yaw;
          Body_Frame_Speed_Feedback.Rol=NamelessQuad.Speed[_PITCH]*Cos_Yaw+NamelessQuad.Speed[_ROLL]*Sin_Yaw;
          
          Total_Controller.Latitude_Speed_Control.FeedBack=Body_Frame_Speed_Feedback.Pit;//机头Pitch方向，Y轴正向
          Total_Controller.Longitude_Speed_Control.FeedBack=Body_Frame_Speed_Feedback.Rol;//横滚Roll方向，X轴正向
          
          PID_Control_Div_LPF(&Total_Controller.Latitude_Speed_Control);
          PID_Control_Div_LPF(&Total_Controller.Longitude_Speed_Control);
          
          accel_target.y=-Total_Controller.Latitude_Speed_Control.Control_OutPut;
          accel_target.x=Total_Controller.Longitude_Speed_Control.Control_OutPut;//期望运动加速度
          accel_to_lean_angles(accel_target,&angle_target);//期望运动加速度转期望姿态倾角
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
    Total_Controller.Pitch_Angle_Control.Expect=0;//水平期望姿态角给0
    Total_Controller.Roll_Angle_Control.Expect=0;
    Take_Off_Reset();//清空积分控制器
  }
  return handmove_flag;
}



#define Minimal_Thrust_Threshold 1150//着陆检测油门最小值
uint16_t Landon_Earth_Cnt=0;
uint8_t Last_Landon_Earth_Flag=0,Landon_Earth_Flag=0;
uint8_t Landon_Earth_Flag_Set=0;

void landon_earth_check(void)//自检触地进入怠速模式
{
  Last_Landon_Earth_Flag=Landon_Earth_Flag;
  //油门控制处于较低行程：
  //1、姿态模式下，油门杆处于低位
  //2、定高模式下，期望速度向下，单加速度环反馈为角小值，
  //加速度控制输出由于长时间积分，到负的较大值，使得油门控制较低
  if(Throttle_Output<=Minimal_Thrust_Threshold
     &&Gyro_Length<=35.0//触地后无旋转，合角速度小于20deg/s
       &&ABS(NamelessQuad.Speed[_YAW])<=30.0//惯导竖直轴速度+-20cm/s
         &&Unwanted_Lock_Flag==0
           &&pos_handmove_check()==false)//无水平手动操作
    Landon_Earth_Cnt++;
  else Landon_Earth_Cnt/=2;
  
  if(Landon_Earth_Cnt>=1000)  Landon_Earth_Cnt=1000;//防止溢出
  if(Landon_Earth_Cnt>=200*2.0)//持续2.0S
  {
    Landon_Earth_Flag=1;//着陆标志位
    //Landon_Earth_Cnt=0;
  }
  else
  {
    Landon_Earth_Flag=0;//着陆标志位
  }
  /*
  if(ABS(Throttle_Rate)>=1.0E-5f)//只要油门变化率不为0，即清空着陆标志位
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
  if(Landon_Earth_Flag==0)//未触地，有姿态控制参与
  {
    Total_Controller.Pitch_Angle_Control.Expect=Target_Angle[0];//水平期望姿态角来源于遥杆给定
    Total_Controller.Roll_Angle_Control.Expect=Target_Angle[1];
    
    if(NamelessQuad.Position[_YAW]<=Safe_Height)//相对初始高度10M以内,暂时忽略漂移
      target_yaw_rate=Nav_Decline_Rate;//以Nav_Decline_rate速度下降
    else target_yaw_rate=Nav_Rapid_Decline_Rate;//以Nav_Rapid_Decline_rate速度下降
    
    target_yaw_alt=0;
    
    land_althold(target_yaw_rate,target_yaw_alt);
  }
  else
  {
    Total_Controller.Pitch_Angle_Control.Expect=0;//水平期望姿态角给0
    Total_Controller.Roll_Angle_Control.Expect=0;
    Take_Off_Reset();//清空积分控制器
    target_yaw_rate=2*Nav_Rapid_Decline_Rate;//以2*Nav_Rapid_Decline_rate速度下降,使得油门量迅速满足怠速条件
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

void land_reset()//着陆过程中存在各种标志位，在一次飞行过程中，可能会频繁切换，需要清空上次未进行完毕的标志位，在切换时会全部清空
{
  //复位过程中的所有标志位，对于应对较为复杂的逻辑过程的必备编程技巧，一定要掌握好
  last_handmove_change_mode=0;
  
  nav_transition_cnt=0;
  nav_transition_flag=0;
  nav_climb_rate_cnt=0;
  distance_land_mode=0;
  last_distance_land_mode=0;//将自动降落模式标志位置0，下一次循环会重新判断
  climb_safe_alt_flag=0;
  first_switch_flag=1;
  home_fixed_flag=0;
  handmove_change_mode=2;//水平位置手动模式
  first_switch_flag=1;//准备好下次回中时刻的切换
  
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
  float distance_to_home=100*get_distance(GPS_Home,GPS_Present);//单位cm
  last_distance_land_mode=distance_land_mode;
  if(distance_to_home>=Faraway_Distance)//离起飞点水平距离超过Faraway_Distance半径
  {
    distance_land_mode=1;//先原地上升至安全高度再返航到水平点正上方
    home_fixed_flag=Faraway;//远离home点
  }
  else if(distance_to_home>=Near_Distance)//离起飞点水平距离Near_Distance~Faraway_Distance半径
  {
    distance_land_mode=2;//先保持当前高度，水平运动至home点正上方，再下降
    home_fixed_flag=Near;//接近home点
  }
  else//与home点距离小于等于Near_Distance半径，已到达home点
  {
    distance_land_mode=3;//水平位置保持为home点，并直接下降
    home_fixed_flag=Arrive;//已锁定home点
  }
  
  check_pos_handmove=pos_handmove_check();//水平位置方向手动
  check_alt_handmove=alt_handmove_check();//竖直高度方向手动
  
  last_handmove_change_mode=handmove_change_mode;
  if(check_pos_handmove==true)//若水平位置自动控制过程中，有手动操作
  {
    last_distance_land_mode=0;//将自动降落模式标志位置0，下一次循环会重新判断
    //distance_land_mode=0;
    climb_safe_alt_flag=0;
    home_fixed_flag=0;
    handmove_change_mode=2;//水平位置手动模式
    first_switch_flag=1;//准备好下次回中时刻的切换
    /**************希望返航过程中，水平打时无高度上升、下降操作，即水平打杆时，高度保持即可**************/
  }
  else handmove_change_mode=1;
  
  if(check_alt_handmove==true)//若高度自动控制过程中，有手动操作
  {
    last_distance_land_mode=0;//将自动降落模式标志位置0，下一次循环会重新判断
    //distance_land_mode=0;
    climb_safe_alt_flag=0;
    home_fixed_flag=0;
    first_switch_flag=1;//准备好下次回中时刻的切换
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
  
  if(Landon_Earth_Flag==0)//未触地，有姿态控制参与
  {
    if(check_pos_handmove==false)//无水平打杆动作位
    {
      if(distance_land_mode==1&&first_switch_flag==1)//首次切返航模式，距离home很远时
      {
        if(NamelessQuad.Position[_YAW]<Safe_Height)//当切返航瞬间的高度小于安全高度时，保持当前水平位置，攀升至安全高度再返航
        {
          land_pos_target.lat=GPS_Present.lat;
          land_pos_target.lng=GPS_Present.lng;
          //target_yaw_rate=Nav_climb_rate;//以Nav_climb_rate速度上升到Nav_Safety_Height安全高度
          nav_climb_rate_cnt=Nav_Climb_Rate;
          target_yaw_rate=Nav_Climb_Rate-nav_climb_rate_cnt;//速度依次递增，避免油门控制量突变
          land_gap_cnt=0;//递增时间步长计数器
          //这里可简单计算一下当微分参数为1.5时
          //1.5*50=75油门控制量瞬间会有75的突变，可能导致飞机不稳定
          target_yaw_alt=0;//目标高度置0
          climb_safe_alt_flag=0;
        }
        else//当切返航瞬间的高度大于安全高度时，保持当前高度，执行返航
        {
          land_pos_target.lat=GPS_Home.lat;
          land_pos_target.lng=GPS_Home.lng;
          target_yaw_rate=0;//目标速度置0
          target_yaw_alt=NamelessQuad.Position[_YAW];//目标保持当前高度
          climb_safe_alt_flag=1;//已经达到安全高度
        }
        first_switch_flag=0;
        last_distance_land_mode=1;//确保能顺利进入下一阶段
      }
      else if(distance_land_mode==1&&last_distance_land_mode==1)//持续处于远离home点较远位置
      {
        if(NamelessQuad.Position[_YAW]>=Safe_Height//当返航的高度超过安全高度时，保持当前高度，飞至home正上方即可
           &&climb_safe_alt_flag==0)//还未到达安全高度
        {
          climb_safe_alt_flag=1;//已到达安全高度
          nav_transition_cnt=Nav_Transition_Period;//设置过渡缓冲时间Nav_Transition_Period个周期
          nav_transition_flag=0;
        }
        else if(climb_safe_alt_flag==0)//离home较远，未达到安全高度，仍然处于保持原地位置，需继续上升
        {
          //水平fixed位置不用再次设置，因为在初始切返航时已设置
          //target_yaw_rate=Nav_climb_rate;//以Nav_climb_rate速度上升到Nav_Safety_Height安全高度
          land_gap_cnt++;
          if(land_gap_cnt>=8)//每8*5=40ms递减
          {
            if(nav_climb_rate_cnt>=1)  nav_climb_rate_cnt--;
            else nav_climb_rate_cnt=0;
            land_gap_cnt=0;
          }
          
          target_yaw_rate=Nav_Climb_Rate-nav_climb_rate_cnt;//速度依次递增，避免油门控制量突变
          //这里可简单计算一下当微分参数为1.5时
          //1.5*50=75油门控制量瞬间会有75的突变，飞机导致不稳定
          target_yaw_alt=0;//目标高度置0
        }
        
        if(climb_safe_alt_flag==1)//只设置一次
        {
          if(nav_transition_cnt>=1)  nav_transition_cnt--;//衰减至0
          else nav_transition_cnt=0;
          
          if(nav_transition_cnt==0)//缓冲时间已结束，设置返航点
          {
            land_pos_target.lat=GPS_Home.lat;
            land_pos_target.lng=GPS_Home.lng;
            target_yaw_rate=0;//目标速度置0
            target_yaw_alt=NamelessQuad.Position[_YAW];//目标保持当前高度
            climb_safe_alt_flag++;//climb_safe_alt_flag==2
          }
          else//缓冲期间
          {
            if(nav_transition_flag==0)//未设置缓冲状态
            {
              nav_transition_flag=1;//有且仅设置1次，设置为在原地悬停nav_transition_cnt个周期
              land_pos_target.lat=GPS_Present.lat;
              land_pos_target.lng=GPS_Present.lng;
              target_yaw_rate=0;
              target_yaw_alt=NamelessQuad.Position[_YAW];
            }
          }
        }
      }
      else if(distance_land_mode==2&&last_distance_land_mode!=2)//首次切返航模式，距离home较近时，保持当前高度，将Home点作为目标点，飞至home正上方
      {
        land_pos_target.lat=GPS_Home.lat;
        land_pos_target.lng=GPS_Home.lng;
        target_yaw_rate=0;//目标速度置0
        target_yaw_alt=NamelessQuad.Position[_YAW];//将目标高度设置为当前高度
        climb_safe_alt_flag=2;
        //这里包含两种情况：1、A->B  2、C->B
        //执行的操作相同，即：保持当前高度，向home靠近
        last_distance_land_mode=2;//确保能顺利进入下一阶段
      }
      else if(distance_land_mode==2&&last_distance_land_mode==2)
      {
        //水平fixed位置不用再次设置，因为在上一状态已设置
        land_pos_target.lat=GPS_Home.lat;
        land_pos_target.lng=GPS_Home.lng;
        target_yaw_rate=0;//目标速度置0
        climb_safe_alt_flag=2;
      }
      else if(distance_land_mode==3&&last_distance_land_mode!=3)//首次进入home点正上方
      {
        land_pos_target.lat=GPS_Home.lat;
        land_pos_target.lng=GPS_Home.lng;
        //target_yaw_rate=Nav_Decline_Rate;//以Nav_Decline_rate目标速度下降
        nav_decline_rate_cnt=Nav_Decline_Rate;
        target_yaw_rate=Nav_Decline_Rate-nav_decline_rate_cnt;
        land_gap_cnt=0;//递增时间步长计数器
        
        target_yaw_alt=0;//将目标高度设置为当前高度
        climb_safe_alt_flag=2;
        
        //这里有且仅有一种情况：1、B->A
        //执行的操作为：水平期望设置为home点，并下降
      }
      else if(distance_land_mode==3&&last_distance_land_mode==3)//处于home点正上方
      {
        land_pos_target.lat=GPS_Home.lat;
        land_pos_target.lng=GPS_Home.lng;
        //target_yaw_rate=Nav_Decline_Rate;//以Nav_Decline_rate目标速度下降
        
        land_gap_cnt++;
        if(land_gap_cnt>=8)//每8*5=40ms递减
        {
          if(nav_decline_rate_cnt<=-1)  nav_decline_rate_cnt++;
          else nav_decline_rate_cnt=0;
          land_gap_cnt=0;
        }
        target_yaw_rate=Nav_Decline_Rate-nav_decline_rate_cnt;//下降速度依次递增，避免油门控制量突变
        
        target_yaw_alt=0;//将目标高度设置为当前高度
        climb_safe_alt_flag=2;
      }
      /*************************************************************/
      land_poshold(land_pos_target,land_pos_now,home_fixed_flag);
      land_althold(target_yaw_rate,target_yaw_alt);
    }
    else//存在水平手动操作
    {
      land_poshold(land_pos_target,land_pos_now,home_fixed_flag);
      if(handmove_change_mode==2&&last_handmove_change_mode==1)
      {
        target_yaw_rate=0;//目标速度置0
        target_yaw_alt=NamelessQuad.Position[_YAW];//将目标高度设置为当前高度
      }
      else if(handmove_change_mode==2&&last_handmove_change_mode==2)
      {
        target_yaw_rate=0;//目标速度置0
        //target_yaw_alt=NamelessQuad.Position[_YAW];//将目标高度设置为当前高度
      }
      land_althold(target_yaw_rate,target_yaw_alt);
    }
  }
  else
  {
    Total_Controller.Pitch_Angle_Control.Expect=0;//水平期望姿态角给0
    Total_Controller.Roll_Angle_Control.Expect=0;
    Take_Off_Reset();//清空积分控制器
    target_yaw_rate=2*Nav_Rapid_Decline_Rate;//以2*Nav_Rapid_Decline_rate速度下降,使得油门量迅速满足怠速条件
    target_yaw_alt=0;
    land_althold(target_yaw_rate,target_yaw_alt);
  }
}


bool GPS_ok()// returns true if the GPS is ok and home position is set
{
  if(GPS_Sate_Num>=7//定位卫星超过7个
     &&GPS_Quality<=3.5f//水平精度因子大于6不可用
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
    land_gps_run();//GPS有效时，执行一键返航操作
  }
  else
  {
    land_nogps_run();//GPS无效时，执行一键着陆操作
  }
}


