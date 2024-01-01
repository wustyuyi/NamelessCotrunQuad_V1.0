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
#ifndef _NAMELESSCOTRUN_OPTICALFLOW_
#define _NAMELESSCOTRUN_OPTICALFLOW_




typedef struct{
unsigned short frame_count_since_last_readout;
signed short pixel_flow_x_integral;
signed short pixel_flow_y_integral;
signed short gyro_x_rate_integral;
signed short gyro_y_rate_integral;
signed short gyro_z_rate_integral;
unsigned int integration_timespan;
unsigned int sonar_timestamp;
unsigned short ground_distance;
signed short gyro_temperature;
unsigned char qual;
}flow_integral_frame;

typedef struct{
float x;
float y;
unsigned short dt;
unsigned char qual;
unsigned char update;
}flow_float;

extern  flow_integral_frame opt_origin_data;
extern Vector2f opt_filter_data,opt_gyro_filter_data,opt_gyro_data,gyro_filter_data;
extern SINS OpticalFlow_SINS;
void OpticalFlow_Init(void);
uint8_t Optflow_Prase(void);
void Optflow_Statemachine(void);
float OpticalFlow_Rotate_Complementary_Filter(float optflow_gyro,float gyro,uint8_t axis);

extern uint8_t OpticalFlow_Is_Work;
extern Vector2f OpticalFlow_Speed,OpticalFlow_Speed_Err,OpticalFlow_Position;
#endif



