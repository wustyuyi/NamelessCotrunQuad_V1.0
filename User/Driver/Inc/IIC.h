#ifndef _IIC_H_   
#define _IIC_H_  


#define SCL_H         GPIOB->BSRR=GPIO_Pin_6
#define SCL_L         GPIOB->BRR=GPIO_Pin_6
#define SDA_H         GPIOB->BSRR=GPIO_Pin_7 
#define SDA_L         GPIOB->BRR=GPIO_Pin_7
#define SDA_read      ((GPIOB->IDR&GPIO_Pin_7)!=0)?1:0

void  IIC_GPIO_Config(void); 
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
#endif 
