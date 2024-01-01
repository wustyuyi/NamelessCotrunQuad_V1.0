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
#include "string.h"
#include "oledfont.h"
#include "oled.h"
#include "stdlib.h"




#define XLevelL  	0x00
#define XLevelH  	0x10
#define XLevel          ((XLevelH&0x0F)*16+XLevelL)
#define Max_Column 	128
#define Max_Row  	64
#define Brightness 	0xCF
#define X_WIDTH 	128
#define Y_WIDTH 	64
#define high 1
#define low 0
#define SCL PCout(3)    //串行时钟
#define SDA PCout(2)    //串行数据

#define READ_SDA   GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)	//SDA 
#define IIC_SDA_H  GPIO_WriteBit(GPIOC,GPIO_Pin_2,Bit_SET)	//SDA 
#define IIC_SDA_L  GPIO_WriteBit(GPIOC,GPIO_Pin_2,Bit_RESET)    //SDA
#define IIC_SCL_H  GPIO_WriteBit(GPIOC,GPIO_Pin_3,Bit_SET)	//SCL
#define IIC_SCL_L  GPIO_WriteBit(GPIOC,GPIO_Pin_3,Bit_RESET)    //SCL



void OLED_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_PinRemapConfig(RCC_APB2Periph_AFIO | GPIO_Remap_SWJ_JTAGDisable , ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOC,&GPIO_InitStructure);
  PCout(2)=1;
  PCout(3)=1;
}

void SDA_OUT(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOC,&GPIO_InitStructure);
}


void SDA_IN(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOC,&GPIO_InitStructure);
}

/***************************
函数名:	void IIC_Start(void)
说明:	产生IIC起始信号
入口:	无
出口:	无
备注:	无
****************************/
void OLED_IIC_Start(void)
{
  SDA_OUT();		// SDA线输出
  IIC_SDA_H;
  IIC_SCL_H;
  //Delay_Us(4);
  IIC_SDA_L;
  //Delay_Us(1);
  IIC_SCL_L;		// 钳住I2C总线,准备发送或接收数据 
}

/***************************
函数名:	void IIC_Stop(void)
说明:	产生IIC停止信号
入口:	无
出口:	无
备注:	无
****************************/
void OLED_IIC_Stop(void)
{
  SDA_OUT();			// SDA线输出
  IIC_SDA_L;
  //Delay_Us(4);
  IIC_SCL_H;
  //Delay_Us(1);
  IIC_SDA_H;			// 发送I2C总线结束信号
  //Delay_Us(5);		// 再次启动需要4.7us
}

/**********************************
函数名:	uint8_t IIC_Wait_Ack(void)
说明:	等待应答信号到来
入口:	无
出口:	uint8_t 1,接收应答失败
0,接收应答成功
备注:	无
**********************************/
uint8_t IIC_Wait_Ack(void)
{
  uint8_t ucErrTime = 0;
  SDA_IN();					// SDA设置为输入  
  IIC_SDA_H;
  //Delay_Us(1);		
  IIC_SCL_H;
  //Delay_Us(1);	 
  while (READ_SDA)			// SDA为高,等待IIC器件拉低
  {
    ucErrTime++;
    if (ucErrTime > 250)	//	40*250=1ms未答复,IIC发出停止信号
    {
      OLED_IIC_Stop();
      return 1;
    }
  }
  IIC_SCL_L;
  return 0;
}

/**************************
函数名:	void IIC_Ack(void)
说明:	产生ACK应答
入口:	无
出口:	无
备注:	无
**************************/
void IIC_Ack(void)
{
  IIC_SCL_L;
  SDA_OUT();
  IIC_SDA_L;
  //Delay_Us(1);
  IIC_SCL_H;
  //Delay_Us(1);
  IIC_SCL_L;
}


/***************************
函数名:	void IIC_NAck(void)
说明:	不产生ACK应答
入口:	无
出口:	无
备注:	无
***************************/
void IIC_NAck(void)
{
  IIC_SCL_L;
  SDA_OUT();
  IIC_SDA_H;
  //Delay_Us(1);
  IIC_SCL_H;
  //Delay_Us(1);
  IIC_SCL_L;
}

/**************************************
函数名:	void IIC_Send_Byte(uint8_t txd)
说明:	IIC发送一个字节
入口:	uint8_t	txd
出口:	无
备注:	无
**************************************/
void Write_IIC_Byte(uint8_t txd)
{
  uint8_t t;
  SDA_OUT();
  IIC_SCL_L;				// 拉低时钟开始数据传输
  for (t = 0; t < 8; t++)
  {
    if ((txd&0x80) >> 7)
    {
      IIC_SDA_H;
    }
    else
    {
      IIC_SDA_L;
    }
    txd <<= 1;
    //Delay_Us(1);
    IIC_SCL_H;
    //Delay_Us(1); 
    IIC_SCL_L;
  }
  IIC_Wait_Ack();
}

/*********************OLED写数据************************************/ 
void OLED_WrDat(unsigned char IIC_Data)
{
  OLED_IIC_Start();
  Write_IIC_Byte(0x78);
  Write_IIC_Byte(0x40);			//write data
  Write_IIC_Byte(IIC_Data);
  OLED_IIC_Stop();
}
/*********************OLED写命令************************************/
void OLED_WrCmd(unsigned char IIC_Command)
{
  OLED_IIC_Start();
  Write_IIC_Byte(0x78);            //Slave address,SA0=0
  Write_IIC_Byte(0x00);			//write command
  Write_IIC_Byte(IIC_Command);
  OLED_IIC_Stop();
}
/*********************OLED 设置坐标************************************/
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
  OLED_WrCmd(0xb0+y);
  OLED_WrCmd(((x&0xf0)>>4)|0x10);
  OLED_WrCmd((x&0x0f)|0x01);
} 
/*********************OLED全屏************************************/
void OLED_Fill(unsigned char bmp_dat) 
{
  unsigned char y,x;
  for(y=0;y<8;y++)
  {
    OLED_WrCmd(0xb0+y);
    OLED_WrCmd(0x01);
    OLED_WrCmd(0x10);
    for(x=0;x<X_WIDTH;x++)
      OLED_WrDat(bmp_dat);
  }
}
/*********************OLED复位************************************/
void OLED_CLS(void)
{
  unsigned char y,x;
  for(y=0;y<8;y++)
  {
    OLED_WrCmd(0xb0+y);
    OLED_WrCmd(0x01);
    OLED_WrCmd(0x10);
    for(x=0;x<X_WIDTH;x++)
      OLED_WrDat(0);
  }
}
/*********************OLED初始化************************************/
void OLED_Init_I2C(void)
{
  delay_ms(100);//初始化之前的延时很重要！
  OLED_WrCmd(0xae);//--turn off oled panel
  OLED_WrCmd(0x00);//---set low column address
  OLED_WrCmd(0x10);//---set high column address
  OLED_WrCmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
  OLED_WrCmd(0x81);//--set contrast control register
  OLED_WrCmd(Brightness); // Set SEG Output Current Brightness
  OLED_WrCmd(0xa0);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
  OLED_WrCmd(0xc0);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
  OLED_WrCmd(0xa6);//--set normal display
  OLED_WrCmd(0xa8);//--set multiplex ratio(1 to 64)
  OLED_WrCmd(0x3f);//--1/64 duty
  OLED_WrCmd(0xd3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
  OLED_WrCmd(0x00);//-not offset
  OLED_WrCmd(0xd5);//--set display clock divide ratio/oscillator frequency
  OLED_WrCmd(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
  OLED_WrCmd(0xd9);//--set pre-charge period
  OLED_WrCmd(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
  OLED_WrCmd(0xda);//--set com pins hardware configuration
  OLED_WrCmd(0x12);
  OLED_WrCmd(0xdb);//--set vcomh
  OLED_WrCmd(0x40);//Set VCOM Deselect Level
  OLED_WrCmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
  OLED_WrCmd(0x02);//
  OLED_WrCmd(0x8d);//--set Charge Pump enable/disable
  OLED_WrCmd(0x14);//--set(0x10) disable
  OLED_WrCmd(0xa4);// Disable Entire Display On (0xa4/0xa5)
  OLED_WrCmd(0xa6);// Disable Inverse Display On (0xa6/a7) 
  OLED_WrCmd(0xaf);//--turn on oled panel
  OLED_Fill(0x00); //初始清屏
  OLED_Set_Pos(0,0);
} 

/****************SPI***************************/
/*------------写一个数据：片选拉高-----------*/
void LCD_WrDat(unsigned char dat)
{
  unsigned char i=8;
  LCD_DCout(Bit_SET);
  for(i=0;i<8;i++)				//传送8位数据：时钟线拉低有效
  {
    LCD_SCLout(Bit_RESET);
    if(dat&0x80)	LCD_SDAout(Bit_SET);
    else	LCD_SDAout(Bit_RESET);
    LCD_SCLout(Bit_SET);
    dat<<=1;
  }
}
/*------------写命令：片选拉低-------------*/
void LCD_WrCmd(unsigned char cmd)
{
  unsigned char i=8;
  LCD_DCout(Bit_RESET);
  for(i=0;i<8;i++)			//传送8位数据：时钟线拉低有效
  {
    LCD_SCLout(Bit_RESET);
    if(cmd&0x80)	LCD_SDAout(Bit_SET);
    else LCD_SDAout(Bit_RESET);
    LCD_SCLout(Bit_SET);
    cmd<<=1;
  }
  LCD_DCout(Bit_SET);
}
/*----------------设置坐标------------------*/
void LCD_Set_Pos(unsigned char x, unsigned char y)
{
  LCD_WrCmd(0xb0+y);
  LCD_WrCmd(((x&0xf0)>>4)|0x10);
  LCD_WrCmd((x&0x0f)|0x01);
}
/*----------------全屏显示-----------------*/
void LCD_Fill(unsigned char bmp_dat)
{
  unsigned char y,x;
  for(y=0;y<8;y++)
  {
    LCD_WrCmd(0xb0+y);
    LCD_WrCmd(0x01);
    LCD_WrCmd(0x10);
    for(x=0;x<X_WIDTH;x++)
    {
      LCD_WrDat(bmp_dat);
    }
  }
}
/*---------------LCD复位-----------------*/
void LCD_CLS(void)
{
  unsigned char y,x;
#ifdef OLED_WORK_MODE_I2C
  for(y=0;y<8;y++)
  {
    OLED_WrCmd(0xb0+y);
    OLED_WrCmd(0x01);
    OLED_WrCmd(0x10);
    for(x=0;x<X_WIDTH;x++)
      OLED_WrDat(0); 
  }
#else  
  for(y=0;y<8;y++)
  {
    LCD_WrCmd(0xb0+y);
    LCD_WrCmd(0x01);
    LCD_WrCmd(0x10);
    for(x=0;x<X_WIDTH;x++)
      LCD_WrDat(0); 
  }
#endif
  
}
/*------显示6X8一组标准的ASCII字符串，显示坐标为（x，y）------*/
void LCD_P6x8Str(unsigned char x,unsigned char  y,unsigned char ch[])
{
  unsigned char c=0,i=0,j=0;
  while (ch[j]!='\0')
  {
    c =ch[j]-32;
#ifdef OLED_WORK_MODE_I2C
    if(x>126){x=0;y++;}
    OLED_Set_Pos(x,y);
    for(i=0;i<6;i++)
      OLED_WrDat(F6x8[c][i]);
#else    
    if(x>126){x=0;y++;}
    LCD_Set_Pos(x,y);
    for(i=0;i<6;i++)
      LCD_WrDat(F6x8[c][i]);
#endif
    x+=6;
    j++;
  }
}
//显示一个6X8的字符
void LCD_P6x8Char(unsigned char x,unsigned char  y,unsigned char ucData)
{
  unsigned char i, ucDataTmp;
  ucDataTmp = ucData-32;
  if(x > 126)
  {
    x= 0;
    y++;
  }
#ifdef OLED_WORK_MODE_I2C
  OLED_Set_Pos(x, y);
  for(i = 0; i < 6; i++)
  {
    OLED_WrDat(F6x8[ucDataTmp][i]);
  }
#else
  LCD_Set_Pos(x, y);
  for(i = 0; i < 6; i++)
  {
    LCD_WrDat(F6x8[ucDataTmp][i]);
  }
#endif
}
/*--------------显示6X8的浮点数--------------*/
void write_6_8_number(unsigned char x,unsigned char y, float number)
{
  unsigned char i=0;
  unsigned char temp[16];
  unsigned char *point=temp;
  float decimal;
  int data;
  if(number<0)
  {
    temp[0]='-';
    LCD_P6x8Char(x,y,temp[0]);
    x+=6;
    number=-number;
  }
  data=(int)number;
  decimal=number-data;					//小数部分
  
  if(data>=1000000000)           //是否能被10^9整除
  {
    temp[i]=48+data/1000000000;
    data=data%1000000000;
    i++;
  }
  if(data>=100000000)           //是否能被10^8整除
  {
    temp[i]=48+data/100000000;
    data=data%100000000;
    i++;
  }
  else
    if(data<100000000&&i!=0)
    {
      temp[i]=0+48;
      i++;
    }
  if(data>=10000000)           //是否能被10^7整除
  {
    temp[i]=48+data/10000000;
    data=data%10000000;
    i++;
  }
  else
    if(data<10000000&&i!=0)
    {
      temp[i]=0+48;
      i++;
    }
  if(data>=1000000)           //是否能被10^6整除
  {
    temp[i]=48+data/1000000;
    data=data%1000000;
    i++;
  }
  else
    if(data<1000000&&i!=0)
    {
      temp[i]=0+48;
      i++;
    }
  if(data>=100000)           //是否能被100000整除
  {
    temp[i]=48+data/100000;
    data=data%100000;
    i++;
  }
  else
    if(data<100000&&i!=0)
    {
      temp[i]=0+48;
      i++;
    }
  if(data>=10000)           //是否能被10000整除
  {
    temp[i]=48+data/10000;
    data=data%10000;
    i++;
  }
  else
    if(data<10000&&i!=0)
    {
      temp[i]=0+48;
      i++;
    }
  if(data>=1000)           //是否能被1000整除
  {
    temp[i]=48+data/1000;
    data=data%1000;
    i++;
  }
  else
    if(data<1000&&i!=0)
    {
      temp[i]=0+48;
      i++;
    }
  if(data>=100)              //是否能被100整除
  {
    temp[i]=48+data/100;
    data=data%100;
    i++;
  }
  else
    if(data<100&&i!=0)
    {
      temp[i]=0+48;
      i++;
    }
  if(data>=10)                  //是否能被10整除
  {
    temp[i]=48+data/10;
    data=data%10;
    i++;
  }
  else
    if(data<10&&i!=0)
    {
      temp[i]=48;
      i++;
    }
  temp[i]=48+data;
  if(decimal>=0.0001)           //判断是否有小数部分
  {
    i++;
    temp[i]='.';                //显示小数点
    i++;
    data=(int)(decimal*1000);
    temp[i]=48+data/100;
    data=data%100;
    i++;
    if(data>0)
    {
      temp[i]=48+data/10;
      data=data%10;
    }
    if(data>=0)
    {
      i++;
      temp[i]=data+48;
    }
  }
  i++;
  temp[i]='\0';
  LCD_P6x8Str(x,y,point);
}
/*------显示8X16一组标准的ASCII字符串，显示坐标为（x，y）------*/
void LCD_P8x16Str(unsigned char x,unsigned char  y,unsigned char ch[])
{
  unsigned char c=0,i=0,j=0;
  while (ch[j]!='\0')
  {
    c =ch[j]-32;
    if(x>120){x=0;y++;}
#ifdef OLED_WORK_MODE_I2C   
    OLED_Set_Pos(x,y);
    for(i=0;i<8;i++)
      OLED_WrDat(F8X16[c*16+i]);
    OLED_Set_Pos(x,y+1);
    for(i=0;i<8;i++)
      OLED_WrDat(F8X16[c*16+i+8]);
#else
    LCD_Set_Pos(x,y);
    for(i=0;i<8;i++)
      LCD_WrDat(F8X16[c*16+i]);
    LCD_Set_Pos(x,y+1);
    for(i=0;i<8;i++)
      LCD_WrDat(F8X16[c*16+i+8]);    
#endif    
    x+=8;
    j++;
  }
}
//显示一个8X16的字符
void LCD_P8x16Char(unsigned char x,unsigned char  y,unsigned char ch)
{
  unsigned char c=0,i=0,j=0;
  c =ch-32;
  if(x>120){x=0;y++;}
#ifdef OLED_WORK_MODE_I2C    
  OLED_Set_Pos(x,y);
  for(i=0;i<8;i++)
    OLED_WrDat(F8X16[c*16+i]);
  OLED_Set_Pos(x,y+1);
  for(i=0;i<8;i++)
    OLED_WrDat(F8X16[c*16+i+8]);
#else
  LCD_Set_Pos(x,y);
  for(i=0;i<8;i++)
    LCD_WrDat(F8X16[c*16+i]);
  LCD_Set_Pos(x,y+1);
  for(i=0;i<8;i++)
    LCD_WrDat(F8X16[c*16+i+8]);  
#endif   
  x+=8;
  j++;
}
/*---------------------显示8X16的浮点数--------------------*/
void write_8_16_number(unsigned char x,unsigned char y, float number)
{
  unsigned char i=0;
  unsigned char temp[16];
  unsigned char *point=temp;
  float decimal;
  int data;
  
  if(number<0)
  {
    temp[0]='-';
    LCD_P8x16Char(x,y,temp[0]);
    x+=1;
    number=-number;
  }
  data=(int)number;
  decimal=number-data;     //小数部分
  if(data>=1000)           //是否可被1000整除
  {
    temp[i]=48+data/1000;
    data=data%1000;
    i++;
  }
  if(data>=100)              //可否被100整除
  {
    temp[i]=48+data/100;
    data=data%100;
    i++;
  }
  else
    if(data<100&&i!=0)
    {
      temp[i]=0+48;
      i++;
    }
  if(data>=10)                  //可否被10整除
  {
    temp[i]=48+data/10;
    data=data%10;
    i++;
  }
  else
    if(data<10&&i!=0)
    {
      temp[i]=48;
      i++;
    }
  temp[i]=48+data;
  if(decimal>=0.0001)           //判断是够为小数
  {
    i++;
    temp[i]='.';                //显示小数点
    i++;
    data=(int)(decimal*1000);
    temp[i]=48+data/100;
    data=data%100;
    i++;
    if(data>0)
    {
      temp[i]=48+data/10;
      data=data%10;
    }
    if(data>=0)
    {
      i++;
      temp[i]=data+48;
    }
  }
  i++;
  temp[i]='\0';
  LCD_P8x16Str(x,y,point);
}


void LCD_clear_L(unsigned char x,unsigned char y)
{
#ifdef OLED_WORK_MODE_I2C  
  OLED_WrCmd(0xb0+y);
  OLED_WrCmd(0x01);
  OLED_WrCmd(0x10);
  OLED_Set_Pos(x,y);
  for(;x<X_WIDTH;x++)
  {
    OLED_WrDat(0);
  }
#else
  LCD_WrCmd(0xb0+y);
  LCD_WrCmd(0x01);
  LCD_WrCmd(0x10);
  LCD_Set_Pos(x,y);
  for(;x<X_WIDTH;x++)
  {
    LCD_WrDat(0);
  }        
#endif
}


void Draw_Logo1(void)
{
  unsigned int ii=0;
  unsigned char x,y;
#ifdef OLED_WORK_MODE_I2C    
  for(y=0;y<8;y++)
  {
    OLED_Set_Pos(0,y);
    for(x=0;x<128;x++)
    {
      OLED_WrDat(NC_Logo[ii++]);
      delay_ms(1);
    }
  }
#else
  for(y=0;y<8;y++)
  {
    LCD_Set_Pos(0,y);
    for(x=0;x<128;x++)
    {
      LCD_WrDat(NC_Logo[ii++]);
      delay_ms(1);
    }
  }
#endif
  delay_ms(2000);
  LCD_CLS();
}


//显示屏初始化
void OLEDInit(void)
{
  LCD_RSTout(Bit_RESET);
  delay_ms(100);
  LCD_RSTout(Bit_SET);//等待RC复位完毕
  
  LCD_WrCmd(0xae);		//--turn off oled panel
  LCD_WrCmd(0x00);		//---set low column address
  LCD_WrCmd(0x10);		//---set high column address
  LCD_WrCmd(0x40);		//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
  LCD_WrCmd(0x81);		//--set contrast control register
  LCD_WrCmd(0xcf); 		// Set SEG Output Current Brightness
  LCD_WrCmd(0xa0);		//--Set SEG/Column Mapping     0xa0???? 0xa1??
  LCD_WrCmd(0xc0);		//Set COM/Row Scan Direction   0xc0???? 0xc8??
  LCD_WrCmd(0xa6);		//--set normal display
  LCD_WrCmd(0xa8);		//--set multiplex ratio(1 to 64)
  LCD_WrCmd(0x3f);		//--1/64 duty
  LCD_WrCmd(0xd3);		//-set display offset Shift Mapping RAM Counter (0x00~0x3F)
  LCD_WrCmd(0x00);		//-not offset
  LCD_WrCmd(0xd5);		//--set display clock divide ratio/oscillator frequency
  LCD_WrCmd(0x80);		//--set divide ratio, Set Clock as 100 Frames/Sec
  LCD_WrCmd(0xd9);		//--set pre-charge period
  LCD_WrCmd(0xf1);		//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
  LCD_WrCmd(0xda);		//--set com pins hardware configuration
  LCD_WrCmd(0x12);
  LCD_WrCmd(0xdb);		//--set vcomh
  LCD_WrCmd(0x40);		//Set VCOM Deselect Level
  LCD_WrCmd(0x20);		//-Set Page Addressing Mode (0x00/0x01/0x02)
  LCD_WrCmd(0x02);		//
  LCD_WrCmd(0x8d);		//--set Charge Pump enable/disable
  LCD_WrCmd(0x14);		//--set(0x10) disable
  LCD_WrCmd(0xa4);		// Disable Entire Display On (0xa4/0xa5)
  LCD_WrCmd(0xa6);		// Disable Inverse Display On (0xa6/a7)
  LCD_WrCmd(0xaf);		//--turn on oled panel
  LCD_Fill(0x00);  		//初始清屏
  LCD_Set_Pos(0,0);
}
void testdrawline(void)
{
  for (int16_t i = 0; i < ssd1306_width(); i += 4) {
    ssd1306_draw_line(0, 0, i, ssd1306_height() - 1, WHITE);
    ssd1306_display();
  }
  for (int16_t i = 0; i < ssd1306_height(); i += 4) {
    ssd1306_draw_line(0, 0, ssd1306_width() - 1, i, WHITE);
    ssd1306_display();
  }
  delay_ms(100);
  
  ssd1306_clear_display();
  for (int16_t i = 0; i < ssd1306_width(); i += 4) {
    ssd1306_draw_line(0, ssd1306_height() - 1, i, 0, WHITE);
    ssd1306_display();
  }
  for (int16_t i = ssd1306_height() - 1; i >= 0; i -= 4) {
    ssd1306_draw_line(0, ssd1306_height() - 1, ssd1306_width() - 1, i, WHITE);
    ssd1306_display();
  }
  delay_ms(100);
  
  ssd1306_clear_display();
  for (int16_t i = ssd1306_width() - 1; i >= 0; i -= 4) {
    ssd1306_draw_line(ssd1306_width() - 1, ssd1306_height() - 1, i, 0, WHITE);
    ssd1306_display();
  }
  for (int16_t i = ssd1306_height() - 1; i >= 0; i -= 4) {
    ssd1306_draw_line(ssd1306_width() - 1, ssd1306_height() - 1, 0, i, WHITE);
    ssd1306_display();
  }
  delay_ms(100);
  
  ssd1306_clear_display();
  for (int16_t i = 0; i < ssd1306_height(); i += 4) {
    ssd1306_draw_line(ssd1306_width() - 1, 0, 0, i, WHITE);
    ssd1306_display();
  }
  for (int16_t i = 0; i < ssd1306_width(); i += 4) {
    ssd1306_draw_line(ssd1306_width() - 1, 0, i, ssd1306_height() - 1, WHITE);
    ssd1306_display();
  }
  delay_ms(100);
  
  ssd1306_display();
  delay_ms(100);
  ssd1306_clear_display();
}

/***************************************************
函数名: void OLED_Init(void)
说明:	OLED显示屏初始化
入口:	无
出口:	无
备注:	上电初始化，运行一次
****************************************************/
void OLED_Init(void)
{
#ifdef OLED_WORK_MODE_I2C 
  OLED_GPIO_Init();
  //OLED_Init_I2C();
  ssd1306_begin(SSD1306_SWITCHCAPVCC);
#else
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOC, ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 |GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  //OLEDInit();
  LCD_RSTout(Bit_RESET);
  delay_ms(100);
  LCD_RSTout(Bit_SET);//等待RC复位完毕
  ssd1306_begin(SSD1306_SWITCHCAPVCC);  
#endif
  ssd1306_clear_display();
  Draw_Logo1();
  LCD_CLS();
}


void OLED_Init_Fast(void)
{
#ifdef OLED_WORK_MODE_I2C 
  OLED_GPIO_Init();
  //OLED_Init_I2C();
  ssd1306_begin(SSD1306_SWITCHCAPVCC);  
#else
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOC, ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 |GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  //OLEDInit(); 
  LCD_RSTout(Bit_RESET);
  delay_ms(100);
  LCD_RSTout(Bit_SET);//等待RC复位完毕
  ssd1306_begin(SSD1306_SWITCHCAPVCC);  
#endif
}

