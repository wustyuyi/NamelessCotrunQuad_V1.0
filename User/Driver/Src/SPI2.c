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
#include "SPI2.h"

SPI_InitTypeDef   SPI_InitStructure;
/************************************
函数名：void SPI_Configuration(void)
说明：SPI配置
入口：无
出口：无
备注：配置SPI2
************************************/
void SPI2_Configuration(void)
{ 
  GPIO_InitTypeDef GPIO_InitStructure;//定义GPIO结构体
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);   
  //-----SPI2-----//
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;								//PB13-->SCK,PB14-->MISO,PB15-->MOSI
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;  																			//PB13/14/15复用推挽输出
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOB,&GPIO_InitStructure);
  	
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;							//设置SPI工作模式:设置为主SPI
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;					//设置SPI的数据大小:SPI发送接收8位帧结构
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;								//串行同步时钟的空闲状态为低电平
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;							//串行同步时钟的第一个跳变沿（上升或下降）数据被采样
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;									//NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;//定义波特率预分频的值:波特率预分频值为2，36MHz/2/4=4.5MHz
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;				//指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
  SPI_InitStructure.SPI_CRCPolynomial = 7;									//CRC值计算的多项式，在全双工模式中CRC作为最后一个字节发送出去
  SPI_Init(SPI2, &SPI_InitStructure);  											//根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器 
  SPI_Cmd(SPI2, ENABLE); 											   						//使能SPI外设
}

/***************************************
函数名：u8 SPI_ReadWriteByte(u8 txData)
说明：SPI读写一个字节函数
入口：u8 txData MOSI写出的字节
出口：u8	MISO写入的字节
备注：返回值为0时，表明没有发送/接收成功
****************************************/
u8 SPI2_ReadWriteByte(u8 txData)
{
  u8 retry = 0;
  
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET) //检查指定的SPI标志位设置与否:发送缓存空标志位
  {
    retry++;
    if (retry > 200)			//超时
      return 0;
  }
  SPI_I2S_SendData(SPI2, txData); 							//通过外设SPIx发送一个数据
  retry = 0;
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) //检查指定的SPI标志位设置与否:接受缓存非空标志位
  {
    retry++;
    if(retry > 200)				//超时
      return 0;
  }
  return SPI_I2S_ReceiveData(SPI2); 						//返回通过SPIx最近接收的数据
}


void SPI2_SetSpeed(uint16 SPI_BaudRatePrescaler)
{	
  if(SPI_BaudRatePrescaler==2)  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;  //预分频值为2
  else if(SPI_BaudRatePrescaler==4) SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;  //预分频值为4
  else if(SPI_BaudRatePrescaler==8) SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8; //预分频值为8
  else if(SPI_BaudRatePrescaler==16) SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;  //预分频值为16
  else if(SPI_BaudRatePrescaler==32) SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;//预分频值为32
  else if(SPI_BaudRatePrescaler==64) SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;  //预分频值为64
  else if(SPI_BaudRatePrescaler==128) SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;  //预分频值为128
  else if(SPI_BaudRatePrescaler==256) SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256; //预分频值为256
  else  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;  //预分频值为4  
}

