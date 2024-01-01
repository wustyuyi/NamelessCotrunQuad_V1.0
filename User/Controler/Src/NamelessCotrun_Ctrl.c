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
#include "NamelessCotrun_Ctrl.h"
#include "control_config.h"

/*****************遥控器行程设置**********************/
uint16 Motor_PWM_1,Motor_PWM_2,Motor_PWM_3,Motor_PWM_4,Motor_PWM_5,Motor_PWM_6;//六个电机输出PWM
uint16 Last_Motor_PWM_1,Last_Motor_PWM_2,Last_Motor_PWM_3,Last_Motor_PWM_4,Last_Motor_PWM_5,Last_Motor_PWM_6;//上次六个电机输出PWM
uint8 MotorTest=0xff;//电机序号测试
uint8_t Controler_High_Mode=1,Last_Controler_High_Mode=1;
uint8_t Controler_Horizontal_Mode=1,Last_Controler_Horizontal_Mode=1;
uint8_t Controler_Land_Mode=1,Last_Controler_Land_Mode=1;
uint8_t Reserve_Mode=0,Last_Reserve_Mode=0;
uint8_t Reserve_Mode_Fast_Exchange_Flag=0,Reserve_Mode_Fast_Exchange_Cnt=0;
uint16_t Reserve_Mode_Cnt=0;
uint8_t Control_Mode_Change=0;
uint16_t High_Hold_Throttle=0;
uint8_t  Pos_Hold_SetFlag=0;
uint8_t SDK_Ctrl_Mode=0;

typedef struct
{
	uint32_t switch_time;
	uint32_t release_time; 
	uint32_t switch_in_time;
}sdk_switch_state;
sdk_switch_state sdk_switch;

/***************************************************
函数名: void Controler_Mode_Select(void)
说明:	控制器模式选择函数
入口:	无
出口:	无
备注:	中断任务调度持续运行
****************************************************/
void Controler_Mode_Select()
{
  Last_Controler_High_Mode=Controler_High_Mode;//上次高度控制模式
  Last_Controler_Horizontal_Mode=Controler_Horizontal_Mode;//上次位置控制模式
  Last_Controler_Land_Mode=Controler_Land_Mode;//上次返航模式
  Last_Reserve_Mode=Reserve_Mode;
  if(PPM_Databuf[4]>=(RC_Calibration[4].max-RC_Calibration[4].deadband))       Controler_High_Mode=2;//气压计、超神波定高
  else if(PPM_Databuf[4]<=(RC_Calibration[4].min+RC_Calibration[4].deadband))  Controler_High_Mode=1;//纯姿态自稳
  
  if(PPM_Databuf[5]>=(RC_Calibration[5].max-RC_Calibration[5].deadband))         Controler_Horizontal_Mode=2;//水平位置控制
  else if(PPM_Databuf[5]<=(RC_Calibration[5].min+RC_Calibration[5].deadband))   Controler_Horizontal_Mode=1;//姿态自稳控制
  
  if(PPM_Databuf[6]>=(RC_Calibration[6].max-RC_Calibration[6].deadband))            {Controler_Land_Mode=2;}//返航模式}
  else if(PPM_Databuf[6]<=(RC_Calibration[6].middle+RC_Calibration[6].deadband))   {Controler_Land_Mode=1;}//非返航模式
  
  if(PPM_Databuf[6]>=(RC_Calibration[6].middle-RC_Calibration[6].deadband)
     &&PPM_Databuf[6]<=(RC_Calibration[6].middle+RC_Calibration[6].deadband))//遥控器三段开关处于中位     
	{
		 sdk_switch.switch_time=(10000*TIME_ISR_CNT+TIM2->CNT)/1000.0;//单位ms
		 sdk_switch.switch_in_time=(sdk_switch.switch_time-sdk_switch.release_time);
		 if(sdk_switch.switch_in_time>=1000)//持续切入1S中，才认为正常切入
			 SDK_Ctrl_Mode=1;   
	}
  else
  {
		 sdk_switch.release_time=(10000*TIME_ISR_CNT+TIM2->CNT)/1000.0;//单位ms
     SDK_Ctrl_Mode=0;
     NCQ_SDK_Reset();
  }  
  
  
  if(PPM_Databuf[7]>=(RC_Calibration[7].max-RC_Calibration[7].deadband))      {Reserve_Mode=2;}
  else if(PPM_Databuf[7]<=(RC_Calibration[7].min+RC_Calibration[7].deadband)) 
  {
    Reserve_Mode=1;
    OpticalFlow_SINS_Reset();
    OpticalFlow_Ctrl_Reset();
  }
  
  
  if(Reserve_Mode_Cnt>=1) Reserve_Mode_Cnt--;
  if(Reserve_Mode_Cnt==0) Reserve_Mode_Fast_Exchange_Cnt=0; 
  if(Last_Reserve_Mode!=Reserve_Mode)
  {
    if(Reserve_Mode==2)  
    {

    }
    if(Reserve_Mode==1)  
    {      
      Reserve_Mode_Cnt=600;//3s自动清零
      Reserve_Mode_Fast_Exchange_Cnt++;
      if(Reserve_Mode_Fast_Exchange_Cnt>=3)//短时间内，连续切3次 
      {
        Reserve_Mode_Fast_Exchange_Flag=1;	
        Reserve_Mode_Fast_Exchange_Cnt=0;
        Total_Controller.High_Position_Control.Expect=NamelessQuad.Position[_YAW]+Target_Height;
        Unwanted_Lock_Flag=0;
      }
    }
  }
  
  
  if(Reserve_Mode_Fast_Exchange_Flag==1)//目的是快速起飞	
  {
    Total_Controller.High_Acce_Control.Scale_Kp=1.0f;
    Total_Controller.High_Acce_Control.Scale_Ki=1.5f; 
    Total_Controller.High_Speed_Control.Scale_Kp=1.2;
    Total_Controller.High_Speed_Control.Scale_Ki=1.2f;
    Total_Controller.High_Position_Control.Scale_Kp=1.5;
    Total_Controller.High_Position_Control.Scale_Ki=1.0f; 
    if(Total_Controller.High_Position_Control.Expect<=NamelessQuad.Position[_YAW])//反馈高度大于期望高度，即恢复正常
    {
      Reserve_Mode_Fast_Exchange_Flag=0;   
    }	
  }
  else 
  { 
    Total_Controller.High_Acce_Control.Scale_Kp=1.0f;
    Total_Controller.High_Acce_Control.Scale_Ki=1.0f; 
    Total_Controller.High_Speed_Control.Scale_Kp=1.0;
    Total_Controller.High_Speed_Control.Scale_Ki=1.0f; 
    Total_Controller.High_Position_Control.Scale_Kp=1.0;
    Total_Controller.High_Position_Control.Scale_Ki=1.0f; 
  }
  
    if(Unwanted_Lock_Flag==1)//定高模式解锁后，无任何操作
  {
    Thr_Push_Over_State=Thr_Push_Over_Deadband();
    if(Thr_Push_Over_State==2)//只要向上推过了中位死区，即把允许自动上锁操作
    {
      Unwanted_Lock_Flag=0;
    }
    else
    {
      Take_Off_Reset();//清积分
      //Throttle_Control_Reset();//清积分
    }
  }
  
  if(Controler_Land_Mode!=Last_Controler_Land_Mode)
  {
    if(Controler_Land_Mode==1)   land_reset();//返航模式切回正常模式
    Total_Controller.High_Position_Control.Expect=NamelessQuad.Position[_YAW];//将开关拨动瞬间的惯导高度设置为期望高度
  }
  
  if(Controler_High_Mode!=Last_Controler_High_Mode)
  {
    if(Controler_High_Mode==2)  {Control_Mode_Change=1;}//自稳切定高，设置基准油门值，悬停高度
    if(Controler_High_Mode==1)  {Control_Mode_Change=1;}//定高切自稳
  }
  
  if(Controler_Horizontal_Mode!=Last_Controler_Horizontal_Mode)//位置通道有切换
  {
    if(Controler_Horizontal_Mode==2)  {Control_Mode_Change=2;Pos_Hold_SetFlag=0;}//自稳切定点，设置悬停点
    if(Controler_Horizontal_Mode==1)  
			{
			  Control_Mode_Change=2;Pos_Hold_SetFlag=1;     
				
				PID_Integrate_Reset(&Total_Controller.Latitude_Speed_Control);//清空水平速度控制器积分项
        PID_Integrate_Reset(&Total_Controller.Latitude_Position_Control);//清空水平位置控制器积分项
        PID_Integrate_Reset(&Total_Controller.Longitude_Speed_Control);//清空水平速度控制器积分项
        PID_Integrate_Reset(&Total_Controller.Longitude_Position_Control);//清空水平位置控制器积分项}//定点时自稳
			}
  }
  
  
  if(Control_Mode_Change==1)//存在定高模式切换，高度只设置一次
  {
    if(Controler_High_Mode==High_Hold_Mode)//本次为定高模式，即自稳切定高
    {
      High_Hold_Throttle=Throttle_Control;//保存当前油门值，只存一次
      /*******************将当前惯导竖直位置估计作为目标高度***************************/
      Total_Controller.High_Position_Control.Expect=NamelessQuad.Position[_YAW];//将开关拨动瞬间的惯导高度设置为期望高度
    }
    else//本次为自稳模式，即定高切自稳
    {
      //Throttle_Control_Reset();
    }
    Control_Mode_Change=0;//将模式切换位置0,有且仅处理一次
  }
  else if(Control_Mode_Change==2)//存在定点模式切换，悬停位置只设置一次
  {
    if(Controler_Horizontal_Mode==Pos_Hold_Mode)//本次为定点模式
    {
      if(Pos_Hold_SetFlag==0&&(GPS_ok()==true))//满足设置悬停点条件
      {
        /*******************将当前惯导水平位置估计作为目标悬停点************************/
        Total_Controller.Latitude_Position_Control.Expect=NamelessQuad.Position[_ROLL];
        Total_Controller.Longitude_Position_Control.Expect=NamelessQuad.Position[_PITCH];
        PID_Integrate_Reset(&Total_Controller.Latitude_Speed_Control);//清空水平速度控制器积分项
        PID_Integrate_Reset(&Total_Controller.Latitude_Position_Control);//清空水平位置控制器积分项
        PID_Integrate_Reset(&Total_Controller.Longitude_Speed_Control);//清空水平速度控制器积分项
        PID_Integrate_Reset(&Total_Controller.Longitude_Position_Control);//清空水平位置控制器积分项
        Pos_Hold_SetFlag=1;
      }
    }
    else//定点切自稳
    {
      PID_Integrate_Reset(&Total_Controller.Latitude_Speed_Control);//清空水平速度控制器积分项
      PID_Integrate_Reset(&Total_Controller.Latitude_Position_Control);//清空水平位置控制器积分项
      PID_Integrate_Reset(&Total_Controller.Longitude_Speed_Control);//清空水平速度控制器积分项
      PID_Integrate_Reset(&Total_Controller.Longitude_Position_Control);//清空水平位置控制器积分项
    }
    Control_Mode_Change=0;//已响应本次定点档位切换
  }
  
  /******当前档位为定点模式，但显示悬停点未设置，说明之前未满足设置定点条件有三种情况********
  1、初始通过开关切定点模式时，GPS状态未满足悬停条件；
  2、初始通过开关切定点模式时，GPS状态未满足悬停条件，之后持续检测仍然未满足GPS定点条件；
  3、之前GPS状态满足悬停条件，但由于GPS信号质量变差，自动切换至不满足GPS定点条件；
  *******重新判断当下是否满足定点条件，如满足条件更新悬停点，允许进入定点模式******/
  if(Controler_Horizontal_Mode==2)
  {
    if(GPS_ok()==true)//首次切定点不满足定点条件，之后又满足定点条件
    {
      if(Pos_Hold_SetFlag==0)//满足定点条件后，有且仅设置一次
      {
        /*******************将当前惯导水平位置估计作为目标悬停点************************/
        Total_Controller.Latitude_Position_Control.Expect=NamelessQuad.Position[_ROLL];
        Total_Controller.Longitude_Position_Control.Expect=NamelessQuad.Position[_PITCH];
        PID_Integrate_Reset(&Total_Controller.Latitude_Speed_Control);//清空水平速度控制器积分项
        PID_Integrate_Reset(&Total_Controller.Latitude_Position_Control);//清空水平位置控制器积分项
        PID_Integrate_Reset(&Total_Controller.Longitude_Speed_Control);//清空水平速度控制器积分项
        PID_Integrate_Reset(&Total_Controller.Longitude_Position_Control);//清空水平位置控制器积分项
        Pos_Hold_SetFlag=1;
      }
    }
    else//定点档位处于定点模式，但未满足定点条件，将Pos_Hold_SetFlag置0，等待满足时再设置悬停点
    {
      Pos_Hold_SetFlag=0;//不满足定点条件时，复位位置锁定标志位，等待满足定点条件时，再次锁定
      PID_Integrate_Reset(&Total_Controller.Latitude_Speed_Control);//清空水平速度控制器积分项
      PID_Integrate_Reset(&Total_Controller.Latitude_Position_Control);//清空水平位置控制器积分项
      PID_Integrate_Reset(&Total_Controller.Longitude_Speed_Control);//清空水平速度控制器积分项
      PID_Integrate_Reset(&Total_Controller.Longitude_Position_Control);//清空水平位置控制器积分项
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



void Angle_Control()//角度环节
{
  static uint16 Yaw_Cnt=0;
  //角度反馈
  Total_Controller.Pitch_Angle_Control.FeedBack=(Pitch-Pitch_Offset);
  PID_Control(&Total_Controller.Pitch_Angle_Control);
  Total_Controller.Roll_Angle_Control.FeedBack =(Roll-Roll_Offset);
  PID_Control(&Total_Controller.Roll_Angle_Control);
  
  if(Yaw_Control==0)//偏航杆置于中位
  {
    if(Yaw_Cnt<=500)//无头模式、飞机上电后一段时间锁定偏航角，磁力计、陀螺仪融合需要一段时间，这里取500
    {
      Yaw_Cnt++;
    }
    if(Total_Controller.Yaw_Angle_Control.Expect==0//回中时赋角度期望值
       ||Yaw_Cnt<=500
         ||Landon_Earth_Flag==1)//或者满足触地条件、复位偏航角期望
    {
      Total_Controller.Yaw_Angle_Control.Expect=Yaw;
    }
    Total_Controller.Yaw_Angle_Control.FeedBack=Yaw;//偏航角反馈
    PID_Control_Yaw(&Total_Controller.Yaw_Angle_Control);//偏航角度控制
    Total_Controller.Yaw_Gyro_Control.Expect=Total_Controller.Yaw_Angle_Control.Control_OutPut;//偏航角速度环期望，来源于偏航角度控制器输出
    
    if(SDK_Line.line_ctrl_enable==1&&SDK_Ctrl_Mode==1)//SDK模式下的循迹模式，偏航角速度期望来源于SDK数据
    {
      Total_Controller.Yaw_Gyro_Control.Expect=2*SDK_Target_Yaw_Gyro;
      Total_Controller.Yaw_Angle_Control.Expect=0;//偏航角期望给0,不进行角度控制
      //SDK_Line.flag=0;
    }
  }
  else//波动偏航方向杆后，只进行内环角速度控制
  {
    Total_Controller.Yaw_Angle_Control.Expect=0;//偏航角期望给0,不进行角度控制
    Total_Controller.Yaw_Gyro_Control.Expect=Yaw_Control;//偏航角速度环期望，直接来源于遥控器打杆量
  }
  //Total_Controller.Yaw_Gyro_Control.Expect=Yaw_Control;//偏航角速度环期望，直接来源于遥控器打杆量
}


uint16_t Yaw_Control_Fault_Cnt=0;
float Last_Yaw_Gyro_Control_Expect=0,Yaw_Gyro_Control_Expect_Delta=0;
float Last_Pitch_Gyro_Control_Expect=0,Pitch_Gyro_Control_Expect_Delta=0;
float Last_Roll_Gyro_Control_Expect=0,Roll_Gyro_Control_Expect_Delta=0;
float Pitch_Roll_Feedforward_Kp=0.1f,Pitch_Roll_Feedforward_Kd=0.0f;// 1.45  0.25         0.85     //0.45
float Yaw_Feedforward_Kp=0.0f,Yaw_Feedforward_Kd=0.05f;//偏航角前馈控制 0.15   1.0  0.3         //0.05
void Gyro_Control()//角速度环
{
  if(GYRO_CONTROL_MODE==PID_MODE)//俯仰、横滚方向姿态内环角速度控制器采用PID控制器
  {
    /***************内环角速度期望****************/
    Total_Controller.Pitch_Gyro_Control.Expect=Total_Controller.Pitch_Angle_Control.Control_OutPut;
    Total_Controller.Roll_Gyro_Control.Expect=Total_Controller.Roll_Angle_Control.Control_OutPut;
    
    /***************内环角速度反馈****************/
    Total_Controller.Pitch_Gyro_Control.FeedBack=Pitch_Gyro;
    Total_Controller.Roll_Gyro_Control.FeedBack=Roll_Gyro;
    
    /***************内环角速度控制****************/
    //PID_Control_Div_LPF(&Total_Controller.Pitch_Gyro_Control);
    //PID_Control_Div_LPF(&Total_Controller.Roll_Gyro_Control);
    
    /***************内环角速度控制：微分参数动态调整****************/
    PID_Control_Div_LPF_For_Gyro(&Total_Controller.Pitch_Gyro_Control);
    PID_Control_Div_LPF_For_Gyro(&Total_Controller.Roll_Gyro_Control);
       
    Pitch_Gyro_Control_Expect_Delta=1000*(Total_Controller.Pitch_Gyro_Control.Expect-Last_Pitch_Gyro_Control_Expect
                                         /Total_Controller.Pitch_Gyro_Control.PID_Controller_Dt.Time_Delta);
    Roll_Gyro_Control_Expect_Delta=1000*(Total_Controller.Roll_Gyro_Control.Expect-Last_Roll_Gyro_Control_Expect
                                        /Total_Controller.Roll_Gyro_Control.PID_Controller_Dt.Time_Delta);
    
    Last_Pitch_Gyro_Control_Expect=Total_Controller.Pitch_Gyro_Control.Expect;
    Last_Roll_Gyro_Control_Expect=Total_Controller.Roll_Gyro_Control.Expect;
    
    Total_Controller.Pitch_Gyro_Control.Control_OutPut+=Pitch_Roll_Feedforward_Kd*Pitch_Gyro_Control_Expect_Delta
      +Pitch_Roll_Feedforward_Kp*Total_Controller.Pitch_Gyro_Control.Expect;
    Total_Controller.Pitch_Gyro_Control.Control_OutPut=constrain_float(Total_Controller.Pitch_Gyro_Control.Control_OutPut,
                                                                       -Total_Controller.Pitch_Gyro_Control.Control_OutPut_Limit,
                                                                       Total_Controller.Pitch_Gyro_Control.Control_OutPut_Limit);
    
    Total_Controller.Roll_Gyro_Control.Control_OutPut+=Pitch_Roll_Feedforward_Kd*Roll_Gyro_Control_Expect_Delta
      +Pitch_Roll_Feedforward_Kp*Total_Controller.Roll_Gyro_Control.Expect;;
      Total_Controller.Roll_Gyro_Control.Control_OutPut=constrain_float(Total_Controller.Roll_Gyro_Control.Control_OutPut,
                                                                        -Total_Controller.Roll_Gyro_Control.Control_OutPut_Limit,
                                                                        Total_Controller.Roll_Gyro_Control.Control_OutPut_Limit);
      
  }
  else if(GYRO_CONTROL_MODE==ADRC_MODE)//俯仰、横滚方向姿态内环角速度控制器采用ADRC自抗扰控制器
  {
    ADRC_Control(&ADRC_Pitch_Controller,
                 Total_Controller.Pitch_Angle_Control.Control_OutPut,//角速度期望
                 Pitch_Gyro);//角速度状态反馈
    ADRC_Control(&ADRC_Roll_Controller,
                 Total_Controller.Roll_Angle_Control.Control_OutPut,//角速度期望
                 Roll_Gyro);//角速度状态反馈
  }
  else//测试用、正常只选择一种模式
  {
    /***************内环角速度期望****************/
    Total_Controller.Pitch_Gyro_Control.Expect=Total_Controller.Pitch_Angle_Control.Control_OutPut;
    Total_Controller.Roll_Gyro_Control.Expect=Total_Controller.Roll_Angle_Control.Control_OutPut;
    /***************内环角速度反馈****************/
    Total_Controller.Pitch_Gyro_Control.FeedBack=Pitch_Gyro;
    Total_Controller.Roll_Gyro_Control.FeedBack=Roll_Gyro;
    
    /***************内环角速度控制****************/
    PID_Control_Div_LPF(&Total_Controller.Pitch_Gyro_Control);
    PID_Control_Div_LPF(&Total_Controller.Roll_Gyro_Control);
    
    ADRC_Control(&ADRC_Pitch_Controller,
                 Total_Controller.Pitch_Angle_Control.Control_OutPut,//角速度期望
                 Pitch_Gyro);//角速度状态反馈
    ADRC_Control(&ADRC_Roll_Controller,
                 Total_Controller.Roll_Angle_Control.Control_OutPut,//角速度期望
                 Roll_Gyro);//角速度状态反馈
  }
  
  //偏航角前馈控制
  //Total_Controller.Yaw_Gyro_Control.FeedBack=Yaw_Gyro;
  Total_Controller.Yaw_Gyro_Control.FeedBack=Yaw_Gyro_Earth_Frame;//Yaw_Gyro;
  
  PID_Control_Div_LPF(&Total_Controller.Yaw_Gyro_Control);
  Yaw_Gyro_Control_Expect_Delta=1000*(Total_Controller.Yaw_Gyro_Control.Expect-Last_Yaw_Gyro_Control_Expect)
    /Total_Controller.Yaw_Gyro_Control.PID_Controller_Dt.Time_Delta;
  //**************************偏航角前馈控制**********************************
  Total_Controller.Yaw_Gyro_Control.Control_OutPut+=Yaw_Feedforward_Kp*Total_Controller.Yaw_Gyro_Control.Expect
                                                   +Yaw_Feedforward_Kd*Yaw_Gyro_Control_Expect_Delta;//偏航角前馈控制
  Total_Controller.Yaw_Gyro_Control.Control_OutPut=constrain_float(Total_Controller.Yaw_Gyro_Control.Control_OutPut,
                                                                   -Total_Controller.Yaw_Gyro_Control.Control_OutPut_Limit,
                                                                   Total_Controller.Yaw_Gyro_Control.Control_OutPut_Limit);
  Last_Yaw_Gyro_Control_Expect=Total_Controller.Yaw_Gyro_Control.Expect;
  /*******偏航控制异常情况判断，即偏航控制量很大时，偏航角速度很小，如此时为强外力干扰、已着地等******************************/
  if(ABS(Total_Controller.Yaw_Gyro_Control.Control_OutPut)>Total_Controller.Yaw_Gyro_Control.Control_OutPut_Limit/2//偏航控制输出相对较大
     &&ABS(Yaw_Gyro)<=30.0)//偏航角速度相对很小
  {
    Yaw_Control_Fault_Cnt++;
    if(Yaw_Control_Fault_Cnt>=500) Yaw_Control_Fault_Cnt=500;
  }
  else Yaw_Control_Fault_Cnt/=2;//不满足，快速削减至0
  
  if(Yaw_Control_Fault_Cnt>=400)//持续5ms*400=2S,特殊处理
  {
    PID_Integrate_Reset(&Total_Controller.Yaw_Gyro_Control);//清空偏航角速度控制的积分
    PID_Integrate_Reset(&Total_Controller.Yaw_Angle_Control);//清空偏航角控制的积分
    Total_Controller.Yaw_Angle_Control.Expect=Yaw;//将当前偏航角，作为期望偏航角
    Yaw_Control_Fault_Cnt=0;
  }
  /*******偏航控制异常处理结束******************************/
}

uint16 Throttle=0,Last_Throttle=0;
void Main_Leading_Control(void)
{
  /*********************根据遥控器切换档位，飞控进入不同模式****************************/
  if(Controler_Land_Mode==1)//非返航着陆模式
  {
    if(Controler_High_Mode==1//姿态自稳定模式
       &&Controler_Horizontal_Mode==1)//GPS定点档位未设置
    {
      Total_Controller.Pitch_Angle_Control.Expect=Target_Angle[0];
      Total_Controller.Roll_Angle_Control.Expect=Target_Angle[1];
      
      if(Throttle_Control<=1000)   Throttle=1000;
      else Throttle=Throttle_Control;//油门直接来源于遥控器油门给定
      Last_Throttle=Throttle;
    }
    else if(Controler_High_Mode==2//定高模式
            &&Controler_Horizontal_Mode==1)//GPS定点档位未设置
    {
      /**************************定高模式，水平姿态期望角来源于遥控器******************************************/    
#if  (Optical_Enable==0)
      Total_Controller.Pitch_Angle_Control.Expect=Target_Angle[0];
      Total_Controller.Roll_Angle_Control.Expect=Target_Angle[1];
#else   //光流辅助悬停
      if(Reserve_Mode==2&&Sensor_Flag.Hcsr04_Health==1&&OpticalFlow_Is_Work==1)//超声波有效且存在光流外设时，才允许进入光流模式  
      {  
        if(SDK_Take_Over_Ctrl==1)       
        {
          OpticalFlow_Control(0);//普通光流模式、无线数传与OPENMV参与的SDK模式        
        }
        else if(SDK_Take_Over_Ctrl==2)  
        {
            if(SDK_Ctrl_Mode==1)    NCQ_SDK_Run();//用户事先指定的SDK开发者模式 
            else  OpticalFlow_Control_Pure(0);//普通光流模式
        }
      }
      else 
      {
        Total_Controller.Pitch_Angle_Control.Expect=Target_Angle[0];
        Total_Controller.Roll_Angle_Control.Expect=Target_Angle[1];
      }	
#endif
			ncq_control_althold();//高度控制  
    }
    else if(Controler_High_Mode==2//定高模式
            &&Controler_Horizontal_Mode==2)//GPS定点档位已设置
    {
      ncq_control_althold();//高度控制OpticalFlow_Control(0);
      ncq_control_poshold();//位置控制
    }
    else//其它
    {
      Total_Controller.Pitch_Angle_Control.Expect=Target_Angle[0];
      Total_Controller.Roll_Angle_Control.Expect=Target_Angle[1];
      if(Throttle_Control<=1000)   Throttle=1000;
      else Throttle=Throttle_Control;//油门直接来源于遥控器油门给定
      Last_Throttle=Throttle;
    }
    land_state_check();
  }
  else//返航着陆模式
  {
    land_run();
  }
}
/************姿态环控制器：角度+角速度****************/
void Attitude_Control(void)
{
  Angle_Control();//角度控制
  Gyro_Control();//角速度控制
}


float Active_Para1,Active_Para2;
/***************************************************
函数名: void Total_Control(void)
说明:	总控制器运行，大体分三步：
1、根据遥控器输入、当前状态，给定运行模式（自稳+油门手动、定高+自稳、定高+定点（控速）等）
2、主导上层控制器给定姿态期望，高度控制等
3、自稳（姿态）控制
入口:	无
出口:	无
备注:	上电初始化，运行一次
****************************************************/
void Total_Control(void)
{
  /***********当PPM_ch6、ch7为模拟通道时，可以作为实时在线调参使用******/
  //Active_Para1=PPM_Databuf[6]-1000;
  //Active_Para2=PPM_Databuf[7]-1000;
  //Active_Para1=0.1*constrain_float(Active_Para1-500,-500,500);
  //Active_Para2=0.0001*constrain_float(Active_Para2,0,1000);
  //Total_Controler.High_Speed_Control.Kp=Active_Para1;
  //Total_Controler.High_Speed_Control.Ki=Active_Para2;
  /*************控制器模式选着******************/
  Controler_Mode_Select();
  /*************主导控制器******************/
  Main_Leading_Control();
  /*************姿态环控制器*****************/
  Attitude_Control();
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


/**************************************************************
***************************************************************
X型安装方式，电机序号与姿态角关系
                  -
                Pitch
          3#             1#
            *          *
-   Roll          *         Roll   +
            *          *
          2#             4#
                Pitch
                  +
加速度传感器轴向与载体X、Y、Z同轴，沿轴向原点看，逆时针旋转角度为+
Y Aixs
*
*
*
*
*
*
* * * * * * * *   X Axis
(0)
*******************************************************************
******************************************************************/
uint16_t Idel_Cnt=0;
#define Idel_Transition_Gap 2//怠速递增间隔时间 10*5=50ms
#define Idel_Transition_Period 100//怠速启动最大计数器  50ms*100=5s
uint16_t Thr_Idle_Transition_Cnt=0;
void Control_Output()
{
  Throttle_Angle_Compensate();//油门倾角补偿
  landon_earth_check();//着陆条件自检
  if(Controler_State==Unlock_Controler)//解锁
  {
    if(Landon_Earth_Flag==1)//检测到着陆条件
    {
      if(Last_Motor_PWM_1<=Thr_Min
         &&Last_Motor_PWM_2<=Thr_Min
           &&Last_Motor_PWM_3<=Thr_Min
             &&Last_Motor_PWM_4<=Thr_Min
               //&&Last_Motor_PWM_5<=Thr_Min
               //&&Last_Motor_PWM_6<=Thr_Min
               )//只有上锁后再解锁时才会满足
      {
        //如果上次油门输出值为最低位，进入怠速时，安排过渡过程
        Thr_Idle_Transition_Cnt=Idel_Transition_Period;
      }
      else//其他时刻进入着陆条件
      {
        if(Last_Landon_Earth_Flag==0)//上次为起飞状态，本次为着陆状态，上锁电机
        {
          Controler_State=Lock_Controler;
					Bling_Set(&Light_3,3000,200,0.5,0,GPIOC,GPIO_Pin_8,0);
        }
      }
      
      Idel_Cnt++;
      if(Idel_Cnt>=Idel_Transition_Gap)
      {
        if(Thr_Idle_Transition_Cnt>=1)
          Thr_Idle_Transition_Cnt--;
        Idel_Cnt=0;
      }
      Motor_PWM_1=Thr_Min+(Idel_Transition_Period-Thr_Idle_Transition_Cnt)*(Thr_Idle-Thr_Min)/Idel_Transition_Period;//油门怠速
      Motor_PWM_2=Thr_Min+(Idel_Transition_Period-Thr_Idle_Transition_Cnt)*(Thr_Idle-Thr_Min)/Idel_Transition_Period;
      Motor_PWM_3=Thr_Min+(Idel_Transition_Period-Thr_Idle_Transition_Cnt)*(Thr_Idle-Thr_Min)/Idel_Transition_Period;
      Motor_PWM_4=Thr_Min+(Idel_Transition_Period-Thr_Idle_Transition_Cnt)*(Thr_Idle-Thr_Min)/Idel_Transition_Period;
      Motor_PWM_5=Thr_Min+(Idel_Transition_Period-Thr_Idle_Transition_Cnt)*(Thr_Idle-Thr_Min)/Idel_Transition_Period;
      Motor_PWM_6=Thr_Min+(Idel_Transition_Period-Thr_Idle_Transition_Cnt)*(Thr_Idle-Thr_Min)/Idel_Transition_Period;
      Take_Off_Reset();//清积分
      ADRC_Integrate_Reset(&ADRC_Pitch_Controller);
      ADRC_Integrate_Reset(&ADRC_Roll_Controller);
    }
    else  //解锁后不满足着陆条件，默认起飞
    {
      if(Controler_High_Mode==1)//姿态档位
      {
        if(Throttle>=Thr_Fly_Start)//大于起飞油门
        {
          if(GYRO_CONTROL_MODE==PID_MODE)//水平姿态环角速度读控制器来源于PID
          {
            Motor_PWM_1=Int_Sort(
                                 Moter1_Thr_Scale*Throttle_Output
                                   +Moter1_Roll_Scale*Total_Controller.Roll_Gyro_Control.Control_OutPut
                                     +Moter1_Pitch_Scale*Total_Controller.Pitch_Gyro_Control.Control_OutPut
                                       +Moter1_Yaw_Scale*Total_Controller.Yaw_Gyro_Control.Control_OutPut);
            Motor_PWM_2=Int_Sort(
                                 Moter2_Thr_Scale*Throttle_Output
                                   +Moter2_Roll_Scale*Total_Controller.Roll_Gyro_Control.Control_OutPut
                                     +Moter2_Pitch_Scale*Total_Controller.Pitch_Gyro_Control.Control_OutPut
                                       +Moter2_Yaw_Scale*Total_Controller.Yaw_Gyro_Control.Control_OutPut);
            Motor_PWM_3=Int_Sort(
                                 Moter3_Thr_Scale*Throttle_Output
                                   +Moter3_Roll_Scale*Total_Controller.Roll_Gyro_Control.Control_OutPut
                                     +Moter3_Pitch_Scale*Total_Controller.Pitch_Gyro_Control.Control_OutPut
                                       +Moter3_Yaw_Scale*Total_Controller.Yaw_Gyro_Control.Control_OutPut);
            Motor_PWM_4=Int_Sort(
                                 Moter4_Thr_Scale*Throttle_Output
                                   +Moter4_Roll_Scale*Total_Controller.Roll_Gyro_Control.Control_OutPut
                                     +Moter4_Pitch_Scale*Total_Controller.Pitch_Gyro_Control.Control_OutPut
                                       +Moter4_Yaw_Scale*Total_Controller.Yaw_Gyro_Control.Control_OutPut);
            Motor_PWM_5=Int_Sort(
                                 Moter5_Thr_Scale*Throttle_Output
                                   +Moter5_Roll_Scale*Total_Controller.Roll_Gyro_Control.Control_OutPut
                                     +Moter5_Pitch_Scale*Total_Controller.Pitch_Gyro_Control.Control_OutPut
                                       +Moter5_Yaw_Scale*Total_Controller.Yaw_Gyro_Control.Control_OutPut);
            Motor_PWM_6=Int_Sort(
                                 Moter6_Thr_Scale*Throttle_Output
                                   +Moter6_Roll_Scale*Total_Controller.Roll_Gyro_Control.Control_OutPut
                                     +Moter6_Pitch_Scale*Total_Controller.Pitch_Gyro_Control.Control_OutPut
                                       +Moter6_Yaw_Scale*Total_Controller.Yaw_Gyro_Control.Control_OutPut);
            
          }
          else//水平姿态环角速度读控制器来源于ADRC
          {
            Motor_PWM_1=Int_Sort(
                                 Moter1_Thr_Scale*Throttle_Output
                                   +Moter1_Roll_Scale*ADRC_Roll_Controller.u
                                     +Moter1_Pitch_Scale*ADRC_Pitch_Controller.u
                                       +Moter1_Yaw_Scale*Total_Controller.Yaw_Gyro_Control.Control_OutPut);
            Motor_PWM_2=Int_Sort(
                                 Moter2_Thr_Scale*Throttle_Output
                                   +Moter2_Roll_Scale*ADRC_Roll_Controller.u
                                     +Moter2_Pitch_Scale*ADRC_Pitch_Controller.u
                                       +Moter2_Yaw_Scale*Total_Controller.Yaw_Gyro_Control.Control_OutPut);
            Motor_PWM_3=Int_Sort(
                                 Moter3_Thr_Scale*Throttle_Output
                                   +Moter3_Roll_Scale*ADRC_Roll_Controller.u
                                     +Moter3_Pitch_Scale*ADRC_Pitch_Controller.u
                                       +Moter3_Yaw_Scale*Total_Controller.Yaw_Gyro_Control.Control_OutPut);
            Motor_PWM_4=Int_Sort(
                                 Moter4_Thr_Scale*Throttle_Output
                                   +Moter4_Roll_Scale*ADRC_Roll_Controller.u
                                     +Moter4_Pitch_Scale*ADRC_Pitch_Controller.u
                                       +Moter4_Yaw_Scale*Total_Controller.Yaw_Gyro_Control.Control_OutPut);
            Motor_PWM_5=Int_Sort(
                                 Moter5_Thr_Scale*Throttle_Output
                                   +Moter5_Roll_Scale*ADRC_Roll_Controller.u
                                     +Moter5_Pitch_Scale*ADRC_Pitch_Controller.u
                                       +Moter5_Yaw_Scale*Total_Controller.Yaw_Gyro_Control.Control_OutPut);
            Motor_PWM_6=Int_Sort(
                                 Moter6_Thr_Scale*Throttle_Output
                                   +Moter6_Roll_Scale*ADRC_Roll_Controller.u
                                     +Moter6_Pitch_Scale*ADRC_Pitch_Controller.u
                                       +Moter6_Yaw_Scale*Total_Controller.Yaw_Gyro_Control.Control_OutPut);
          }
        }
        else//小于起飞油门
        {
          Motor_PWM_1=Int_Sort(Throttle_Output);
          Motor_PWM_2=Int_Sort(Throttle_Output);
          Motor_PWM_3=Int_Sort(Throttle_Output);
          Motor_PWM_4=Int_Sort(Throttle_Output);
          Motor_PWM_5=Int_Sort(Throttle_Output);
          Motor_PWM_6=Int_Sort(Throttle_Output);
          Take_Off_Reset();//清积分
          ADRC_Integrate_Reset(&ADRC_Pitch_Controller);
          ADRC_Integrate_Reset(&ADRC_Roll_Controller);
        }
        Motor_PWM_1=Value_Limit(Thr_Idle,2000,Motor_PWM_1);//总输出限幅
        Motor_PWM_2=Value_Limit(Thr_Idle,2000,Motor_PWM_2);
        Motor_PWM_3=Value_Limit(Thr_Idle,2000,Motor_PWM_3);
        Motor_PWM_4=Value_Limit(Thr_Idle,2000,Motor_PWM_4);
        Motor_PWM_5=Value_Limit(Thr_Idle,2000,Motor_PWM_5);
        Motor_PWM_6=Value_Limit(Thr_Idle,2000,Motor_PWM_6);
				Throttle_Control_Reset();
      }
      else if(Controler_High_Mode==2)//油门托管、定高档位
      {
        if(GYRO_CONTROL_MODE==PID_MODE)//水平姿态环角速度读控制器来源于PID
        {
          Motor_PWM_1=Int_Sort(
                               Moter1_Thr_Scale*Throttle_Output
                                 +Moter1_Roll_Scale*Total_Controller.Roll_Gyro_Control.Control_OutPut
                                   +Moter1_Pitch_Scale*Total_Controller.Pitch_Gyro_Control.Control_OutPut
                                     +Moter1_Yaw_Scale*Total_Controller.Yaw_Gyro_Control.Control_OutPut);
          Motor_PWM_2=Int_Sort(
                               Moter2_Thr_Scale*Throttle_Output
                                 +Moter2_Roll_Scale*Total_Controller.Roll_Gyro_Control.Control_OutPut
                                   +Moter2_Pitch_Scale*Total_Controller.Pitch_Gyro_Control.Control_OutPut
                                     +Moter2_Yaw_Scale*Total_Controller.Yaw_Gyro_Control.Control_OutPut);
          Motor_PWM_3=Int_Sort(
                               Moter3_Thr_Scale*Throttle_Output
                                 +Moter3_Roll_Scale*Total_Controller.Roll_Gyro_Control.Control_OutPut
                                   +Moter3_Pitch_Scale*Total_Controller.Pitch_Gyro_Control.Control_OutPut
                                     +Moter3_Yaw_Scale*Total_Controller.Yaw_Gyro_Control.Control_OutPut);
          Motor_PWM_4=Int_Sort(
                               Moter4_Thr_Scale*Throttle_Output
                                 +Moter4_Roll_Scale*Total_Controller.Roll_Gyro_Control.Control_OutPut
                                   +Moter4_Pitch_Scale*Total_Controller.Pitch_Gyro_Control.Control_OutPut
                                     +Moter4_Yaw_Scale*Total_Controller.Yaw_Gyro_Control.Control_OutPut);
          Motor_PWM_5=Int_Sort(
                               Moter5_Thr_Scale*Throttle_Output
                                 +Moter5_Roll_Scale*Total_Controller.Roll_Gyro_Control.Control_OutPut
                                   +Moter5_Pitch_Scale*Total_Controller.Pitch_Gyro_Control.Control_OutPut
                                     +Moter5_Yaw_Scale*Total_Controller.Yaw_Gyro_Control.Control_OutPut);
          Motor_PWM_6=Int_Sort(
                               Moter6_Thr_Scale*Throttle_Output
                                 +Moter6_Roll_Scale*Total_Controller.Roll_Gyro_Control.Control_OutPut
                                   +Moter6_Pitch_Scale*Total_Controller.Pitch_Gyro_Control.Control_OutPut
                                     +Moter6_Yaw_Scale*Total_Controller.Yaw_Gyro_Control.Control_OutPut);
        }
        else//水平姿态环角速度读控制器来源于ADRC
        {
          Motor_PWM_1=Int_Sort(
                               Moter1_Thr_Scale*Throttle_Output
                                 +Moter1_Roll_Scale*ADRC_Roll_Controller.u
                                   +Moter1_Pitch_Scale*ADRC_Pitch_Controller.u
                                     +Moter1_Yaw_Scale*Total_Controller.Yaw_Gyro_Control.Control_OutPut);
          Motor_PWM_2=Int_Sort(
                               Moter2_Thr_Scale*Throttle_Output
                                 +Moter2_Roll_Scale*ADRC_Roll_Controller.u
                                   +Moter2_Pitch_Scale*ADRC_Pitch_Controller.u
                                     +Moter2_Yaw_Scale*Total_Controller.Yaw_Gyro_Control.Control_OutPut);
          Motor_PWM_3=Int_Sort(
                               Moter3_Thr_Scale*Throttle_Output
                                 +Moter3_Roll_Scale*ADRC_Roll_Controller.u
                                   +Moter3_Pitch_Scale*ADRC_Pitch_Controller.u
                                     +Moter3_Yaw_Scale*Total_Controller.Yaw_Gyro_Control.Control_OutPut);
          Motor_PWM_4=Int_Sort(
                               Moter4_Thr_Scale*Throttle_Output
                                 +Moter4_Roll_Scale*ADRC_Roll_Controller.u
                                   +Moter4_Pitch_Scale*ADRC_Pitch_Controller.u
                                     +Moter4_Yaw_Scale*Total_Controller.Yaw_Gyro_Control.Control_OutPut);
          Motor_PWM_5=Int_Sort(
                               Moter5_Thr_Scale*Throttle_Output
                                 +Moter5_Roll_Scale*ADRC_Roll_Controller.u
                                   +Moter5_Pitch_Scale*ADRC_Pitch_Controller.u
                                     +Moter5_Yaw_Scale*Total_Controller.Yaw_Gyro_Control.Control_OutPut);
          Motor_PWM_6=Int_Sort(
                               Moter6_Thr_Scale*Throttle_Output
                                 +Moter6_Roll_Scale*ADRC_Roll_Controller.u
                                   +Moter6_Pitch_Scale*ADRC_Pitch_Controller.u
                                     +Moter6_Yaw_Scale*Total_Controller.Yaw_Gyro_Control.Control_OutPut);
          
        }
        Motor_PWM_1=Value_Limit(Thr_Idle,2000,Motor_PWM_1);//总输出限幅
        Motor_PWM_2=Value_Limit(Thr_Idle,2000,Motor_PWM_2);
        Motor_PWM_3=Value_Limit(Thr_Idle,2000,Motor_PWM_3);
        Motor_PWM_4=Value_Limit(Thr_Idle,2000,Motor_PWM_4);
        Motor_PWM_5=Value_Limit(Thr_Idle,2000,Motor_PWM_5);
        Motor_PWM_6=Value_Limit(Thr_Idle,2000,Motor_PWM_6);
      }
    }
  }
  else//未解锁，油门置于最低位，停转
  {
    Motor_PWM_1=Thr_Min;
    Motor_PWM_2=Thr_Min;
    Motor_PWM_3=Thr_Min;
    Motor_PWM_4=Thr_Min;
    Motor_PWM_5=Thr_Min;
    Motor_PWM_6=Thr_Min;
    Take_Off_Reset();//清积分
    Throttle_Control_Reset();
    ADRC_Integrate_Reset(&ADRC_Pitch_Controller);
    ADRC_Integrate_Reset(&ADRC_Roll_Controller);
  }
  Last_Motor_PWM_1=Motor_PWM_1;
  Last_Motor_PWM_2=Motor_PWM_2;
  Last_Motor_PWM_3=Motor_PWM_3;
  Last_Motor_PWM_4=Motor_PWM_4;
  Last_Motor_PWM_5=Motor_PWM_5;
  Last_Motor_PWM_6=Motor_PWM_6;
  
  
  Motor_PWM_1=Value_Limit(0,2000,Motor_PWM_1);//总输出限幅
  Motor_PWM_2=Value_Limit(0,2000,Motor_PWM_2);
  Motor_PWM_3=Value_Limit(0,2000,Motor_PWM_3);
  Motor_PWM_4=Value_Limit(0,2000,Motor_PWM_4);
  Motor_PWM_5=Value_Limit(0,2000,Motor_PWM_5);
  Motor_PWM_6=Value_Limit(0,2000,Motor_PWM_6);
  if(MotorTest==0x00)
  {
    PWM_Set(Thr_Min,Thr_Min,Thr_Min,Thr_Min,Thr_Min,Thr_Min);
  }
  else
  {
    PWM_Set((0x01&MotorTest) ? Motor_PWM_1:0,
            (0x02&MotorTest) ? Motor_PWM_2:0,
            (0x04&MotorTest) ? Motor_PWM_3:0,
            (0x08&MotorTest) ? Motor_PWM_4:0,
            (0x10&MotorTest) ? Motor_PWM_5:0,
            (0x20&MotorTest) ? Motor_PWM_6:0);
  }
}




