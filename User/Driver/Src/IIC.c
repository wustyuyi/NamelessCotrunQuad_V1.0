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
#include "IIC.h"


void Soft_I2C_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  GPIO_InitStructure.GPIO_Pin    = GPIO_Pin_6 | GPIO_Pin_7 ;
  GPIO_InitStructure.GPIO_Mode   = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed  = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  GPIO_InitStructure.GPIO_Pin    = GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode   = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed  = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
  
  delay_ms(10);
  GPIO_SetBits(GPIOB,GPIO_Pin_6 | GPIO_Pin_7);
  GPIO_SetBits(GPIOC,GPIO_Pin_4 | GPIO_Pin_5);
}

void SDA_IOOUT(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_7 ;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void SDA_IOIN(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_7 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void SDA1_IOOUT(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_5 ;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void SDA1_IOIN(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}

static void I2C_delay(void)
{
  //volatile int i = 1;	//7
  //while (i)
  //    i--;
}

static void I2C_Delay_Adjust(void)
{
  volatile int i = 1;	//7
  while (i)
    i--;
}

//**************************************
void I2C_Start(void)
{
  SDA_IOOUT();
  SCL_H;
  SDA_H;
  I2C_delay();
  SDA_L;
  I2C_delay();
}
//**************************************
void I2C_Stop(void)
{
  SDA_IOOUT();
  SCL_L;
  I2C_delay();
  SDA_L;
  I2C_delay();
  SCL_H;
  I2C_delay();
  SDA_H;
  I2C_delay();
}

//**************************************
unsigned char I2C_SlaveAck(void)
{
  SDA_IOOUT();
  SCL_L;
  I2C_delay();
  SDA_H;
  
  SDA_IOIN();
  I2C_delay();
  SCL_H;
  
  I2C_delay();
  
  if(SDA_read)
  {
    SCL_L;
    return 0;
  }
  SCL_L;
  I2C_delay();
  return 1;
}

//**************************************
void I2C_SendByte(unsigned char byte)
{
  unsigned char i = 8;
  SDA_IOOUT();
  while (i--)
  {
    SCL_L;
    I2C_delay();
    if (byte & 0x80)
      SDA_H;
    else
      SDA_L;
    byte <<= 1;
    I2C_delay();
    SCL_H;
    I2C_delay();
  }
  SCL_L;
  if(I2C_SlaveAck()==0)
  {
    return ;
  }
}

//**************************************
unsigned char I2C_RecvByte(void)
{
  unsigned char i;
  unsigned char dat = 0;
  SDA_IOIN();
  for (i=0; i<8; i++)
  {
    dat <<= 1;
    SCL_H;
    I2C_delay();
    dat |= SDA_read;
    SCL_L;
    I2C_delay();
  }
  return dat;
}


//**************************************
void I2C1_Start(void)
{
  SDA1_IOOUT();
  SCL1_H;
  SDA1_H;
  I2C_Delay_Adjust();
  SDA1_L;
  I2C_Delay_Adjust();
}
//**************************************
void I2C1_Stop(void)
{
  SDA1_IOOUT();
  SCL1_L;
  I2C_Delay_Adjust();
  SDA1_L;
  I2C_Delay_Adjust();
  SCL1_H;
  I2C_Delay_Adjust();
  SDA1_H;
  I2C_Delay_Adjust();
}

//**************************************
unsigned char I2C1_SlaveAck(void)
{
  SDA1_IOOUT();
  SCL1_L;
  I2C_Delay_Adjust();
  SDA1_H;
  
  SDA1_IOIN();
  I2C_Delay_Adjust();
  SCL1_H;
  I2C_Delay_Adjust();  
  if(SDA1_read)
  {
    SCL1_L;
    return 0;
  }
  SCL1_L;
  I2C_Delay_Adjust();
  return 1;
}

//**************************************
void I2C1_SendByte(unsigned char byte)
{
  unsigned char i = 8;
  SDA1_IOOUT();
  while (i--)
  {
    SCL1_L;
    I2C_Delay_Adjust();
    if (byte & 0x80)
      SDA1_H;
    else
      SDA1_L;
    byte <<= 1;
    I2C_Delay_Adjust();
    SCL1_H;
    I2C_Delay_Adjust();
  }
  SCL1_L;
  if(I2C1_SlaveAck()==0)
  {
    return ;
  }
}

//**************************************
unsigned char I2C1_RecvByte(void)
{
  unsigned char i;
  unsigned char dat = 0;
  SDA1_IOIN();
  for (i=0; i<8; i++)
  {
    dat <<= 1;
    SCL1_H;
    I2C_Delay_Adjust();
    dat |= SDA1_read;
    SCL1_L;
    I2C_Delay_Adjust();
  }
  return dat;
}

void Single_WriteI2C1(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data)
{
  I2C1_Start();
  I2C1_SendByte(SlaveAddress);
  I2C1_SendByte(REG_Address);
  I2C1_SendByte(REG_data);
  I2C1_Stop();
}

//**************************************
unsigned char Single_ReadI2C1(unsigned char SlaveAddress,unsigned char REG_Address)
{
  unsigned char REG_data;
  I2C1_Start();
  I2C1_SendByte(SlaveAddress);
  I2C1_SendByte(REG_Address);
  I2C1_Start();
  I2C1_SendByte(SlaveAddress+1);
  REG_data=I2C1_RecvByte();
  I2C1_SlaveAck();
  I2C1_Stop();
  return REG_data;
}

////////////////////////////////////////////////////

//**************************************
void Single_WriteI2C(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data)
{
  I2C_Start();
  I2C_SendByte(SlaveAddress);
  I2C_SendByte(REG_Address);
  I2C_SendByte(REG_data);
  I2C_Stop();
}

//**************************************
unsigned char Single_ReadI2C(unsigned char SlaveAddress,unsigned char REG_Address)
{
  unsigned char REG_data;
  I2C_Start();
  I2C_SendByte(SlaveAddress);
  I2C_SendByte(REG_Address);
  I2C_Start();
  I2C_SendByte(SlaveAddress+1);
  REG_data=I2C_RecvByte();
  I2C_SlaveAck();
  I2C_Stop();
  return REG_data;
}

unsigned short int Double_ReadI2C(unsigned char SlaveAddress,unsigned char REG_Address)
{
  unsigned char msb , lsb ;
  msb = Single_ReadI2C(SlaveAddress,REG_Address);
  lsb = Single_ReadI2C(SlaveAddress,REG_Address+1);
  return ( ((unsigned short int)msb) << 8 | lsb) ;
}

unsigned long int Three_ReadI2C(unsigned char SlaveAddress,unsigned char REG_Address)
{
  unsigned char msb , lsb,xlsb;
  msb = Single_ReadI2C(SlaveAddress,REG_Address);
  lsb = Single_ReadI2C(SlaveAddress,REG_Address+1);
  xlsb= Single_ReadI2C(SlaveAddress,REG_Address+2);
  return (((unsigned long int)msb<< 16)|((unsigned long int)lsb<<8)|xlsb) ;
}




//**************************************
void I2C_Start_Adjust(void)
{
  SDA_IOOUT();
  SCL_H;
  SDA_H;
  I2C_Delay_Adjust();
  SDA_L;
  I2C_Delay_Adjust();
}
//**************************************
void I2C_Stop_Adjust(void)
{
  SDA_IOOUT();
  SCL_L;
  I2C_Delay_Adjust();
  SDA_L;
  I2C_Delay_Adjust();
  SCL_H;
  I2C_Delay_Adjust();
  SDA_H;
  I2C_Delay_Adjust();
}

//**************************************
unsigned char I2C_SlaveAck_Adjust(void)
{
  SDA_IOOUT();
  SCL_L;
  I2C_Delay_Adjust();
  SDA_H;
  
  SDA_IOIN();
  I2C_Delay_Adjust();
  SCL_H;
  
  I2C_Delay_Adjust();
  
  if(SDA_read)
  {
    SCL_L;
    return 0;
  }
  SCL_L;
  I2C_Delay_Adjust();
  return 1;
}

//**************************************
void I2C_SendByte_Adjust(unsigned char byte)
{
  unsigned char i = 8;
  SDA_IOOUT();
  while (i--)
  {
    SCL_L;
    I2C_Delay_Adjust();
    if (byte & 0x80)
      SDA_H;
    else
      SDA_L;
    byte <<= 1;
    I2C_Delay_Adjust();
    SCL_H;
    I2C_Delay_Adjust();
  }
  SCL_L;
  if(I2C_SlaveAck_Adjust()==0)
  {
    return ;
  }
}

//**************************************
unsigned char I2C_RecvByte_Adjust(void)
{
  unsigned char i;
  unsigned char dat = 0;
  SDA_IOIN();
  for (i=0; i<8; i++)
  {
    dat <<= 1;
    SCL_H;
    I2C_Delay_Adjust();
    dat |= SDA_read;
    SCL_L;
    I2C_Delay_Adjust();
  }
  return dat;
}

//**************************************
void Single_WriteI2C_Adjust(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data)
{
  I2C_Start_Adjust();
  I2C_SendByte_Adjust(SlaveAddress);
  I2C_SendByte_Adjust(REG_Address);
  I2C_SendByte_Adjust(REG_data);
  I2C_Stop_Adjust();
}

//**************************************
unsigned char Single_ReadI2C_Adjust(unsigned char SlaveAddress,unsigned char REG_Address)
{
  unsigned char REG_data;
  I2C_Start_Adjust();
  I2C_SendByte_Adjust(SlaveAddress);
  I2C_SendByte_Adjust(REG_Address);
  I2C_Start_Adjust();
  I2C_SendByte_Adjust(SlaveAddress+1);
  REG_data=I2C_RecvByte_Adjust();
  I2C_SlaveAck_Adjust();
  I2C_Stop_Adjust();
  return REG_data;
}

unsigned short int Double_ReadI2C_Adjust(unsigned char SlaveAddress,unsigned char REG_Address)
{
  unsigned char msb , lsb ;
  msb = Single_ReadI2C_Adjust(SlaveAddress,REG_Address);
  lsb = Single_ReadI2C_Adjust(SlaveAddress,REG_Address+1);
  return ( ((unsigned short int)msb) << 8 | lsb) ;
}

unsigned long int Three_ReadI2C_Adjust(unsigned char SlaveAddress,unsigned char REG_Address)
{
  unsigned char msb , lsb,xlsb;
  msb = Single_ReadI2C_Adjust(SlaveAddress,REG_Address);
  lsb = Single_ReadI2C_Adjust(SlaveAddress,REG_Address+1);
  xlsb= Single_ReadI2C_Adjust(SlaveAddress,REG_Address+2);
  return (((unsigned long int)msb<< 16)|((unsigned long int)lsb<<8)|xlsb) ;
}

