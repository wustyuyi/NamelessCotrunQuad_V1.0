/* Copyright (c)  2019-2025 Wuhan Nameless Innovation Technology Co.,Ltd. All rights reserved.*/
/*----------------------------------------------------------------------------------------------------------------------/
                ��Դ����������ѣ������ߵ���ʷ�Ѿ�֤�����ڹ�����������£���������Ŀ�Դ������������˰����ߣ��Է��ز�����
								Ŀ���Ƶķ�ʽ�в�ͨ���õĿ�Դ��Ŀ��Ҫ��רְ��Ա�����ۺ�����ְ��ֽ�ѧ��ͳ���û�����������ʵ������ɶԲ�
								Ʒ��һ�δ���������������������ۺϿ��ǣ������ɿؿ�Դ�����У������������˾���漤��ܴ��룬�汾������ʵ��
								���ܣ����ڹ�˾��Ʒ���������������Ӱ��ͻ�ѧϰ���������ȫ�����Ÿ��ͻ�ѧϰ���ͻ���ֲ�Ͷ��ο��������뱣����
								���Ȩ��
-----------------------------------------------------------------------------------------------------------------------/
*               ������ֻ��������ѧϰʹ�ã���Ȩ����Ȩ���������ƴ��Ŷӣ������ƴ��Ŷӽ��ɿس���Դ���ṩ�������ߣ�
*               ������ҪΪ�����ƴ��Ŷ��ṩ������δ��������ɣ����ý�Դ�����ṩ�����ˣ����ý�Դ����ŵ����Ϲ�����������أ� 
*               �������Դ�����Ĳ�����緢��������Ϊ�������ƴ��Ŷӽ���֮�Է��ɽ��������
-----------------------------------------------------------------------------------------------------------------------
*                                                 Ϊʲôѡ���������£�
*                                         �ж����ļ۸�������׵Ŀ�Դ�ɿأ�
*                                         ����ҵ������֮������µ��ۺ����
*                                         ׷�����û����飬��Ч����ѧϰ֮·��
*                                         ���²��ٹµ�������������տ�Դ�߶ȣ�
*                                         ��Ӧ���ҷ�ƶ���٣��ٽ��������ƹ�ƽ��
*                                         ��ʱ���ܶ�����ʣ����������˹�ͬ�塣 
-----------------------------------------------------------------------------------------------------------------------
*               ������Ϣ���ܶ���ֹ��ǰ�����������˳���������
*               ��Դ���ף���ѧ����ϧ��ף������Ϯ�����׳ɹ�������
*               ѧϰ�����ߣ��������Ƽ���DJI��ZEROTECH��XAG��AEE��GDU��AUTEL��EWATT��HIGH GREAT�ȹ�˾��ҵ
*               ��ְ�����뷢�ͣ�15671678205@163.com���豸ע��ְ����λ����λ��������
*               �����ƴ���Դ�ɿ�QQȺ��2��Ⱥ465082224��1��Ⱥ540707961����Ա������
*               CSDN���ͣ�http://blog.csdn.net/u011992534
*               �ſ�ID��NamelessCotrun����С��
*               Bվ��ѧ��Ƶ��https://space.bilibili.com/67803559/#/video
*               �ͻ�ʹ���ĵá��Ľ������������http://www.openedv.com/forum.php?mod=viewthread&tid=234214&extra=page=1
*               �Ա����̣�https://shop348646912.taobao.com/?spm=2013.1.1000126.2.5ce78a88ht1sO2
*               �ٶ�����:�����ƴ���Դ�ɿ�
*               ��˾����:www.nameless.tech
*               �������¹����׿�TI��Դ�ɿ���Ƴ��ԡ�֪��ר��:https://zhuanlan.zhihu.com/p/54471146
*               �޸�����:2019/11/27                    
*               �汾���۷���PRO����WisdomPilot_Pro_V1.0.0
*               ��Ȩ���У�����ؾ���
*               Copyright(C) 2019-2025 �人�������¿Ƽ����޹�˾ 
*               All rights reserved
-----------------------------------------------------------------------------------------------------------------------
*               ��Ҫ��ʾ��
*               �����Ա�����ת�ֵķɿء��������ѡ�����ѧ�ܵĶ����Խ��ۺ�Ⱥѧϰ������
*               ����ֱ�����������������������ϣ��������´�����������Ȩ�����˲��ý�
*               ���ϴ��봫���Ϲ��������أ�������ı��ΪĿ���������ϴ��룬�����д˲�
*               ���ߣ���˾����ǰ��֪����1���ڼ�ʱ�����������ѧУ����λ����������
*               ������ַ��Ϣ�ᱻ�����ڹ�˾�������ٷ�΢�Ź���ƽ̨���ٷ��������͡�֪��
*               ר���Լ��Ա�������ҳ���Թ�ʾ���棬����������Ϊ�����Ϊ�����۵㣬Ӱ��
*               ��ѧ���ҹ���������������ܿ�ͺ������˻����������������ء�
*               �����Ϊ����˾����ش���ʧ�ߣ����Է���;���������л���ĺ�����лл������
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

