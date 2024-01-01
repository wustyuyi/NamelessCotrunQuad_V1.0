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
#include "usart.h"
#include "stdio.h"
DMA_InitTypeDef DMA_InitStructure;
uint16_t DMA1_MEM_LEN;//保存DMA每次数据传送的长度
/*
DMA1的各通道配置这里的传输形式是固定的,这点要根据不同的情况来修改
从存储器->外设模式/8位数据宽度/存储器增量模式
DMA_CHx:DMA通道CHx      cpar:外设地址
cmar:存储器地址         cndtr:数据传输量
*/
void Quad_DMA_Config(DMA_Channel_TypeDef* DMA_CHx,uint32_t cpar,uint32_t cmar,uint16_t cndtr)
{
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//使能DMA传输
  DMA_DeInit(DMA_CHx);   											        //将DMA的通道1寄存器重设为缺省值
  DMA1_MEM_LEN=cndtr;
  DMA_InitStructure.DMA_PeripheralBaseAddr = cpar;  //DMA外设基地址
  DMA_InitStructure.DMA_MemoryBaseAddr =cmar;				//DMA内存基地址
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;//外设作为数据传输的目的地
  DMA_InitStructure.DMA_BufferSize = cndtr;  												//DMA通道的DMA缓存的大小
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //外设地址寄存器不变
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  					//内存地址寄存器递增
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//数据宽度为8位
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;        //数据宽度为8位
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  									       //工作在正常缓存模式
  DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;                  //DMA通道 x拥有中优先级
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                           //DMA通道x没有设置为内存到内存传输
  DMA_Init(DMA_CHx, &DMA_InitStructure);//根据DMA_InitStruct中指定的参数初始化DMA的通道USART1_Tx_DMA_Channel所标识的寄存器
}

void Quad_DMA_Enable(DMA_Channel_TypeDef*DMA_CHx)//开启一次DMA传输
{
  DMA_Cmd(DMA_CHx, DISABLE );
  //关闭USART1 TX DMA1所指示的通道
  DMA_InitStructure.DMA_BufferSize =DMA1_MEM_LEN;
  DMA_Init(DMA1_Channel4, &DMA_InitStructure);
  DMA_Cmd(DMA_CHx, ENABLE);  //使能USART1 TX DMA1 所指示的通道
}

void Quad_DMA1_USART1_SEND(u32 SendBuff,u16 len)//DMA---USART1传输
{
  Quad_DMA_Config(DMA1_Channel4,(u32)&USART1->DR,(u32)SendBuff,len);//DMA1通道4,外设为串口1,存储器为SendBuff,长度len.
  USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
  Quad_DMA_Enable(DMA1_Channel4);
  //while(DMA_GetFlagStatus(DMA1_FLAG_TC4) != SET);
  //DMA_ClearFlag(DMA1_FLAG_TC4);//清除发送完成标志
}

/***************************************************
函数名: void USART1_Init(unsigned long bound)
说明:	串口1初始化
入口:	波特率
出口:	无
备注:	上电初始化，运行一次
****************************************************/
void USART1_Init(unsigned long bound)
{
  NVIC_InitTypeDef NVIC_InitStructure;//定义NVIC初始化结构体
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  
  USART_InitStructure.USART_BaudRate = bound;//
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;//8bits
  USART_InitStructure.USART_StopBits = USART_StopBits_1;//stop bit is 1
  USART_InitStructure.USART_Parity = USART_Parity_No;//no parity
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//no Hardware Flow Control
  USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;//enable tx and rx
  USART_Init(USART1, &USART_InitStructure);//
  
  USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//rx interrupt is enable
  USART_Cmd(USART1, ENABLE);
  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//优先级组别2，具体参见misc.h line80
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//串口中断1、对应山外上位机、主串口
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}


void UART1_Send(unsigned char tx_buf)
{
  while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET);//这里跟分析fputc时是一样的
  USART_SendData(USART1 , tx_buf);//发送字符数组里的单个字符
  while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET);
}




void USART1_Send(unsigned char *tx_buf, int len)
{
  USART_ClearFlag(USART1, USART_FLAG_TC);
  USART_ClearITPendingBit(USART1,USART_FLAG_TXE);
  while(len--)
  {
    USART_SendData(USART1, *tx_buf);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TC) != 1);
    USART_ClearFlag(USART1, USART_FLAG_TC);
    USART_ClearITPendingBit(USART1, USART_FLAG_TXE);
    tx_buf++;
  }
  
}

void USART1_Receive(unsigned char *rx_buf, int len)
{
  //rx_count = 0;
  //rx_length = len;
  //rx_address = rx_buf;
}



//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
//#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
    
void _sys_exit(int x) { x = x; }//定义_sys_exit()以避免使用半主机模式 

int fputc(int ch, FILE *f)//重定义fputc函数 
{      
  USART_SendData(USART1, (unsigned char) ch);
  while (!(USART1->SR & USART_FLAG_TXE));
  return (ch);
}
#endif 


void USART1_IRQHandler(void)
{ 
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
    NCLink_Data_Prase_Prepare(USART_ReceiveData(USART1));
    USART_ClearITPendingBit(USART1,USART_IT_RXNE);
  }
}


void USART1_Send_Dma(uint8_t *dma_buf,uint16_t dma_cnt)
{
	Quad_DMA_Config(DMA1_Channel4,(u32)&USART1->DR,(u32)dma_buf,dma_cnt);//DMA1通道4,外设为串口1,存储器为dma_buf,长度dma_cnt
  USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
  Quad_DMA_Enable(DMA1_Channel4);
}


void DMA_Send_Vcan(float userdata1,float userdata2,
									 float userdata3,float userdata4,
									 float userdata5,float userdata6,
									 float userdata7,float userdata8)
{
	static uint8_t databuf[36];
	uint8_t _cnt=0;
	databuf[_cnt++]=0x03;
	databuf[_cnt++]=0xfc;
	Float2Byte(&userdata1,databuf,_cnt);//3
	_cnt+=4;
	Float2Byte(&userdata2,databuf,_cnt);//7
	_cnt+=4;
	Float2Byte(&userdata3,databuf,_cnt);//11
	_cnt+=4;
	Float2Byte(&userdata4,databuf,_cnt);//15
	_cnt+=4;
	Float2Byte(&userdata5,databuf,_cnt);//19
	_cnt+=4;
	Float2Byte(&userdata6,databuf,_cnt);//23
	_cnt+=4;
	Float2Byte(&userdata7,databuf,_cnt);//27
	_cnt+=4;
	Float2Byte(&userdata8,databuf,_cnt);//31
	_cnt+=4;
	databuf[_cnt++]=0xfc;//35
	databuf[_cnt++]=0x03;//36
	//USART1_Send_Dma(databuf,_cnt);
	Serial_Data_Send(databuf,_cnt);
}





void wust_sendware(unsigned char *wareaddr, int16_t waresize)
{
#define CMD_WARE     3
  uint8 cmdf[2] = {CMD_WARE, ~CMD_WARE};
  uint8 cmdr[2] = {~CMD_WARE, CMD_WARE};
  USART1_Send(cmdf, sizeof(cmdf));
  USART1_Send(wareaddr, waresize);
  USART1_Send(cmdr, sizeof(cmdr));
}



void UART2_Send(unsigned char tx_buf)
{
  while(USART_GetFlagStatus(USART2, USART_FLAG_TC)==RESET);//这里跟分析fputc时是一样的
  USART_SendData(USART2 , tx_buf);//发送字符数组里的单个字符
  while(USART_GetFlagStatus(USART2, USART_FLAG_TC)==RESET);
}

void USART2_Send(unsigned char *tx_buf, int len)
{
  USART_ClearFlag(USART2, USART_FLAG_TC);
  USART_ClearITPendingBit(USART2, USART_FLAG_TXE);
  while(len--)
  {
    USART_SendData(USART2, *tx_buf);
    while(USART_GetFlagStatus(USART2, USART_FLAG_TC) != 1);
    USART_ClearFlag(USART2, USART_FLAG_TC);
    USART_ClearITPendingBit(USART2, USART_FLAG_TXE);
    tx_buf++;
  }
}


unsigned char Buffer[2]={9,8};
void USART2_Init(unsigned long bound)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO
                         |RCC_APB2Periph_GPIOA , ENABLE);//串口2
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);//串口2 低速
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  //	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  
  USART_InitStructure.USART_BaudRate = bound;//
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;//8bits
  USART_InitStructure.USART_StopBits = USART_StopBits_1;//stop bit is 1
  USART_InitStructure.USART_Parity = USART_Parity_No;//no parity
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//no Hardware Flow Control
  USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;//enable tx and rx
  USART_Init(USART2, &USART_InitStructure);//
  
  USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);//rx interrupt is enable
  USART_Cmd(USART2, ENABLE);
  
  //USART2_Send((unsigned char *)Buffer,2);
  //UART2_Send(0xAA);
}




void wust_sendimage(unsigned char *wareaddr, int16_t waresize)
{
#define CMD_Image    1
  uint8 cmdf[2] = {CMD_Image, ~CMD_Image};
  uint8 cmdr[2] = {~CMD_Image, CMD_Image};
  USART1_Send(cmdf, sizeof(cmdf));
  USART1_Send(wareaddr, waresize);
  USART1_Send(cmdr, sizeof(cmdr));
}


void USART3_Init(unsigned long bound)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure; 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  USART_InitStructure.USART_BaudRate = bound;//
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;//8bits
  USART_InitStructure.USART_StopBits = USART_StopBits_1;//stop bit is 1
  USART_InitStructure.USART_Parity = USART_Parity_No;//no parity
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//no Hardware Flow Control
  USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;//enable tx and rx
  USART_Init(USART3, &USART_InitStructure);//
  USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);//rx interrupt is enable
  USART_Cmd(USART3, ENABLE);
}

void USART3_Send(unsigned char tx_buf)
{
  while(USART_GetFlagStatus(USART3, USART_FLAG_TC) != 1);
  USART_SendData(USART3, tx_buf);
  USART_ClearFlag(USART3, USART_FLAG_TC);
  USART_ClearITPendingBit(USART3, USART_FLAG_TXE);
}
void UART3_Send(unsigned char *tx_buf, int len)
{
  USART_ClearFlag(USART3, USART_FLAG_TC);
  USART_ClearITPendingBit(USART3, USART_FLAG_TXE);
  while(len--)
  {
    USART_SendData(USART3, *tx_buf);
    while(USART_GetFlagStatus(USART3, USART_FLAG_TC) != 1);
    USART_ClearFlag(USART3, USART_FLAG_TC);
    USART_ClearITPendingBit(USART3, USART_FLAG_TXE);
    tx_buf++;
  }
}


RingBuff_t OpticalFlow_Ringbuf;
void USART4_Init(unsigned long bound)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE );
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE );
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //UART4 TX；
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出；
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure); //端口C；
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //UART4 RX；
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入；
  GPIO_Init(GPIOC, &GPIO_InitStructure); //端口C；
  
  USART_InitStructure.USART_BaudRate = bound; //波特率；
  USART_InitStructure.USART_WordLength = USART_WordLength_8b; //数据位8位；
  USART_InitStructure.USART_StopBits = USART_StopBits_1; //停止位1位；
  USART_InitStructure.USART_Parity = USART_Parity_No ; //无校验位；
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件流控；
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//收发模式；
  USART_Init(UART4, &USART_InitStructure);//配置串口参数；
  USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
  USART_Cmd(UART4, ENABLE); //使能串口；
  RingBuff_Init(&OpticalFlow_Ringbuf);
  OpticalFlow_Is_Work=Config_Init_Uart();
}

void USART4_Send(u8 Data) //发送一个字节；
{
  USART_SendData(UART4,Data);
  while( USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET );
}


void UART4_Send(u8 *Data) //发送字符串；
{
  while(*Data)
    USART4_Send(*Data++);
}


void UART4_IRQHandler(void) //中断处理函数；
{
  if(USART_GetITStatus(UART4, USART_IT_RXNE) == SET) //判断是否发生中断；
  {
    USART_ClearFlag(UART4, USART_IT_RXNE); //清除标志位
    RingBuf_Write(USART_ReceiveData(UART4),&OpticalFlow_Ringbuf,28);//往环形队列里面写数据
  }
}


RingBuff_t COM5_Ringbuf;
void USART5_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE );
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE );
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //UART5 RX；
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入；
  GPIO_Init(GPIOD, &GPIO_InitStructure); //端口D；
  
  USART_InitStructure.USART_BaudRate = 921600; //波特率；
  USART_InitStructure.USART_WordLength = USART_WordLength_8b; //数据位8位；
  USART_InitStructure.USART_StopBits = USART_StopBits_1; //停止位1位；
  USART_InitStructure.USART_Parity = USART_Parity_No ; //无校验位；
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件流控；
  USART_InitStructure.USART_Mode = USART_Mode_Rx;//发模式；
  USART_Init(UART5, &USART_InitStructure);//配置串口参数；
  USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);
  USART_Cmd(UART5, ENABLE); //使能串口；
 

  RingBuff_Init(&COM5_Ringbuf);
}





void USART5_Send(u8 Data) //发送一个字节；
{
  USART_SendData(UART5,Data);
  while( USART_GetFlagStatus(UART5, USART_FLAG_TC) == RESET );
}

void UART5_Send(u8 *Data) //发送字符串；
{
  while(*Data)
    USART5_Send(*Data++);
}


void UART5_IRQHandler(void) //中断处理函数；
{
  if(USART_GetITStatus(UART5, USART_IT_RXNE) == SET) //判断是否发生中断；
  {
		tofsense_prase(USART_ReceiveData(UART5));//RingBuf_Write(USART_ReceiveData(UART5),&COM5_Ringbuf,50);//往环形队列里面写数据
    USART_ClearFlag(UART5, USART_IT_RXNE); //清除标志位；
  }
}



u16 GPS_ISR_CNT=0;
uint16 Ublox_Try_Cnt=0;
uint16 Ublox_Try_Makesure=0;
uint16 Ublox_Try_Start=0;
uint8 Ublox_Data[95]={0};
uint16 Ublox_Cnt=0;
uint16 GPS_Update_finished=0;
uint16 GPS_Update_finished_Correct_Flag=0;
Testime GPS_Time_Delta;
void USART2_IRQHandler(void)//解析GPS输出的UBLOX  PVT协议
{
  unsigned char ch;
  if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
  {
    //Test_Period(&GPS_Time_Delta1);
    if(GPS_ISR_CNT<=2000)
    {
      GPS_ISR_CNT++;
    }
    
    ch=USART_ReceiveData(USART2);
    
    if(Ublox_Try_Makesure==1)
    {
      Ublox_Data[Ublox_Cnt++]=ch;
      if(Ublox_Cnt==94)
      {
        Ublox_Cnt=0;
        Ublox_Try_Makesure=0;
        GPS_Update_finished=1;
        GPS_Update_finished_Correct_Flag=1;
        Test_Period(&GPS_Time_Delta);//GPS数据更新间隔测试
      }
    }
    
    if(Ublox_Try_Makesure==0
       &&ch==0xB5)//出现帧头首字节，判断帧头是否完整
    {
      Ublox_Try_Start=1;
      Ublox_Try_Cnt=0;
    }
    
    if(Ublox_Try_Start==1)
    {
      Ublox_Try_Cnt++;
      if(Ublox_Try_Cnt>=5)
      {
        Ublox_Try_Start=0;
        Ublox_Try_Cnt=0;
        
        if(ch==0x5C) Ublox_Try_Makesure=1;//确认为帧头，开始接受
        else Ublox_Try_Makesure=0;//非帧头，复位等待再次确认
      }
    }
  }
  USART_ClearITPendingBit(USART2, USART_IT_RXNE);
  
}



void USART3_IRQHandler(void)
{
  if(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == SET)
  {
    SDK_Data_Receive_Prepare(USART_ReceiveData(USART3));
  }
  USART_ClearITPendingBit(USART3, USART_IT_RXNE);
}


