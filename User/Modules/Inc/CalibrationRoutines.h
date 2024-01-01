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
#ifndef _CALIBRATIONROUTINES_H
#define _CALIBRATIONROUTINES_H

#include "stm32f10x.h"

typedef struct
{
  float x_sumplain ;
  float x_sumsq;
  float x_sumcube ;
  
  float y_sumplain ;
  float y_sumsq ;
  float y_sumcube ;
  
  float z_sumplain ;
  float z_sumsq ;
  float z_sumcube ;
  
  float xy_sum ;
  float xz_sum ;
  float yz_sum ;
  
  float x2y_sum ;
  float x2z_sum ;
  float y2x_sum ;
  float y2z_sum ;
  float z2x_sum ;
  float z2y_sum ;
  
  unsigned int size;
}Least_Squares_Intermediate_Variable;


int sphere_fit_least_squares(const float x[], const float y[], const float z[],
                             unsigned int size, unsigned int max_iterations,float delta,
                             float *sphere_x, float *sphere_y, float *sphere_z,
                             float *sphere_radius);

void LS_Init(Least_Squares_Intermediate_Variable * pLSQ);
unsigned int LS_Accumulate(Least_Squares_Intermediate_Variable * pLSQ, float x, float y, float z);
void LS_Calculate(Least_Squares_Intermediate_Variable * pLSQ, unsigned int max_iterations, float delta,
                  float *sphere_x, float *sphere_y, float *sphere_z,
                  float *sphere_radius);

extern Least_Squares_Intermediate_Variable Mag_LS;
#endif

