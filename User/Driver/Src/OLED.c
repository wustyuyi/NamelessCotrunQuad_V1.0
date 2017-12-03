#include "Headfile.h"
#include "string.h"
#include "oledfont.h"
#include "oled.h"
#include "stdlib.h"
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
#define XLevelL  		0x00
#define XLevelH  		0x10
#define XLevel     ((XLevelH&0x0F)*16+XLevelL)
#define Max_Column 	128
#define Max_Row  		64
#define Brightness 	0xCF
#define X_WIDTH 		128
#define Y_WIDTH 		64

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
  for(y=0;y<8;y++)
  {
    LCD_WrCmd(0xb0+y);
    LCD_WrCmd(0x01);
    LCD_WrCmd(0x10);
    for(x=0;x<X_WIDTH;x++)
      LCD_WrDat(0);
  }
}
/*------显示6X8一组标准的ASCII字符串，显示坐标为（x，y）------*/
void LCD_P6x8Str(unsigned char x,unsigned char  y,unsigned char ch[])
{
  unsigned char c=0,i=0,j=0;
  while (ch[j]!='\0')
  {
    c =ch[j]-32;
    if(x>126){x=0;y++;}
    LCD_Set_Pos(x,y);
    for(i=0;i<6;i++)
      LCD_WrDat(F6x8[c][i]);
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
    LCD_Set_Pos(x, y);
    for(i = 0; i < 6; i++)
    {
      LCD_WrDat(F6x8[ucDataTmp][i]);
    }
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
    LCD_Set_Pos(x,y);
    for(i=0;i<8;i++)
      LCD_WrDat(F8X16[c*16+i]);
    LCD_Set_Pos(x,y+1);
    for(i=0;i<8;i++)
      LCD_WrDat(F8X16[c*16+i+8]);
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
    LCD_Set_Pos(x,y);
  	for(i=0;i<8;i++)
  	  LCD_WrDat(F8X16[c*16+i]);
  	LCD_Set_Pos(x,y+1);
  	for(i=0;i<8;i++)
  	  LCD_WrDat(F8X16[c*16+i+8]);
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
	LCD_WrCmd(0xb0+y);
	LCD_WrCmd(0x01);
	LCD_WrCmd(0x10);
        LCD_Set_Pos(x,y);
	for(;x<X_WIDTH;x++)
        {
		LCD_WrDat(0);
        }
}
//显示屏初始化
void OLEDInit(void)
{

  LCD_SCLout(Bit_RESET);
  delay_ms(100);
  LCD_RSTout(Bit_SET);//等待RC复位完毕

  LCD_WrCmd(0xae);		//--turn off oled panel
  LCD_WrCmd(0x00);		//---set low column address
  LCD_WrCmd(0x10);		//---set high column address
  LCD_WrCmd(0x40);		//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
  LCD_WrCmd(0x81);		//--set contrast control register
  LCD_WrCmd(0xcf); 		// Set SEG Output Current Brightness
  LCD_WrCmd(0xa1);		//--Set SEG/Column Mapping     0xa0???? 0xa1??
  LCD_WrCmd(0xc8);		//Set COM/Row Scan Direction   0xc0???? 0xc8??
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

/***************************************************
函数名: void OLED_Init(void)
说明:	OLED显示屏初始化
入口:	无
出口:	无
备注:	上电初始化，运行一次
****************************************************/
void OLED_Init(void)
{
GPIO_InitTypeDef  GPIO_InitStructure;
RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOC, ENABLE);
GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 |GPIO_Pin_3;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_Init(GPIOC, &GPIO_InitStructure);

OLEDInit();
}
