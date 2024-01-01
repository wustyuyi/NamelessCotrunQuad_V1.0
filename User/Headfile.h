#ifndef _Headfile_H
#define _Headfile_H
/*----------------------------------------------------------------------------------------------------------------------/
*               本程序只供购买者学习使用，版权著作权属于无名科创团队，无名科创团队将飞控程序源码提供给购买者，
*               购买者要为无名科创团队提供保护，未经作者许可，不得将源代码提供给他人，不得将源代码放到网上供他人免费下载， 
*               更不能以此销售牟利，如发现上述行为，无名科创团队将诉之以法律解决！！！
-----------------------------------------------------------------------------------------------------------------------/
*               生命不息、奋斗不止；前人栽树，后人乘凉！！！
*               开源不易，且学且珍惜，祝早日逆袭、进阶成功！！！
*               学习优秀者，简历可推荐到DJI、ZEROTECH、XAG、AEE、GDU、AUTEL、EWATT、HIGH GREAT等公司就业
*               求职简历请发送：15671678205@163.com，需备注求职意向单位、岗位、待遇等
*               无名科创开源飞控QQ群：540707961
*               CSDN博客：http://blog.csdn.net/u011992534
*               优酷ID：NamelessCotrun无名小哥
*               B站教学视频：https://space.bilibili.com/67803559/#/video
*               客户使用心得、改进意见征集贴：http://www.openedv.com/forum.php?mod=viewthread&tid=234214&extra=page=1
*               淘宝店铺：https://shop348646912.taobao.com/?spm=2013.1.1000126.2.5ce78a88ht1sO2
*               百度贴吧:无名科创开源飞控
*               修改日期:2018/8/30
*               版本：慧飞者——V1.0.1
*               版权所有，盗版必究。
*               Copyright(C) 武汉科技大学无名科创团队 2017-2025
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

//GY86传感器  MPU6050（陀螺仪加速度计）+HMC5883L（磁力计）+MS5611（气压计）
//#define IMU_BOARD_GY86
//NC686传感器  MPU6050（陀螺仪加速度计）+IST8310（磁力计）+SPL06-001（气压计）
#define IMU_BOARD_NC686
//GY683传感器  MPU6050（陀螺仪加速度计）+IST8310（磁力计）+FBM320（气压计）
//#define IMU_BOARD_NC683


//超声波定高
#define HC_SR04  1
#define SD_Log_Enable 0

#define Int_Sort    (int16_t)
#define ABS(X)  (((X)>0)?(X):-(X))
#define MAX(a,b)  ((a)>(b)?(a):(b))
#define MIN(a,b)  ((a)<(b)?(a):(b))
/////////////////////////////////////////////////////////////////////////////////////
//数据拆分宏定义，在发送大于1字节的数据类型时，比如int16、float等，需要把数据拆分成单独字节进行发送
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
  uint16 Time_Delta_INT;//单位ms
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
//IO口地址映射
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

//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入


/*************板载硬件驱动头文件***********************/
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


/************IMU传感器头文件**************/
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
#include "US_100.h"     //超声波
#include "GPS.h"        //GPS M8N
#include "PX4FLOW.h"    //PX4FLOW光流传感器
//#include "ADNS3080.h" //APM光流传感器
//#include "BH1750.h"   //APM光流传感器
//#include "DHT11.h"    //温湿度传感器
#include "tofsense.h"
/*************姿态解算+滤波器+惯导+控制算法类头文件***********************/
#include "IMU.h"//姿态解算
#include "PID.h"//PID控制器
#include "NamelessCotrun_Ctrl.h"//飞控总控制器（位置+速度+加速度+姿态）
#include "SINS.h"//惯导融合
#include "Calibration.h"//传感器标定
#include "Filter.h"//传感器滤波
#include "Bling.h"//状态指示
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

