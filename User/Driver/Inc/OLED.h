/*----------------------------------------------------------------------------------------------------------------------/
*               本程序只供购买者学习使用，版权著作权属于无名科创团队，无名科创团队将飞控程序源码提供给购买者，
*               购买者要为无名科创团队提供保护，未经作者许可，不得将源代码提供给他人，不得将源代码放到网上供他人免费下载， 
*               更不能以此销售牟利，如发现上述行为，无名科创团队将诉之以法律解决！！！
-----------------------------------------------------------------------------------------------------------------------/
*               生命不息、奋斗不止；前人栽树，后人乘凉！！！
*               开源不易，且学且珍惜，祝早日逆袭、进阶成功！！！
*               学习优秀者，简历可推荐到DJI、ZEROTECH、XAG、AEE、GDU、AUTEL、EWATT、HIGH GREAT等公司就业
*               求职简历请发送：15671678205@163.com，需备注求职意向单位、岗位、待遇等
*               无名科创开源飞控QQ群：540707961
*               CSDN博客：http://blog.csdn.net/u011992534
*               优酷ID：NamelessCotrun无名小哥
*               B站教学视频：https://space.bilibili.com/67803559/#/video
*               客户使用心得、改进意见征集贴：http://www.openedv.com/forum.php?mod=viewthread&tid=234214&extra=page=1
*               淘宝店铺：https://shop348646912.taobao.com/?spm=2013.1.1000126.2.5ce78a88ht1sO2
*               百度贴吧:无名科创开源飞控
*               修改日期:2018/8/30
*               版本：慧飞者——V1.0.1
*               版权所有，盗版必究。
*               Copyright(C) 武汉科技大学无名科创团队 2017-2025
*               All rights reserved
----------------------------------------------------------------------------------------------------------------------*/
#ifndef __OLED_H
#define __OLED_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"



//#define  OLED_WORK_MODE_I2C  1//OLED使用I2C模式驱动，当采用SPI模式时，注释本行即可


#define LCD_DCout(data)		GPIO_WriteBit(GPIOC,GPIO_Pin_0,data)//DC
#define LCD_RSTout(data)	GPIO_WriteBit(GPIOC,GPIO_Pin_1,data)//RES
#define LCD_SDAout(data)	GPIO_WriteBit(GPIOC,GPIO_Pin_2,data)//D1
#define LCD_SCLout(data)	GPIO_WriteBit(GPIOC,GPIO_Pin_3,data)//D0
void LCD_WrDat(unsigned char dat);
void LCD_WrCmd(unsigned char cmd);
void OLED_WrCmd(unsigned char IIC_Data);
void OLED_WrDat(unsigned char IIC_Data);
void LCD_Set_Pos(unsigned char x, unsigned char y);
void OLED_Set_Pos(unsigned char x, unsigned char y);
void LCD_P6x8Char(unsigned char x,unsigned char  y,unsigned char ch);
void LCD_P6x8Str(unsigned char x,unsigned char  y,unsigned char ch[]);
void write_6_8_number(unsigned char x,unsigned char  y,float number);
void LCD_P8x16Char(unsigned char x,unsigned char  y,unsigned char ch);
void LCD_P8x16Str(unsigned char x,unsigned char  y,unsigned char ch[]);
void write_8_16_number(unsigned char x,unsigned char  y,float number);
void LCD_clear_L(unsigned char x,unsigned char y);
void OLED_Init(void);
void OLED_Init_Fast(void);
void LCD_CLS(void);
#endif



