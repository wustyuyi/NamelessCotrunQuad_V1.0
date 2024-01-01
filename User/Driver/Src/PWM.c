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
#include "PWM.h"


#define  MAX_PWM 2500 //400hz    周期2.5ms
//#define  MAX_PWM 5000  //200hz  周期5ms
//#define  MAX_PWM 10000 //100hz  周期10ms
//#define  MAX_PWM 20000 //50hz  周期20ms

/***************************************************
函数名: void PWM_GPIO_Init(void)
说明:	PWM输出IO初始化
入口:	无
出口:	无
备注:	上电初始化，运行一次
****************************************************/
void PWM_GPIO_Init(void )
{
  GPIO_InitTypeDef GPIO_InitStructure;
  //开始TIM4 的时钟 及GPIOB时钟 和AFIO时钟
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//定时器3作为PWM输出
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO ,ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
  
  //设置PA5、PA6、PB0、PB1 为推挽输出
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;//
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//输出速率
  GPIO_Init(GPIOA,&GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;//
  GPIO_Init(GPIOB,&GPIO_InitStructure);
  
  
  /*************TIM4******************/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;//只用到两路，因为PB6、PB7已作为I2C口
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  //GPIO_PinRemapConfig(GPIO_Remap_TIM4 , ENABLE);//引脚复用映像  PD12 PD13 PD14 PD15
}


void PWM_Init(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  
  uint16_t prescalerValue = 0, ccr1_PWMVal = 0;
  PWM_GPIO_Init();
  prescalerValue = 72-1;//10us
  //-----TIM3定时配置-----//
  TIM_TimeBaseStructure.TIM_Period = MAX_PWM;		//40000/2M=20ms-->50Hz，从0开始计数,这个值被写入到Auto-Reload Register中
  TIM_TimeBaseStructure.TIM_Prescaler = 0;	       //暂时不分频
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;	       //时钟分割
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数模式
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;	//重复比较次数更新事件
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
  TIM_PrescalerConfig(TIM3, prescalerValue, TIM_PSCReloadMode_Immediate);//预分频,现在计时器频率为20MHz
  
  //-----PWM配置-----//
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 		//选择定时器模式:TIM脉冲宽度调制模式1-->向上计数为有效电平
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
  TIM_OCInitStructure.TIM_Pulse = ccr1_PWMVal;					//duty cycle
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 	//输出极性:TIM输出比较极性高
  
  TIM_OC1Init(TIM3, &TIM_OCInitStructure);  		//初始化外设TIM3 OC1-->Motor1
  TIM_OC2Init(TIM3, &TIM_OCInitStructure);  		//初始化外设TIM3 OC2-->Motor2
  TIM_OC3Init(TIM3, &TIM_OCInitStructure);  		//初始化外设TIM3 OC3-->Motor3
  TIM_OC4Init(TIM3, &TIM_OCInitStructure);  		//初始化外设TIM3 OC4-->Motor4
  
  TIM_ARRPreloadConfig(TIM3, ENABLE);//自动重载寄存器使能，下一个更新事件自动更新影子寄存器
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
  TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
  TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
  TIM_Cmd(TIM3, ENABLE);
  
  
  /*************TIM4**********************/
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);//配置时钟
  TIM_TimeBaseStructure.TIM_Period=MAX_PWM;
  TIM_TimeBaseStructure.TIM_Prescaler=71; //72  1us
  TIM_TimeBaseStructure.TIM_ClockDivision=0;
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;//向上计数
  TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);
  
  TIM_OCInitStructure.TIM_OCMode =TIM_OCMode_PWM1;//PWM1模式1
  TIM_OCInitStructure.TIM_OutputState =TIM_OutputState_Enable;//比较输出使能
  TIM_OCInitStructure.TIM_Pulse = ccr1_PWMVal; //设置占空比
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出比较极性高
  
  //TIM_OC1Init(TIM4, &TIM_OCInitStructure);//初始化TIM4的CH1通道
  //TIM_OC2Init(TIM4, &TIM_OCInitStructure);//初始化TIM4的CH2通道
  TIM_OC3Init(TIM4, &TIM_OCInitStructure);//初始化TIM4的CH3通道
  TIM_OC4Init(TIM4, &TIM_OCInitStructure);//初始化TIM4的CH4通道
  
  //TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
  //TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
  TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
  TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
  TIM_ARRPreloadConfig(TIM4,ENABLE);//使能TIM4在CH3通道ARR3上的预装载寄存器
  TIM_Cmd(TIM4,ENABLE);//使能定时器4
  //PWM_Set(1000,1000,1000,1000,1000,1000,1000,1000);
}





/***********************************************************************************
函数名：void PWM_Set(const u16 pwm1, const u16 pwm2, const u16 pwm3, const u16 pwm4 ,const uint16_t pwm5, const uint16_t pwm6)
说明：PWM输出设置
入口：四个通道的值
出口：无
备注：满占空为2.5ms（20ms）
************************************************************************************/
void PWM_Set(const uint16_t pwm1, const uint16_t pwm2,
             const uint16_t pwm3, const uint16_t pwm4,
             const uint16_t pwm5, const uint16_t pwm6)
{
  TIM_SetCompare4(TIM3, pwm1);
  TIM_SetCompare3(TIM3, pwm2);
  TIM_SetCompare2(TIM3, pwm3);
  TIM_SetCompare1(TIM3, pwm4);
  
  TIM_SetCompare3(TIM4, pwm5);
  TIM_SetCompare4(TIM4, pwm6);
}





