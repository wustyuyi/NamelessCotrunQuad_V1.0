/* Copyright (c)  2019-2025 Wuhan Nameless Innovation Technology Co.,Ltd. All rights reserved.*/
/*----------------------------------------------------------------------------------------------------------------------/
                开源并不等于免费，先驱者的历史已经证明，在国内这个环境下，毫无收益的开源，单靠坊间个人爱好者，自发地参与项
								目完善的方式行不通，好的开源项目需要请专职人员做好售后服务、手把手教学、统计用户反馈需求、在实践中完成对产
								品的一次次完善与迭代升级。经过综合考虑，无名飞控开源代码中，程序仅保留公司正版激活功能代码，版本激活无实际
								功能，属于公司产品常规出厂操作，不影响客户学习，其余代码全部开放给客户学习，客户移植和二次开发代码请保留代
								码版权。
-----------------------------------------------------------------------------------------------------------------------/
*               本程序只供购买者学习使用，版权著作权属于无名科创团队，无名科创团队将飞控程序源码提供给购买者，
*               购买者要为无名科创团队提供保护，未经作者许可，不得将源代码提供给他人，不得将源代码放到网上供他人免费下载， 
*               更不能以此销售牟利，如发现上述行为，无名科创团队将诉之以法律解决！！！
-----------------------------------------------------------------------------------------------------------------------
*                                                 为什么选择无名创新？
*                                         感动人心价格厚道，最靠谱的开源飞控；
*                                         国内业界良心之作，最精致的售后服务；
*                                         追求极致用户体验，高效进阶学习之路；
*                                         萌新不再孤单求索，合理把握开源尺度；
*                                         响应国家扶贫号召，促进教育体制公平；
*                                         新时代奋斗最出彩，建人类命运共同体。 
-----------------------------------------------------------------------------------------------------------------------
*               生命不息、奋斗不止；前人栽树，后人乘凉！！！
*               开源不易，且学且珍惜，祝早日逆袭、进阶成功！！！
*               学习优秀者，简历可推荐到DJI、ZEROTECH、XAG、AEE、GDU、AUTEL、EWATT、HIGH GREAT等公司就业
*               求职简历请发送：15671678205@163.com，需备注求职意向单位、岗位、待遇等
*               无名科创开源飞控QQ群：2号群465082224、1号群540707961（人员已满）
*               CSDN博客：http://blog.csdn.net/u011992534
*               优酷ID：NamelessCotrun无名小哥
*               B站教学视频：https://space.bilibili.com/67803559/#/video
*               客户使用心得、改进意见征集贴：http://www.openedv.com/forum.php?mod=viewthread&tid=234214&extra=page=1
*               淘宝店铺：https://shop348646912.taobao.com/?spm=2013.1.1000126.2.5ce78a88ht1sO2
*               百度贴吧:无名科创开源飞控
*               公司官网:www.nameless.tech
*               无名创新国内首款TI开源飞控设计初衷、知乎专栏:https://zhuanlan.zhihu.com/p/54471146
*               修改日期:2019/11/27                    
*               版本：慧飞者PRO——WisdomPilot_Pro_V1.0.0
*               版权所有，盗版必究。
*               Copyright(C) 2019-2025 武汉无名创新科技有限公司 
*               All rights reserved
-----------------------------------------------------------------------------------------------------------------------
*               重要提示：
*               正常淘宝咸鱼转手的飞控、赠送朋友、传给学弟的都可以进售后群学习交流，
*               不得直接在网上销售无名创新资料，无名创新代码有声明版权，他人不得将
*               资料代码传网上供他人下载，不得以谋利为目的销售资料代码，发现有此操
*               作者，公司会提前告知，请1天内及时处理，否则你的学校、单位、姓名、电
*               话、地址信息会被贴出在公司官网、官方微信公众平台、官方技术博客、知乎
*               专栏以及淘宝店铺首页予以公示公告，此种所作所为，会成为个人污点，影响
*               升学、找工作、社会声誉、很快就很在无人机界出名，后果很严重。
*               因此行为给公司造成重大损失者，会以法律途径解决，感谢您的合作，谢谢！！！
----------------------------------------------------------------------------------------------------------------------*/
#include "Headfile.h"
#include "Temperature_Ctrl.h"

#define Temperature_Ctrl_Enable   1

#define Temperature_Setpoint   50//IMU恒温控制50摄氏度
const float Temp_Control_Unit[20]=
{1  ,1 ,1 ,0 ,0 ,0 , 0 ,50    ,30  ,0 ,80,  20.00  ,3.0   ,100.0  ,0    ,0 ,100 , 1 ,  1 ,  1 };//水平维度方向加速度控制器 20 3 50  //  10  3  80
/*
1偏差限幅标志；  2积分限幅标志；3积分分离标志；   4期望；
5反馈            6偏差；        7上次偏差；       8偏差限幅值；
9积分分离偏差值；10积分值       11积分限幅值；    12控制参数Kp；
13控制参数Ki；   14控制参数Kd； 15控制器总输出；  16上次控制器总输出
17总输出限幅度； 18变积分控制时的积分增益
*/		
void Temperature_Ctrl_Init(void)
{
  Total_Controller.IMU_Temperature_Control.Err_Limit_Flag=(uint8)(Temp_Control_Unit[0]);//1偏差限幅标志
  Total_Controller.IMU_Temperature_Control.Integrate_Limit_Flag=(uint8)(Temp_Control_Unit[1]);//2积分限幅标志
  Total_Controller.IMU_Temperature_Control.Integrate_Separation_Flag=(uint8)(Temp_Control_Unit[2]);//3积分分离标志
  Total_Controller.IMU_Temperature_Control.Expect=Temp_Control_Unit[3];//4期望
  Total_Controller.IMU_Temperature_Control.FeedBack=Temp_Control_Unit[4];//5反馈值
  Total_Controller.IMU_Temperature_Control.Err=Temp_Control_Unit[5];//6偏差
  Total_Controller.IMU_Temperature_Control.Last_Err=Temp_Control_Unit[6];//7上次偏差
  Total_Controller.IMU_Temperature_Control.Err_Max=Temp_Control_Unit[7];//8偏差限幅值
  Total_Controller.IMU_Temperature_Control.Integrate_Separation_Err=Temp_Control_Unit[8];//9积分分离偏差值
  Total_Controller.IMU_Temperature_Control.Integrate=Temp_Control_Unit[9];//10积分值
  Total_Controller.IMU_Temperature_Control.Integrate_Max=Temp_Control_Unit[10];//11积分限幅值
  Total_Controller.IMU_Temperature_Control.Kp=Temp_Control_Unit[11];//12控制参数Kp
  Total_Controller.IMU_Temperature_Control.Ki=Temp_Control_Unit[12];//13控制参数Ki
  Total_Controller.IMU_Temperature_Control.Kd=Temp_Control_Unit[13];//14控制参数Ki
  Total_Controller.IMU_Temperature_Control.Control_OutPut=Temp_Control_Unit[14];//15控制器总输出
  Total_Controller.IMU_Temperature_Control.Last_Control_OutPut=Temp_Control_Unit[15];//16上次控制器总输出
  Total_Controller.IMU_Temperature_Control.Control_OutPut_Limit=Temp_Control_Unit[16];//17上次控制器总输出
  Total_Controller.IMU_Temperature_Control.Scale_Kp=Temp_Control_Unit[17];
  Total_Controller.IMU_Temperature_Control.Scale_Ki=Temp_Control_Unit[18];
  Total_Controller.IMU_Temperature_Control.Scale_Kd=Temp_Control_Unit[19];  
}

void Simulation_PWM_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin    = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode   = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed  = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);
}

#define Simulation_PWM_Period_MAX  100//100*1ms=0.1S
void Simulation_PWM_Output(uint16_t width)
{
#if Temperature_Ctrl_Enable
	uint16_t static cnt=0;
	cnt++;
	if(cnt>=Simulation_PWM_Period_MAX)  cnt=0;
  if(cnt<=width) GPIO_SetBits(GPIOA,GPIO_Pin_5);
	else GPIO_ResetBits(GPIOA,GPIO_Pin_5);
#else
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);
#endif
	
}


void Temperature_Ctrl(void)
{
#if Temperature_Ctrl_Enable
 uint16_t static cnt=0;
 cnt++;
 Total_Controller.IMU_Temperature_Control.Expect=Temperature_Setpoint;
 Total_Controller.IMU_Temperature_Control.FeedBack=WP_Sensor.temperature;
 if(cnt>=10)  //10*1ms=0.01S
 {
	 PID_Control(&Total_Controller.IMU_Temperature_Control);
	 Total_Controller.IMU_Temperature_Control.Control_OutPut=constrain_float(Total_Controller.IMU_Temperature_Control.Control_OutPut,0,Simulation_PWM_Period_MAX);
	 cnt=0;
 }
#else
	Total_Controller.IMU_Temperature_Control.Control_OutPut=0;
#endif
}

uint8_t Temperature_State_Check(void)
{
#if Temperature_Ctrl_Enable
  return (ABS(Total_Controller.IMU_Temperature_Control.Err))<=2.0f?1:0;
#else
	return 1;
#endif	
}


void Temperature_Ctrl_Run(void)
{
	Temperature_Ctrl();	
	Simulation_PWM_Output(Total_Controller.IMU_Temperature_Control.Control_OutPut);
}

