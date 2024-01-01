/*
********************************************************************************
*
*                                 Queue.c
*
* File          : Queue.c
* Version       : V1.0
* Author        : whq
* Mode          : Thumb2
* Toolchain     :
* Description   : 队列操作
*
* History       : 2014.11.29   修正存入队列时，可能造成读队列数据长度异常

* Date          : 2013.07.22
*******************************************************************************/
#include <stdio.h>
#include <string.h>

#include "Queue.h"
u8 USB_ReceiveFlg = false;
u8 Hid_RxData[50];


/*******************************************************************************
* Function Name : uint32_t QUEUE_PacketCreate(QUEUE8_t *pQ8, uint8_t *pBuf, uint32_t lenSize)
* Description   : 队列建立
* Input         :   pQ8:    队列
                    pBuf:   队列缓冲区地址
                    bufSize:队列缓冲区大小
* Output        :
* Other         :
* Date          : 2013.08.29
*******************************************************************************/
uint32_t QUEUE_PacketCreate(QUEUE8_t *pQ8, uint8_t *pBuf, uint32_t bufSize)
{
    ASSERT_PARAM(pQ8);
    ASSERT_PARAM(pBuf);
    ASSERT_PARAM(bufSize);

    pQ8->bufSize    = bufSize;
    pQ8->pBuf       = pBuf;
    pQ8->pStart     = pBuf;
    pQ8->pEnd       = pBuf;

    return 0;
}

/*******************************************************************************
* Function Name : uint32_t QUEUE_PacketIn(QUEUE8_t *pQ8, uint8_t *pData, uint32_t len)
* Description   : 数据载入队列
* Input         :   pQ8:    队列
                    pData:  要进队列的数据
                    len:    数据长度
* Output        :
* Other         :
* Date          : 2013.08.29
*******************************************************************************/
uint32_t QUEUE_PacketIn(QUEUE8_t *pQ8, uint8_t *pData, uint32_t len)
{
    volatile uint8_t    *pEnd   = NULL;

    uint32_t            index   = 0;

    ASSERT_PARAM(pData);
    ASSERT_PARAM(pQ8);
    ASSERT_PARAM(pQ8->pBuf);
    ASSERT_PARAM(pQ8->pStart);
    ASSERT_PARAM(pQ8->pEnd);

    pEnd = pQ8->pEnd;

    for (index = 0; index < len; index++)
    {
        if (++pEnd >= pQ8->pBuf + pQ8->bufSize)
        {
            pEnd = pQ8->pBuf;
        }
        if (pEnd == pQ8->pStart)
        {
            break;
        }

        *pQ8->pEnd = *pData++;

        pQ8->pEnd = pEnd;
    }

    return index;
}

/*******************************************************************************
* Function Name : uint32_t QUEUE_PacketOut(QUEUE8_t *pQ8, uint8_t *pData, uint32_t dataLen)
* Description   : 队列中取数据
* Input         :   pQ8:    队列
                    pData:  缓冲区
                    dataLen:缓冲区大小
* Output        :
* Other         :
* Date          : 2013.08.29
*******************************************************************************/
uint32_t QUEUE_PacketOut(QUEUE8_t *pQ8, uint8_t *pData, uint32_t dataLen)
{
    uint32_t index = 0;

    ASSERT_PARAM(pData);
    ASSERT_PARAM(pQ8);
    ASSERT_PARAM(pQ8->pBuf);
    ASSERT_PARAM(pQ8->pStart);
    ASSERT_PARAM(pQ8->pEnd);

    while ((pQ8->pStart != pQ8->pEnd) && (index < dataLen) && (index < pQ8->bufSize))
    {
        pData[index++] = *pQ8->pStart++;
        if (pQ8->pStart >= pQ8->pBuf + pQ8->bufSize)
        {
            pQ8->pStart = pQ8->pBuf;
        }
    }

    return index;
}

/*******************************************************************************
* Function Name : uint32_t QUEUE_PacketLengthGet(QUEUE8_TYPE *pQ8)
* Description   : 队列中的数据长度
* Input         :   pQ8:    队列
                    pData:  缓冲区
                    dataLen:缓冲区大小
* Output        :
* Other         :
* Date          : 2013.08.29
*******************************************************************************/
uint32_t QUEUE_PacketLengthGet(QUEUE8_t *pQ8)
{

    volatile uint8_t    *pStart     = NULL;
    uint32_t            index       = 0;

    ASSERT_PARAM(pQ8);
    ASSERT_PARAM(pQ8->pStart);
    ASSERT_PARAM(pQ8->pEnd);

    pStart = pQ8->pStart;

    while ((pStart != pQ8->pEnd) && (index < pQ8->bufSize))
    {
        index++;
        if (++pStart >= pQ8->pBuf + pQ8->bufSize)
        {
            pStart = pQ8->pBuf;
        }
    }

    return index;
}


/*******************************************************************************
* Function Name : uint32_t QUEUE_PacketStartEndDifferentCharSplit(QUEUE8_t *pQ8, uint8_t startChar, uint8_t endChar, uint8_t *pData, uint32_t dataLen)
* Description   : 以起始符和结束符取队列中的数据 (取出的数据 包括起始符 和分隔符)
* Input         :   pQ8:        队列
                    startChar:  起始符
                    endChar:    结束符
                    pData:      缓冲区
                    dataLen:    缓冲区大小
* Output        :
* Other         :
* Date          : 2013.08.29
*******************************************************************************/
uint32_t QUEUE_PacketStartEndDifferentCharSplit(QUEUE8_t *pQ8, uint8_t startChar, uint8_t endChar, uint8_t *pData, uint32_t dataLen)
{
    int32_t count;
    int32_t index;
    volatile uint8_t *pStart;
    volatile uint8_t *pEnd;

    ASSERT_PARAM(pData);
    ASSERT_PARAM(pQ8);
    ASSERT_PARAM(pQ8->pBuf);
    ASSERT_PARAM(pQ8->pStart);
    ASSERT_PARAM(pQ8->pEnd);

    pStart      = pQ8->pStart;
    count       = pQ8->bufSize;

    while ((pStart != pQ8->pEnd) && count--)        //查找起始字符
    {
        if (startChar == *pStart) break;
        if (++pStart >= pQ8->pBuf + pQ8->bufSize) pStart = pQ8->pBuf;
    }

    if (pStart == pQ8->pEnd) return 0;              //未找到起始符
    if (count == -1) return 0;
    pEnd = pStart;
    if (++pEnd >= pQ8->pBuf + pQ8->bufSize) pEnd = pQ8->pBuf;

    while ((pEnd != pQ8->pEnd) && count--)          //查找结束字符
    {
        if (endChar == *pEnd) break;
        if (++pEnd >= pQ8->pBuf + pQ8->bufSize) pEnd = pQ8->pBuf;
    }

    if (pEnd == pQ8->pEnd) return 0;                //未找结束符
    if (count == -1) return 0;
    if (++pEnd >= pQ8->pBuf + pQ8->bufSize) pEnd = pQ8->pBuf;

    count   = pQ8->bufSize - count;
    index   = 0;
    //获取从起始字符到结束字符的数据
    while ((pStart != pEnd) && (index < dataLen) && (index < pQ8->bufSize) && count--)
    {
        pData[index++] = *pStart++;
        if (pStart >= pQ8->pBuf + pQ8->bufSize) pStart = pQ8->pBuf;
    }

    pQ8->pStart = pEnd;
    return index;
}

/*******************************************************************************
* Function Name : uint32_t QUEUE_PacketStartEndCharSplit(QUEUE8_t *pQ8, uint8_t splitChar, uint8_t *pData, uint32_t dataLen)
* Description   : 提取首尾分隔符内的数据(包括分隔符)
* Input         :   pQ8:        队列
                    startChar:  起始符
                    endChar:    结束符
                    pData:      缓冲区
                    dataLen:    缓冲区大小
* Output        :
* Other         :
* Date          : 2013.08.30
*******************************************************************************/
uint32_t QUEUE_PacketStartEndCharSplit(QUEUE8_t *pQ8, uint8_t splitChar, uint8_t *pData, uint32_t dataLen)
{
    int32_t count;
    int32_t index;
    volatile uint8_t *pStart;
    volatile uint8_t *pEnd;

    ASSERT_PARAM(pData);
    ASSERT_PARAM(pQ8);
    ASSERT_PARAM(pQ8->pBuf);
    ASSERT_PARAM(pQ8->pStart);
    ASSERT_PARAM(pQ8->pEnd);

    pStart      = pQ8->pStart;
    count       = pQ8->bufSize;

    while ((pStart != pQ8->pEnd) && count--)        //查找起始字符
    {
        if (splitChar == *pStart) break;
        if (++pStart >= pQ8->pBuf + pQ8->bufSize) pStart = pQ8->pBuf;
    }

    if (pStart == pQ8->pEnd) return 0;              //未找到起始符
    if (count == -1) return 0;
    pEnd = pStart;
    if (++pEnd >= pQ8->pBuf + pQ8->bufSize) pEnd = pQ8->pBuf;

    while ((pEnd != pQ8->pEnd) && count--)          //查找结束字符
    {
        if (splitChar == *pEnd) break;
        if (++pEnd >= pQ8->pBuf + pQ8->bufSize) pEnd = pQ8->pBuf;
    }

    if (pEnd == pQ8->pEnd) return 0;                //未找结束符
    if (count == -1) return 0;
    if (++pEnd >= pQ8->pBuf + pQ8->bufSize) pEnd = pQ8->pBuf;

    count   = pQ8->bufSize - count;
    index   = 0;
    //获取从起始字符到结束字符的数据
    while ((pStart != pEnd) && (index < dataLen) && (index < pQ8->bufSize) && count--)
    {
        pData[index++] = *pStart++;
        if (pStart >= pQ8->pBuf + pQ8->bufSize) pStart = pQ8->pBuf;
    }

    //如果取出的数据只包括分隔符，有可能是上次结束符和下次起始符，因此放弃上次结束符。
    if (index <= 2)
    {
        index = 0;
        if (--pStart < pQ8->pBuf) pStart = pQ8->pBuf + pQ8->bufSize - 1;
    }

    pQ8->pStart = pStart;
    return index;
}

/*******************************************************************************
* Function Name : uint32_t QUEUE_PacketCharSplit(QUEUE8_t *pQ8, uint8_t splitChar, uint8_t *pData, uint32_t dataLen)
* Description   : 提取单结束分隔符的数据 (包括分隔符)
* Input         :
* Output        :
* Other         :
* Date          : 2013.10.20
*******************************************************************************/
uint32_t QUEUE_PacketCharSplit(QUEUE8_t *pQ8, uint8_t splitChar, uint8_t *pData, uint32_t dataLen)
{
    int32_t count;
    int32_t index;
    volatile uint8_t *pStart;
    volatile uint8_t *pEnd;

    ASSERT_PARAM(pData);
    ASSERT_PARAM(pQ8);
    ASSERT_PARAM(pQ8->pBuf);
    ASSERT_PARAM(pQ8->pStart);
    ASSERT_PARAM(pQ8->pEnd);

    pStart      = pQ8->pStart;
    count       = pQ8->bufSize;

    while ((pStart != pQ8->pEnd) && count--)        //查找起始字符
    {
        if (splitChar == *pStart) break;
        if (++pStart >= pQ8->pBuf + pQ8->bufSize) pStart = pQ8->pBuf;
    }

    if (pStart == pQ8->pEnd) return 0;              //未找到起始符
    if (count == -1) return 0;
    pEnd = pStart;
    if (++pEnd >= pQ8->pBuf + pQ8->bufSize) pEnd = pQ8->pBuf;

    pStart      = pQ8->pStart;
    count       = pQ8->bufSize;
    index       = 0;
    while ((pStart != pEnd) && (index < dataLen) && count--)        //查找起始字符
    {
        pData[index++] = *pStart;
        if (++pStart >= pQ8->pBuf + pQ8->bufSize) pStart = pQ8->pBuf;
    }

    pQ8->pStart = pStart;
    return index;
}

/*******************************************************************************
* Function Name :QUEUE_PacketDoubleEndCharSplit
* Description   :提取双结束分隔符的数据 (包括分隔符)
* Input         :QUEUE8_t * pQ8
* Input         :uint8_t splitChar1
* Input         :uint8_t splitChar2
* Input         :uint8_t * pData
* Input         :uint32_t dataLen
* Output        :uint32_t
* Other         :
* Date          :2014/03/27
*******************************************************************************/
uint32_t QUEUE_PacketDoubleEndCharSplit(QUEUE8_t *pQ8, uint8_t splitChar1, uint8_t splitChar2, uint8_t *pData, uint32_t dataLen)
{
    int32_t count;
    int32_t index;
    volatile uint8_t *pStart;
    volatile uint8_t *pEnd;
    uint8_t lastChar = 0;

    ASSERT_PARAM(pData);
    ASSERT_PARAM(pQ8);
    ASSERT_PARAM(pQ8->pBuf);
    ASSERT_PARAM(pQ8->pStart);
    ASSERT_PARAM(pQ8->pEnd);

    pStart      = pQ8->pStart;
    count       = pQ8->bufSize;

    while ((pStart != pQ8->pEnd) && count--)        //查找起始字符
    {
        if ((splitChar1 == lastChar) && (splitChar2 == *pStart)) break;

        lastChar = *pStart;

        if (++pStart >= pQ8->pBuf + pQ8->bufSize) pStart = pQ8->pBuf;
    }

    if (pStart == pQ8->pEnd) return 0;              //未找到起始符
    if (count == -1) return 0;
    pEnd = pStart;
    if (++pEnd >= pQ8->pBuf + pQ8->bufSize) pEnd = pQ8->pBuf;

    pStart      = pQ8->pStart;
    count       = pQ8->bufSize;
    index       = 0;
    while ((pStart != pEnd) && (index < dataLen) && count--)        //查找起始字符
    {
        pData[index++] = *pStart;
        if (++pStart >= pQ8->pBuf + pQ8->bufSize) pStart = pQ8->pBuf;
    }

    pQ8->pStart = pStart;
    return index;
}





/*******************************************************************************
* Function Name : uint32_t QUEUE_PacketCreate(QUEUE_STRUCT_t *pQueue, uint8_t *pBuf, uint32_t bufSize)
* Description   : 结构体队列
* Input         :   pQueue:     队列名
                    pBuf:       队列缓冲区
                    bufSize:    换冲区大小(字节)
                    blkSize:    单结构体大小(字节)
* Output        : 0: 成功
* Other         :
* Date          : 2014.08.13
*******************************************************************************/
uint32_t QUEUE_StructCreate(QUEUE_STRUCT_t *pQueue, void *pBuf, uint32_t bufSize, uint16_t blkSize)
{
    ASSERT_PARAM(pQueue);
    ASSERT_PARAM(pBuf);
    ASSERT_PARAM(bufSize);
    ASSERT_PARAM(blkSize);

    pQueue->elemSize    = blkSize;
    pQueue->sumCount    = bufSize / blkSize;
    pQueue->pBuf        = pBuf;
    pQueue->start       = 0;
    pQueue->end         = 0;
    return 0;
}

/*******************************************************************************
* Function Name : uint32_t QUEUE_StructIn(QUEUE_STRUCT_t *pQueue, void *pData, uint16_t blkCount)
* Description   : 结构体队列入栈 缓冲区中如果满则不载入
* Input         :   pQueue:     队列名
                    pData:      准备入栈的数据
                    blkCount:   准备入栈的结构体个数(单位:结构体个数)
* Output        : 成功入栈结构体的个数
* Other         :
* Date          : 2014.08.14
*******************************************************************************/
uint32_t QUEUE_StructIn(QUEUE_STRUCT_t *pQueue, void *pData, uint32_t blkCount)
{
    uint32_t i = blkCount;
    uint32_t end = 0;

    ASSERT_PARAM(pQueue);
    ASSERT_PARAM(pQueue->pBuf);
    ASSERT_PARAM(pData);

    end = pQueue->end;
    for (i = 0; i < blkCount; i++)
    {
        //再装一组数据后，指针是否指向栈尾
        if (++end >= pQueue->sumCount)
        {
            end = 0;
        }

        //缓冲区填满 直接退出
        if (end == pQueue->start)
        {
            break;
        }

        memcpy((uint8_t *)pQueue->pBuf + pQueue->end * pQueue->elemSize, pData, pQueue->elemSize);

        pData = (uint8_t *)pData + pQueue->elemSize;
        pQueue->end = end;
    }

    return i;
}

/*******************************************************************************
* Function Name : uint32_t QUEUE_StructOut(QUEUE_STRUCT_t *pQueue, void *pData, uint16_t blkCount)
* Description   : 结构体队列出栈
* Input         :   pQueue:     队列名
                    pData:      准备出栈的数据缓冲区
                    blkCount:   存放出栈结构体的最大个数(单位:结构体个数)
* Output        : 成功出栈结构体的个数
* Other         :
* Date          : 2014.08.14
*******************************************************************************/
uint32_t QUEUE_StructOut(QUEUE_STRUCT_t *pQueue, void *pData, uint32_t blkCount)
{
    uint32_t index = 0;

    ASSERT_PARAM(pQueue);
    ASSERT_PARAM(pQueue->pBuf);
    ASSERT_PARAM(pData);

    while ((pQueue->start != pQueue->end) && (index < pQueue->sumCount) && (index < blkCount))
    {
        memcpy(pData, (uint8_t *)pQueue->pBuf + pQueue->start * pQueue->elemSize, pQueue->elemSize);

        pData = (uint8_t *)pData + pQueue->elemSize;
        index++;
        if (++pQueue->start >= pQueue->sumCount)
        {
            pQueue->start = 0;
        }
    }

    return index;
}

/*******************************************************************************
* Function Name : uint32_t QUEUE_StructCountGet(QUEUE_STRUCT_t *pQueue)
* Description   : 获取结构体队列中的个数(结构体个数)
* Input         :
* Output        :
* Other         :
* Date          : 2014.08.14
*******************************************************************************/
uint32_t QUEUE_StructCountGet(QUEUE_STRUCT_t *pQueue)
{
    uint32_t index = 0;
    uint32_t start =0;

    ASSERT_PARAM(pQueue);
    ASSERT_PARAM(pQueue->pBuf);

    start = pQueue->start;
    while ((start != pQueue->end) && (index < pQueue->sumCount))
    {
        index++;
        if (++start >= pQueue->sumCount)
        {
            start = 0;
        }
    }

    return index;
}


#if     DEBUG_FULL_ASSERT

/*******************************************************************************
* Function Name : void ASSERT_FAILED(uint8_t* file, uint32_t line)
* Description   : 异常
* Input         :
* Output        :
* Other         :
* Date          : 2013.08.29
*******************************************************************************/
void ASSERT_FAILED(uint8_t* file, uint32_t line)
{
    uint8_t flg = 1;

    printf("wrong information 文件:%s 第%d行\r\n", file, line);
    while (flg);
}

#endif



void Usb_Hid_Receive()//不断查询
{
  if (USB_ReceiveFlg == true)
  {
		if(Hid_RxData[0]==0xFC
       &&Hid_RxData[1]==0xFF)
    {
			NCLink_Data_Prase_Process(Hid_RxData,Hid_RxData[3]+7);
    }
		USB_ReceiveFlg = 0x00;
  }
}



