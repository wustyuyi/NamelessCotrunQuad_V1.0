#include "Headfile.h"
#include "Key.h"
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
int16_t Page_Number=0;//2
/***************************************************
函数名: void Key_Init(void)
说明:	按键初始化
入口:	无
出口:	无
备注:	上电初始化，运行一次
****************************************************/
void Key_Init(void)
{
GPIO_InitTypeDef  GPIO_InitStructure;
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8 | GPIO_Pin_9;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/***************************觉得不错，欢迎打赏，请小哥吃热干面：支付宝账号：1094744141@qq.com*********************************/
uint8 QuadShow_Cnt=0;
void QuadInit(void)
{
QuadShow_Cnt++;
delay_ms(100);
if(QuadShow_Cnt==4)  {LCD_CLS();delay_ms(500);}
if(QuadShow_Cnt<=3)
{
LCD_P8x16Str(0,0,"NamelessCotrun");
if(Sensor_Init_Flag.NRF24L01_Okay==1) LCD_P8x16Str(10,2,"NRF Is Okay");
if(Sensor_Init_Flag.MPU6050_Okay==1) LCD_P8x16Str(10,4,"MPU Is Okay");
if(Sensor_Init_Flag.Mag_Okay==1) LCD_P8x16Str(10,6,"Mag Is Okay");
}
else
{
LCD_P8x16Str(0,0,"NamelessCotrun");
if(Sensor_Init_Flag.Baro_Okay==1) LCD_P8x16Str(10,2,"MS Is Okay");
}


}

/***************************************************
函数名: void Key_Scan()
说明:	按键扫描程序，显示屏切换翻页
入口:	无
出口:	无
备注:	在主函数While(1)里面，利用中断空隙时间一直运行
****************************************************/
void Key_Scan()
{
  if(QuadKey1==0)
  {
    delay_ms(10);
    if(QuadKey1==0)
    {
      while(QuadKey1==0);
      Page_Number++;
      if(Page_Number>12) Page_Number=0;
      LCD_CLS();
    }
  }

  if(QuadKey2==0)
  {
    delay_ms(10);
    if(QuadKey2==0)
    {
      while(QuadKey2==0);
      Page_Number--;
      if(Page_Number<0) Page_Number=12;
      LCD_CLS();
    }
  }
}

/***************************************************
函数名: void QuadShow()
说明:	显示屏切换翻页
入口:	无
出口:	无
备注:	在主函数While(1)里面，利用中断空隙时间一直运行
****************************************************/
void QuadShow()
{
 uint16_t i=0;
 if(Page_Number==0)
 {
 LCD_clear_L(0,0); write_6_8_number(0,0,GPS_Sate_Num);

 write_6_8_number(40,0,Gyro_Length);
 write_6_8_number(80,0,HC_SR04_Distance);
 LCD_clear_L(0,1);write_6_8_number(0,1,Yaw);write_6_8_number(80,1,Mag_Yaw);
 LCD_clear_L(0,2);write_6_8_number(0,2,Pitch);write_6_8_number(0,2,Pitch);write_6_8_number(60,2,Pitch_Gyro);
 LCD_clear_L(0,3);write_6_8_number(0,3,Roll);write_6_8_number(60,3,Roll_Gyro);
 LCD_clear_L(0,4);write_6_8_number(0,4,SPL06_001_Filter_P );write_6_8_number(80,4,SPL06_001_Offset);
 LCD_clear_L(0,5);write_6_8_number(0,5,Gyro_Delta_Length);write_6_8_number(50,5,SPL06_001_Filter_high);
 LCD_clear_L(0,6);write_6_8_number(0,6,Time4_Delta.Time_Delta);
 write_6_8_number(50,6,NamelessQuad.Position[_YAW]);

  LCD_clear_L(0,7);
 write_6_8_number(0,7,NamelessQuad.Speed[_YAW]);
 write_6_8_number(40,7,Origion_NamelessQuad.Acceleration[_YAW]);

 }
 else  if(Page_Number==1)
 {
 LCD_clear_L(0,0);  LCD_P6x8Str(0,0,"A_Scale    A_Off:");
 LCD_clear_L(0,1);  LCD_P6x8Str(0,1,"X:");write_6_8_number(20,1,K[0]);write_6_8_number(80,1,B[0]);
 LCD_clear_L(0,2);  LCD_P6x8Str(0,2,"Y:");write_6_8_number(20,2,K[1]);write_6_8_number(80,2,B[1]);
 LCD_clear_L(0,3);  LCD_P6x8Str(0,3,"Z:");write_6_8_number(20,3,K[2]);write_6_8_number(80,3,B[2]);
 LCD_clear_L(0,4);  LCD_P6x8Str(0,4,"Mag  Offset:");
 LCD_clear_L(0,5);  LCD_P6x8Str(0,5,"X:");write_6_8_number(20,5,Mag_Offset[0]);
 LCD_clear_L(0,6);  LCD_P6x8Str(0,6,"Y:");write_6_8_number(20,6,Mag_Offset[1]);
 LCD_clear_L(0,7);  LCD_P6x8Str(0,7,"Z:");write_6_8_number(20,7,Mag_Offset[2]);
 }
  else  if(Page_Number==2)
 {
  LCD_clear_L(0,0);
  LCD_P6x8Str(0,0,"QuadData:");
  write_6_8_number(55,0,QuadData[0]);
  write_6_8_number(90,0,QuadData[1]);
  LCD_clear_L(0,1);
  LCD_P6x8Str(0,1,"SWH1-2:");
  write_6_8_number(45,1,QuadRemoteFlag[0]);
  write_6_8_number(80,1,QuadRemoteFlag[1]);
  LCD_clear_L(0,2);
  LCD_P6x8Str(0,2,"SWH3-4:");
  write_6_8_number(45,2,QuadRemoteFlag[2]);
  write_6_8_number(80,2,QuadRemoteFlag[3]);
  LCD_clear_L(0,3);
  LCD_P6x8Str(0,3,"Thr");
  write_6_8_number(30,3,Throttle_Control);
  write_6_8_number(80,3,Throttle_Rate);
  LCD_clear_L(0,4);
  LCD_P6x8Str(0,4,"Pit");
  write_6_8_number(30,4,Pitch_Control);
  write_6_8_number(80,4,Total_Controler.High_Speed_Control.Expect);
  LCD_clear_L(0,5);
  LCD_P6x8Str(0,5,"Rol");
  write_6_8_number(30,5,Roll_Control);


  LCD_clear_L(0,6);
  LCD_P6x8Str(0,6,"Yaw");
  write_6_8_number(30,6,Yaw_Control);
  if(Controler_High_Mode==1)        LCD_P6x8Str(80,6,"Self_B");
  else if(Controler_High_Mode==2)   LCD_P6x8Str(80,6,"High_H");
  else if(Controler_High_Mode==3)   LCD_P6x8Str(80,6,"Pos_H");

  LCD_clear_L(0,7);
  write_6_8_number(0,7,Total_Controler.Yaw_Angle_Control.Expect);
  write_6_8_number(55,7,Yaw);
  write_6_8_number(85,7,Total_Controler.Yaw_Gyro_Control.Expect);

 }
 else if(Page_Number==3)
 {
 LCD_clear_L(0,0);
 LCD_P6x8Str(0,0,"A_Kp");
 LCD_P6x8Str(45,0,"A_Ki");
 LCD_P6x8Str(80,0,"A_Kd");
 LCD_clear_L(0,1);
 write_6_8_number(0 ,1,Total_Controler.Pitch_Angle_Control.Kp);
 write_6_8_number(45,1,Total_Controler.Pitch_Angle_Control.Ki);
 write_6_8_number(80,1,Total_Controler.Pitch_Angle_Control.Kd);
 LCD_clear_L(0,2);
 LCD_P6x8Str(0,2,"W_Kp");
 LCD_P6x8Str(45,2,"W_Ki");
 LCD_P6x8Str(80,2,"W_Kd");
 LCD_clear_L(0,3);
 write_6_8_number(0,3,Total_Controler.Pitch_Gyro_Control.Kp);
 write_6_8_number(45,3,Total_Controler.Pitch_Gyro_Control.Ki);
 write_6_8_number(80,3,Total_Controler.Pitch_Gyro_Control.Kd);

 LCD_clear_L(0,4);
 LCD_P6x8Str(0,4,"A_Kp");
 LCD_P6x8Str(45,4,"A_Ki");
 LCD_P6x8Str(80,4,"A_Kd");
 LCD_clear_L(0,5);
 write_6_8_number(0 ,5,Total_Controler.Yaw_Angle_Control.Kp);
 write_6_8_number(45,5,Total_Controler.Yaw_Angle_Control.Ki);
 write_6_8_number(80,5,Total_Controler.Yaw_Angle_Control.Kd);
 LCD_clear_L(0,6);
 LCD_P6x8Str(0,6,"W_Kp");
 LCD_P6x8Str(45,6,"W_Ki");
 LCD_P6x8Str(80,6,"W_Kd");
 LCD_clear_L(0,7);
 write_6_8_number(0,7,Total_Controler.Yaw_Gyro_Control.Kp);
 write_6_8_number(45,7,Total_Controler.Yaw_Gyro_Control.Ki);
 write_6_8_number(80,7,Total_Controler.Yaw_Gyro_Control.Kd);
 }
 else if(Page_Number==4)
 {
 LCD_clear_L(0,0);
 LCD_P6x8Str(10,0,"GPS_Date"); write_6_8_number(80,0,GPS_Time_Delta.Time_Delta);
 LCD_clear_L(0,1);
 LCD_P6x8Str(0,1,"Lo_deg:");
 write_6_8_number(50,1,Longitude_Deg);
 LCD_clear_L(0,2);
 LCD_P6x8Str(0,2,"d/100w:");
 write_6_8_number(50,2,Longitude_Min);

 LCD_clear_L(0,3);
 LCD_P6x8Str(0,3,"La_deg:");
 write_6_8_number(50,3,Latitude_Deg);
 LCD_clear_L(0,4);
 LCD_P6x8Str(0,4,"d/100w:");
 write_6_8_number(50,4,Latitude_Min);

 LCD_clear_L(0,5);
 if(GPS_Fix_Flag[0]==0x01)
   LCD_P6x8Str(0,5,"fix");
 else LCD_P6x8Str(0,5,"nof");

 if(GPS_FixType==0x03)
   LCD_P6x8Str(25,5,"3D");
 else if(GPS_FixType==0x02)
   LCD_P6x8Str(25,5,"2D");
 else LCD_P6x8Str(25,5,"0D");
 write_6_8_number(42,5,GPS_Sate_Num);
 write_6_8_number(60,5,TimeBeijing[0]);
 LCD_P6x8Str(75,5,":");
 write_6_8_number(84,5,TimeBeijing[1]);
 LCD_P6x8Str(100,5,":");
 write_6_8_number(105,5,TimeBeijing[2]);
 LCD_clear_L(0,6);
 LCD_P6x8Str(0,6,"V:");
 write_6_8_number(10,6,GPS_Vel.N);
 write_6_8_number(65,6,GPS_Vel.E);
 LCD_clear_L(0,7);
 write_6_8_number(0,7,GPS_Vel.U);
 write_6_8_number(80,7,GPS_Quality);
 }
  else if(Page_Number==5)
 {
 LCD_clear_L(0,0);
 LCD_P6x8Str(25,0,"SINS");
 LCD_clear_L(0,1);  LCD_P6x8Str(0,1,"z_ag:");  write_6_8_number(50,1,Z_g_av); write_6_8_number(90,1,Yaw);
 LCD_clear_L(0,2);  LCD_P6x8Str(0,2,"y_ag:");  write_6_8_number(50,2,Y_g_av); write_6_8_number(90,2,Roll);
 LCD_clear_L(0,3);  LCD_P6x8Str(0,3,"x_ag:");  write_6_8_number(50,3,X_g_av); write_6_8_number(90,3,Pitch);
 LCD_clear_L(0,4);  LCD_P6x8Str(0,4,"z_acce:");  write_6_8_number(50,4,NamelessQuad.Acceleration[_YAW]);
 LCD_clear_L(0,5);  LCD_P6x8Str(0,5,"z_Speed:");  write_6_8_number(50,5,NamelessQuad.Speed[_YAW]);
 LCD_clear_L(0,6);  LCD_P6x8Str(0,6,"z_High:");  write_6_8_number(50,6,NamelessQuad.Position[_YAW]);
 LCD_clear_L(0,7);  LCD_P6x8Str(0,7,"z_H:");  write_6_8_number(50,7,AirPresure_Altitude);write_6_8_number(90,7,HC_SR04_Distance);
 }
  else if(Page_Number==6)
 {
 LCD_clear_L(0,0);
 LCD_P6x8Str(0,0,"Thr");
 write_6_8_number(30,0,Throttle_Control);    write_6_8_number(80,0,High_Hold_Throttle);

 LCD_clear_L(0,2);
 LCD_P6x8Str(0,2,"Contr_MODE");
 if(Controler_High_Mode==1)        LCD_P6x8Str(80,2,"Self_B");
 else if(Controler_High_Mode==2)   LCD_P6x8Str(80,2,"High_H");
 else if(Controler_High_Mode==3)   LCD_P6x8Str(80,2,"Pos_H");
 LCD_clear_L(0,4);
 LCD_P6x8Str(0,4,"H_Kp");  LCD_P6x8Str(45,4,"H_Ki");  LCD_P6x8Str(80,4,"H_Kd");
 LCD_clear_L(0,5);
 write_6_8_number(0 ,5,Total_Controler.High_Position_Control.Kp);
 write_6_8_number(45,5,Total_Controler.High_Position_Control.Ki);
 write_6_8_number(80,5,Total_Controler.High_Position_Control.Kd);

 LCD_clear_L(0,6);
 LCD_P6x8Str(0,6,"S_Kp");  LCD_P6x8Str(45,6,"S_Ki");  LCD_P6x8Str(80,6,"S_Kd");

 LCD_clear_L(0,7);
 write_6_8_number(0,7,Total_Controler.High_Speed_Control.Kp);
 write_6_8_number(45,7,Total_Controler.High_Speed_Control.Ki);
 write_6_8_number(80,7,Total_Controler.High_Speed_Control.Kd);
 }
 else if(Page_Number==7)
 {
 LCD_clear_L(0,1);
 write_6_8_number(0,1,NamelessQuad.Acceleration[_PITCH]);
 write_6_8_number(65,1,NamelessQuad.Acceleration[_ROLL]);
 LCD_clear_L(0,2);
 write_6_8_number(0,2,NamelessQuad.Speed[_PITCH]);
 write_6_8_number(65,2,NamelessQuad.Speed[_ROLL]);
 LCD_clear_L(0,3);
 write_6_8_number(0,3,NamelessQuad.Position[_PITCH]);
 write_6_8_number(65,3,NamelessQuad.Position[_ROLL]);

 LCD_clear_L(0,4);
 write_6_8_number(0,4,NamelessQuad.Acceleration[_PITCH]);
 write_6_8_number(65,4,NamelessQuad.Acceleration[_ROLL]);

 LCD_clear_L(0,5);
 write_6_8_number(0,5,NamelessQuad.Acceleration[_YAW]);
 write_6_8_number(65,5,Pitch);
 LCD_clear_L(0,6);
 write_6_8_number(0,6,NamelessQuad.Speed[_YAW]);
 write_6_8_number(65,6,Roll);
 }
  else if(Page_Number==8)
 {
 LCD_clear_L(0,0);
 LCD_P6x8Str(0,0,"S_P:");
 write_6_8_number(30,0,Body_Frame_To_XYZ[_PITCH]);

 LCD_clear_L(0,1);
 LCD_P6x8Str(0,1,"S_R");
 write_6_8_number(30,1,Body_Frame_To_XYZ[_ROLL]);

 LCD_clear_L(0,2);
 write_6_8_number(0,2,GPS_Ground_Speed);
 write_6_8_number(65,2,GPS_Yaw);


 LCD_clear_L(0,3);
 LCD_P6x8Str(0,3,"G_V");
 write_6_8_number(0,3,GPS_Speed_Resolve[0]);
 write_6_8_number(65,3,GPS_Speed_Resolve[1]);

 LCD_clear_L(0,4);
 LCD_P6x8Str(0,4,"sate_N:");
 write_6_8_number(65,4,GPS_Sate_Num);

 LCD_clear_L(0,5);
 LCD_P6x8Str(0,5,"GPS_Q:");
 write_6_8_number(45,5,GPS_Quality);
 }
  else if(Page_Number==9)
 {
 LCD_clear_L(0,0);
 LCD_P6x8Str(0,0,"A_E:");
 write_6_8_number(30,0,Total_Controler.Pitch_Angle_Control.Expect);
 write_6_8_number(30,1,Total_Controler.Roll_Angle_Control.Expect);

 LCD_clear_L(0,2);
 LCD_P6x8Str(0,2,"S_O:");
 write_6_8_number(30,2,Total_Controler.Latitude_Speed_Control.Control_OutPut);
 write_6_8_number(30,3,Total_Controler.Longitude_Speed_Control.Control_OutPut);

 LCD_clear_L(0,4);
 LCD_P6x8Str(0,4,"S_E:");
 write_6_8_number(30,4,Total_Controler.Latitude_Speed_Control.Expect);
 write_6_8_number(30,5,Total_Controler.Longitude_Speed_Control.Expect);

 LCD_clear_L(0,6);
 LCD_P6x8Str(0,6,"S_F:");
 write_6_8_number(30,6,Total_Controler.Latitude_Speed_Control.FeedBack);
 write_6_8_number(30,7,Total_Controler.Longitude_Speed_Control.FeedBack);
 }
   else if(Page_Number==10)//加速度矫正显示页
 {
 LCD_clear_L(0,0);
 LCD_P6x8Str(10,0,"Accel_Correct");
 write_6_8_number(105,0,flight_direction);
 LCD_clear_L(0,1);
 write_6_8_number(0,1,acce_sample[0].x);
 write_6_8_number(40,1,acce_sample[0].y);
 write_6_8_number(70,1,acce_sample[0].z);
 LCD_clear_L(0,2);
 write_6_8_number(0,2,acce_sample[1].x);
 write_6_8_number(40,2,acce_sample[1].y);
 write_6_8_number(70,2,acce_sample[1].z);
 LCD_clear_L(0,3);
 write_6_8_number(0,3,acce_sample[2].x);
 write_6_8_number(40,3,acce_sample[2].y);
 write_6_8_number(70,3,acce_sample[2].z);
 LCD_clear_L(0,4);
 write_6_8_number(0,4,acce_sample[3].x);
 write_6_8_number(40,4,acce_sample[3].y);
 write_6_8_number(70,4,acce_sample[3].z);
 LCD_clear_L(0,5);
 write_6_8_number(0,5,acce_sample[4].x);
 write_6_8_number(40,5,acce_sample[4].y);
 write_6_8_number(70,5,acce_sample[4].z);
 LCD_clear_L(0,6);
 write_6_8_number(0,6,acce_sample[5].x);
 write_6_8_number(40,6,acce_sample[5].y);
 write_6_8_number(70,6,acce_sample[5].z);
 }
 else if(Page_Number==11)//磁力计矫正显示页
 {
 LCD_clear_L(0,0);
 LCD_P6x8Str(10,0,"Mag_Correct");
 write_6_8_number(105,0,Mag_Calibration_Mode);
 LCD_clear_L(0,1);
 write_6_8_number(0,1,Mag_Offset_Read.x);
 write_6_8_number(40,1,Mag_Offset_Read.y);
 write_6_8_number(70,1,Mag_Offset_Read.z);
 LCD_clear_L(0,2);
 write_6_8_number(0,2,Mag.x_min);
 write_6_8_number(40,2,Mag.x_max);
 write_6_8_number(70,2,Mag.x_offset);
 LCD_clear_L(0,3);
 write_6_8_number(0,2,Mag.y_min);
 write_6_8_number(40,2,Mag.y_max);
 write_6_8_number(70,2,Mag.y_offset);
 LCD_clear_L(0,4);
 write_6_8_number(0,2,Mag.z_min);
 write_6_8_number(40,2,Mag.z_max);
 write_6_8_number(70,2,Mag.z_offset);

 LCD_clear_L(0,3);
 LCD_P6x8Str(0,3,"0 To 360");
 write_6_8_number(70,3,Yaw);
 LCD_clear_L(0,4);
 LCD_P6x8Str(0,4,"Mag Is Okay?");
 write_6_8_number(80,4,Mag_Is_Okay_Flag[0]);
 write_6_8_number(110,4,Mag_Is_Okay_Flag[1]);

 LCD_clear_L(0,5);
 for(i=0;i<12;i++)
 {
   write_6_8_number(10*i,5,Mag_360_Flag[0][i]);
 }
 LCD_clear_L(0,6);
 for(i=0;i<12;i++)
 {
   write_6_8_number(10*i,6,Mag_360_Flag[1][i]);
 }
 LCD_clear_L(0,7);
 if(Mag_Calibration_Mode==0) LCD_P6x8Str(0,7,"Make Z+ Upside Sky");
 else if(Mag_Calibration_Mode==1) LCD_P6x8Str(0,7,"Make Y+ Upside Sky");
 else if(Mag_Calibration_Mode==2) LCD_P6x8Str(0,7,"Start With Yaw Move");
 }
 else if(Page_Number==12)//加速度矫正显示页
 {
 LCD_clear_L(0,0);
 LCD_P6x8Str(10,0,"Mag");
 LCD_clear_L(0,1);
 write_6_8_number(0,1,Mag_IST8310.Mag_Data_Correct[0]);
 write_6_8_number(40,1,Mag_IST8310.Mag_Data_Correct[1]);
 write_6_8_number(70,1,Mag_IST8310.Mag_Data_Correct[2]);
 LCD_clear_L(0,2);
 write_6_8_number(0,2,imu.accelRaw[0]);
 write_6_8_number(40,2,imu.accelRaw[1]);
 write_6_8_number(70,2,imu.accelRaw[2]);
 LCD_clear_L(0,3);
 write_6_8_number(0,3,X_w_av);
 write_6_8_number(40,3,Y_w_av);
 write_6_8_number(70,3,Z_w_av);
 LCD_clear_L(0,4);
 write_6_8_number(0,4,SPL06_001_Filter_P);
 write_6_8_number(70,4,SPL06_001_Filter_high);
 }
}
