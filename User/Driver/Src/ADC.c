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
#include "headfile.h"
#include "ADC.h"
#include "stm32f10x_adc.h"


float MCU_TEPERATE = 0.0;
unsigned short average = 0;
unsigned short ADC_Value[10];
float mcu_current_temperate=0; 
/******************************************************************************
* 函数名称       : DMA_Configuraiton
* 描述           : DMA 模块设置
* 输入           : 无
* 输出           : 无
* 返回           : 无
*******************************************************************************/
void DMA_Configuration (void)
{
  DMA_InitTypeDef DMA_InitStructure;
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
  DMA_DeInit(DMA1_Channel1);//将DMA的通道1寄存器重设为缺省值
  DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)( &(ADC1->DR));//DMA外设ADC基地址
  DMA_InitStructure.DMA_MemoryBaseAddr = (unsigned long)&ADC_Value;//DMA内存基地址
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//内存作为数据传输的目的地
  DMA_InitStructure.DMA_BufferSize = 2;//DMA通道的DMA缓存的大小
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//外设地址寄存器不变
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//内存地址寄存器递增
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //数据宽度为16位
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//数据宽度为16位
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//工作在循环缓存模式
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;//DMA通道 x拥有高优先级
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//DMA通道x没有设置为内存到内存传输
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);//根据DMA_InitStruct中指定的参数初始化DMA的通道
  DMA_ITConfig(DMA1_Channel1,DMA1_IT_TC1,ENABLE);//允许DMA通道1传输结束中断
  DMA_Cmd(DMA1_Channel1, ENABLE);
}

/******************************************************************************
* 函数名称       : ADC_GPIO_Init
* 描述           : ADC GPIO口设置
* 输入           : 无
* 输出           : 无
* 返回           : 无
*******************************************************************************/
void ADC_GPIO_Init (void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}


/******************************************************************************
* 函数名称       : ADC_Configuraiton
* 描述           : ADC 模块设置
* 输入           : 无
* 输出           : 无
* 返回           : 无
*******************************************************************************/
void ADC_Configuration (void)
{
  ADC_InitTypeDef ADC_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
  RCC_ADCCLKConfig(RCC_PCLK2_Div6);//ADC最大时钟频率为14M
  ADC_DeInit(ADC1); //将外设 ADC1 的全部寄存器重设为缺省值
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//ADC工作模式:ADC1和ADC2工作在独立模式
  ADC_InitStructure.ADC_ScanConvMode = ENABLE; //模数转换工作在扫描模式
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//模数转换工作在连续转换模式
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;  //外部触发由软件触发
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//ADC数据右对齐
  ADC_InitStructure.ADC_NbrOfChannel = 2;//顺序进行规则转换的ADC通道的数目
  ADC_Init(ADC1, &ADC_InitStructure);//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器
  ADC_TempSensorVrefintCmd(ENABLE);//开启内部温度传感器
  /***设置指定ADC的规则组通道，设置它们的转化顺序和采样时间;ADC1,ADC通道x,规则采样顺序值为y,采样时间为239.5周期  */
  ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 1, ADC_SampleTime_239Cycles5);
  ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 2, ADC_SampleTime_239Cycles5);
  
  ADC_DMACmd(ADC1, ENABLE);// 开启ADC的DMA支持（要实现DMA功能，还需独立配置DMA通道等参数）  
  ADC_Cmd(ADC1, ENABLE);//使能指定的ADC1
  ADC_ResetCalibration(ADC1);//复位指定的ADC1的校准寄存器
  while(ADC_GetResetCalibrationStatus(ADC1)); //获取ADC1复位校准寄存器的状态,设置状态则等待
  ADC_StartCalibration(ADC1); //开始指定ADC1的校准状态
  while(ADC_GetCalibrationStatus(ADC1));//获取指定ADC1的校准程序,设置状态则等待
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);
  ADC_ITConfig(ADC1,ADC_IT_EOC,ENABLE);//使能ADC中断
  ADC_ExternalTrigConvCmd(ADC1, ENABLE); //使能ADC经外部触发启动转换功能
}


/*******************************************************************************
* 函数名称: calculate_MCU_temperate
* 函数功能: 计算当前单片机内部的温度
* 输入参数: Value                   -- 内部温度传感器AD测量值
* 输出参数: mcu_current_temperate   -- MCU当前温度测量值
* 函数说明：无
*******************************************************************************/
float adc4_temp = 0.0;
float calculate_MCU_temperate (float Value)
{ 
  static const float mcu_25_temperate = 1.43;// MCU在25度的典型值 为1.43；
  static const float avg_slope = 0.0043;//单片机温度与电压值曲线的平均斜率  4.3mV/摄氏度
  adc4_temp = 3.3*Value/4096.0f;
  mcu_current_temperate = (((mcu_25_temperate-adc4_temp)/avg_slope) + 25.0);
  return (mcu_current_temperate); 
}

//以下为中断处理函数，定时器2提供500ns的定时，500ns内部AD取40个mcu温度传感器上的值。
/*******************************************************************************
* 函数名称: DMAChannel1_IRQHandler
* 函数功能: DMA中断处理函数
* 输入参数: 无
* 输出参数: 无
* 函数说明：无
*******************************************************************************/
void DMA1_Channel1_IRQHandler(void)
{    
  //unsigned char i;
  //unsigned short sum;
  if(DMA_GetITStatus(DMA1_IT_TC1))  //在DMA通道1传输完成中断中进行检测
  {
    //for(i=0;i<1;i++)
    //{
    //    sum = ADC_Value[i];
    //}
  }
  //average = sum / 1;
  DMA_ClearITPendingBit(DMA1_IT_GL1);//清DMA通道1的
}


void Chip_ADC_Init()
{
  NVIC_InitTypeDef NVIC_InitStructure;
  ADC_GPIO_Init();
  ADC_Configuration();
  DMA_Configuration();
  /* Configure one bit for preemption priority */ 
  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;         
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;   
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;         
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            
  NVIC_Init(&NVIC_InitStructure);
}

