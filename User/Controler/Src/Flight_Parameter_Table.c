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
#include "Flight_Parameter_Table.h"

volatile FLASH_Status Parameter_Table_FLASHStatus = FLASH_COMPLETE;      //Flash����״̬����

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
  for(i=0;i<4;i++)//���ֽ�����
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
  for(i=0;i<8;i++)//���ֽ�����
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
  for(i=0;i<12;i++)//���ֽ�����
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
	__set_PRIMASK(1);          //�����ж�
#if FLASH_EEPROM_ENABLE
  uint16_t i=0;
  ReadFlashParameterALL(Table);//�Ȱ�Ƭ���ڵ��������ݶ�������
  Table->Parameter_Table[Label]=WriteData;//����Ҫ���ĵ��ֶθ���ֵ
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
	ReadFlashParameterALL(Table);//�Ȱ�Ƭ���ڵ��������ݶ�������
  Table->Parameter_Table[Label]=WriteData;//����Ҫ���ĵ��ֶθ���ֵ	
	uint32_t WriteAddress = (uint32_t)(PARAMETER_TABLE_STARTADDR_EEPROM+Label*4);
	//W25QXX_Write_N_Data(WriteAddress,(float *)(&Table->Parameter_Table[Label]),1);
  W25QXX_Write_N_Data(PARAMETER_TABLE_STARTADDR_EEPROM,(uint32_t *)(&Table->Parameter_Table[0]),FLIGHT_PARAMETER_TABLE_NUM);
#endif
		__set_PRIMASK(0);          //�����ж�
}


void WriteFlashParameter_Two(uint16_t Label,
                             float WriteData1,
                             float WriteData2,
                             volatile FLIGHT_PARAMETER *Table)
{
	__set_PRIMASK(1);          //�����ж�
#if FLASH_EEPROM_ENABLE
  uint16_t i=0;
  ReadFlashParameterALL(Table);//�Ȱ�Ƭ���ڵ��������ݶ�������
  Table->Parameter_Table[Label]=WriteData1;//����Ҫ���ĵ��ֶθ���ֵ
  Table->Parameter_Table[Label+1]=WriteData2;//����Ҫ���ĵ��ֶθ���ֵ
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
  ReadFlashParameterALL(Table);//�Ȱ�Ƭ���ڵ��������ݶ�������
  Table->Parameter_Table[Label]=WriteData1;//����Ҫ���ĵ��ֶθ���ֵ
  Table->Parameter_Table[Label+1]=WriteData2;//����Ҫ���ĵ��ֶθ���ֵ
	//W25QXX_Write_N_Data(WriteAddress,(float *)(&Table->Parameter_Table[Label]),2);
  W25QXX_Write_N_Data(PARAMETER_TABLE_STARTADDR_EEPROM,(uint32_t *)(&Table->Parameter_Table[0]),FLIGHT_PARAMETER_TABLE_NUM);
#endif
  __set_PRIMASK(0);          //�����ж�
}

void WriteFlashParameter_Three(uint16_t Label,
                               float WriteData1,
                               float WriteData2,
                               float WriteData3,
                               volatile FLIGHT_PARAMETER *Table)
{
	__set_PRIMASK(1);          //�����ж�
#if FLASH_EEPROM_ENABLE
  uint16_t i=0;
  ReadFlashParameterALL(Table);//�Ȱ�Ƭ���ڵ��������ݶ�������
  Table->Parameter_Table[Label]=WriteData1;//����Ҫ���ĵ��ֶθ���ֵ
  Table->Parameter_Table[Label+1]=WriteData2;//����Ҫ���ĵ��ֶθ���ֵ
  Table->Parameter_Table[Label+2]=WriteData3;//����Ҫ���ĵ��ֶθ���ֵ
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
  ReadFlashParameterALL(Table);//�Ȱ�Ƭ���ڵ��������ݶ�������
  Table->Parameter_Table[Label]=WriteData1;//����Ҫ���ĵ��ֶθ���ֵ
  Table->Parameter_Table[Label+1]=WriteData2;//����Ҫ���ĵ��ֶθ���ֵ
	Table->Parameter_Table[Label+2]=WriteData3;//����Ҫ���ĵ��ֶθ���ֵ
	//W25QXX_Write_N_Data(WriteAddress,(float *)(&Table->Parameter_Table[Label]),3);
	W25QXX_Write_N_Data(PARAMETER_TABLE_STARTADDR_EEPROM,(uint32_t *)(&Table->Parameter_Table[0]),FLIGHT_PARAMETER_TABLE_NUM);
#endif
  __set_PRIMASK(0);          //�����ж�
}

