#include "Headfile.h"
#include "SPI1.h"

void SPI_init(int flag)//改变速度
{
  GPIO_InitTypeDef GPIO_InitStructure;
  SPI_InitTypeDef   SPI_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 | RCC_APB2Periph_AFIO |RCC_APB2Periph_GPIOA,ENABLE);	//开端口时钟、SPI时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6| GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode =GPIO_Mode_Out_PP; //推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  

  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; //设置SPI为双线双向全双工模式
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;	 //主机模式
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;//发送、接收8位帧结构
  SPI_InitStructure.SPI_CPOL =SPI_CPOL_High ; //始终悬空高  // SPI_CPOL_Low//始终悬空低 
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;//第2个时钟沿捕获 //SPI_CPHA_1Edge第1个时钟沿捕获 
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;	 //硬件控制NSS信号（ss） 置成软件时,NSS脚可以他用	  // SPI_NSS_Hard 
  if(flag==2)  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;  //预分频值为2
  else if(flag==4) SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;  //预分频值为4
  else if(flag==8) SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8; //预分频值为8
  else if(flag==16) SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;  //预分频值为16
  else if(flag==32) SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;//预分频值为32
  else if(flag==64) SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;  //预分频值为64
  else if(flag==128) SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;  //预分频值为128
  else if(flag==256) SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256; //预分频值为256
  else  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;  //预分频值为4 
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; //数据传输由最高位开始	   //SD卡高位先传送
  SPI_InitStructure.SPI_CRCPolynomial = 7;	 //定义了CRC值计算的多项式为7
  SPI_Init(SPI1, &SPI_InitStructure); 
  SPI_Cmd(SPI1,ENABLE); 
}

char SPI_SendReceive(char data)     //SPI1的收发
  {		  
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);  //while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET); 
  SPI_I2S_SendData(SPI1, data);	
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
  return  SPI_I2S_ReceiveData(SPI1);
  } 
