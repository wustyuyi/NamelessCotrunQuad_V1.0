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
#include "spl06_001.h"


float  spl_cal_data[9]={0};

#define PRESSURE_REG 0X00
#define TEMP_REG 0X03
#define PRS_CFG 0x06
#define TMP_CFG 0x07
#define MEAS_CFG 0x08

#define SPL06_REST_VALUE 0x09
#define SPL06_REST_REG 0x0C

#define PRODUCT_ID 0X0D

#define uint32 unsigned int

static struct spl0601_t spl0601;
static struct spl0601_t *p_spl0601;

void spl0601_write(uint8 hwadr, uint8 regadr, uint8 val);
uint8 spl0601_read(uint8 hwadr, uint8 regadr);
void spl0601_get_calib_param(void);


/*****************************************************************************
�� �� ��  : spl0601_write
��������  : I2C �Ĵ���д���Ӻ���
�������  : uint8 hwadr   Ӳ����ַ
uint8 regadr  �Ĵ�����ַ
uint8 val     ֵ
�������  : ��
�� �� ֵ  :
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2015��11��30��
��    ��   : WL
�޸�����   : �����ɺ���

*****************************************************************************/
void spl0601_write(unsigned char hwadr, unsigned char regadr, unsigned char val)
{
  //	hwI2C0_Device_Addr = hwadr;
  //	bI2C0_TxM_Data[0] = regadr;
  //	bI2C0_TxM_Data[1] = val;
  //
  //	I2C0_Engine(2,0,0);
  Single_WriteI2C(hwadr,regadr,val);
}

/*****************************************************************************
�� �� ��  : spl0601_read
��������  : I2C �Ĵ�����ȡ�Ӻ���
�������  : uint8 hwadr   Ӳ����ַ
uint8 regadr  �Ĵ�����ַ
�������  :
�� �� ֵ  : uint8 ����ֵ
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2015��11��30��
��    ��   : WL
�޸�����   : �����ɺ���

*****************************************************************************/
uint8 spl0601_read(unsigned char hwadr, unsigned char regadr)
{
  uint8 reg_data;
  
  //	hwI2C0_Device_Addr = hwadr;
  //	bI2C0_TxM_Data[0] = regadr; //
  //	I2C0_Engine(1,1,1);
  
  //	reg_data = bI2C0_RxM_Data[0];
  reg_data=Single_ReadI2C(hwadr,regadr);
  return reg_data;
}

/*****************************************************************************
�� �� ��  : spl0601_init
��������  : SPL06-01 ��ʼ������
�������  : void
�������  : ��
�� �� ֵ  :
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2015��11��30��
��    ��   : WL
�޸�����   : �����ɺ���

*****************************************************************************/
void spl0601_init(void)
{
  p_spl0601 = &spl0601; /* read Chip Id */
  p_spl0601->i32rawPressure = 0;
  p_spl0601->i32rawTemperature = 0;
  p_spl0601->chip_id = 0x34;
  spl0601_get_calib_param();
	
  spl_cal_data[0]=p_spl0601->calib_param.c0;
	spl_cal_data[1]=p_spl0601->calib_param.c1;
	spl_cal_data[2]=p_spl0601->calib_param.c00;
	spl_cal_data[3]=p_spl0601->calib_param.c10;
	spl_cal_data[4]=p_spl0601->calib_param.c01;
	spl_cal_data[5]=p_spl0601->calib_param.c01;
	spl_cal_data[6]=p_spl0601->calib_param.c20;
	spl_cal_data[7]=p_spl0601->calib_param.c21;
	spl_cal_data[8]=p_spl0601->calib_param.c30;
}

void SPL06_Init(void)//��ѹ�Ƴ�ʼ������
{
  // sampling rate = 32Hz; Pressure oversample = 8;
  // spl0601_rateset(PRESSURE_SENSOR,32, 8);
  // sampling rate = 32Hz; Temperature oversample = 8;
  // spl0601_rateset(TEMPERATURE_SENSOR,32, 8);
  //spl0601_rateset(PRESSURE_SENSOR,128, 32);
  spl0601_rateset(PRESSURE_SENSOR,64, 32);
  // sampling rate = 1Hz; Temperature oversample = 1;
  spl0601_rateset(TEMPERATURE_SENSOR,128, 2);
  //Start background measurement
  spl0601_start_continuous(CONTINUOUS_P_AND_T);
}



/*****************************************************************************
�� �� ��  : spl0601_rateset
��������  :  �����¶ȴ�������ÿ����������Լ���������
�������  : uint8 u8OverSmpl  ��������         Maximal = 128
uint8 u8SmplRate  ÿ���������(Hz) Maximal = 128
uint8 iSensor     0: Pressure; 1: Temperature
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2015��11��24��
��    ��   : WL
�޸�����   : �����ɺ���

*****************************************************************************/
void spl0601_rateset(uint8 iSensor, uint8 u8SmplRate, uint8 u8OverSmpl)
{
  uint8 reg = 0;
  int32 i32kPkT = 0;
  switch(u8SmplRate)
  {
  case 2:
    reg |= (1<<4);//���ƶ�4λ��ԭ5λ����ԭ���ṩ���������⣬20180410����С���
    break;
  case 4:
    reg |= (2<<4);
    break;
  case 8:
    reg |= (3<<4);
    break;
  case 16:
    reg |= (4<<4);
    break;
  case 32:
    reg |= (5<<4);
    break;
  case 64:
    reg |= (6<<4);
    break;
  case 128:
    reg |= (7<<4);
    break;
  case 1:
  default:
    break;
  }
  switch(u8OverSmpl)
  {
  case 2:
    reg |= 1;
    i32kPkT = 1572864;
    break;
  case 4:
    reg |= 2;
    i32kPkT = 3670016;
    break;
  case 8:
    reg |= 3;
    i32kPkT = 7864320;
    break;
  case 16:
    i32kPkT = 253952;
    reg |= 4;
    break;
  case 32:
    i32kPkT = 516096;
    reg |= 5;
    break;
  case 64:
    i32kPkT = 1040384;
    reg |= 6;
    break;
  case 128:
    i32kPkT = 2088960;
    reg |= 7;
    break;
  case 1:
  default:
    i32kPkT = 524288;
    break;
  }
  
  if(iSensor == 0)
  {
    p_spl0601->i32kP = i32kPkT;
    spl0601_write(HW_ADR, 0x06, reg);
    if(u8OverSmpl > 8)
    {
      reg = spl0601_read(HW_ADR, 0x09);
      spl0601_write(HW_ADR, 0x09, reg | 0x04);
    }
  }
  if(iSensor == 1)
  {
    p_spl0601->i32kT = i32kPkT;
    spl0601_write(HW_ADR, 0x07, reg|0x80);  //Using mems temperature
    if(u8OverSmpl > 8)
    {
      reg = spl0601_read(HW_ADR, 0x09);
      spl0601_write(HW_ADR, 0x09, reg | 0x08);
    }
  }
}

/*****************************************************************************
�� �� ��  : spl0601_get_calib_param
��������  : ��ȡУ׼����
�������  : void
�������  : ��
�� �� ֵ  :
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2015��11��30��
��    ��   : WL
�޸�����   : �����ɺ���

*****************************************************************************/
void spl0601_get_calib_param(void)
{
  uint32 h;
  uint32 m;
  uint32 l;
  h =  spl0601_read(HW_ADR, 0x10);
  l  =  spl0601_read(HW_ADR, 0x11);
  p_spl0601->calib_param.c0 = (int16)h<<4 | l>>4;
  p_spl0601->calib_param.c0 = (p_spl0601->calib_param.c0&0x0800)?(0xF000|p_spl0601->calib_param.c0):p_spl0601->calib_param.c0;
  h =  spl0601_read(HW_ADR, 0x11);
  l  =  spl0601_read(HW_ADR, 0x12);
  p_spl0601->calib_param.c1 = (int16)(h&0x0F)<<8 | l;
  p_spl0601->calib_param.c1 = (p_spl0601->calib_param.c1&0x0800)?(0xF000|p_spl0601->calib_param.c1):p_spl0601->calib_param.c1;
  h =  spl0601_read(HW_ADR, 0x13);
  m =  spl0601_read(HW_ADR, 0x14);
  l =  spl0601_read(HW_ADR, 0x15);
  p_spl0601->calib_param.c00 = (int32)h<<12 | (int32)m<<4 | (int32)l>>4;
  p_spl0601->calib_param.c00 = (p_spl0601->calib_param.c00&0x080000)?(0xFFF00000|p_spl0601->calib_param.c00):p_spl0601->calib_param.c00;
  h =  spl0601_read(HW_ADR, 0x15);
  m =  spl0601_read(HW_ADR, 0x16);
  l =  spl0601_read(HW_ADR, 0x17);
  p_spl0601->calib_param.c10 = (int32)h<<16 | (int32)m<<8 | l;
  p_spl0601->calib_param.c10 = (p_spl0601->calib_param.c10&0x080000)?(0xFFF00000|p_spl0601->calib_param.c10):p_spl0601->calib_param.c10;
  h =  spl0601_read(HW_ADR, 0x18);
  l  =  spl0601_read(HW_ADR, 0x19);
  p_spl0601->calib_param.c01 = (int16)h<<8 | l;
  h =  spl0601_read(HW_ADR, 0x1A);
  l  =  spl0601_read(HW_ADR, 0x1B);
  p_spl0601->calib_param.c11 = (int16)h<<8 | l;
  h =  spl0601_read(HW_ADR, 0x1C);
  l  =  spl0601_read(HW_ADR, 0x1D);
  p_spl0601->calib_param.c20 = (int16)h<<8 | l;
  h =  spl0601_read(HW_ADR, 0x1E);
  l  =  spl0601_read(HW_ADR, 0x1F);
  p_spl0601->calib_param.c21 = (int16)h<<8 | l;
  h =  spl0601_read(HW_ADR, 0x20);
  l  =  spl0601_read(HW_ADR, 0x21);
  p_spl0601->calib_param.c30 = (int16)h<<8 | l;
}


/*****************************************************************************
�� �� ��  : spl0601_start_temperature
��������  : ����һ���¶Ȳ���
�������  : void
�������  : ��
�� �� ֵ  :
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2015��11��30��
��    ��   : WL
�޸�����   : �����ɺ���

*****************************************************************************/
void spl0601_start_temperature(void)
{
  spl0601_write(HW_ADR, 0x08, 0x02);
}

/*****************************************************************************
�� �� ��  : spl0601_start_pressure
��������  : ����һ��ѹ��ֵ����
�������  : void
�������  : ��
�� �� ֵ  :
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2015��11��30��
��    ��   : WL
�޸�����   : �����ɺ���

*****************************************************************************/
void spl0601_start_pressure(void)
{
  spl0601_write(HW_ADR, 0x08, 0x01);
}

/*****************************************************************************
�� �� ��  : spl0601_start_continuous
��������  : Select node for the continuously measurement
�������  : uint8 mode  1: pressure; 2: temperature; 3: pressure and temperature
�������  : ��
�� �� ֵ  :
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2015��11��25��
��    ��   : WL
�޸�����   : �����ɺ���

*****************************************************************************/
void spl0601_start_continuous(uint8 mode)
{
  spl0601_write(HW_ADR, 0x08, mode+4);
}


/*****************************************************************************
�� �� ��  : spl0601_get_raw_temp
��������  : ��ȡ�¶ȵ�ԭʼֵ����ת����32Bits����
�������  : void
�������  : ��
�� �� ֵ  :
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2015��11��30��
��    ��   : WL
�޸�����   : �����ɺ���

*****************************************************************************/
void spl0601_get_raw_temp(void)
{
  uint8 h[3] = {0};
  h[0] = spl0601_read(HW_ADR, 0x03);
  h[1] = spl0601_read(HW_ADR, 0x04);
  h[2] = spl0601_read(HW_ADR, 0x05);
  p_spl0601->i32rawTemperature = (int32)h[0]<<16 | (int32)h[1]<<8 | (int32)h[2];
  p_spl0601->i32rawTemperature= (p_spl0601->i32rawTemperature&0x800000) ? (0xFF000000|p_spl0601->i32rawTemperature) : p_spl0601->i32rawTemperature;
}

/*****************************************************************************
�� �� ��  : spl0601_get_raw_pressure
��������  : ��ȡѹ��ԭʼֵ����ת����32bits����
�������  : void
�������  : ��
�� �� ֵ  :
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2015��11��30��
��    ��   : WL
�޸�����   : �����ɺ���

*****************************************************************************/
void spl0601_get_raw_pressure(void)
{
  uint8 h[3];
  h[0] = spl0601_read(HW_ADR, 0x00);
  h[1] = spl0601_read(HW_ADR, 0x01);
  h[2] = spl0601_read(HW_ADR, 0x02);
  p_spl0601->i32rawPressure = (int32)h[0]<<16 | (int32)h[1]<<8 | (int32)h[2];
  p_spl0601->i32rawPressure= (p_spl0601->i32rawPressure&0x800000) ? (0xFF000000|p_spl0601->i32rawPressure) : p_spl0601->i32rawPressure;
}


/*****************************************************************************
�� �� ��  : spl0601_get_temperature
��������  : �ڻ�ȡԭʼֵ�Ļ����ϣ����ظ���У׼����¶�ֵ
�������  : void
�������  : ��
�� �� ֵ  :
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2015��11��30��
��    ��   : WL
�޸�����   : �����ɺ���

*****************************************************************************/
float spl0601_get_temperature(void)
{
  float fTCompensate;
  float fTsc;
  
  fTsc = p_spl0601->i32rawTemperature / (float)p_spl0601->i32kT;
  fTCompensate =  p_spl0601->calib_param.c0 * 0.5 + p_spl0601->calib_param.c1 * fTsc;
  return fTCompensate;
}

/*****************************************************************************
�� �� ��  : spl0601_get_pressure
��������  : �ڻ�ȡԭʼֵ�Ļ����ϣ����ظ���У׼���ѹ��ֵ
�������  : void
�������  : ��
�� �� ֵ  :
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2015��11��30��
��    ��   : WL
�޸�����   : �����ɺ���

*****************************************************************************/
float spl0601_get_pressure(void)
{
  float fTsc, fPsc;
  float qua2, qua3;
  float fPCompensate;
  
  fTsc = p_spl0601->i32rawTemperature / (float)p_spl0601->i32kT;
  fPsc = p_spl0601->i32rawPressure / (float)p_spl0601->i32kP;
  qua2 = p_spl0601->calib_param.c10 + fPsc * (p_spl0601->calib_param.c20 + fPsc* p_spl0601->calib_param.c30);
  qua3 = fTsc * fPsc * (p_spl0601->calib_param.c11 + fPsc * p_spl0601->calib_param.c21);
  //qua3 = 0.9f *fTsc * fPsc * (p_spl0601->calib_param.c11 + fPsc * p_spl0601->calib_param.c21);
  
  fPCompensate = p_spl0601->calib_param.c00 + fPsc * qua2 + fTsc * p_spl0601->calib_param.c01 + qua3;
  //fPCompensate = p_spl0601->calib_param.c00 + fPsc * qua2 + 0.9f *fTsc  * p_spl0601->calib_param.c01 + qua3;
  return fPCompensate;
}



float temperature;
float pressure;
uint8_t baro_flag=0;
float user_spl0601_get()
{
  static uint16_t spl06_cnt=0;
  spl06_cnt++;
  if(spl06_cnt==1)//1
  {
    spl0601_get_raw_temp();
    temperature = spl0601_get_temperature();
  }
  else  if(spl06_cnt==22)//105ms
  {
    spl0601_get_raw_pressure();
    pressure = spl0601_get_pressure();
    spl06_cnt=0;
    baro_flag=1;
  }
  return 0;
}



float true_Altitude=0;
float SPL06_001_Offset=0;
float Get_Altitude_SPL06_001(float baroPress)
{
  float Tempbaro=(float)(baroPress/SPL06_001_Offset)*1.0;
  true_Altitude = 4433000.0f * (1 - powf((float)(Tempbaro),0.190295f));
  return true_Altitude;
}

uint8 SPL06_001_Offset_Okay=0;
uint8 SPL06_001_Finished=0;
float SPL06_001_Filter_P,SPL06_001_Filter_high;
unsigned int SPL06_001_Cnt=0;
/***************************************************
������: void SPL06_001_StateMachine(void)
˵��:	��ѹ�Ƹ���״̬��
���:	��
����:	��
��ע:	��ѹ���¶Ƚ���ɼ������ı��������
        �����״̬��ʱ��        
ע���ߣ�����С��
****************************************************/

void SPL06_001_StateMachine(void)
{
  user_spl0601_get();
  if(SPL06_001_Cnt<=50)  SPL06_001_Cnt++;
  if(SPL06_001_Cnt==49)
  {
    SPL06_001_Offset_Okay=1;
    High_Okay_flag=1;
    SPL06_001_Offset=pressure;
    if(SPL06_001_Offset_Okay==1)//��ʼ��ѹ����������
    {
      SPL06_001_Filter_P=pressure;
      SPL06_001_Filter_high=Get_Altitude_SPL06_001(SPL06_001_Filter_P);
      Baro_Show.Offset_Pressure=SPL06_001_Filter_P;
    }
    Strapdown_INS_Reset(&NamelessQuad,_YAW,SPL06_001_Filter_high,0);
  }
  
  if(SPL06_001_Offset_Okay==1
     &&baro_flag==1)//��ʼ��ѹ����������
  {
    baro_flag=0;
    Baro_Show.Raw_Pressure=SPL06_001_Filter_P=pressure;
    
    Baro_Show.High=SPL06_001_Filter_high=Get_Altitude_SPL06_001(SPL06_001_Filter_P);
		WP_Sensor.baro_altitude=Baro_Show.High;
    Baro_Show.Climbrate=(Baro_Show.High-Baro_Show.Last_High)/0.110;//��ѹ�Ƽ���õ��������ٶȣ���λcm/s
    Baro_Show.Last_High=Baro_Show.High;
  }
  
}

