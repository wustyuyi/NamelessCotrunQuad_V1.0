#include "Headfile.h"
/*----------------------------------------------------------------------------------------------------------------------/
        *               本程序只供购买者学习使用，版权著作权属于无名科创团队，
        *               无名科创团队将飞控程序源码提供给购买者，
        *               购买者要为无名科创团队提供保护，
        *               未经作者许可，不得将源代码提供给他人
        *               不得将源代码放到网上供他人免费下载，
        *               更不能以此销售牟利，如发现上述行为，
        *               无名科创团队将诉之以法律解决！！！
-----------------------------------------------------------------------------------------------------------------------/
        *               生命不息、奋斗不止；前人栽树，后人乘凉！！！
        *               开源不易，且学且珍惜，祝早日逆袭、进阶成功！！！
-----------------------------------------------------------------------------------------------------------------------/
        *		无名科创开源飞控 V1.1	武汉科技大学  By.YuYi
        *		CSDN博客: http://blog.csdn.net/u011992534
        *               优酷ID：NamelessCotrun无名小哥
        *               无名科创开源飞控QQ群：540707961
        *               https://shop348646912.taobao.com/?spm=2013.1.1000126.2.5ce78a88ht1sO2
        *               百度贴吧:无名科创开源飞控
        *               修改日期:2017/10/30
        *               版本：V1.1
        *               版权所有，盗版必究。
        *               Copyright(C) 武汉科技大学无名科创团队 2017-2019
        *               All rights reserved
----------------------------------------------------------------------------------------------------------------------*/
/***************************觉得不错，欢迎打赏，请小哥吃热干面：支付宝账号：1094744141@qq.com*********************************/
Vector3_Nav Earth_Frame_Accel_Target={0,0,0};   //导航（地理）坐标系，正东、正北方向目标运动加速度期望
Vector3_Nav Earth_Frame_Pos_Err={0,0,0};        //导航（地理）坐标系，正东、正北方向w位置偏差
Vector2_Ang Body_Frame_Accel_Target={0,0};      //导航（地理）坐标系，机体横滚(Y正)、俯仰(X正)方向目标运动加速度期望
Vector2_Ang Body_Frame_Speed_Feedback={0,0};    //导航（地理）坐标系，机体横滚(Y正)、俯仰(X正)方向目标运动速度反馈
Vector2_Ang Body_Frame_Pos_Err={0,0};           //机体方向上位置偏差
Vector2_Ang Body_Frame_Brake_Speed={0,0};       //机体方向上刹车速度

uint16 High_Pos_Control_Cnt=0;//高度位置控制计数器
uint16 High_Vel_Control_Cnt=0;//高度速度控制计数器
/*****************遥控器行程设置**********************/
#define  Deadband       300//油门中位死区
#define  Deadzone_Min   350//油门杆给定期望速度时，下行程临界值
#define  Deadzone_Max   650//油门杆给定期望速度时，上行程临界值
#define  Thr_Top 1000//油门最大上行程
#define  Thr_Buttom 0//油门最大下行程
#define  Climb_Up_Speed_Max    500//向上最大攀爬速度，cm/s
#define  Climb_Down_Speed_Max  200//向下最大下降速度，cm/s
#define  Thr_Start  1150//起转油门量，油门倾角补偿用，太大会导致过补偿
#define  Thr_Fly_Start  1250//起飞油门量
#define  Thr_Min 1000
#define  Thr_Idle 1100//油门怠速
uint16 Motor_PWM_1,Motor_PWM_2,Motor_PWM_3,Motor_PWM_4;//四个电机输出PWM
uint8 MotorTest=0xff;//电机序号测试



float Yaw_Feedforward=0.25;//偏航角前馈控制;
float Yaw_Vel_Feedforward_Output=0;//竖直速度前馈控制器输出;
float Yaw_Vel_Feedforward_Rate=1.0;//竖直速度前馈控制器，APM里面为1、0.45;
float Yaw_Vel_Feedforward_Delta=0;//竖直期望速度变化率;
float Last_Yaw_Vel_Target=0;
float Yaw_Vel_Target=0;

uint8_t Controler_High_Mode=1,Last_Controler_High_Mode=1;
uint8_t Controler_Horizontal_Mode=1,Last_Controler_Horizontal_Mode=1;

#define Self_Balance_Mode 1//自稳、纯姿态加油门补偿
#define High_Hold_Mode    2//定高模式
#define Pos_Hold_Mode 3//定点模式

uint8_t Control_Mode_Change=0;
#define Self_To_High  1//自稳切定高
#define High_To_Pos   2//定高切定点

//GPS定点下打杆控速模式与直接姿态角
uint8 GPS_Speed_Control_Mode=0;
#define Speed_Mode 0
#define Angle_Mode 1

float  Speed_Hold_Pitch=0,Speed_Hold_Roll=0;
uint16_t High_Hold_Throttle=0;
uint8_t  High_Hold_SetFlag=0;
uint8_t  Pos_Hold_SetFlag=0;
uint16_t  HomePoint_Is_Okay=0;
void Controler_Mode_Select()
{
   Last_Controler_High_Mode=Controler_High_Mode;//上次高度控制模式
   Last_Controler_Horizontal_Mode=Controler_Horizontal_Mode;//上次位置控制模式

   if(PPM_Databuf[4]>=1900)       Controler_High_Mode=2;//气压计定高
   else if(PPM_Databuf[4]<=1100)  Controler_High_Mode=1;//纯姿态自稳

   if(PPM_Databuf[5]>=1900)        Controler_Horizontal_Mode=2;//水平位置控制
   else if(PPM_Databuf[5]<=1100)  Controler_Horizontal_Mode=1;//姿态自稳控制

   if(Controler_High_Mode!=Last_Controler_High_Mode)
   {
     if(Controler_High_Mode==2)  {Control_Mode_Change=1;High_Hold_SetFlag=0;}//自稳切定高
   }
   else Control_Mode_Change=0;//无模式切换


   if(Controler_Horizontal_Mode!=Last_Controler_Horizontal_Mode)//位置通道有切换
   {
     if(Controler_Horizontal_Mode==2)  {Control_Mode_Change=2;Pos_Hold_SetFlag=0;}//自稳切定点
   }
   else Control_Mode_Change=0;//无模式切换



   if(Controler_High_Mode==High_Hold_Mode//本次为定高模式
      &&Last_Controler_High_Mode==Self_Balance_Mode//上次为自稳模式
      &&High_Hold_SetFlag==0)//高度只设置一次
   {
      High_Hold_Throttle=Throttle_Control;//保存当前油门值，只存一次
    /*******************将当前惯导竖直位置估计作为目标高度***************************/
      Total_Controler.High_Position_Control.Expect
        =NamelessQuad.Position[_YAW];//将开关拨动瞬间的惯导高度设置为期望高度
      High_Hold_SetFlag=1;
   }


   if(Controler_High_Mode==Pos_Hold_Mode//本次为定点模式
      &&Control_Mode_Change==2//本次切定点
       &&Pos_Hold_SetFlag==0
        &&GPS_Sate_Num>=9//定位卫星超过9个
         &&GPS_Quality<=3.0//水平精度因子大于6不可用,水平位置期望只设置一次
          &&GPS_Home_Set==1)
   {
     /*******************将当前惯导水平位置估计作为目标悬停点************************/
      Total_Controler.Latitude_Position_Control.Expect
        =NamelessQuad.Position[_ROLL];
      Total_Controler.Longitude_Position_Control.Expect
        =NamelessQuad.Position[_PITCH];
      Pos_Hold_SetFlag=1;
   }
/******当前档位为定点模式，但显示悬停点未设置，说明之前未满足设置定点条件有三种情况********
   1、初始通过开关切定点模式时，GPS状态未满足悬停条件；
   2、初始通过开关切定点模式时，GPS状态未满足悬停条件，之后持续检测仍然未满足GPS定点条件；
   3、之前GPS状态满足悬停条件，但由于GPS信号质量变差，自动切换至不满足GPS定点条件；
*******重新判断当下是否满足定点条件，如满足条件更新悬停点，允许进入定点模式******/
   if(Controler_Horizontal_Mode==2
      &&Pos_Hold_SetFlag==0)
   {
      if(GPS_Sate_Num>=9//定位卫星超过9个
         &&GPS_Quality<=3.0//水平精度因子大于6不可用
           &&GPS_Home_Set==1
           )
      {
      /*******************将当前惯导水平位置估计作为目标悬停点************************/
        Total_Controler.Latitude_Position_Control.Expect=NamelessQuad.Position[_ROLL];
        Total_Controler.Longitude_Position_Control.Expect=NamelessQuad.Position[_PITCH];
        Pos_Hold_SetFlag=1;
      }
   }
/******若满足GPS定点模式，对Pos_Hold_SetFlag置1，允许进入定点模式*****************/
}



uint16 Value_Limit(uint16 Min,uint16 Max,uint16 Data)
{
   if(Data>=Max) Data=Max;
   else if(Data<=Min) Data=Min;
   return Data;
}


float Yaw_Base=0;
uint16 Yaw_Cnt=0;
void Angle_Control()//角度环节
{
      //角度反馈
     Total_Controler.Pitch_Angle_Control.FeedBack=Pitch;
     PID_Control(&Total_Controler.Pitch_Angle_Control);
     Total_Controler.Roll_Angle_Control.FeedBack =Roll;
     PID_Control(&Total_Controler.Roll_Angle_Control);


     if(Yaw_Control==0)//偏航杆置于中位
     {
          if(Yaw_Cnt<=500)//无头模式、飞机上电后一段时间锁定偏航角，磁力计、陀螺仪融合需要一段时间，这里取500
          {
            Yaw_Cnt++;
          }
          if(Total_Controler.Yaw_Angle_Control.Expect==0||Yaw_Cnt<=500)//回中时赋角度期望值
          {
            Total_Controler.Yaw_Angle_Control.Expect=Yaw;
          }
          Total_Controler.Yaw_Angle_Control.FeedBack=Yaw;//偏航角反馈

          PID_Control_Yaw(&Total_Controler.Yaw_Angle_Control);//偏航角度控制
          Total_Controler.Yaw_Gyro_Control.Expect=Total_Controler.Yaw_Angle_Control.Control_OutPut;//偏航角速度环期望，来源于偏航角度控制器输出
     }
     else//波动偏航方向杆后，只进行内环角速度控制
     {
        Total_Controler.Yaw_Angle_Control.Expect=0;//偏航角期望给0,不进行角度控制
        Total_Controler.Yaw_Gyro_Control.Expect=Yaw_Control;//偏航角速度环期望，直接来源于遥控器打杆量
     }

}




void Gyro_Control()//角速度环
{
if(GYRO_CONTROL_MODE==PID_MODE)//俯仰、横滚方向姿态内环角速度控制器采用PID控制器
{
     /***************内环角速度期望****************/
     Total_Controler.Pitch_Gyro_Control.Expect=Total_Controler.Pitch_Angle_Control.Control_OutPut;
     Total_Controler.Roll_Gyro_Control.Expect=Total_Controler.Roll_Angle_Control.Control_OutPut;
     /***************内环角速度反馈****************/
     Total_Controler.Pitch_Gyro_Control.FeedBack=Pitch_Gyro;
     Total_Controler.Roll_Gyro_Control.FeedBack=Roll_Gyro;

     /***************内环角速度控制****************/
     PID_Control_Div_LPF(&Total_Controler.Pitch_Gyro_Control);
     PID_Control_Div_LPF(&Total_Controler.Roll_Gyro_Control);
}
else if(GYRO_CONTROL_MODE==ADRC_MODE)//俯仰、横滚方向姿态内环角速度控制器采用ADRC自抗扰控制器
{


}
else//测试用、正常只选择一种模式
{
    /***************内环角速度期望****************/
    Total_Controler.Pitch_Gyro_Control.Expect=Total_Controler.Pitch_Angle_Control.Control_OutPut;
    Total_Controler.Roll_Gyro_Control.Expect=Total_Controler.Roll_Angle_Control.Control_OutPut;
    /***************内环角速度反馈****************/
    Total_Controler.Pitch_Gyro_Control.FeedBack=Pitch_Gyro;
    Total_Controler.Roll_Gyro_Control.FeedBack=Roll_Gyro;

    /***************内环角速度控制****************/
    PID_Control_Div_LPF(&Total_Controler.Pitch_Gyro_Control);
    PID_Control_Div_LPF(&Total_Controler.Roll_Gyro_Control);


}

//偏航角前馈控制
 Total_Controler.Yaw_Gyro_Control.FeedBack=Yaw_Gyro;
 PID_Control_Div_LPF(&Total_Controler.Yaw_Gyro_Control);
 //**************************偏航角前馈控制**********************************
 Total_Controler.Yaw_Gyro_Control.Control_OutPut=Total_Controler.Yaw_Gyro_Control.Control_OutPut
   +Yaw_Feedforward*Total_Controler.Yaw_Gyro_Control.Expect;//偏航角前馈控制
 if(Total_Controler.Yaw_Gyro_Control.Control_OutPut>=Total_Controler.Yaw_Angle_Control.Control_OutPut_Limit)
   Total_Controler.Yaw_Gyro_Control.Control_OutPut=Total_Controler.Yaw_Angle_Control.Control_OutPut_Limit;
 if(Total_Controler.Yaw_Gyro_Control.Control_OutPut<=-Total_Controler.Yaw_Angle_Control.Control_OutPut_Limit)
   Total_Controler.Yaw_Gyro_Control.Control_OutPut=-Total_Controler.Yaw_Angle_Control.Control_OutPut_Limit;
}

uint16 Throttle=0,Last_Throttle=0,Throttle_Hover=1450;
void Main_Leading_Control(void)
{
/*********************根据遥控器切换档位，飞控进入不同模式****************************/
    if(Controler_High_Mode==1//姿态自稳定模式
       &&Controler_Horizontal_Mode==1)//GPS定点档位未设置
  {
     Total_Controler.Pitch_Angle_Control.Expect=Target_Angle[0];
     Total_Controler.Roll_Angle_Control.Expect=Target_Angle[1];

     if(Throttle_Control<=1000)   Throttle=1000;
     //else Throttle=Throttle_Control;//油门直接来源于遥控器油门给定
     else Throttle=Throttle_Control*set_lpf_alpha(2,0.02)+(1-set_lpf_alpha(2,0.02))*Last_Throttle;//油门直接来源于遥控器油门给定
     Last_Throttle=Throttle;
  }
  else if(Controler_High_Mode==2//定高模式
          &&Controler_Horizontal_Mode==1)//GPS定点档位未设置
  {
/**************************定高模式，水平姿态期望角来源于遥控器******************************************/

#if  (Optical_Enable==0)
     Total_Controler.Pitch_Angle_Control.Expect=Target_Angle[0];
     Total_Controler.Roll_Angle_Control.Expect=Target_Angle[1];
#else   //光流辅助悬停
    if(Roll_Control==0
        &&Pitch_Control==0)//无水平遥控量给定
    {
        //位置期望
        if(NamelessCotrunOptical.Postion_Expect.x==0&&NamelessCotrunOptical.Postion_Expect.y==0)//方向杆回中后，只设置一次
        {
          NamelessCotrunOptical.Postion_Expect.x=NamelessCotrunOptical.Position.x;
          NamelessCotrunOptical.Postion_Expect.y=NamelessCotrunOptical.Position.y;
        }
        NamelessCotrunOptical.Postion_Feedback.x=NamelessCotrunOptical.Position.x;
        NamelessCotrunOptical.Postion_Feedback.y=NamelessCotrunOptical.Position.y;//位置反馈

        NamelessCotrunOptical.Postion_Err.x=NamelessCotrunOptical.Postion_Expect.x-NamelessCotrunOptical.Postion_Feedback.x;
        NamelessCotrunOptical.Postion_Err.y=NamelessCotrunOptical.Postion_Expect.y-NamelessCotrunOptical.Postion_Feedback.y;//位置偏差

        NamelessCotrunOptical.Speed_Expect.x=constrain_float(0.1*NamelessCotrunOptical.Postion_Err.x,-100,100);//速度期望
        NamelessCotrunOptical.Speed_Expect.y=constrain_float(0.1*NamelessCotrunOptical.Postion_Err.y,-100,100);

        NamelessCotrunOptical.Speed_Feedback.x=NamelessCotrunOptical.Speed.x;
        NamelessCotrunOptical.Speed_Feedback.y=NamelessCotrunOptical.Speed.y;//速度反馈

        NamelessCotrunOptical.Speed_Err.x=NamelessCotrunOptical.Speed_Expect.x-NamelessCotrunOptical.Speed_Feedback.x;
        NamelessCotrunOptical.Speed_Err.y=NamelessCotrunOptical.Speed_Expect.y-NamelessCotrunOptical.Speed_Feedback.y;//速度偏差


        Total_Controler.Pitch_Angle_Control.Expect=constrain_float(-0.15*NamelessCotrunOptical.Speed_Err.y,-15,15);//角度期望
        Total_Controler.Roll_Angle_Control.Expect=constrain_float(0.15*NamelessCotrunOptical.Speed_Err.x,-15,15);//角度期望
    }
    else
    {
        Total_Controler.Pitch_Angle_Control.Expect=Target_Angle[0];
        Total_Controler.Roll_Angle_Control.Expect=Target_Angle[1];
        NamelessCotrunOptical.Postion_Expect.x=0;
        NamelessCotrunOptical.Postion_Expect.y=0;

    }
#endif
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
      if(RC_NewData[0]>=Deadzone_Min
         &&RC_NewData[0]<=Deadzone_Max)
     {
          //高度位置环输出给定速度期望
          if(Total_Controler.High_Position_Control.Expect==0)//油门回中后，只设置一次
          {
            Total_Controler.High_Position_Control.Expect=NamelessQuad.Position[_YAW];//油门回中后，更新高度期望
          }
          High_Pos_Control_Cnt++;
          if(High_Pos_Control_Cnt>=2)//竖直高度控制周期2*5=10ms
          {
              High_Pos_Control_Cnt=0;
              Total_Controler.High_Position_Control.FeedBack=NamelessQuad.Position[_YAW];//反馈
              PID_Control(&Total_Controler.High_Position_Control);//海拔高度位置控制器
              //内环速度期望
#ifdef YAW_VEL_FEEDFORWARD  //速度前馈控制器
              Yaw_Vel_Target=Total_Controler.High_Position_Control.Control_OutPut;//本次速度期望
              Yaw_Vel_Feedforward_Delta=(Yaw_Vel_Target-Last_Yaw_Vel_Target)/(2*Delta);//速度期望变化率
              Yaw_Vel_Feedforward_Output=Yaw_Vel_Feedforward_Rate*Yaw_Vel_Feedforward_Delta;
              Last_Yaw_Vel_Target=Yaw_Vel_Target;//上次速度期望
#endif
              Total_Controler.High_Speed_Control.Expect=Total_Controler.High_Position_Control.Control_OutPut;
                ;
          }
     }
     else if(RC_NewData[0]>Deadzone_Max)//给定上升速度期望
     {
            //油门杆上推、给定速度期望
           Total_Controler.High_Speed_Control.Expect=Climb_Up_Speed_Max*(RC_NewData[0]-Deadzone_Max)/(Thr_Top-Deadzone_Max);//最大上升速度50cm/s
           Total_Controler.High_Position_Control.Expect=0;//位置环期望置0
     }
     else if(RC_NewData[0]<Deadzone_Min)//给定下降速度期望
     {
            //油门杆下推、给定速度期望
           Total_Controler.High_Speed_Control.Expect=Climb_Down_Speed_Max*(RC_NewData[0]-Deadzone_Min)/(Deadzone_Min-Thr_Buttom);//最大下降速度40cm/s
           Total_Controler.High_Position_Control.Expect=0;//位置环期望置0
     }

/*高度控制器第2步*/
/********
        *
        *
   ****
 *
 *
 ********/

/*******************************竖直速度控制器开始*******************************************************************/
     High_Vel_Control_Cnt++;
     if(High_Vel_Control_Cnt>=1)//竖直高度控制周期5*1=5ms
     {
        High_Vel_Control_Cnt=0;
        Total_Controler.High_Speed_Control.FeedBack=NamelessQuad.Speed[_YAW];//惯导速度估计给速度反馈
        PID_Control_Div_LPF(&Total_Controler.High_Speed_Control);//海拔高度速度控制
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
      Total_Controler.High_Acce_Control.Expect=Total_Controler.High_Speed_Control.Control_OutPut;//加速度期望
#ifdef YAW_VEL_FEEDFORWARD  //速度前馈控制器
      Total_Controler.High_Acce_Control.Expect+=Yaw_Vel_Feedforward_Output;//加上前馈控制器输出
#endif
      Total_Controler.High_Acce_Control.FeedBack=Filter_Feedback_NamelessQuad.Acceleration[_YAW];//加速度反馈
      PID_Control_Err_LPF(&Total_Controler.High_Acce_Control);//海拔高度加速度控制
/*******************************竖直加速度控制器结束******************************************************************/
      if(YAW_Pos_Control_Accel_Disable==0)
    {
      Throttle=Int_Sort(//Throttle_Hover//悬停油门
              High_Hold_Throttle+Total_Controler.High_Acce_Control.Control_OutPut);//油门来源于高度加速度控制器输出
    }
    else
    {
      Throttle=Int_Sort(//Throttle_Hover//悬停油门
              High_Hold_Throttle+Total_Controler.High_Speed_Control.Control_OutPut);//油门来源于高度速度控制器输出
    }
/*****************************************高度控制器结束，给定油门控制量***********************************************************/
  }
  else if(Controler_High_Mode==2//定高模式
          &&Controler_Horizontal_Mode==2)//GPS定点档位已设置)
  {
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
      if(RC_NewData[0]>=Deadzone_Min&&RC_NewData[0]<=Deadzone_Max)
     {
          //高度位置环输出给定速度期望
          if(Total_Controler.High_Position_Control.Expect==0)//油门回中后，只设置一次
          {
            Total_Controler.High_Position_Control.Expect=NamelessQuad.Position[_YAW];//油门回中后，更新高度期望
          }
          High_Pos_Control_Cnt++;
          if(High_Pos_Control_Cnt>=2)//竖直高度控制周期4*5=10ms
          {
              High_Pos_Control_Cnt=0;
              Total_Controler.High_Position_Control.FeedBack=NamelessQuad.Position[_YAW];//反馈
              PID_Control(&Total_Controler.High_Position_Control);//海拔高度位置控制器
              //内环速度期望
#ifdef YAW_VEL_FEEDFORWARD  //速度前馈控制器
              Yaw_Vel_Target=Total_Controler.High_Position_Control.Control_OutPut;//本次速度期望
              Yaw_Vel_Feedforward_Delta=(Yaw_Vel_Target-Last_Yaw_Vel_Target)/(2*Delta);//速度期望变化率
              Yaw_Vel_Feedforward_Output=Yaw_Vel_Feedforward_Rate*Yaw_Vel_Feedforward_Delta;
              Last_Yaw_Vel_Target=Yaw_Vel_Target;//上次速度期望
#endif
              Total_Controler.High_Speed_Control.Expect=Total_Controler.High_Position_Control.Control_OutPut;
          }
     }
     else if(RC_NewData[0]>Deadzone_Max)//给定上升速度期望
     {
            //油门杆上推、给定速度期望
           Total_Controler.High_Speed_Control.Expect=Climb_Up_Speed_Max*(RC_NewData[0]-Deadzone_Max)/(Thr_Top-Deadzone_Max);//最大上升速度50cm/s
           Total_Controler.High_Position_Control.Expect=0;//位置环期望置0
     }
     else if(RC_NewData[0]<Deadzone_Min)//给定下降速度期望
     {
            //油门杆下推、给定速度期望
           Total_Controler.High_Speed_Control.Expect=Climb_Down_Speed_Max*(RC_NewData[0]-Deadzone_Min)/(Deadzone_Min-Thr_Buttom);//最大下降速度40cm/s
           Total_Controler.High_Position_Control.Expect=0;//位置环期望置0
     }

/*高度控制器第2步*/
/********
        *
        *
   ****
 *
 *
 ********/

/*******************************竖直速度控制器开始*******************************************************************/
     High_Vel_Control_Cnt++;
     if(High_Vel_Control_Cnt>=1)//竖直高度控制周期5*1=5ms
     {
        High_Vel_Control_Cnt=0;
        Total_Controler.High_Speed_Control.FeedBack=NamelessQuad.Speed[_YAW];//惯导速度估计给速度反馈
        PID_Control_Div_LPF(&Total_Controler.High_Speed_Control);//海拔高度速度控制
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
      Total_Controler.High_Acce_Control.Expect=Total_Controler.High_Speed_Control.Control_OutPut;//加速度期望
#ifdef YAW_VEL_FEEDFORWARD  //速度前馈控制器
      Total_Controler.High_Acce_Control.Expect+=Yaw_Vel_Feedforward_Output;//加上前馈控制器输出
#endif
      Total_Controler.High_Acce_Control.FeedBack=Filter_Feedback_NamelessQuad.Acceleration[_YAW];//加速度反馈
      PID_Control_Err_LPF(&Total_Controler.High_Acce_Control);//海拔高度加速度控制
/*******************************竖直加速度控制器结束******************************************************************/
      if(YAW_Pos_Control_Accel_Disable==0)
    {
      Throttle=Int_Sort(//Throttle_Hover//悬停油门
              High_Hold_Throttle+Total_Controler.High_Acce_Control.Control_OutPut);//油门来源于高度加速度控制器输出
    }
    else
    {
      Throttle=Int_Sort(//Throttle_Hover//悬停油门
              High_Hold_Throttle+Total_Controler.High_Speed_Control.Control_OutPut);//油门来源于高度速度控制器输出
    }
/*****************************************高度控制器结束，给定油门控制量**********************************************/


/*******************************水平位置控制器开始***********************************************************/
  if(GPS_Sate_Num>=9//定位卫星超过9个
       &&GPS_Quality<=3.0//水平精度因子大于6不可用
         &&GPS_Home_Set==1
         )
   {
     if(Roll_Control==0
        &&Pitch_Control==0)//无水平遥控量给定
    {
    //位置期望,经纬、航行速度、高度
    if(Total_Controler.Latitude_Position_Control.Expect==0&&Total_Controler.Longitude_Position_Control.Expect==0)//方向杆回中后，只设置一次
    {
      Total_Controler.Latitude_Position_Control.Expect=NamelessQuad.Position[_ROLL];
      Total_Controler.Longitude_Position_Control.Expect=NamelessQuad.Position[_PITCH];
    }

    //位置反馈，来源于当前惯导的位置估计
      Total_Controler.Latitude_Position_Control.FeedBack=NamelessQuad.Position[_ROLL];
      Total_Controler.Longitude_Position_Control.FeedBack=NamelessQuad.Position[_PITCH];
    //导航坐标系下E、N方向上位置偏差
      Earth_Frame_Pos_Err.N=Total_Controler.Latitude_Position_Control.Expect-Total_Controler.Latitude_Position_Control.FeedBack;
      Earth_Frame_Pos_Err.E=Total_Controler.Longitude_Position_Control.Expect-Total_Controler.Longitude_Position_Control.FeedBack;
    //导航坐标系下机体Pitch、Roll方向上位置偏差
      Body_Frame_Pos_Err.Pit=-Earth_Frame_Pos_Err.E*Sin_Yaw+Earth_Frame_Pos_Err.N*Cos_Yaw;
      Body_Frame_Pos_Err.Rol=Earth_Frame_Pos_Err.E*Cos_Yaw+Earth_Frame_Pos_Err.N*Sin_Yaw;
    //导航坐标系下机体Pitch、Roll方向上期望刹车速度，这里为单比例运算不调用PID_Control()函数
      Body_Frame_Pos_Err.Pit=constrain_float(Body_Frame_Pos_Err.Pit,-Total_Controler.Latitude_Position_Control.Err_Max, Total_Controler.Latitude_Position_Control.Err_Max);//位置偏差限幅，单位cm
      Body_Frame_Pos_Err.Rol=constrain_float(Body_Frame_Pos_Err.Rol,-Total_Controler.Longitude_Position_Control.Err_Max,Total_Controler.Longitude_Position_Control.Err_Max);//位置偏差限幅，单位cm

      Body_Frame_Brake_Speed.Pit=Total_Controler.Latitude_Position_Control.Kp*Body_Frame_Pos_Err.Pit;
      Body_Frame_Brake_Speed.Rol=Total_Controler.Longitude_Position_Control.Kp*Body_Frame_Pos_Err.Rol;
      //速度控制器期望
      Total_Controler.Latitude_Speed_Control.Expect =Body_Frame_Brake_Speed.Pit;
      Total_Controler.Longitude_Speed_Control.Expect=Body_Frame_Brake_Speed.Rol;
    //导航系的水平速度，转化到机体坐标系X-Y方向上
    //沿载体Pitch、Roll方向水平速度控制
      Body_Frame_Speed_Feedback.Pit=-NamelessQuad.Speed[_PITCH]*Sin_Yaw+NamelessQuad.Speed[_ROLL]*Cos_Yaw;
      Body_Frame_Speed_Feedback.Rol=NamelessQuad.Speed[_PITCH]*Cos_Yaw+NamelessQuad.Speed[_ROLL]*Sin_Yaw;
    //沿载体方向速度反馈量
      Total_Controler.Latitude_Speed_Control.FeedBack=Body_Frame_Speed_Feedback.Pit;//机头Pitch方向，Y轴正向
      Total_Controler.Longitude_Speed_Control.FeedBack=Body_Frame_Speed_Feedback.Rol;//横滚Roll方向，X轴正向
    //沿载体方向速度控制器
      //PID_Control(&Total_Controler.Latitude_Speed_Control);
      //PID_Control(&Total_Controler.Longitude_Speed_Control);
      PID_Control_Err_LPF(&Total_Controler.Latitude_Speed_Control);
      PID_Control_Err_LPF(&Total_Controler.Longitude_Speed_Control);

      Total_Controler.Pitch_Angle_Control.Expect=-Total_Controler.Latitude_Speed_Control.Control_OutPut;
      Total_Controler.Roll_Angle_Control.Expect=Total_Controler.Longitude_Speed_Control.Control_OutPut;
 /*******************************水平位置控制器结束***********************************************************/
    }
    else //只进行水平速度控制，无水平位置控制
   {
      //分两种情况，1、导航坐标系的航向速度控制；
     //             2、载体坐标系方向上的速度控制
     if(GPS_Speed_Control_Mode==Angle_Mode)//推动方向杆，对应期望角度
     {
       Total_Controler.Pitch_Angle_Control.Expect=Target_Angle[0];
       Total_Controler.Roll_Angle_Control.Expect=Target_Angle[1];
     }
     else//推动方向杆，对应给定载体坐标系的沿Pitch,Roll方向运动速度
     {
      Total_Controler.Latitude_Speed_Control.Expect =-Target_Angle[0]*4.0;// 最大期望速度50*3/100=1.5m/s
      Total_Controler.Longitude_Speed_Control.Expect=Target_Angle[1]*4.0;
       //导航系的水平速度，转化到机体坐标系X-Y方向上
       //沿载体Pitch、Roll方向水平速度控制
      Body_Frame_Speed_Feedback.Pit=-NamelessQuad.Speed[_PITCH]*Sin_Yaw+NamelessQuad.Speed[_ROLL]*Cos_Yaw;
      Body_Frame_Speed_Feedback.Rol=NamelessQuad.Speed[_PITCH]*Cos_Yaw+NamelessQuad.Speed[_ROLL]*Sin_Yaw;

      Total_Controler.Latitude_Speed_Control.FeedBack=Body_Frame_Speed_Feedback.Pit;//机头Pitch方向，Y轴正向
      Total_Controler.Longitude_Speed_Control.FeedBack=Body_Frame_Speed_Feedback.Rol;//横滚Roll方向，X轴正向

      //PID_Control(&Total_Controler.Latitude_Speed_Control);
      //PID_Control(&Total_Controler.Longitude_Speed_Control);
      PID_Control_Err_LPF(&Total_Controler.Latitude_Speed_Control);
      PID_Control_Err_LPF(&Total_Controler.Longitude_Speed_Control);

      Total_Controler.Pitch_Angle_Control.Expect=-Total_Controler.Latitude_Speed_Control.Control_OutPut;
      Total_Controler.Roll_Angle_Control.Expect=Total_Controler.Longitude_Speed_Control.Control_OutPut;
     }

      Total_Controler.Latitude_Position_Control.Expect=0;
      Total_Controler.Longitude_Position_Control.Expect=0;
   }
   }
  else//不满足定点条件，控制量给水平姿态
  {
/********对GPS定点模式位置0，直接进入姿态模式，等待GPS信号再次满足条件时，***********
*********自动切换至GPS定点模式，结合Controler_Mode_Select函数理解运行过程**********/
     Pos_Hold_SetFlag=0;//置0，当开关档位仍为定点模式时，
                        //在控制模式里面自检是否允许再次进入GPS定点模式
     Total_Controler.Pitch_Angle_Control.Expect=Target_Angle[0];
     Total_Controler.Roll_Angle_Control.Expect=Target_Angle[1];
  }
  }

}
/************姿态环控制器：角度+角速度****************/
void Altitude_Control(void)
{
  Angle_Control();//角度控制
  Gyro_Control();//角速度控制
}


float Active_Para1,Active_Para2;
void Total_Control(void)
{
  static uint16_t Mode_Check_Cnt=0;
  /***********当PPM_ch6、ch7为模拟通道时，可以作为实时在线调参使用******/
  Active_Para1=PPM_Databuf[6]-1000;
  Active_Para2=PPM_Databuf[7]-1000;
  Active_Para1=0.1*constrain_float(Active_Para1-500,-500,500);
  //Active_Para2=0.0001*constrain_float(Active_Para2,0,1000);
  //Total_Controler.High_Speed_Control.Kp=Active_Para1;
  //Total_Controler.High_Speed_Control.Ki=Active_Para2;

  /*************控制器模式选着******************/
  Mode_Check_Cnt++;
  if(Mode_Check_Cnt>=4)//每20ms检测一次，PPM信号刷新周期为20ms
  {
    Controler_Mode_Select();
    Mode_Check_Cnt=0;
  }
  /*************主导控制器******************/
  Main_Leading_Control();
  /*************姿态环控制器*****************/
  Altitude_Control();
}


uint16_t Landon_Earth_Cnt=0;
uint8_t Landon_Earth_Flag=0;
uint8_t Landon_Earth_Flag_Set=0;
void Landon_Earth_Check(void)//自检触地进入怠速模式
{
   if(ABS(NamelessQuad.Acceleration[_YAW])<=15//竖直Z轴运动加速度很小
       &&Throttle_Control==Thr_Min//油门杆处于最低行程位
         &&Gyro_Length<=2.0//触地后无旋转
          &&ABS(NamelessQuad.Speed[_YAW])<=20.0)//速度很小
     Landon_Earth_Cnt++;
   else Landon_Earth_Cnt/=2;
   if(Landon_Earth_Cnt>=10000)  Landon_Earth_Cnt=10000;//防止溢出
   if(Landon_Earth_Cnt>=250*4)//持续4S
   {
     Landon_Earth_Flag=1;//着陆标志位
   }

   if(ABS(Throttle_Rate)>=1.0E-5f)//只要油门变化率不为0，即清空着陆标志位
   {
     Landon_Earth_Flag=0;
     Landon_Earth_Cnt=0;
   }

}

uint16_t Throttle_Output=0;
void Throttle_Angle_Compensate()//油门倾角补偿
{
  float CosPitch_CosRoll=ABS(Cos_Pitch*Cos_Roll);
  float Throttle_Makeup=0;
  float Temp=0;
  if(CosPitch_CosRoll>=0.999999)  CosPitch_CosRoll=0.999999;
  if(CosPitch_CosRoll<=0.000001)  CosPitch_CosRoll=0.000001;
  if(CosPitch_CosRoll<=0.50)  CosPitch_CosRoll=0.50;//Pitch,Roll约等于30度
  if(Throttle>=Thr_Start)//大于起转油门量
  {
      Temp=(uint16_t)(MAX(ABS(100*Pitch),ABS(100*Roll)));
      Temp=constrain_float(9000-Temp,0,3000)/(3000*CosPitch_CosRoll);
      Throttle_Makeup=(Throttle-Thr_Start)*Temp;//油门倾角补偿
      Throttle_Output=(uint16_t)(Thr_Start+Throttle_Makeup);
      Throttle_Output=(uint16_t)(constrain_float(Throttle_Output,Thr_Start,2000));
  }
  else Throttle_Output=Throttle;
}




void Control_Output()
{
Throttle_Angle_Compensate();//油门倾角补偿
//Landon_Earth_Check();//着陆条件自检
if(Controler_State==Unlock_Controler)//解锁
{
  if(Landon_Earth_Flag==1)//检测到着陆条件
  {
      Motor_PWM_1=Thr_Idle;//油门怠速
      Motor_PWM_2=Thr_Idle;
      Motor_PWM_3=Thr_Idle;
      Motor_PWM_4=Thr_Idle;
  }
  else
  {
     if(Controler_High_Mode==1)//姿态档位
     {
         if(Throttle>=Thr_Fly_Start)//大于起飞油门
         {
            if(GYRO_CONTROL_MODE==PID_MODE)//水平姿态环角速度读控制器来源于PID
            {
              Motor_PWM_1=Int_Sort(Throttle_Output
                            -Total_Controler.Roll_Gyro_Control.Control_OutPut
                            -Total_Controler.Pitch_Gyro_Control.Control_OutPut
                            +Total_Controler.Yaw_Gyro_Control.Control_OutPut);
              Motor_PWM_2=Int_Sort(Throttle_Output
                            +Total_Controler.Roll_Gyro_Control.Control_OutPut
                            +Total_Controler.Pitch_Gyro_Control.Control_OutPut
                            +Total_Controler.Yaw_Gyro_Control.Control_OutPut);
              Motor_PWM_3=Int_Sort(Throttle_Output
                            +Total_Controler.Roll_Gyro_Control.Control_OutPut
                            -Total_Controler.Pitch_Gyro_Control.Control_OutPut
                            -Total_Controler.Yaw_Gyro_Control.Control_OutPut);
              Motor_PWM_4=Int_Sort(Throttle_Output
                            -Total_Controler.Roll_Gyro_Control.Control_OutPut
                            +Total_Controler.Pitch_Gyro_Control.Control_OutPut
                            -Total_Controler.Yaw_Gyro_Control.Control_OutPut);
            }
            else//水平姿态环角速度读控制器来源于ADRC
            {


            }
         }
         else//小于起飞油门
         {
               Motor_PWM_1=Int_Sort(Throttle_Output);
               Motor_PWM_2=Int_Sort(Throttle_Output);
               Motor_PWM_3=Int_Sort(Throttle_Output);
               Motor_PWM_4=Int_Sort(Throttle_Output);
               Take_Off_Reset();//清积分
         }
     }
     else if(Controler_High_Mode==2)//油门托管、定高档位
     {
            if(GYRO_CONTROL_MODE==PID_MODE)//水平姿态环角速度读控制器来源于PID
            {
              Motor_PWM_1=Int_Sort(Throttle_Output
                            -Total_Controler.Roll_Gyro_Control.Control_OutPut
                            -Total_Controler.Pitch_Gyro_Control.Control_OutPut
                            +Total_Controler.Yaw_Gyro_Control.Control_OutPut);
              Motor_PWM_2=Int_Sort(Throttle_Output
                            +Total_Controler.Roll_Gyro_Control.Control_OutPut
                            +Total_Controler.Pitch_Gyro_Control.Control_OutPut
                            +Total_Controler.Yaw_Gyro_Control.Control_OutPut);
              Motor_PWM_3=Int_Sort(Throttle_Output
                            +Total_Controler.Roll_Gyro_Control.Control_OutPut
                            -Total_Controler.Pitch_Gyro_Control.Control_OutPut
                            -Total_Controler.Yaw_Gyro_Control.Control_OutPut);
              Motor_PWM_4=Int_Sort(Throttle_Output
                            -Total_Controler.Roll_Gyro_Control.Control_OutPut
                            +Total_Controler.Pitch_Gyro_Control.Control_OutPut
                            -Total_Controler.Yaw_Gyro_Control.Control_OutPut);
            }
            else//水平姿态环角速度读控制器来源于ADRC
            {



            }
     }
  }
}
else//未解锁，油门置于最低位
{
  Motor_PWM_1=Thr_Min;
  Motor_PWM_2=Thr_Min;
  Motor_PWM_3=Thr_Min;
  Motor_PWM_4=Thr_Min;
}
  Motor_PWM_1=Value_Limit(0,2000,Motor_PWM_1);//总输出限幅
  Motor_PWM_2=Value_Limit(0,2000,Motor_PWM_2);
  Motor_PWM_3=Value_Limit(0,2000,Motor_PWM_3);
  Motor_PWM_4=Value_Limit(0,2000,Motor_PWM_4);
  if(MotorTest==0x00)
  {
    PWM_Set(1000,1000,1000,1000);
  }
  else
  {
    PWM_Set((0x01&MotorTest) ? Motor_PWM_1:0,
            (0x02&MotorTest) ? Motor_PWM_2:0,
            (0x04&MotorTest) ? Motor_PWM_3:0,
            (0x08&MotorTest) ? Motor_PWM_4:0);
  }
}
/***************************觉得不错，欢迎打赏，请小哥吃热干面：支付宝账号：1094744141@qq.com*********************************/



