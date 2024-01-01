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
  if(SDK_Ctrl_Mode==0)//SDK模式下，无数据接收，正常光流模式
  {
      if(Roll_Control==0
         &&Pitch_Control==0)//无水平遥控量给定
      {
        /**************************光流位置控制器************************************/
        if(OpticalFlow_Pos_Ctrl_Expect.x==0
           &&OpticalFlow_Pos_Ctrl_Expect.y==0)
        {
          if(force_brake_flag==1||(rMat[2][2]>=0.95
             &&pythagorous2(OpticalFlow_SINS.Speed[_PITCH],OpticalFlow_SINS.Speed[_ROLL])<=40))//打杆回中后，根据当前速度、倾角判断是否进行悬停
          {
            OpticalFlow_Pos_Ctrl_Expect.x=OpticalFlow_SINS.Position[_PITCH];
            OpticalFlow_Pos_Ctrl_Expect.y=OpticalFlow_SINS.Position[_ROLL];
          }
          else  //打杆回中未满足悬停条件时，只进行速度控制 
          {
            OpticalFlow_Pos_Ctrl_Output.x=0;
            OpticalFlow_Pos_Ctrl_Output.y=0;
          }
        }
        else  OpticalFlow_Pos_Control();
       
        /***********当只需要速度控制时，开启以下注释，仅限调试时用*************/
         //OpticalFlow_Pos_Ctrl_Output.x=0;
         //OpticalFlow_Pos_Ctrl_Output.y=0;
        /**************************基于模型的加速度-姿态角映射，相比直接给姿态，参数差异大概在20倍左右************************************/
        OpticalFlow_Vel_Control(OpticalFlow_Pos_Ctrl_Output);//速度期望
      }
      else
      {
        OpticalFlow_Pos_Ctrl_Output.x=OpticalFlow_Expect_Speed_Mapping(-Target_Angle[1],Pit_Rol_Max,OpticalFlow_Speed_Control_Max);
        OpticalFlow_Pos_Ctrl_Output.y=OpticalFlow_Expect_Speed_Mapping(-Target_Angle[0],Pit_Rol_Max,OpticalFlow_Speed_Control_Max); 
        if(OpticalFlow_Speed_Control_Mode==1)
        {
          OpticalFlow_Vel_Control(OpticalFlow_Pos_Ctrl_Output);//速度期望
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
  else//SDK接收模式
  {
      if(Roll_Control==0
         &&Pitch_Control==0)//无水平遥控量给定
    {  
        if(SDK_Line.line_ctrl_enable==1)//线检测
        {
          /***********当只需要速度控制时，开启以下注释，仅限调试时用*************/
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
        else if(SDK_Point.flag==1)//跟踪点检测
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
        else//SDK模式下，未检测对于特征
        {
              /**************************光流位置控制器************************************/
              if(OpticalFlow_Pos_Ctrl_Expect.x==0
                 &&OpticalFlow_Pos_Ctrl_Expect.y==0)
              {
                if(force_brake_flag==1||(rMat[2][2]>=0.95
                   &&pythagorous2(OpticalFlow_SINS.Speed[_PITCH],OpticalFlow_SINS.Speed[_ROLL])<=40))//打杆回中后，根据当前速度、倾角判断是否进行悬停
                {
                  OpticalFlow_Pos_Ctrl_Expect.x=OpticalFlow_SINS.Position[_PITCH];
                  OpticalFlow_Pos_Ctrl_Expect.y=OpticalFlow_SINS.Position[_ROLL];
                }
                else  //打杆回中未满足悬停条件时，只进行速度控制 
                {
                  OpticalFlow_Pos_Ctrl_Output.x=0;
                  OpticalFlow_Pos_Ctrl_Output.y=0;
                }
              }
              else  OpticalFlow_Pos_Control();
                /**************************基于模型的加速度-姿态角映射，相比直接给姿态，参数差异大概在20倍左右************************************/
              OpticalFlow_Vel_Control(OpticalFlow_Pos_Ctrl_Output);//速度期望        
              PID_LPF_Reset(&Total_Controller.SDK_Roll_Position_Control,SDK_Roll_Position_Controler);
              PID_LPF_Reset(&Total_Controller.SDK_Pitch_Position_Control,SDK_Pitch_Position_Controler);
       }
    }
    else//SDK模式下存在手动打杆操作时，控制量来源于遥控器给定
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
		/////////////////////////////////SDK位置控制开始////////////////////////////////////////						
	if(ngs_sdk.update_flag==true)
	{
			if(ngs_sdk.move_flag.sdk_front_flag==true||ngs_sdk.move_flag.sdk_behind_flag==true)//前进/后退
			{
					OpticalFlow_Pos_Ctrl_Expect.x=OpticalFlow_SINS.Position[_PITCH];										//左右保持
					OpticalFlow_Pos_Ctrl_Expect.y=OpticalFlow_SINS.Position[_ROLL]+ngs_sdk.f_distance;	//前后调整		
					Total_Controller.High_Position_Control.Expect=NamelessQuad.Position[_YAW];	 				//上下保持																
			}
			
			if(ngs_sdk.move_flag.sdk_left_flag==true||ngs_sdk.move_flag.sdk_right_flag==true)//向左/向右
			{
				  OpticalFlow_Pos_Ctrl_Expect.x=OpticalFlow_SINS.Position[_PITCH]+ngs_sdk.f_distance;//左右调整
					OpticalFlow_Pos_Ctrl_Expect.y=OpticalFlow_SINS.Position[_ROLL];										 //前后保持			
					Total_Controller.High_Position_Control.Expect=NamelessQuad.Position[_YAW];			 	 //上下保持														
			}
			
			if(ngs_sdk.move_flag.sdk_up_flag==true||ngs_sdk.move_flag.sdk_down_flag==true)//上升/下降
			{
					OpticalFlow_Pos_Ctrl_Expect.x=OpticalFlow_SINS.Position[_PITCH];															//前后保持
					OpticalFlow_Pos_Ctrl_Expect.y=OpticalFlow_SINS.Position[_ROLL];																//左右保持
				  Total_Controller.High_Position_Control.Expect=NamelessQuad.Position[_YAW]+ngs_sdk.f_distance; //上下调整										
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
         &&Pitch_Control==0)//无水平遥控量给定
      {
        /**************************光流位置控制器************************************/
        if(OpticalFlow_Pos_Ctrl_Expect.x==0
           &&OpticalFlow_Pos_Ctrl_Expect.y==0)
        {
          if(force_brake_flag==1||(rMat[2][2]>=0.95
             &&pythagorous2(OpticalFlow_SINS.Speed[_PITCH],OpticalFlow_SINS.Speed[_ROLL])<=40))//打杆回中后，根据当前速度、倾角判断是否进行悬停
          {
            OpticalFlow_Pos_Ctrl_Expect.x=OpticalFlow_SINS.Position[_PITCH];
            OpticalFlow_Pos_Ctrl_Expect.y=OpticalFlow_SINS.Position[_ROLL];
          }
          else  //打杆回中未满足悬停条件时，只进行速度控制 
          {
            OpticalFlow_Pos_Ctrl_Output.x=0;
            OpticalFlow_Pos_Ctrl_Output.y=0;
          }
        }
        else  OpticalFlow_Pos_Control();
       
        /***********当只需要速度控制时，开启以下注释，仅限调试时用*************/
         //OpticalFlow_Pos_Ctrl_Output.x=0;
         //OpticalFlow_Pos_Ctrl_Output.y=0;
        /**************************基于模型的加速度-姿态角映射，相比直接给姿态，参数差异大概在20倍左右************************************/
        OpticalFlow_Vel_Control(OpticalFlow_Pos_Ctrl_Output);//速度期望
      }
      else
      {
        OpticalFlow_Pos_Ctrl_Output.x=OpticalFlow_Expect_Speed_Mapping(-Target_Angle[1],Pit_Rol_Max,OpticalFlow_Speed_Control_Max);
        OpticalFlow_Pos_Ctrl_Output.y=OpticalFlow_Expect_Speed_Mapping(-Target_Angle[0],Pit_Rol_Max,OpticalFlow_Speed_Control_Max); 
        if(OpticalFlow_Speed_Control_Mode==1)
        {
          OpticalFlow_Vel_Control(OpticalFlow_Pos_Ctrl_Output);//速度期望
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
  if(OpticalFlow_Pos_Ctrl_Cnt>=10)//50ms控制一次速度，避免输入频率过大，系统响应不过来
  {
    //计算位置偏差  
    OpticalFlow_Pos_Ctrl_Err.x=OpticalFlow_Pos_Ctrl_Expect.x-OpticalFlow_SINS.Position[_PITCH];
    OpticalFlow_Pos_Ctrl_Err.y=OpticalFlow_Pos_Ctrl_Expect.y-OpticalFlow_SINS.Position[_ROLL];
    //计算位置控制输出
    OpticalFlow_Pos_Ctrl_Output.x=Total_Controller.Optical_Position_Control.Kp*OpticalFlow_Pos_Ctrl_Err.x;
    OpticalFlow_Pos_Ctrl_Output.y=Total_Controller.Optical_Position_Control.Kp*OpticalFlow_Pos_Ctrl_Err.y;
    OpticalFlow_Pos_Ctrl_Cnt=0;
  }
}


void OpticalFlow_Vel_Control(Vector2f target)
{ 
  static uint16_t OpticalFlow_Vel_Ctrl_Cnt=0;
  OpticalFlow_Ctrl_Expect.x= target.x;//速度期望
  OpticalFlow_Ctrl_Expect.y= target.y;
  OpticalFlow_Vel_Ctrl_Cnt++;
  if(OpticalFlow_Vel_Ctrl_Cnt>=4)//20ms控制一次速度，避免输入频率过大，系统响应不过来
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
    accel_target.x=-constrain_float(OpticalFlow_Ctrl_Output.x,-Total_Controller.Optical_Speed_Control.Control_OutPut_Limit,Total_Controller.Optical_Speed_Control.Control_OutPut_Limit);//期望运动加速度
    accel_to_lean_angles(accel_target,&angle_target);//期望运动加速度转期望姿态倾角
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
  if(OpticalFlow_Vel_Ctrl_Cnt>=4)//20ms控制一次速度，避免输入频率过大，系统响应不过来
  {
    OpticalFlow_Ctrl_Err.y=constrain_float(OpticalFlow_Ctrl_Expect.y-OpticalFlow_SINS.Speed[_ROLL] ,-Total_Controller.Optical_Speed_Control.Err_Max,Total_Controller.Optical_Speed_Control.Err_Max);
    
    OpticalFlow_Ctrl_Integrate.y+=Total_Controller.Optical_Speed_Control.Ki*OpticalFlow_Ctrl_Err.y;
    
    OpticalFlow_Ctrl_Integrate.y=constrain_float(OpticalFlow_Ctrl_Integrate.y,-Total_Controller.Optical_Speed_Control.Integrate_Max,Total_Controller.Optical_Speed_Control.Integrate_Max);
    
    OpticalFlow_Ctrl_Output.y=OpticalFlow_Ctrl_Integrate.y+Total_Controller.Optical_Speed_Control.Kp*OpticalFlow_Ctrl_Err.y;

    accel_target.y=-constrain_float(OpticalFlow_Ctrl_Output.y,-Total_Controller.Optical_Speed_Control.Control_OutPut_Limit,Total_Controller.Optical_Speed_Control.Control_OutPut_Limit);//450
    accel_to_lean_angles(accel_target,&angle_target);//期望运动加速度转期望姿态倾角
    Total_Controller.Pitch_Angle_Control.Expect=angle_target.y;
    OpticalFlow_Vel_Ctrl_Cnt=0;
  }
}

