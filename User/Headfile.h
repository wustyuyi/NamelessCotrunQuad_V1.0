#ifndef _Headfile_H
#define _Headfile_H
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
/***************************觉得不错，欢迎打赏，请小哥吃热干面：支付宝账号：1094744141@qq.com*********************************/
#define PI 3.1415926535898
#define CNTLCYCLE  0.005f
#define AHRS_DT  0.005f
#define Delta 0.005f
#define Dt 0.005f
#define _YAW    0
#define _PITCH  1
#define _ROLL   2
//GY86传感器  MPU6050（陀螺仪加速度计）+HMC5883L（磁力计）+MS5611（气压计）
//#define IMU_BOARD_GY86
//NC686传感器  MPU6050（陀螺仪加速度计）+IST8310（磁力计）+SPL06-001（气压计）
#define IMU_BOARD_NC686
//GY683传感器  MPU6050（陀螺仪加速度计）+IST8310（磁力计）+FBM320（气压计）
//#define IMU_BOARD_NC683
//超声波定高
//#define HC_SR04


#define Int_Sort    (int16_t)
#define ABS(X)  (((X)>0)?(X):-(X))
#define MAX(a,b)  ((a)>(b)?(a):(b))
#define MIN(a,b)  ((a)<(b)?(a):(b))
/////////////////////////////////////////////////////////////////////////////////////
//数据拆分宏定义，在发送大于1字节的数据类型时，比如int16、float等，需要把数据拆分成单独字节进行发送
#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)      ) )
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )
#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )
#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )
//#define BYTE3(x)  (uint8_t)((x>>24)&0x00ff)
//#define BYTE2(x)  (uint8_t)((x>>16)&0x00ff)
//#define BYTE1(x)  (uint8_t)((x>>8)&0x00ff)
//#define BYTE0(x)  (uint8_t)((x)&0x00ff)


#include "math.h"
#include "stdio.h"
#include "stdint.h"
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

typedef   signed           char int8;
typedef unsigned           char uint8;
typedef unsigned           char byte;
typedef   signed short     int int16;
typedef unsigned short     int uint16;

typedef enum{
  false = 0,
  true = !false
}bool;

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
 float E;
 float N;
 float U;
}Vector3_Nav;

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
#include "PPM.h"
#include "FLASH.h"
#include "USART.h"
#include "DELAY.h"
#include "SYSTEM.h"
#include "OLED.h"
#include "IIC.h"
#include "TIME.h"
#include "PWM.h"

#include "Time_Cnt.h"
#include "KEY.h"
#include "SPI1.h"


#include "SPI2.h"
#include "NRF24L01.H"


/************IMU传感器头文件**************/
#include "MPU6050.h"
#ifdef  IMU_BOARD_GY86
  #include "MS5611.h"
  #include "HMC5883.h"
#endif

#ifdef IMU_BOARD_NC686
  #include "IST8310.h"
  #include "SPL06_001.h"
#endif

#ifdef IMU_BOARD_NC683
  #include "IST8310.h"
  #include "FBM320.h"
#endif

#include "US_100.h"     //超声波
#include "GPS.h"        //GPS M8N
#include "PX4FLOW.h"    //PX4FLOW光流传感器
//#include "ADNS3080.h" //APM光流传感器
//#include "BH1750.h"   //APM光流传感器
//#include "DHT11.h"    //温湿度传感器
/*************姿态解算+滤波器+惯导+控制算法类头文件***********************/
#include "IMU.h"//姿态解算
#include "PID.h"//PID控制器
#include "NamelessCorun_Ctrl.h"//飞控总控制器（位置+速度+加速度+姿态）
#include "SINS.h"//惯导融合
#include "Calibration.h"//传感器标定
#include "Filter.h"//传感器滤波
#include "Bling.h"//状态指示
//#include "ADRC.h"
//#include "NamelessCorun_OpticalFlow.h"

#define RDY_LED  GPIO_Pin_5
#define GPS_LED  GPIO_Pin_10
#define LTC_LED  GPIO_Pin_4
#define WORK_LED GPIO_Pin_5


//#define RC_NRF24L01  0
#define RC_PPM  1

typedef struct
{
  uint16 NRF24L01_Okay:1;
  uint16 MPU6050_Okay:1;
  uint16 Mag_Okay:1;
  uint16 Baro_Okay:1;
}Sensor_Okay_Flag;
/***************************觉得不错，欢迎打赏，请小哥吃热干面：支付宝账号：1094744141@qq.com*********************************/
extern float AirPresure_Altitude;
extern u32 Test_Cnt1,Test_Cnt2;
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