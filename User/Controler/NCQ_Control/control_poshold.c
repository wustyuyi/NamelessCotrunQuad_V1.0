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
#include "control_poshold.h"


Vector3_Nav Earth_Frame_Accel_Target={0,0,0};   //导航（地理）坐标系，正东、正北方向目标运动加速度期望
Vector3_Nav Earth_Frame_Pos_Err={0,0,0};        //导航（地理）坐标系，正东、正北方向w位置偏差
Vector2_Ang Body_Frame_Accel_Target={0,0};      //导航（地理）坐标系，机体横滚(Y正)、俯仰(X正)方向目标运动加速度期望
Vector2_Ang Body_Frame_Speed_Feedback={0,0};    //导航（地理）坐标系，机体横滚(Y正)、俯仰(X正)方向目标运动速度反馈
Vector2_Ang Body_Frame_Pos_Err={0,0};           //机体方向上位置偏差
Vector2_Ang Body_Frame_Brake_Speed={0,0};       //机体方向上刹车速度
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
  static uint16 Horizontal_Pos_Control_Cnt=0;//高度速度控制计数器
  static uint16 Horizontal_Vel_Control_Cnt=0;//高度速度控制计数器
  
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
        if(Total_Controller.Latitude_Position_Control.Expect==0
           &&Total_Controller.Longitude_Position_Control.Expect==0)//方向杆回中后，只设置一次
        {
          // Total_Controller.Latitude_Position_Control.Expect=NamelessQuad.Position[_ROLL];
          //Total_Controller.Longitude_Position_Control.Expect=NamelessQuad.Position[_PITCH];
          if(get_stopping_point_xy(&UAV_Cushion_Stop_Point)==1)
          {
            Total_Controller.Latitude_Position_Control.Expect=UAV_Cushion_Stop_Point.y;
            Total_Controller.Longitude_Position_Control.Expect=UAV_Cushion_Stop_Point.x;
          }
          else//只采用速度刹车
          {
            //速度控制器期望
            Total_Controller.Latitude_Speed_Control.Expect =0;
            Total_Controller.Longitude_Speed_Control.Expect=0;  
          }
        }
        else
        {
          //位置反馈，来源于当前惯导的位置估计
          Total_Controller.Latitude_Position_Control.FeedBack=NamelessQuad.Position[_ROLL];
          Total_Controller.Longitude_Position_Control.FeedBack=NamelessQuad.Position[_PITCH];
          //导航坐标系下E、N方向上位置偏差
          Earth_Frame_Pos_Err.N=Total_Controller.Latitude_Position_Control.Expect-Total_Controller.Latitude_Position_Control.FeedBack;
          Earth_Frame_Pos_Err.E=Total_Controller.Longitude_Position_Control.Expect-Total_Controller.Longitude_Position_Control.FeedBack;
          //导航坐标系下机体Pitch、Roll方向上位置偏差
          Body_Frame_Pos_Err.Pit=-Earth_Frame_Pos_Err.E*Sin_Yaw+Earth_Frame_Pos_Err.N*Cos_Yaw;
          Body_Frame_Pos_Err.Rol=Earth_Frame_Pos_Err.E*Cos_Yaw+Earth_Frame_Pos_Err.N*Sin_Yaw;
          //导航坐标系下机体Pitch、Roll方向上期望刹车速度，这里为单比例运算不调用PID_Control()函数
          Body_Frame_Pos_Err.Pit=constrain_float(Body_Frame_Pos_Err.Pit,-Total_Controller.Latitude_Position_Control.Err_Max, Total_Controller.Latitude_Position_Control.Err_Max);//位置偏差限幅，单位cm
          Body_Frame_Pos_Err.Rol=constrain_float(Body_Frame_Pos_Err.Rol,-Total_Controller.Longitude_Position_Control.Err_Max,Total_Controller.Longitude_Position_Control.Err_Max);//位置偏差限幅，单位cm
          
          Body_Frame_Brake_Speed.Pit=Total_Controller.Latitude_Position_Control.Kp*Body_Frame_Pos_Err.Pit;
          Body_Frame_Brake_Speed.Rol=Total_Controller.Longitude_Position_Control.Kp*Body_Frame_Pos_Err.Rol;
          //速度控制器期望
          Total_Controller.Latitude_Speed_Control.Expect =Body_Frame_Brake_Speed.Pit;
          Total_Controller.Longitude_Speed_Control.Expect=Body_Frame_Brake_Speed.Rol;  
        }
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
    }
    else //只进行水平速度控制，无水平位置控制
    {
      //分两种情况，1、导航坐标系的航向速度控制；
      //            2、载体坐标系方向上的速度控制
      if(GPS_Speed_Control_Mode==Angle_Mode)//推动方向杆，对应期望角度
      {
        Total_Controller.Pitch_Angle_Control.Expect=Target_Angle[0];
        Total_Controller.Roll_Angle_Control.Expect=Target_Angle[1];
      }
      else//推动方向杆，对应给定载体坐标系的沿Pitch,Roll方向运动速度
      {
        Horizontal_Vel_Control_Cnt++;
        if(Horizontal_Vel_Control_Cnt>=2)//10ms控制一次速度
        {
          Total_Controller.Latitude_Speed_Control.Expect =ncq_speed_mapping(-Target_Angle[0],Pit_Rol_Max,Max_Horvel);
          Total_Controller.Longitude_Speed_Control.Expect =ncq_speed_mapping(Target_Angle[1],Pit_Rol_Max,Max_Horvel);
          //导航系的水平速度，转化到机体坐标系X-Y方向上
          //沿载体Pitch、Roll方向水平速度控制
          Body_Frame_Speed_Feedback.Pit=-NamelessQuad.Speed[_PITCH]*Sin_Yaw+NamelessQuad.Speed[_ROLL]*Cos_Yaw;
          Body_Frame_Speed_Feedback.Rol= NamelessQuad.Speed[_PITCH]*Cos_Yaw+NamelessQuad.Speed[_ROLL]*Sin_Yaw;
          
          Total_Controller.Latitude_Speed_Control.FeedBack=Body_Frame_Speed_Feedback.Pit;//机头Pitch方向，Y轴正向
          Total_Controller.Longitude_Speed_Control.FeedBack=Body_Frame_Speed_Feedback.Rol;//横滚Roll方向，X轴正向
          
          PID_Control_Div_LPF(&Total_Controller.Latitude_Speed_Control);
          PID_Control_Div_LPF(&Total_Controller.Longitude_Speed_Control);//水平速度控制器得到期望运动加速度
 
          
          accel_target.y=-Total_Controller.Latitude_Speed_Control.Control_OutPut;
          accel_target.x=Total_Controller.Longitude_Speed_Control.Control_OutPut;//期望运动加速度
          accel_to_lean_angles(accel_target,&angle_target);//期望运动加速度转期望姿态倾角
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
  else//不满足定点条件，控制量给水平姿态
  {
    /********对GPS定点模式位置0，直接进入姿态模式，等待GPS信号再次满足条件时，***********
    *********自动切换至GPS定点模式，结合Controler_Mode_Select函数理解运行过程**********/
    Pos_Hold_SetFlag=0;//置0，当开关档位仍为定点模式时，
    //在控制模式里面自检是否允许再次进入GPS定点模式
    Total_Controller.Pitch_Angle_Control.Expect=Target_Angle[0];
    Total_Controller.Roll_Angle_Control.Expect=Target_Angle[1];
  }
  
}



//定点模式下，遥杆回中后，先用水平速度控制刹车，待刹停后再赋值位置选点
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
  
  if(vel_total <= 20.0f //合水平速度的小于等于20cm/s
     && accel_total<=40 //合水平加速度的小于等于40cm/s^2
       && rMat[2][2]>=0.97)//Cos_Pitch*Cos_Roll、单个方向水平姿态约为15deg，两个方向水平姿态角约为10deg  
  {
    stopping_point->x = curr_pos.x;
    stopping_point->y = curr_pos.y;
    return 1;
  }
  return 0;
}

