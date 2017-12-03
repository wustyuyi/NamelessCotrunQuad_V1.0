#include "Headfile.h"
#include "IIC.h"
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

void IIC_GPIO_Config(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  GPIO_InitStructure.GPIO_Pin    = GPIO_Pin_6 | GPIO_Pin_7 ;
  GPIO_InitStructure.GPIO_Mode   = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed  = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  delay_ms(10);
  GPIO_SetBits(GPIOB,GPIO_Pin_6 | GPIO_Pin_7);

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

static void I2C_delay(void)
{
    //volatile int i = 1;	//7
    //while (i)
        //i--;
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

