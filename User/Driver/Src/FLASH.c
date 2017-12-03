#include "Headfile.h"
#include "stm32f10x_flash.h"//flash操作接口文件（在库文件中），必须要包含
#include "FLASH.h"
/*----------------------------------------------------------------------------------------------------------------------/
        *               本程序只供购买者学习使用，版权著作权属于无名科创团队，
        *               无名科创团队将飞控程序源码提供给购买者，
        *               购买者要为无名科创团队提供保护，
        *               未经作者许可，不得将源代码提供给他人
        *               不得将源代码放到网上供他人免费下载，
        *               更不能以此销售牟利，如发现上述行为，
        *               无名科创团队将诉之以法律解决！！！
-----------------------------------------------------------------------------------------------------------------------/
        *               生命不息、奋斗不止；前人栽树，后人乘凉！！！
        *               开源不易，且学且珍惜，祝早日逆袭、进阶成功！！！
-----------------------------------------------------------------------------------------------------------------------/
	*		无名科创开源飞控 V1.1	武汉科技大学  By.YuYi
	*		CSDN博客: http://blog.csdn.net/u011992534
	*               优酷ID：NamelessCotrun无名小哥
	*               无名科创开源飞控QQ群：540707961
        *               https://shop348646912.taobao.com/?spm=2013.1.1000126.2.5ce78a88ht1sO2
        *               百度贴吧:无名科创开源飞控
        *               修改日期:2017/10/30
        *               版本：V1.1
        *               版权所有，盗版必究。
        *               Copyright(C) 武汉科技大学无名科创团队 2017-2019
        *               All rights reserved
----------------------------------------------------------------------------------------------------------------------*/

union {
float Bit32;
unsigned char Bit8[4];
}flash;

/****************************************************************
*Function:	STM32F103系列内部Flash读写操作
*Author:    ValerianFan
*Date:		2014/04/09
*E-Mail:	fanwenjingnihao@163.com
*Other:		该程序不能直接编译运行，只包含了Flash读写操作
****************************************************************/
//#define  STARTADDR  0x08010000                   	 //STM32F103RB 其他型号基本适用，未测试
#define  STARTADDR  0x08040000//0x080350A8
volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;      //Flash操作状态变量
/****************************************************************
*Name:		ReadFlashNBtye
*Function:	从内部Flash读取N字节数据
*Input:		ReadAddress：数据地址（偏移地址）ReadBuf：数据指针	ReadNum：读取字节数
*Output:	读取的字节数
*Author:    ValerianFan
*Date:		2014/04/09
*E-Mail:	fanwenjingnihao@163.com
*Other:
****************************************************************/
int ReadFlashNBtye(uint32_t ReadAddress, uint8_t *ReadBuf, int32_t ReadNum)
{
        int DataNum = 0;
		ReadAddress = (uint32_t)STARTADDR + ReadAddress;
        while(DataNum < ReadNum)
		{
           *(ReadBuf + DataNum) = *(__IO uint8_t*) ReadAddress++;
           DataNum++;
        }
        return DataNum;
}

/****************************************************************
*Name:		WriteFlashOneWord
*Function:	向内部Flash写入32位数据
*Input:		WriteAddress：数据地址（偏移地址）WriteData：写入数据
*Output:	NULL
*Author:    ValerianFan
*Date:		2014/04/09
*E-Mail:	fanwenjingnihao@163.com
*Other:
****************************************************************/
void WriteFlashOneWord(uint32_t WriteAddress,uint32_t WriteData)
{
	FLASH_UnlockBank1();
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
        FLASHStatus = FLASH_ErasePage(STARTADDR);
	if(FLASHStatus == FLASH_COMPLETE)
	{
		FLASHStatus = FLASH_ProgramWord(STARTADDR + WriteAddress, WriteData);    //flash.c 中API函数
		//FLASHStatus = FLASH_ProgramWord(StartAddress+4, 0x56780000);//需要写入更多数据时开启
		//FLASHStatus = FLASH_ProgramWord(StartAddress+8, 0x87650000);//需要写入更多数据时开启
	}
	FLASH_LockBank1();
}


void WriteFlashHarfWord(uint32_t WriteAddress,uint16_t WriteData)
{
	FLASH_UnlockBank1();
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
        FLASHStatus = FLASH_ErasePage(STARTADDR);
	if(FLASHStatus == FLASH_COMPLETE)
	{
            FLASHStatus = FLASH_ProgramHalfWord(STARTADDR + WriteAddress, WriteData);    //flash.c 中API函数
	}
	FLASH_LockBank1();
}

void WriteFlashNineFloat(uint32_t WriteAddress,
                         float WriteData1,
                         float WriteData2,
                         float WriteData3,
                         float WriteData4,
                         float WriteData5,
                         float WriteData6,
                         float WriteData7,
                         float WriteData8,
                         float WriteData9)
{
        uint32_t Buf[9]={0};
        Buf[0]=*(uint32_t *)(&WriteData1);//把内存里面这四个字节写入到Flash
        Buf[1]=*(uint32_t *)(&WriteData2);
        Buf[2]=*(uint32_t *)(&WriteData3);
        Buf[3]=*(uint32_t *)(&WriteData4);
        Buf[4]=*(uint32_t *)(&WriteData5);
        Buf[5]=*(uint32_t *)(&WriteData6);
        Buf[6]=*(uint32_t *)(&WriteData7);
        Buf[7]=*(uint32_t *)(&WriteData8);
        Buf[8]=*(uint32_t *)(&WriteData9);

        FLASH_UnlockBank1();
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
        FLASHStatus = FLASH_ErasePage(STARTADDR);
	if(FLASHStatus == FLASH_COMPLETE)
	{
		FLASHStatus = FLASH_ProgramWord(STARTADDR + WriteAddress,Buf[0]);
		FLASHStatus = FLASH_ProgramWord(STARTADDR + WriteAddress+4,Buf[1]);
		FLASHStatus = FLASH_ProgramWord(STARTADDR + WriteAddress+8,Buf[2]);
                FLASHStatus = FLASH_ProgramWord(STARTADDR + WriteAddress+12,Buf[3]);
		FLASHStatus = FLASH_ProgramWord(STARTADDR + WriteAddress+16,Buf[4]);
		FLASHStatus = FLASH_ProgramWord(STARTADDR + WriteAddress+20,Buf[5]);
                FLASHStatus = FLASH_ProgramWord(STARTADDR + WriteAddress+24,Buf[6]);
		FLASHStatus = FLASH_ProgramWord(STARTADDR + WriteAddress+28,Buf[7]);
		FLASHStatus = FLASH_ProgramWord(STARTADDR + WriteAddress+32,Buf[8]);

	}
	FLASH_LockBank1();
}

uint8_t ReadFlashThreeFloat(uint32_t ReadAddress,
                         float *WriteData1,
                         float *WriteData2,
                         float *WriteData3)
{
    uint8_t buf[12];
    uint16_t i=0;
    uint8_t flag=0x00;
    ReadAddress = (uint32_t)STARTADDR + ReadAddress;
    *WriteData1=*(float *)(ReadAddress);
    *WriteData2=*(float *)(ReadAddress+4);
    *WriteData3=*(float *)(ReadAddress+8);
    FLASH_LockBank1();

    for(i=0;i<12;i++)//单字节数据
    {
        *(buf+i)=*(__IO uint8_t*) ReadAddress++;
    }
    if((buf[0]==0xff&&buf[1]==0xff&&buf[2]==0xff&&buf[3]==0xff))
       flag=flag|0x01;
    if((buf[4]==0xff&&buf[5]==0xff&&buf[6]==0xff&&buf[7]==0xff))
       flag=flag|0x02;
    if((buf[8]==0xff&&buf[9]==0xff&&buf[10]==0xff&&buf[11]==0xff))
       flag=flag|0x04;
    return flag;
}

