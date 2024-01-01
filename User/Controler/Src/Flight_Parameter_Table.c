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
#include "Flight_Parameter_Table.h"

volatile FLASH_Status Parameter_Table_FLASHStatus = FLASH_COMPLETE;      //Flash操作状态变量

void ReadFlashParameterALL(volatile FLIGHT_PARAMETER *WriteData)
{
#if FLASH_EEPROM_ENABLE
  uint16_t i=0;
  uint32_t ReadAddress = (uint32_t)PARAMETER_TABLE_STARTADDR;
  for(i=0;i<FLIGHT_PARAMETER_TABLE_NUM;i++)
  {
    WriteData->Parameter_Table[i]=*(float *)(ReadAddress+4*i);
  }
  FLASH_LockBank1();
#else
	uint32_t ReadAddress = (uint32_t)(PARAMETER_TABLE_STARTADDR_EEPROM);
	W25QXX_Read_N_Data(ReadAddress,(uint32_t *)(&WriteData->Parameter_Table),FLIGHT_PARAMETER_TABLE_NUM);
#endif
}


uint8_t ReadFlashParameterOne(uint16_t Label,float *ReadData)
{
#if FLASH_EEPROM_ENABLE
  uint16_t i=0;
  uint8_t buf[4];
  float temp_data=0;
  uint32_t ReadAddress = (uint32_t)PARAMETER_TABLE_STARTADDR+Label*4;
  temp_data=*(float *)(ReadAddress);
  FLASH_LockBank1();
  for(i=0;i<4;i++)//单字节数据
  {
    *(buf+i)=*(__IO uint8_t*) ReadAddress++;
  }
	
	*ReadData=temp_data;
  if((buf[0]==0xff&&buf[1]==0xff&&buf[2]==0xff&&buf[3]==0xff))
  {
		return 0;
	}
  else
  {
    //*ReadData=temp_data;
    return 1;
  }
#else
  uint32_t ReadAddress = (uint32_t)(PARAMETER_TABLE_STARTADDR_EEPROM+Label*4);
	return W25QXX_Read_N_Data(ReadAddress,(uint32_t *)ReadData,1);
#endif
}

uint8_t ReadFlashParameterTwo(uint16_t Label,float *ReadData1,float *ReadData2)
{
#if FLASH_EEPROM_ENABLE
  uint16_t i=0;
  uint8_t buf[8];
  float temp_data1=0,temp_data2=0;
  uint32_t ReadAddress = (uint32_t)PARAMETER_TABLE_STARTADDR+Label*4;
  temp_data1=*(float *)(ReadAddress);
  ReadAddress+=4;
  temp_data2=*(float *)(ReadAddress);
  
  FLASH_LockBank1();
  for(i=0;i<8;i++)//单字节数据
  {
    *(buf+i)=*(__IO uint8_t*) ReadAddress++;
  }
	*ReadData1=temp_data1;
	*ReadData2=temp_data2;
	
  if((buf[0]==0xff&&buf[1]==0xff&&buf[2]==0xff&&buf[3]==0xff)
     &&(buf[4]==0xff&&buf[5]==0xff&&buf[6]==0xff&&buf[7]==0xff))
    return 0;
  else
  {
//    *ReadData1=temp_data1;
//    *ReadData2=temp_data2;
    return 1;
  }
#else
  uint32_t ReadAddress = (uint32_t)(PARAMETER_TABLE_STARTADDR_EEPROM+Label*4);
  float readtemp[2]; 
	uint8_t flag=W25QXX_Read_N_Data(ReadAddress,(uint32_t *)(readtemp),2);
	if(flag==1)
	{
	  *ReadData1=readtemp[0];
		*ReadData2=readtemp[1];
	}
	return flag;
#endif
}

uint8_t ReadFlashParameterThree(uint16_t Label,float *ReadData1,float *ReadData2,float *ReadData3)
{
#if FLASH_EEPROM_ENABLE
  uint16_t i=0;
  uint8_t buf[12];
  float temp_data1=0,temp_data2=0,temp_data3=0;
  uint32_t ReadAddress = (uint32_t)PARAMETER_TABLE_STARTADDR+Label*4;
  temp_data1=*(float *)(ReadAddress);
  ReadAddress+=4;
  temp_data2=*(float *)(ReadAddress);
  ReadAddress+=4;
  temp_data3=*(float *)(ReadAddress);
  
  FLASH_LockBank1();
  for(i=0;i<12;i++)//单字节数据
  {
    *(buf+i)=*(__IO uint8_t*) ReadAddress++;
  }
	
	*ReadData1=temp_data1;
	*ReadData2=temp_data2;
	*ReadData3=temp_data3;
	
  if((buf[0]==0xff&&buf[1]==0xff&&buf[2]==0xff&&buf[3]==0xff)
     &&(buf[4]==0xff&&buf[5]==0xff&&buf[6]==0xff&&buf[7]==0xff)
       &&(buf[8]==0xff&&buf[9]==0xff&&buf[10]==0xff&&buf[11]==0xff))
    return 0;
  else
  {
//    *ReadData1=temp_data1;
//    *ReadData2=temp_data2;
//    *ReadData3=temp_data3;
    return 1;
  }
#else
  uint32_t ReadAddress = (uint32_t)(PARAMETER_TABLE_STARTADDR_EEPROM+Label*4);
  float readtemp[3]; 
	uint8_t flag=W25QXX_Read_N_Data(ReadAddress,(uint32_t *)(readtemp),3);
	if(flag==1)
	{
	  *ReadData1=readtemp[0];
		*ReadData2=readtemp[1];
		*ReadData3=readtemp[2];
	}
	return flag;
#endif
}


volatile FLIGHT_PARAMETER Table_Parameter;
void WriteFlashParameter(uint16_t Label,
                         float WriteData,
                         volatile FLIGHT_PARAMETER *Table)
{
	__set_PRIMASK(1);          //关总中断
#if FLASH_EEPROM_ENABLE
  uint16_t i=0;
  ReadFlashParameterALL(Table);//先把片区内的所有数据都都出来
  Table->Parameter_Table[Label]=WriteData;//将需要更改的字段赋新值
  FLASH_UnlockBank1();
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
  Parameter_Table_FLASHStatus = FLASH_ErasePage(PARAMETER_TABLE_STARTADDR);
  if(Parameter_Table_FLASHStatus == FLASH_COMPLETE)
  {
    for(i=0;i<FLIGHT_PARAMETER_TABLE_NUM;i++)
    {
      Parameter_Table_FLASHStatus = FLASH_ProgramWord(PARAMETER_TABLE_STARTADDR + 4*i,*(uint32_t *)(&Table->Parameter_Table[i]));
    }
  }
  FLASH_LockBank1();
#else
	ReadFlashParameterALL(Table);//先把片区内的所有数据都都出来
  Table->Parameter_Table[Label]=WriteData;//将需要更改的字段赋新值	
	uint32_t WriteAddress = (uint32_t)(PARAMETER_TABLE_STARTADDR_EEPROM+Label*4);
	//W25QXX_Write_N_Data(WriteAddress,(float *)(&Table->Parameter_Table[Label]),1);
  W25QXX_Write_N_Data(PARAMETER_TABLE_STARTADDR_EEPROM,(uint32_t *)(&Table->Parameter_Table[0]),FLIGHT_PARAMETER_TABLE_NUM);
#endif
		__set_PRIMASK(0);          //开总中断
}


void WriteFlashParameter_Two(uint16_t Label,
                             float WriteData1,
                             float WriteData2,
                             volatile FLIGHT_PARAMETER *Table)
{
	__set_PRIMASK(1);          //关总中断
#if FLASH_EEPROM_ENABLE
  uint16_t i=0;
  ReadFlashParameterALL(Table);//先把片区内的所有数据都都出来
  Table->Parameter_Table[Label]=WriteData1;//将需要更改的字段赋新值
  Table->Parameter_Table[Label+1]=WriteData2;//将需要更改的字段赋新值
  FLASH_UnlockBank1();
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
  Parameter_Table_FLASHStatus = FLASH_ErasePage(PARAMETER_TABLE_STARTADDR);
  if(Parameter_Table_FLASHStatus == FLASH_COMPLETE)
  {
    for(i=0;i<FLIGHT_PARAMETER_TABLE_NUM;i++)
    {
      Parameter_Table_FLASHStatus = FLASH_ProgramWord(PARAMETER_TABLE_STARTADDR + 4*i,*(uint32_t *)(&Table->Parameter_Table[i]));
    }
  }
  FLASH_LockBank1();
#else
	uint32_t WriteAddress = (uint32_t)(PARAMETER_TABLE_STARTADDR_EEPROM+Label*4);
  ReadFlashParameterALL(Table);//先把片区内的所有数据都都出来
  Table->Parameter_Table[Label]=WriteData1;//将需要更改的字段赋新值
  Table->Parameter_Table[Label+1]=WriteData2;//将需要更改的字段赋新值
	//W25QXX_Write_N_Data(WriteAddress,(float *)(&Table->Parameter_Table[Label]),2);
  W25QXX_Write_N_Data(PARAMETER_TABLE_STARTADDR_EEPROM,(uint32_t *)(&Table->Parameter_Table[0]),FLIGHT_PARAMETER_TABLE_NUM);
#endif
  __set_PRIMASK(0);          //开总中断
}

void WriteFlashParameter_Three(uint16_t Label,
                               float WriteData1,
                               float WriteData2,
                               float WriteData3,
                               volatile FLIGHT_PARAMETER *Table)
{
	__set_PRIMASK(1);          //关总中断
#if FLASH_EEPROM_ENABLE
  uint16_t i=0;
  ReadFlashParameterALL(Table);//先把片区内的所有数据都都出来
  Table->Parameter_Table[Label]=WriteData1;//将需要更改的字段赋新值
  Table->Parameter_Table[Label+1]=WriteData2;//将需要更改的字段赋新值
  Table->Parameter_Table[Label+2]=WriteData3;//将需要更改的字段赋新值
  FLASH_UnlockBank1();
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
  Parameter_Table_FLASHStatus = FLASH_ErasePage(PARAMETER_TABLE_STARTADDR);
  if(Parameter_Table_FLASHStatus == FLASH_COMPLETE)
  {
    for(i=0;i<FLIGHT_PARAMETER_TABLE_NUM;i++)
    {
      Parameter_Table_FLASHStatus = FLASH_ProgramWord(PARAMETER_TABLE_STARTADDR + 4*i,*(uint32_t *)(&Table->Parameter_Table[i]));
    }
  }
  FLASH_LockBank1();
#else
	uint32_t WriteAddress = (uint32_t)(PARAMETER_TABLE_STARTADDR_EEPROM+Label*4);
  ReadFlashParameterALL(Table);//先把片区内的所有数据都都出来
  Table->Parameter_Table[Label]=WriteData1;//将需要更改的字段赋新值
  Table->Parameter_Table[Label+1]=WriteData2;//将需要更改的字段赋新值
	Table->Parameter_Table[Label+2]=WriteData3;//将需要更改的字段赋新值
	//W25QXX_Write_N_Data(WriteAddress,(float *)(&Table->Parameter_Table[Label]),3);
	W25QXX_Write_N_Data(PARAMETER_TABLE_STARTADDR_EEPROM,(uint32_t *)(&Table->Parameter_Table[0]),FLIGHT_PARAMETER_TABLE_NUM);
#endif
  __set_PRIMASK(0);          //开总中断
}

