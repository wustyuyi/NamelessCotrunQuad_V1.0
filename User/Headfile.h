#ifndef _Headfile_H
#define _Headfile_H
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
#define PI 3.1415926535898
#define CNTLCYCLE  0.005f
#define AHRS_DT  0.005f
#define Delta 0.005f
#define Dt 0.005f
#define _YAW    0
#define _PITCH  1
#define _ROLL   2

#define Sampling_Freq 200//200hz

//GY86������  MPU6050�������Ǽ��ٶȼƣ�+HMC5883L�������ƣ�+MS5611����ѹ�ƣ�
//#define IMU_BOARD_GY86
//NC686������  MPU6050�������Ǽ��ٶȼƣ�+IST8310�������ƣ�+SPL06-001����ѹ�ƣ�
#define IMU_BOARD_NC686
//GY683������  MPU6050�������Ǽ��ٶȼƣ�+IST8310�������ƣ�+FBM320����ѹ�ƣ�
//#define IMU_BOARD_NC683


//����������
#define HC_SR04  1
#define SD_Log_Enable 0

#define Int_Sort    (int16_t)
#define ABS(X)  (((X)>0)?(X):-(X))
#define MAX(a,b)  ((a)>(b)?(a):(b))
#define MIN(a,b)  ((a)<(b)?(a):(b))
/////////////////////////////////////////////////////////////////////////////////////
//���ݲ�ֺ궨�壬�ڷ��ʹ���1�ֽڵ���������ʱ������int16��float�ȣ���Ҫ�����ݲ�ֳɵ����ֽڽ��з���
//#define BYTE3(x)  (uint8_t)((x>>24)&0x00ff)
//#define BYTE2(x)  (uint8_t)((x>>16)&0x00ff)
//#define BYTE1(x)  (uint8_t)((x>>8)&0x00ff)
//#define BYTE0(x)  (uint8_t)((x)&0x00ff)


#include "math.h"
#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"
#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "misc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_conf.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_flash.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_i2c.h"
#include "mass_mal.h"
#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h"
#include "memory.h"	    
#include "usb_bot.h"  
#include "malloc.h"	 
#include "diskio.h"
#include "exfuns.h"
#include "fattester.h"
#include "w25qxx.h"
#include "copyright.h"
#include "arm_math.h"
#include "HW_Config.h"
#include "Queue.h"
#include "ringbuf.h"
#include "NCLink.h"



typedef   signed           char int8;
typedef unsigned           char uint8;
typedef unsigned           char byte;
typedef   signed short     int int16;
typedef unsigned short     int uint16;



typedef struct
{
  int32_t x;
  int32_t y;
}Vector2i;

typedef struct
{
  float x;
  float y;
}Vector2f;


typedef struct
{
  float x;
  float y;
  float z;
}Vector3f;


typedef struct
{
  float q0;
  float q1;
  float q2;
  float q3;
}Vector4q;


typedef struct
{
  int16_t x;
  int16_t y;
  int16_t z;
}Vector3i;



typedef struct
{
  float E;
  float N;
  float U;
}Vector3_Nav;

typedef struct
{
  float E;
  float N;
}Vector2f_Nav;



typedef struct
{
  int32_t lat;
  int32_t lng;
}Vector2_Nav;



typedef struct
{
  float x;
  float y;
  float z;
}Vector3_Body;


typedef struct
{
  float Pit;
  float Rol;
}Vector2_Ang;


typedef struct
{
  float Pit;
  float Rol;
}Vector2_Body;


typedef struct
{
  float Pit;
  float Rol;
  float Yaw;
}Vector3f_Body;


typedef struct
{
  float North;
  float East;
}Vector2_Earth;

typedef struct
{
  Vector3f a;
  Vector3f b;
  Vector3f c;
}Matrix3f;

typedef struct
{
  float Last_Time;
  float Now_Time;
  float Time_Delta;
  uint16 Time_Delta_INT;//��λms
}Testime;


typedef struct
{
  float max;
  float min;
  float middle;
  float deadband;
}Vector_RC;

//#define true  true
//#define false false


typedef union
{
	unsigned char Bdata[4];
	float Fdata;
	uint32_t Idata;
}Float_2_Byte;



typedef struct
{
  Vector3f gyro_raw;
  Vector3f accel_raw;
  Vector3f mag_raw;
	float acce_filter[3];
	float temperature;
  float baro_temp_raw;
	float baro_pressure_raw;
	float baro_presure_offset;
	float baro_altitude;
	float last_baro_altitude;
	float baro_altitude_div;
	float last_baro_altitude_div;
	float baro_altitude_acc;
	uint8_t imu_updtate_flag;
	uint8_t baro_updtate_flag;
	uint8_t us100_updtate_flag;
	uint8_t tfmini_updtate_flag;
}Sensor;


#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2))
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr))
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum))
//IO�ڵ�ַӳ��
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08

//IO�ڲ���,ֻ�Ե�һ��IO��!
//ȷ��n��ֵС��16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //���
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //����

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //���
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //����

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //���
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //����

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //���
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //����

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //���
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //����

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //���
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //����

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //���
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //����


/*************����Ӳ������ͷ�ļ�***********************/
#include "SBUS.h"
#include "PPM.h"
#include "FLASH.h"
#include "mmc_sd.h"	
#include "USART.h"
#include "DELAY.h"
#include "SYSTEM.h"
#include "OLED.h"
#include "ssd1306.h"
#include "IIC.h"
#include "TIME.h"
#include "PWM.h"
#include "ADC.h"
#include "Time_Cnt.h"
#include "KEY.h"
#include "SPI1.h"
#include "OpticalFlow_LC306.h"
#include "Temperature_Ctrl.h"

#include "SPI2.h"
#include "NRF24L01.H"


/************IMU������ͷ�ļ�**************/
#include "MPU6050.h"
#ifdef  IMU_BOARD_GY86
#include "MS5611.h"
#endif

#include "HMC5883.h"

#ifdef IMU_BOARD_NC686
#include "IST8310.h"
#include "SPL06_001.h"
#endif

#ifdef IMU_BOARD_NC683
#include "IST8310.h"
#include "FBM320.h"
#endif
#include "QMC5883.h"
#include "US_100.h"     //������
#include "GPS.h"        //GPS M8N
#include "PX4FLOW.h"    //PX4FLOW����������
//#include "ADNS3080.h" //APM����������
//#include "BH1750.h"   //APM����������
//#include "DHT11.h"    //��ʪ�ȴ�����
#include "tofsense.h"
/*************��̬����+�˲���+�ߵ�+�����㷨��ͷ�ļ�***********************/
#include "IMU.h"//��̬����
#include "PID.h"//PID������
#include "NamelessCotrun_Ctrl.h"//�ɿ��ܿ�������λ��+�ٶ�+���ٶ�+��̬��
#include "SINS.h"//�ߵ��ں�
#include "Calibration.h"//�������궨
#include "Filter.h"//�������˲�
#include "Bling.h"//״ָ̬ʾ
#include "ADRC.h"
#include "NamelessCotrun_OpticalFlow.h"
#include "OpticalFlow_Control.h"
#include "alt_ekf.h"
#include "control_config.h"
#include "control_althold.h"
#include "Flight_Parameter_Table.h"
#include "Flight_Control_Fault.h"
#include "NamelessCotrun_SDK.h"
/*********Mavlink**********************/


#define LTC_LED  GPIO_Pin_12
#define RDY_LED  GPIO_Pin_13
#define GPS_LED  GPIO_Pin_14
#define WORK_LED GPIO_Pin_15


//#define RC_NRF24L01  0
#define RC_PPM  1

typedef struct
{
  uint16 NRF24L01_Okay:1;
  uint16 MPU6050_Okay:1;
  uint16 Mag_Okay:1;
  uint16 Baro_Okay:1;
}Sensor_Okay_Flag;





extern float AirPresure_Altitude;
extern u32 Test_Cnt1[2],Test_Cnt2[2];
extern Sensor_Okay_Flag Sensor_Init_Flag;
extern uint16_t High_Okay_flag;

#endif

/*----------------------------------------------------------------------------------------------------------------------/
*               ������ֻ��������ѧϰʹ�ã���Ȩ����Ȩ���������ƴ��Ŷӣ�
*               �����ƴ��Ŷӽ��ɿس���Դ���ṩ�������ߣ�
*               ������ҪΪ�����ƴ��Ŷ��ṩ������
*               δ��������ɣ����ý�Դ�����ṩ������
*               ���ý�Դ����ŵ����Ϲ�����������أ�
*               �������Դ�����Ĳ�����緢��������Ϊ��
*               �����ƴ��Ŷӽ���֮�Է��ɽ��������
-----------------------------------------------------------------------------------------------------------------------/
*               ������Ϣ���ܶ���ֹ��ǰ�����������˳���������
*               ��Դ���ף���ѧ����ϧ��ף������Ϯ�����׳ɹ�������
-----------------------------------------------------------------------------------------------------------------------/
*		�����ƴ���Դ�ɿ� V1.1	�人�Ƽ���ѧ  By.YuYi
*		CSDN����: http://blog.csdn.net/u011992534
*               �ſ�ID��NamelessCotrun����С��
*               �����ƴ���Դ�ɿ�QQȺ��540707961
*               https://shop348646912.taobao.com/?spm=2013.1.1000126.2.5ce78a88ht1sO2
*               �ٶ�����:�����ƴ���Դ�ɿ�
*               �޸�����:2017/10/30
*               �汾��V1.1
*               ��Ȩ���У�����ؾ���
*               Copyright(C) �人�Ƽ���ѧ�����ƴ��Ŷ� 2017-2019
*               All rights reserved
----------------------------------------------------------------------------------------------------------------------*/

