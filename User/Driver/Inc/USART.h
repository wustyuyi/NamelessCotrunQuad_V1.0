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
#ifndef __USART_H
#define __USART_H


void USART1_Init(unsigned long bound);
void USART1_Send(unsigned char *tx_buf, int len);
void USART1_Receive(unsigned char *rx_buf, int len);
void UART1_Send(unsigned char tx_buf);
void wust_sendware(unsigned char *wareaddr, int16_t waresize);
void Quad_DMA1_USART1_SEND(u32 SendBuff,u16 len);//DMA---USART1����
void DMA_Send_Vcan(float userdata1,float userdata2,
									 float userdata3,float userdata4,
									 float userdata5,float userdata6,
									 float userdata7,float userdata8);
void USART1_Send_Dma(uint8_t *dma_buf,uint16_t dma_cnt);


void USART2_Init(unsigned long bound);

void USART3_Init(unsigned long bound);
void USART3_Send(unsigned char tx_buf);
void UART3_Send(unsigned char *tx_buf, int len);
void USART2_Send(unsigned char *tx_buf, int len);


void USART4_Init(unsigned long bound);
void USART5_Init(void);



extern uint8_t RecBag[3];
extern uint8 US_100_Cnt;


extern unsigned int GPS_Data_Cnt;
extern u16 GPS_ISR_CNT;
extern  u8 GPS_Buf[2][100];
extern uint8 Ublox_Data[95];

extern uint16 GPS_Update_finished,GPS_Update_finished_Correct_Flag;
extern Testime GPS_Time_Delta;
extern RingBuff_t COM5_Ringbuf,OpticalFlow_Ringbuf;


#endif


