
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
#ifndef _SPL06_001_H
#define _SPL06_001_H
#include <stm32f10x.h>

#define s32 int32
#define int16 short
#define int32 int
#define uint8 unsigned char
//#define HW_ADR 0x77 //SDO HIGH OR NC
#define HW_ADR (0x76<<1) //SDO LOW
#define CONTINUOUS_PRESSURE     1
#define CONTINUOUS_TEMPERATURE  2
#define CONTINUOUS_P_AND_T      3
#define PRESSURE_SENSOR     0
#define TEMPERATURE_SENSOR  1


struct spl0601_calib_param_t {
  int16 c0;
  int16 c1;
  int32 c00;
  int32 c10;
  int16 c01;
  int16 c11;
  int16 c20;
  int16 c21;
  int16 c30;
};

struct spl0601_t {
  struct spl0601_calib_param_t calib_param;/**<calibration data*/
  uint8 chip_id; /**<chip id*/
  int32 i32rawPressure;
  int32 i32rawTemperature;
  int32 i32kP;
  int32 i32kT;
};

extern float temperature,temperature2,baro_Offset;
extern unsigned char baro_start;
extern float SPL06_001_Filter_P,SPL06_001_Filter_high,SPL06_001_Offset;
extern uint8 SPL06_001_Offset_Okay;
extern float spl_cal_data[9];

void SPL06_Init(void);
void spl0601_init(void);
void spl0601_rateset(uint8 iSensor, uint8 u8OverSmpl, uint8 u8SmplRate);
void spl0601_start_temperature(void);
void spl0601_start_pressure(void);
void spl0601_start_continuous(uint8 mode);
void spl0601_get_raw_temp(void);
void spl0601_get_raw_pressure(void);
float spl0601_get_temperature(void);
float spl0601_get_pressure(void);
float user_spl0601_get(void);

void SPL06_001_StateMachine(void);


#endif

