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
#include "stm32f10x_flash.h"//flash操作接口文件（在库文件中），必须要包含
#include "FLASH.h"



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
//#define  STARTADDR  0x0803A000//0x080350A8   2K=2048=0x800  //STM32F103RB 其他型号基本适用，未测试
#define  STARTADDR  0x08060000//0x0807D000//500K后作为数据存储  2K=2048=0x800  //STM32F103RET 其他型号基本适用，未测试
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
#if FLASH_EEPROM_ENABLE
  int DataNum = 0;
  ReadAddress = (uint32_t)STARTADDR + ReadAddress;
  while(DataNum < ReadNum)
  {
    *(ReadBuf + DataNum) = *(__IO uint8_t*) ReadAddress++;
    DataNum++;
  }
  return DataNum;
#else
	ReadAddress+=PARAMETER_TABLE_STARTADDR_EEPROM;
	return W25QXX_Read_N_Data(ReadAddress,(uint32_t *)ReadBuf,ReadNum);
#endif
}


uint8_t ReadFlashOneWord(uint32_t ReadAddress,uint32_t *ReadData)
{
#if FLASH_EEPROM_ENABLE
  uint16_t i=0;
  uint8_t buf[4];
  uint32_t temp_data=0;
  temp_data=*(uint32_t *)(ReadAddress);
  FLASH_LockBank1();
  for(i=0;i<4;i++)//单字节数据
  {
    *(buf+i)=*(__IO uint8_t*) ReadAddress++;
  }
  if((buf[0]==0xff&&buf[1]==0xff&&buf[2]==0xff&&buf[3]==0xff))
    return 0;
  else
  {
    *ReadData=temp_data;
    return 1;
  }
#else
	ReadAddress+=PARAMETER_TABLE_STARTADDR_EEPROM;
	return W25QXX_Read_N_Data(ReadAddress,(uint32_t *)ReadData,1);
#endif
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
	  __set_PRIMASK(1);          //关总中断
#if FLASH_EEPROM_ENABLE
  FLASH_UnlockBank1();
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
  FLASHStatus = FLASH_ErasePage(WriteAddress);
  if(FLASHStatus == FLASH_COMPLETE)
  {
    FLASHStatus = FLASH_ProgramWord(WriteAddress, WriteData);    //flash.c 中API函数
  }
  FLASH_LockBank1();
#else
	WriteAddress+=PARAMETER_TABLE_STARTADDR_EEPROM;
	float writetemp;
	writetemp=WriteData;
	W25QXX_Write_N_Data(WriteAddress,(uint32_t *)(&writetemp),1);
#endif
	  __set_PRIMASK(0);          //开总中断
}



void WriteFlashHarfWord(uint32_t WriteAddress,uint16_t WriteData)
{
	__set_PRIMASK(1);          //关总中断
#if FLASH_EEPROM_ENABLE
  FLASH_UnlockBank1();
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
  FLASHStatus = FLASH_ErasePage(STARTADDR);
  if(FLASHStatus == FLASH_COMPLETE)
  {
    FLASHStatus = FLASH_ProgramHalfWord(STARTADDR + WriteAddress, WriteData);    //flash.c 中API函数
  }
  FLASH_LockBank1();
#else
	WriteAddress+=PARAMETER_TABLE_STARTADDR_EEPROM;
	float writetemp;
	writetemp=WriteData;
	W25QXX_Write_N_Data(WriteAddress,(uint32_t *)(&writetemp),1);
#endif
  __set_PRIMASK(0);          //开总中断
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
	__set_PRIMASK(1);          //关总中断
#if FLASH_EEPROM_ENABLE
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
#else
  WriteAddress+=PARAMETER_TABLE_STARTADDR_EEPROM;
	float writetemp[9]={0};
	writetemp[0]=WriteData1;
	writetemp[1]=WriteData2;
	writetemp[2]=WriteData3;
	writetemp[3]=WriteData4;
	writetemp[4]=WriteData5;
	writetemp[5]=WriteData6;
	writetemp[6]=WriteData7;
	writetemp[7]=WriteData8;
	writetemp[8]=WriteData9;
	W25QXX_Write_N_Data(WriteAddress,(uint32_t *)(writetemp),9);
#endif
  __set_PRIMASK(0);          //开总中断
}

uint8_t ReadFlashThreeFloat(uint32_t ReadAddress,
                            float *WriteData1,
                            float *WriteData2,
                            float *WriteData3)
{
#if FLASH_EEPROM_ENABLE
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
#else
  ReadAddress+=PARAMETER_TABLE_STARTADDR_EEPROM;
  float readtemp[3]; 
	uint8_t flag=W25QXX_Read_N_Data(ReadAddress,(uint32_t *)(readtemp),3);
	if(flag==1)
	{
	  *WriteData1=readtemp[0];
		*WriteData2=readtemp[1];
		*WriteData3=readtemp[2];
	}
	return flag;
#endif
}


