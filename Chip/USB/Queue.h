/*
********************************************************************************
*
*                                 Queue.h
*
* File          : Queue.h
* Version       : V1.0
* Author        : whq
* Mode          : Thumb2
* Toolchain     :
* Description   : ���в���ͷ�ļ�
*
* History       :
* Date          : 2013.07.22
*******************************************************************************/


#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "Headfile.h"

#ifdef  __cplusplus
extern "C"
{
#endif



#include "stdint.h"

#define DEBUG_FULL_ASSERT       0

#if     DEBUG_FULL_ASSERT
#define ASSERT_PARAM(a)          ((a) ? (void)0 : ASSERT_FAILED((uint8_t *)__FILE__, __LINE__))
void ASSERT_FAILED(uint8_t* file, uint32_t line);
#else
#define ASSERT_PARAM(a)
#endif





typedef volatile struct {
    volatile uint32_t   bufSize;        //�������ܴ�С
    volatile uint8_t    *pStart;        //��ʼ��ַ
    volatile uint8_t    *pEnd;          //������ַ
    volatile uint8_t    *pBuf;          //�������׵�ַ
}QUEUE8_t;


typedef volatile struct {
    volatile uint32_t   elemSize;       //�ṹ�嵥Ԫ��С
    volatile uint32_t   sumCount;       //�ṹ�嵥Ԫ��������
    volatile uint32_t   start;          //�����ṹ���ַ
    volatile uint32_t   end;            //�������׵�ַ
    volatile void       *pBuf;          //��ʼ�ṹ���ַ
}QUEUE_STRUCT_t;



uint32_t QUEUE_PacketCreate(QUEUE8_t *pQ8, uint8_t *pBuf, uint32_t bufSize);
uint32_t QUEUE_PacketIn(QUEUE8_t *pQ8, uint8_t *pData, uint32_t len);
uint32_t QUEUE_PacketOut(QUEUE8_t *pQ8, uint8_t *pData, uint32_t dataLen);
uint32_t QUEUE_PacketLengthGet(QUEUE8_t *pQ8);

uint32_t QUEUE_PacketCharSplit(QUEUE8_t *pQ8, uint8_t splitChar, uint8_t *pData, uint32_t dataLen);
uint32_t QUEUE_PacketStartEndCharSplit(QUEUE8_t *pQ8, uint8_t splitChar, uint8_t *pData, uint32_t dataLen);
uint32_t QUEUE_PacketStartEndDifferentCharSplit(QUEUE8_t *pQ8, uint8_t startChar, uint8_t endChar, uint8_t *pData, uint32_t dataLen);
uint32_t QUEUE_PacketDoubleEndCharSplit(QUEUE8_t *pQ8, uint8_t splitChar1, uint8_t splitChar2, uint8_t *pData, uint32_t dataLen);


uint32_t QUEUE_StructCreate(QUEUE_STRUCT_t *pQueue, void *pBuf, uint32_t bufSize, uint16_t blkSize);
uint32_t QUEUE_StructIn(QUEUE_STRUCT_t *pQueue, void *pData, uint32_t blkCount);
uint32_t QUEUE_StructOut(QUEUE_STRUCT_t *pQueue, void *pData, uint32_t blkCount);
uint32_t QUEUE_StructCountGet(QUEUE_STRUCT_t *pQueue);


#ifdef  __cplusplus
}
#endif

extern u8 USB_ReceiveFlg,Hid_RxData[50];
void Usb_Hid_Receive(void);//���ϲ�ѯ

#endif

