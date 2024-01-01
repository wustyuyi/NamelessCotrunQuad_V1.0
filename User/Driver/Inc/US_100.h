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

#ifndef _US_100_H_
#define _US_100_H_


/*******1、HCSR04高度超过一米数据会习惯性跳变，数据跳变的范围所在高度每个模块均不一样，
*******故当采用HCSR04时，最大高度不宜超过一米，或者用户自行测试自己使用的超声波模块
*******数据跳变所在的高度区间，HCSR04低空数据仍然需要结合惯导，做防跳变处理。
********2、当使用US100超声波模块测距时，有效距离通常可到3米，实测2.5以下数据都很稳定
********强烈推荐使用US100模块替代HCSR04,US100数据可以不做防跳变处理，即可用于惯导融合
*********************************************************************************/
/*
//HCSR04
#define Effective_Height_Time_Max  5800//模块有效高度的间隔时间，限幅约24000->400cm,15000->250cm，11765->200cm  5882->100
#define User_Height_Max  80//用户使用的最大高度值，单位为cm，需要流出一定裕度给气压计/超声波切换过渡
*/

//US100
#define Effective_Height_Time_Max  11765//模块有效高度的间隔时间，限幅约24000->400cm,15000->250cm，11765->200cm  5882->100   15000
#define User_Height_Max  180//用户使用的最大高度值，单位为cm，需要流出一定裕度给气压计/超声波切换过渡   200



#define US_100_Distance_CMD    0x55
#define US_100_Temperature_CMD 0x50

float US_100_Distance(uint8 MSB,uint8 LSB);
float US_100_Temperature(uint8 data);
extern uint16 HC_SR04_RSSI;
extern uint8_t HCSR_04_Update_Flag;
#define HC_SR04_OUT_LOW    GPIO_ResetBits(GPIOA,GPIO_Pin_0);
#define HC_SR04_OUT_HIGH   GPIO_SetBits(GPIOA,GPIO_Pin_0);


void HC_SR04_UP(void);
void HC_SR04_DN(void);
void HC_SR04_Init(void);
void HC_SR04_Start(void);
void HC_SR04_Statemachine(void);
extern float HC_SR04_Distance,HC_SR04_Distance_Filter,HC_SR04_Bubble_Distance;
extern float HC_SR04_Distance_Record[5],HCSR04_Data[5];
#endif


