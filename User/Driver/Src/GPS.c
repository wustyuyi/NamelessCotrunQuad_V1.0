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
#include "GPS.h"
#include "USART.h"
#include <math.h>
#include <string.h>
double Last_Longitude=0,Last_Latitude=0;
int32_t Longitude_Origion=0,Latitude_Origion=0,Altitude_Origion=0;//PVT解析出来的原始经纬度，相当于正常deg*10^7
double Longitude,Latitude;
double Longitude_Deg,Latitude_Deg,Longitude_Min,Latitude_Min;
float GPS_Ground_Speed=0;//对地速度
float GPS_Yaw=0;//运动航向
float GPS_Quality=0;//定位质量
uint16 GPS_Sate_Num=0,Last_GPS_Sate_Num=0;//参与定位卫星数
float GPS_Speed_Resolve[2]={0,0};//GPS观测速度
u16 TimeBeijing[3];//北京时间
char TimeStr[8];
Vector3_Nav Last_GPS_Vel={0};//NED向速度
Vector3_Nav GPS_Vel={0};//NED向速度
Vector3_Nav GPS_Vel_Div={0};//GPS输出NED向速度微分（加速度）
float GPS_Pos_DOP=0;//定位精度因子//定位类型
uint8 GPS_FixType=0;//定位类型
uint8 GPS_Fix_Flag[4]={0};//定位标志
float Horizontal_Acc_Est=0;//水平位置精度
int16 Vertical_Acc_Est=0;//竖直位置精度
int16 Speed_Acc_Est=0;//竖直位置精度
float High_GPS=0;//海拔高度
Testime GPS_PVT_Parse_Time_Delta;
void GPS_PVT_Parse(void)
{
  Test_Period(&GPS_PVT_Parse_Time_Delta);//GPS数据解析周期测试
  Last_Longitude=Longitude;
  Last_Latitude=Latitude;
  
  Last_GPS_Vel.E=GPS_Vel.E;
  Last_GPS_Vel.N=GPS_Vel.N;
  Last_GPS_Vel.U=GPS_Vel.U;
  //北京时间
  TimeBeijing[0]=Ublox_Data[9]+8;//时
  TimeBeijing[1]=Ublox_Data[10];//分
  TimeBeijing[2]=Ublox_Data[11];//秒
  
  GPS_FixType=Ublox_Data[21];//定位类型
  
  GPS_Fix_Flag[0]=Ublox_Data[22]&0x01;//是否有效定位
  GPS_Fix_Flag[1]=(Ublox_Data[22]&0x02)>>1;//差分模式是否开启(DGPS)
  GPS_Fix_Flag[2]=(Ublox_Data[22]&0x3A)>>2;//省电模式、未用
  GPS_Fix_Flag[3]=Ublox_Data[22]&0x20;//航向是否有效
  Last_GPS_Sate_Num=GPS_Sate_Num;
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
  
  
  High_GPS=Ublox_Data[35]//GPS获取海拔高度
    +(Ublox_Data[36]<<8)
      +(Ublox_Data[37]<<16)
        +(Ublox_Data[38]<<24);  
  Altitude_Origion=High_GPS;
  High_GPS/=1000;//m
  Altitude_Origion=High_GPS;
  
  
  
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
        Horizontal_Acc_Est*=0.001f;//m
        
        
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
	
	
	GPS_Vel_Div.E=1000*(GPS_Vel.E-Last_GPS_Vel.E)/(GPS_PVT_Parse_Time_Delta.Time_Delta);//单位cm/s^2
	GPS_Vel_Div.N=1000*(GPS_Vel.N-Last_GPS_Vel.N)/(GPS_PVT_Parse_Time_Delta.Time_Delta);//单位cm/s^2
	GPS_Vel_Div.U=1000*(GPS_Vel.U-Last_GPS_Vel.U)/(GPS_PVT_Parse_Time_Delta.Time_Delta);//单位cm/s^2
}


const uint8_t NEMA_Disable_Header[6]={0xB5,0x62,0x06,0x01,0x03,0x00};//
const uint8_t NEMA_Disable_Buf[20][5]={
  0xF0,0x0A,0x00,0x04,0x23,
  0xF0,0x09,0x00,0x03,0x21,
  0xF0,0x00,0x00,0xFA,0x0F,
  0xF0,0x01,0x00,0xFB,0x11,
  0xF0,0x0D,0x00,0x07,0x29,
  0xF0,0x06,0x00,0x00,0x1B,
  0xF0,0x02,0x00,0xFC,0x13,
  0xF0,0x07,0x00,0x01,0x1D,
  0xF0,0x03,0x00,0xFD,0x15,
  0xF0,0x04,0x00,0xFE,0x17,
  0xF0,0x0E,0x00,0x08,0x2B,
  0xF0,0x0F,0x00,0x09,0x2D,
  0xF0,0x05,0x00,0xFF,0x19,
  0xF0,0x08,0x00,0x02,0x1F,//7
  0xF1,0x00,0x00,0xFB,0x12,
  0xF1,0x01,0x00,0xFC,0x14,
  0xF1,0x03,0x00,0xFE,0x18,
  0xF1,0x04,0x00,0xFF,0x1A,
  0xF1,0x05,0x00,0x00,0x1C,
  0xF1,0x06,0x00,0x01,0x1E,
};
const uint8_t Ublox_Disable_Header[6]={0xB5,0x62,0x06,0x01,0x03,0x00};//
const uint8_t Ublox_Disable_Buf[61][5]={
  0x0B ,0x30 ,0x00 ,0x45 ,0xC0,
  0x0B ,0x50 ,0x00 ,0x65 ,0x00,
  0x0B ,0x33 ,0x00 ,0x48 ,0xC6,
  0x0B ,0x31 ,0x00 ,0x46 ,0xC2,
  0x0B ,0x00 ,0x00 ,0x15 ,0x60,
  0x10 ,0x02 ,0x00 ,0x1C ,0x73,
  0x10 ,0x02 ,0x00 ,0x1C ,0x73,
  0x10 ,0x02 ,0x00 ,0x1C ,0x73,
  0x10 ,0x10 ,0x00 ,0x2A ,0x8F,
  0x21 ,0x0E ,0x00 ,0x39 ,0xBE,
  0x21 ,0x08 ,0x00 ,0x33 ,0xB2,
  0x21 ,0x09 ,0x00 ,0x34 ,0xB4,
  0x21 ,0x0B ,0x00 ,0x36 ,0xB8,
  0x21 ,0x0F ,0x00 ,0x3A ,0xC0,
  0x21 ,0x0D ,0x00 ,0x38 ,0xBC,
  0x0A ,0x05 ,0x00 ,0x19 ,0x67,
  0x0A ,0x09 ,0x00 ,0x1D ,0x6F,
  0x0A ,0x0B ,0x00 ,0x1F ,0x73,
  0x0A ,0x02 ,0x00 ,0x16 ,0x61,
  0x0A ,0x06 ,0x00 ,0x1A ,0x69,
  0x0A ,0x07 ,0x00 ,0x1B ,0x6B,
  0x0A ,0x21 ,0x00 ,0x35 ,0x9F,
  0x0A ,0x2E ,0x00 ,0x42 ,0xB9,
  0x0A ,0x08 ,0x00 ,0x1C ,0x6D,
  0x01 ,0x60 ,0x00 ,0x6B ,0x02,
  0x01 ,0x22 ,0x00 ,0x2D ,0x86,
  0x01 ,0x31 ,0x00 ,0x3C ,0xA4,
  0x01 ,0x04 ,0x00 ,0x0F ,0x4A,
  0x01 ,0x40 ,0x00 ,0x4B ,0xC2,
  0x01 ,0x61 ,0x00 ,0x6C ,0x04,
  0x01 ,0x09 ,0x00 ,0x14 ,0x54,
  0x01 ,0x34 ,0x00 ,0x3F ,0xAA,
  0x01 ,0x01 ,0x00 ,0x0C ,0x44,
  0x01 ,0x02 ,0x00 ,0x0D ,0x46,
  0x01 ,0x07 ,0x00 ,0x12 ,0x50,
  0x01 ,0x35 ,0x00 ,0x40 ,0xAC,
  0x01 ,0x32 ,0x00 ,0x3D ,0xA6,
  0x01 ,0x06 ,0x00 ,0x11 ,0x4E,
  0x01 ,0x03 ,0x00 ,0x0E ,0x48,
  0x01 ,0x30 ,0x00 ,0x3B ,0xA2,
  0x01 ,0x24 ,0x00 ,0x2F ,0x8A,
  0x01 ,0x23 ,0x00 ,0x2E ,0x88,
  0x01 ,0x20 ,0x00 ,0x2B ,0x82,
  0x01 ,0x21 ,0x00 ,0x2C ,0x84,
  0x01 ,0x11 ,0x00 ,0x1C ,0x64,
  0x01 ,0x12 ,0x00 ,0x1D ,0x66,
  0x02 ,0x30 ,0x00 ,0x3C ,0xA5,
  0x02 ,0x31 ,0x00 ,0x3D ,0xA7,
  0x02 ,0x10 ,0x00 ,0x1C ,0x65,
  0x02 ,0x15 ,0x00 ,0x21 ,0x6F,
  0x02 ,0x11 ,0x00 ,0x1D ,0x67,
  0x02 ,0x13 ,0x00 ,0x1F ,0x6B,
  0x02 ,0x20 ,0x00 ,0x2C ,0x85,
  0x0D ,0x11 ,0x00 ,0x28 ,0x88,
  0x0D ,0x16 ,0x00 ,0x2D ,0x92,
  0x0D ,0x13 ,0x00 ,0x2A ,0x8C,
  0x0D ,0x04 ,0x00 ,0x1B ,0x6E,
  0x0D ,0x03 ,0x00 ,0x1A ,0x6C,
  0x0D ,0x12 ,0x00 ,0x29 ,0x8A,
  0x0D ,0x01 ,0x00 ,0x18 ,0x68,
  0x0D ,0x06 ,0x00 ,0x1D ,0x72
};

const uint8_t PVT_Enable_Buf[11]={0xB5,0x62,0x06,0x01,0x03,0x00,0x01,0x07,0x01,0x13,0x51};

//const uint8_t Output_Rate_10hz_2[14]={0xB5,0x62,0x06,0x08,0x06,0x00,0x64,0x00,0x01,0x00,0x00,0x00,0x79,0x10};
const uint8_t Output_Rate_10hz_2[14]={0xB5,0x62,0x06,0x08,0x06,0x00,0x64,0x00,0x01,0x00,0x01,0x00,0x7A,0x12};
const uint8_t Output_Rate_10hz_1[8]={0xB5,0x62,0x06,0x08,0x00,0x00,0x0E,0x30};


//38400
//B5 62 06 00 14 00 01 00 00 00 D0 08 00 00 00 96 00 00 01 00 01 00 00 00 00 00 8B 54
//B5 62 06 00 01 00 01 08 22
const uint8_t Output_Baud_38400_2[28]={0xB5 ,0x62 ,0x06 ,0x00 ,0x14 ,0x00 ,0x01 ,0x00 ,0x00 ,
0x00 ,0xD0 ,0x08 ,0x00 ,0x00 ,0x00 ,0x96 ,0x00 ,0x00 ,
0x01 ,0x00 ,0x01 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x8B ,0x54};
const uint8_t Output_Baud_38400_1[9]={0xB5 ,0x62 ,0x06 ,0x00 ,0x01 ,0x00 ,0x01 ,0x08 ,0x22};
//115200
//B5 62 06 00 14 00 01 00 00 00 D0 08 00 00 00 C2 01 00 01 00 01 00 00 00 00 00 B8 42
//B5 62 06 00 01 00 01 08 22
const uint8_t Output_Baud_115200_2[28]={0xB5 ,0x62 ,0x06 ,0x00 ,0x14 ,0x00 ,0x01 ,0x00 ,0x00 ,
0x00 ,0xD0 ,0x08 ,0x00 ,0x00 ,0x00 ,0xC2 ,0x01 ,0x00 ,
0x01 ,0x00 ,0x01 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0xB8 ,0x42};
const uint8_t Output_Baud_115200_1[9]={0xB5 ,0x62 ,0x06 ,0x00 ,0x01 ,0x00 ,0x01 ,0x08 ,0x22};
//921600
//B5 62 06 00 14 00 01 00 00 00 D0 08 00 00 00 10 0E 00 01 00 01 00 00 00 00 00 13 1E
//B5 62 06 00 01 00 01 08 22
const uint8_t Output_Baud_921600_2[28]={0xB5 ,0x62 ,0x06 ,0x00 ,0x14 ,0x00 ,0x01 ,0x00 ,0x00 ,
0x00 ,0xD0 ,0x08 ,0x00 ,0x00 ,0x00 ,0x10 ,0x0E ,0x00 ,
0x01 ,0x00 ,0x01 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x13 ,0x1E};
const uint8_t Output_Baud_921600_1[9]={0xB5 ,0x62 ,0x06 ,0x00 ,0x01 ,0x00 ,0x01 ,0x08 ,0x22};



const uint8_t GPS_Save_Config[21]={0xB5,0x62,0x06,0x09,0x0D,0x00,0x00,0x00,0x00,
0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,
0x17,0x31,0xBF};



#define Ublox_Set_By_NamelessCotrunQuad//如果GPS板载FLash，只需要设置一次后注释本行即可
#define Default_Baud_Is_Know  38400//默认波特率已知时，节省初始化轮询时间
const unsigned long NCQ_Prase_Baud=921600;

const unsigned long Baud_Poll[8]={9600,19200,38400,
57600,115200,230400,460800,921600};
void Set_GPS_USART(void)
{
#ifdef  Ublox_Set_By_NamelessCotrunQuad
#ifdef Default_Baud_Is_Know
  Ublox_Set_Output_PVT_10hz_Baud_Set(Default_Baud_Is_Know);//以默认波特率设置一次即可
#else
  for(uint16_t i=0;i<8;i++)
  {
    Ublox_Set_Output_PVT_10hz_Baud_Set(Baud_Poll[i]);//未知波特率轮询设置
  }
#endif
#endif
}


void Ublox_Set_Output_PVT_10hz_Baud_Set(unsigned long Baud)
{
  uint16_t i=0,j=0;
  USART2_Init(Baud);
  for(i=0;i<20;i++)//禁掉所有NEMA输出语句
  {
    for(j=0;j<3;j++)
    {
      USART2_Send((unsigned char *)NEMA_Disable_Header,sizeof(NEMA_Disable_Header));
      USART2_Send((unsigned char *)NEMA_Disable_Buf[i],5);
    }
    //delay_ms(50);
  }
  delay_ms(10);
  for(i=0;i<61;i++)//禁掉所有ublox输出语句
  {
    for(j=0;j<3;j++)
    {
      USART2_Send((unsigned char *)Ublox_Disable_Header,sizeof(Ublox_Disable_Header));
      USART2_Send((unsigned char *)Ublox_Disable_Buf[i],5);
    }
    //delay_ms(10);
  }
  delay_ms(10);
  for(j=0;j<3;j++)
  {
    USART2_Send((unsigned char *)PVT_Enable_Buf,11);//打开PVT
    //delay_ms(5);
  }
  delay_ms(10);
  for(j=0;j<5;j++)
  {
    USART2_Send((unsigned char *)Output_Rate_10hz_2,14);//设置10hz刷新1
    USART2_Send((unsigned char *)Output_Rate_10hz_1,8);//设置10hz刷新2
    //delay_ms(10);
  }
  delay_ms(10);
  if(NCQ_Prase_Baud==921600)
  {
    for(j=0;j<5;j++)
    {
      USART2_Send((unsigned char *)Output_Baud_921600_2,28);
      USART2_Send((unsigned char *)Output_Baud_921600_1,9);
      //delay_ms(10);
    }
  }
  else if(NCQ_Prase_Baud==115200)
  {
    for(j=0;j<5;j++)
    {
      USART2_Send((unsigned char *)Output_Baud_115200_2,28);
      USART2_Send((unsigned char *)Output_Baud_115200_1,9);
      //delay_ms(10);
    }
  }
  else
  {
    for(j=0;j<5;j++)
    {
      USART2_Send((unsigned char *)Output_Baud_38400_2,28);
      USART2_Send((unsigned char *)Output_Baud_38400_1,9);
      //delay_ms(10);
    }
  }
  USART2_Init(NCQ_Prase_Baud);
  delay_ms(10);
  for(j=0;j<5;j++)
  {
    USART2_Send((unsigned char *)GPS_Save_Config,21);
    //delay_ms(10);
  }
}

