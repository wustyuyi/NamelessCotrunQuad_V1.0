#include "Headfile.h"
#include "GPS.h"
#include "USART.h"
#include <math.h>
#include <string.h>
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
double Last_Longitude=0,Last_Latitude=0;
int32_t Longitude_Origion=0,Latitude_Origion=0;//PVT解析出来的原始经纬度，相当于正常deg*10^7
double Longitude,Latitude;
double Longitude_Deg,Latitude_Deg,Longitude_Min,Latitude_Min;
float GPS_Ground_Speed=0;//对地速度
float GPS_Yaw=0;//运动航向
float GPS_Quality=0;//定位质量
uint16 GPS_Sate_Num=0;//参与定位卫星数
float GPS_Speed_Resolve[2]={0,0};//GPS观测速度
u16 TimeBeijing[3];//北京时间
char TimeStr[8];
Vector3_Nav GPS_Vel={0};//NED向速度
float GPS_Pos_DOP=0;//定位精度因子//定位类型
uint8 GPS_FixType=0;//定位类型
uint8 GPS_Fix_Flag[4]={0};//定位标志
int16 Horizontal_Acc_Est=0;//水平位置精度
int16 Vertical_Acc_Est=0;//竖直位置精度
int16 Speed_Acc_Est=0;//竖直位置精度
float High_GPS=0;//海拔高度
void GPS_PVT_Parse(void)
{
  Last_Longitude=Longitude;
  Last_Latitude=Latitude;
  //北京时间
  TimeBeijing[0]=Ublox_Data[9]+8;//时
  TimeBeijing[1]=Ublox_Data[10];//分
  TimeBeijing[2]=Ublox_Data[11];//秒

  GPS_FixType=Ublox_Data[21];//定位类型

  GPS_Fix_Flag[0]=Ublox_Data[23]&0x01;//是否有效定位
  GPS_Fix_Flag[1]=(Ublox_Data[23]&0x02)>>1;//差分模式是否开启(DGPS)
  GPS_Fix_Flag[2]=(Ublox_Data[23]&0x3A)>>2;//省电模式、未用
  GPS_Fix_Flag[3]=Ublox_Data[23]&0x20;//航向是否有效

  GPS_Sate_Num=Ublox_Data[24];//参与定位卫星个数

  Longitude_Origion=Ublox_Data[25]//经度*10^7
             +(Ublox_Data[26]<<8)
              +(Ublox_Data[27]<<16)
               +(Ublox_Data[28]<<24);
  Longitude=Longitude_Origion*0.0000001f;//deg


  Latitude_Origion=Ublox_Data[29]//纬度*10^7
             +(Ublox_Data[30]<<8)
              +(Ublox_Data[31]<<16)
               +(Ublox_Data[32]<<24);
  Latitude=Latitude_Origion*0.0000001f;//deg


  Longitude_Deg=(int)(Longitude);//经纬度处理，用于OLED显示
  Longitude_Min=((int)((Longitude-Longitude_Deg)*10000000));
  Latitude_Deg=(int)(Latitude);
  Latitude_Min=((int)((Latitude-Latitude_Deg)*10000000));


  High_GPS=Ublox_Data[37]//GPS获取海拔高度
             +(Ublox_Data[38]<<8)
              +(Ublox_Data[39]<<16)
               +(Ublox_Data[40]<<24);
  High_GPS/=1000;//m


  Horizontal_Acc_Est=Ublox_Data[41]//水平位置估计精度
             +(Ublox_Data[42]<<8)
              +(Ublox_Data[43]<<16)
               +(Ublox_Data[44]<<24);;
  Horizontal_Acc_Est*=0.01;//m


  Vertical_Acc_Est=Ublox_Data[45]//垂直位置估计精度
             +(Ublox_Data[46]<<8)
              +(Ublox_Data[47]<<16)
               +(Ublox_Data[48]<<24);;
  Vertical_Acc_Est*=0.01;//m


  GPS_Vel.N=Ublox_Data[49]//GPS获取的沿导航系正北速度
             +(Ublox_Data[50]<<8)
              +(Ublox_Data[51]<<16)
               +(Ublox_Data[52]<<24);
  GPS_Vel.N/=10;//cm/s  N


  GPS_Vel.E=Ublox_Data[53]//GPS获取的沿导航系正东向速度
             +(Ublox_Data[54]<<8)
              +(Ublox_Data[55]<<16)
               +(Ublox_Data[56]<<24);//mm/s
  GPS_Vel.E/=10;//cm/s  E


  GPS_Vel.U=Ublox_Data[57]//GPS获取的沿导航系 '天' 向速度
             +(Ublox_Data[58]<<8)
              +(Ublox_Data[59]<<16)
               +(Ublox_Data[60]<<24);
  GPS_Vel.U/=(-10);//cm/s  D

  GPS_Speed_Resolve[0]=GPS_Vel.N;//Y  Axis
  GPS_Speed_Resolve[1]=GPS_Vel.E;//X  Axis


  GPS_Ground_Speed=Ublox_Data[61]//载体对地速度
             +(Ublox_Data[62]<<8)
              +(Ublox_Data[63]<<16)
               +(Ublox_Data[64]<<24);
  GPS_Ground_Speed/=10;//cm/s


  GPS_Yaw=Ublox_Data[65]//载体运动航向角
             +(Ublox_Data[66]<<8)
              +(Ublox_Data[67]<<16)
               +(Ublox_Data[68]<<24);
  GPS_Yaw*=0.00001;//deg

  Speed_Acc_Est=Ublox_Data[69]//速度估计精度
             +(Ublox_Data[70]<<8)
              +(Ublox_Data[71]<<16)
               +(Ublox_Data[72]<<24);
  Speed_Acc_Est*=0.1;//cm/s


  GPS_Pos_DOP=Ublox_Data[77]
             +(Ublox_Data[78]<<8);
  GPS_Pos_DOP*=0.01;
  GPS_Quality=GPS_Pos_DOP;//位置精度因子
}

