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
#include "usart.h"
#include "stdio.h"
DMA_InitTypeDef DMA_InitStructure;
uint16_t DMA1_MEM_LEN;//����DMAÿ�����ݴ��͵ĳ���
/*
DMA1�ĸ�ͨ����������Ĵ�����ʽ�ǹ̶���,���Ҫ���ݲ�ͬ��������޸�
�Ӵ洢��->����ģʽ/8λ���ݿ��/�洢������ģʽ
DMA_CHx:DMAͨ��CHx      cpar:�����ַ
cmar:�洢����ַ         cndtr:���ݴ�����
*/
void Quad_DMA_Config(DMA_Channel_TypeDef* DMA_CHx,uint32_t cpar,uint32_t cmar,uint16_t cndtr)
{
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//ʹ��DMA����
  DMA_DeInit(DMA_CHx);   											        //��DMA��ͨ��1�Ĵ�������Ϊȱʡֵ
  DMA1_MEM_LEN=cndtr;
  DMA_InitStructure.DMA_PeripheralBaseAddr = cpar;  //DMA�������ַ
  DMA_InitStructure.DMA_MemoryBaseAddr =cmar;				//DMA�ڴ����ַ
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;//������Ϊ���ݴ����Ŀ�ĵ�
  DMA_InitStructure.DMA_BufferSize = cndtr;  												//DMAͨ����DMA����Ĵ�С
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //�����ַ�Ĵ�������
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  					//�ڴ��ַ�Ĵ�������
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//���ݿ��Ϊ8λ
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;        //���ݿ��Ϊ8λ
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  									       //��������������ģʽ
  DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;                  //DMAͨ�� xӵ�������ȼ�
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                           //DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
  DMA_Init(DMA_CHx, &DMA_InitStructure);//����DMA_InitStruct��ָ���Ĳ�����ʼ��DMA��ͨ��USART1_Tx_DMA_Channel����ʶ�ļĴ���
}

void Quad_DMA_Enable(DMA_Channel_TypeDef*DMA_CHx)//����һ��DMA����
{
  DMA_Cmd(DMA_CHx, DISABLE );
  //�ر�USART1 TX DMA1��ָʾ��ͨ��
  DMA_InitStructure.DMA_BufferSize =DMA1_MEM_LEN;
  DMA_Init(DMA1_Channel4, &DMA_InitStructure);
  DMA_Cmd(DMA_CHx, ENABLE);  //ʹ��USART1 TX DMA1 ��ָʾ��ͨ��
}

void Quad_DMA1_USART1_SEND(u32 SendBuff,u16 len)//DMA---USART1����
{
  Quad_DMA_Config(DMA1_Channel4,(u32)&USART1->DR,(u32)SendBuff,len);//DMA1ͨ��4,����Ϊ����1,�洢��ΪSendBuff,����len.
  USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
  Quad_DMA_Enable(DMA1_Channel4);
  //while(DMA_GetFlagStatus(DMA1_FLAG_TC4) != SET);
  //DMA_ClearFlag(DMA1_FLAG_TC4);//���������ɱ�־
}

/***************************************************
������: void USART1_Init(unsigned long bound)
˵��:	����1��ʼ��
���:	������
����:	��
��ע:	�ϵ��ʼ��������һ��
****************************************************/
void USART1_Init(unsigned long bound)
{
  NVIC_InitTypeDef NVIC_InitStructure;//����NVIC��ʼ���ṹ��
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
  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//���ȼ����2������μ�misc.h line80
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//�����ж�1����Ӧɽ����λ����������
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}


void UART1_Send(unsigned char tx_buf)
{
  while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET);//���������fputcʱ��һ����
  USART_SendData(USART1 , tx_buf);//�����ַ�������ĵ����ַ�
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



//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
//#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
    
void _sys_exit(int x) { x = x; }//����_sys_exit()�Ա���ʹ�ð�����ģʽ 

int fputc(int ch, FILE *f)//�ض���fputc���� 
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
	Quad_DMA_Config(DMA1_Channel4,(u32)&USART1->DR,(u32)dma_buf,dma_cnt);//DMA1ͨ��4,����Ϊ����1,�洢��Ϊdma_buf,����dma_cnt
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
  while(USART_GetFlagStatus(USART2, USART_FLAG_TC)==RESET);//���������fputcʱ��һ����
  USART_SendData(USART2 , tx_buf);//�����ַ�������ĵ����ַ�
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
                         |RCC_APB2Periph_GPIOA , ENABLE);//����2
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);//����2 ����
  
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
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //UART4 TX��
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�������������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure); //�˿�C��
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //UART4 RX��
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //�������룻
  GPIO_Init(GPIOC, &GPIO_InitStructure); //�˿�C��
  
  USART_InitStructure.USART_BaudRate = bound; //�����ʣ�
  USART_InitStructure.USART_WordLength = USART_WordLength_8b; //����λ8λ��
  USART_InitStructure.USART_StopBits = USART_StopBits_1; //ֹͣλ1λ��
  USART_InitStructure.USART_Parity = USART_Parity_No ; //��У��λ��
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ�����أ�
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//�շ�ģʽ��
  USART_Init(UART4, &USART_InitStructure);//���ô��ڲ�����
  USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
  USART_Cmd(UART4, ENABLE); //ʹ�ܴ��ڣ�
  RingBuff_Init(&OpticalFlow_Ringbuf);
  OpticalFlow_Is_Work=Config_Init_Uart();
}

void USART4_Send(u8 Data) //����һ���ֽڣ�
{
  USART_SendData(UART4,Data);
  while( USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET );
}


void UART4_Send(u8 *Data) //�����ַ�����
{
  while(*Data)
    USART4_Send(*Data++);
}


void UART4_IRQHandler(void) //�жϴ�������
{
  if(USART_GetITStatus(UART4, USART_IT_RXNE) == SET) //�ж��Ƿ����жϣ�
  {
    USART_ClearFlag(UART4, USART_IT_RXNE); //�����־λ
    RingBuf_Write(USART_ReceiveData(UART4),&OpticalFlow_Ringbuf,28);//�����ζ�������д����
  }
}


RingBuff_t COM5_Ringbuf;
void USART5_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE );
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE );
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //UART5 RX��
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //�������룻
  GPIO_Init(GPIOD, &GPIO_InitStructure); //�˿�D��
  
  USART_InitStructure.USART_BaudRate = 921600; //�����ʣ�
  USART_InitStructure.USART_WordLength = USART_WordLength_8b; //����λ8λ��
  USART_InitStructure.USART_StopBits = USART_StopBits_1; //ֹͣλ1λ��
  USART_InitStructure.USART_Parity = USART_Parity_No ; //��У��λ��
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ�����أ�
  USART_InitStructure.USART_Mode = USART_Mode_Rx;//��ģʽ��
  USART_Init(UART5, &USART_InitStructure);//���ô��ڲ�����
  USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);
  USART_Cmd(UART5, ENABLE); //ʹ�ܴ��ڣ�
 

  RingBuff_Init(&COM5_Ringbuf);
}





void USART5_Send(u8 Data) //����һ���ֽڣ�
{
  USART_SendData(UART5,Data);
  while( USART_GetFlagStatus(UART5, USART_FLAG_TC) == RESET );
}

void UART5_Send(u8 *Data) //�����ַ�����
{
  while(*Data)
    USART5_Send(*Data++);
}


void UART5_IRQHandler(void) //�жϴ�������
{
  if(USART_GetITStatus(UART5, USART_IT_RXNE) == SET) //�ж��Ƿ����жϣ�
  {
		tofsense_prase(USART_ReceiveData(UART5));//RingBuf_Write(USART_ReceiveData(UART5),&COM5_Ringbuf,50);//�����ζ�������д����
    USART_ClearFlag(UART5, USART_IT_RXNE); //�����־λ��
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
void USART2_IRQHandler(void)//����GPS�����UBLOX  PVTЭ��
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
        Test_Period(&GPS_Time_Delta);//GPS���ݸ��¼������
      }
    }
    
    if(Ublox_Try_Makesure==0
       &&ch==0xB5)//����֡ͷ���ֽڣ��ж�֡ͷ�Ƿ�����
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
        
        if(ch==0x5C) Ublox_Try_Makesure=1;//ȷ��Ϊ֡ͷ����ʼ����
        else Ublox_Try_Makesure=0;//��֡ͷ����λ�ȴ��ٴ�ȷ��
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


