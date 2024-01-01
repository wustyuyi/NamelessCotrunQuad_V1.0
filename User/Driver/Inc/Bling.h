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
#ifndef __BLING_H
#define __BLING_H


#define LEDR PCout(6)   	//R
#define LEDG PCout(7)   	//G
#define LEDB PCout(8)   	//B

typedef struct
{
  uint16_t Bling_Contiune_Time;//闪烁持续时间
  uint16_t Bling_Period;//闪烁周期
  float  Bling_Percent;//闪烁占空比
  uint16_t  Bling_Cnt;//闪烁计数器
  GPIO_TypeDef* Port; //端口
  uint16_t Pin;//引脚
  uint8_t Endless_Flag;//无尽模式
}Bling_Light;


void Bling_Set(Bling_Light *Light,
               uint32_t Continue_time,//持续时间
               uint16_t Period,//周期100ms~1000ms
               float Percent,//0~100%
               uint16_t  Cnt,
               GPIO_TypeDef* Port,
               uint16_t Pin
                 ,uint8_t Flag);
void Bling_Process(Bling_Light *Light);
void Bling_Working(uint16 bling_mode);
void Bling_Init(void);
void Quad_Start_Bling(void);
extern Bling_Light Light_1,Light_2,Light_3;
extern uint16_t Bling_Mode;

#endif
