#ifndef _ADRC_H_
#define _ADRC_H_
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
typedef struct
{
/*****安排过度过程*******/
float x1;//跟踪微分期状态量
float x2;//跟踪微分期状态量微分项
float r;//时间尺度
float h;//ADRC系统积分时间
uint16 N0;//跟踪微分器解决速度超调h0=N*h

float h0;
float fh;//最速微分加速度跟踪量
/*****扩张状态观测器*******/
/******已系统输出y和输入u来跟踪估计系统状态和扰动*****/
float z1;
float z2;
float z3;//根据控制对象输入与输出，提取的扰动信息
float e;//系统状态误差
float y;//系统输出量
float fe;
float fe1;
float beta_01;
float beta_02;
float beta_03;
float b;


/**********系统状态误差反馈率*********/
float e0;//状态误差积分项
float e1;//状态偏差
float e2;//状态量微分项
float u0;//非线性组合系统输出
float u;//带扰动补偿后的输出
float b0;//扰动补偿

/*********第一种组合形式*********/
float beta_0;//线性
float beta_1;//非线性组合参数
float beta_2;//u0=beta_1*e1+beta_2*e2+(beta_0*e0);
/*********第二种组合形式*********/
float alpha1;//u0=beta_1*fal(e1,alpha1,zeta)+beta_2*fal(e2,alpha2,zeta)
float alpha2;//0<alpha1<1<alpha2
float zeta;//线性段的区间长度
/*********第三种组合形式*********/
float h1;//u0=-fhan(e1,e2,r,h1);
uint16 N1;//跟踪微分器解决速度超调h0=N*h
/*********第四种组合形式*********/
float c;//u0=-fhan(e1,c*e2*e2,r,h1);

float e2_lpf;
Butter_BufferData ADRC_LPF_Buffer;//控制器低通输入输出缓冲

float TD_Input;
float Last_TD_Input;
float TD_Input_Div;

float ESO_Input;
float Last_ESO_Input;
float ESO_Input_Div;
}Fhan_Data;



void ADRC_Init(Fhan_Data *fhan_Input1,Fhan_Data *fhan_Input2);
void Fhan_ADRC(Fhan_Data *fhan_Input,float expect_ADRC);
void ADRC_Control(Fhan_Data *fhan_Input,float expect_ADRC,float feedback);
void ADRC_Integrate_Reset(Fhan_Data *fhan_Input) ;
extern Fhan_Data ADRC_Pitch_Controller,ADRC_Roll_Controller;

void Advanced_ESO(Fhan_Data *fhan_Input);
#endif

