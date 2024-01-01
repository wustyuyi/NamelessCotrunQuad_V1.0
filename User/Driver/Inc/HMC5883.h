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
#ifndef __HMC5883_H_
#define __HMC5883_H_


//*****B寄存器配置增益量程***********/
#define MAG_GAIN_SCALE0 1370//0x00   0.88Ga
#define MAG_GAIN_SCALE1 1090//0x20   1.30Ga
#define MAG_GAIN_SCALE2 820//0x40    1.90Ga
#define MAG_GAIN_SCALE3 660//0x60    2.50Ga
#define MAG_GAIN_SCALE4 440//0x80    4.00Ga
#define MAG_GAIN_SCALE5 390//0xA0    4.70Ga
#define MAG_GAIN_SCALE6 330//0xC0    5.66Ga
#define MAG_GAIN_SCALE7 230//0xE0    8.10Ga


extern float Mag_Data[3];

#define N2 5
extern float Data_X_MAG[N2];
extern float Data_Y_MAG[N2];
extern float Data_Z_MAG[N2];

float GildeAverageValueFilter_MAG(float NewValue,float *Data);
#define	HMC5883L_Addr   0x3C	//磁场传感器器件地址
void HMC5883L_Initial(void);
void HMC5883L_Read(void);
void HMC5883L_StateMachine(void);

extern float MAGData[3];
extern uint8_t Extern_Mag_Work_Flag;
extern uint8 extern_mag_id[3];

#endif


