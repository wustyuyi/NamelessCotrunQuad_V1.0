#ifndef _RINGBUF_H
#define _RINGBUF_H

#define  RINGBUFF_LEN   50     //定义最大接收字节数 50
typedef struct
{
  uint16_t Head;           
  uint16_t Tail;
  uint16_t Lenght;
  uint8_t  Ring_Buff[RINGBUFF_LEN];
}RingBuff_t;

#define USER_RINGBUFF  1  //使用环形缓冲区形式接收数据
#if  USER_RINGBUFF
/**如果使用环形缓冲形式接收串口数据***/
void RingBuff_Init(RingBuff_t *ringBuff);
u8 Write_RingBuff(uint8_t data,RingBuff_t *ringBuff);
u8 Read_RingBuff(uint8_t *rData,RingBuff_t *ringBuff);
#endif


void RingBuf_Write(unsigned char data,RingBuff_t *ringBuff,uint16_t Length);
u8 RingBuf_Read(unsigned char* pData,RingBuff_t *ringBuff);

#endif

