/*----------------------------------------------------------------------------------------------------------------------/
*               ������ֻ��������ѧϰʹ�ã���Ȩ����Ȩ���������ƴ��Ŷӣ������ƴ��Ŷӽ��ɿس���Դ���ṩ�������ߣ�
*               ������ҪΪ�����ƴ��Ŷ��ṩ������δ��������ɣ����ý�Դ�����ṩ�����ˣ����ý�Դ����ŵ����Ϲ�����������أ� 
*               �������Դ�����Ĳ�����緢��������Ϊ�������ƴ��Ŷӽ���֮�Է��ɽ��������
-----------------------------------------------------------------------------------------------------------------------/
*               ������Ϣ���ܶ���ֹ��ǰ�����������˳���������
*               ��Դ���ף���ѧ����ϧ��ף������Ϯ�����׳ɹ�������
*               ѧϰ�����ߣ��������Ƽ���DJI��ZEROTECH��XAG��AEE��GDU��AUTEL��EWATT��HIGH GREAT�ȹ�˾��ҵ
*               ��ְ�����뷢�ͣ�15671678205@163.com���豸ע��ְ����λ����λ��������
*               �����ƴ���Դ�ɿ�QQȺ��540707961
*               CSDN���ͣ�http://blog.csdn.net/u011992534
*               �ſ�ID��NamelessCotrun����С��
*               Bվ��ѧ��Ƶ��https://space.bilibili.com/67803559/#/video
*               �ͻ�ʹ���ĵá��Ľ������������http://www.openedv.com/forum.php?mod=viewthread&tid=234214&extra=page=1
*               �Ա����̣�https://shop348646912.taobao.com/?spm=2013.1.1000126.2.5ce78a88ht1sO2
*               �ٶ�����:�����ƴ���Դ�ɿ�
*               �޸�����:2018/8/30
*               �汾���۷��ߡ���V1.0.1
*               ��Ȩ���У�����ؾ���
*               Copyright(C) �人�Ƽ���ѧ�����ƴ��Ŷ� 2017-2025
*               All rights reserved
----------------------------------------------------------------------------------------------------------------------*/
#ifndef _IIC_H_
#define _IIC_H_


#define SCL_H         GPIOB->BSRR=GPIO_Pin_6
#define SCL_L         GPIOB->BRR=GPIO_Pin_6
#define SDA_H         GPIOB->BSRR=GPIO_Pin_7
#define SDA_L         GPIOB->BRR=GPIO_Pin_7
#define SDA_read      ((GPIOB->IDR&GPIO_Pin_7)!=0)?1:0


#define SCL1_H         GPIOC->BSRR=GPIO_Pin_4
#define SCL1_L         GPIOC->BRR=GPIO_Pin_4
#define SDA1_H         GPIOC->BSRR=GPIO_Pin_5
#define SDA1_L         GPIOC->BRR=GPIO_Pin_5
#define SDA1_read     ((GPIOC->IDR&GPIO_Pin_5)!=0)?1:0

void  Soft_I2C_Init(void);
void Single_WriteI2C(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data);
unsigned char Single_ReadI2C(unsigned char SlaveAddress,unsigned char REG_Address);
unsigned short int Double_ReadI2C(unsigned char SlaveAddress,unsigned char REG_Address);
unsigned long int Three_ReadI2C(unsigned char SlaveAddress,unsigned char REG_Address);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_SendByte(unsigned char byte);
unsigned char I2C_SlaveAck(void);
unsigned char I2C_RecvByte(void);
void SDA_IOOUT(void);
void SDA_IOIN(void);

void Single_WriteI2C1(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data);
unsigned char Single_ReadI2C1(unsigned char SlaveAddress,unsigned char REG_Address);	


void Single_WriteI2C_Adjust(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data);
unsigned char Single_ReadI2C_Adjust(unsigned char SlaveAddress,unsigned char REG_Address);
unsigned short int Double_ReadI2C_Adjust(unsigned char SlaveAddress,unsigned char REG_Address);
unsigned long int Three_ReadI2C_Adjust(unsigned char SlaveAddress,unsigned char REG_Address);


#endif
