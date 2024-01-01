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
