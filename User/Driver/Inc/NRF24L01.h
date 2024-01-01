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
#ifndef __NRF24L01_H
#define __NRF24L01_H

#define  Scale_Pecent_Max  0.75   //最大解锁幅值量程因子
#define  Pit_Rol_Max 35           //最大俯仰、横滚期望
#define  Yaw_Max     200          //最大偏航期望
#define  Buttom_Safe_Deadband  50 //油门底部安全死区



//-----NRF24L01寄存器操作命令-----//
#define READ_REG_NRF    0x00  //读配置寄存器,低5位为寄存器地址
#define WRITE_REG_NRF   0x20  //写配置寄存器,低5位为寄存器地址
#define RD_RX_PLOAD     0x61  //读RX有效数据,1~32字节
#define WR_TX_PLOAD     0xA0  //写TX有效数据,1~32字节
#define FLUSH_TX        0xE1  //清除TX FIFO寄存器.发射模式下用
#define FLUSH_RX        0xE2  //清除RX FIFO寄存器.接收模式下用
#define REUSE_TX_PL     0xE3  //重新使用上一包数据,CE为高,数据包被不断发送.
#define NOP             0xFF  //空操作,可以用来读状态寄存器

//-----SPI(NRF24L01)寄存器地址-----//
#define NRF24L01_CONFIG 0x00  //配置寄存器地址;bit0:1接收模式,0发射模式;bit1:电选择;bit2:CRC模式;bit3:CRC使能;
//bit4:中断MAX_RT(达到最大重发次数中断)使能;bit5:中断TX_DS使能;bit6:中断RX_DR使能
#define EN_AA           0x01  //使能自动应答功能  bit0~5,对应通道0~5
#define EN_RXADDR       0x02  //接收地址允许,bit0~5,对应通道0~5
#define SETUP_AW        0x03  //设置地址宽度(所有数据通道):bit1,0:00,3字节;01,4字节;02,5字节;
#define SETUP_RETR      0x04  //建立自动重发;bit3:0,自动重发计数器;bit7:4,自动重发延时 250*x+86us
#define RF_CH           0x05  //RF通道,bit6:0,工作通道频率;
#define RF_SETUP        0x06  //RF寄存器;bit3:传输速率(0:1Mbps,1:2Mbps);bit2:1,发射功率;bit0:低噪声放大器增益
#define STATUS          0x07  //状态寄存器;bit0:TX FIFO满标志;bit3:1,接收数据通道号(最大:6);bit4,达到最多次重发
//bit5:数据发送完成中断;bit6:接收数据中断;
#define OBSERVE_TX      0x08  //发送检测寄存器,bit7:4,数据包丢失计数器;bit3:0,重发计数器
#define CD              0x09  //载波检测寄存器,bit0,载波检测;
#define RX_ADDR_P0      0x0A  //数据通道0接收地址,最大长度5个字节,低字节在前
#define RX_ADDR_P1      0x0B  //数据通道1接收地址,最大长度5个字节,低字节在前
#define RX_ADDR_P2      0x0C  //数据通道2接收地址,最低字节可设置,高字节,必须同RX_ADDR_P1[39:8]相等;
#define RX_ADDR_P3      0x0D  //数据通道3接收地址,最低字节可设置,高字节,必须同RX_ADDR_P1[39:8]相等;
#define RX_ADDR_P4      0x0E  //数据通道4接收地址,最低字节可设置,高字节,必须同RX_ADDR_P1[39:8]相等;
#define RX_ADDR_P5      0x0F  //数据通道5接收地址,最低字节可设置,高字节,必须同RX_ADDR_P1[39:8]相等;
#define TX_ADDR         0x10  //发送地址(低字节在前),ShockBurstTM模式下,RX_ADDR_P0与此地址相等
#define RX_PW_P0        0x11  //接收数据通道0有效数据宽度(1~32字节),设置为0则非法
#define RX_PW_P1        0x12  //接收数据通道1有效数据宽度(1~32字节),设置为0则非法
#define RX_PW_P2        0x13  //接收数据通道2有效数据宽度(1~32字节),设置为0则非法
#define RX_PW_P3        0x14  //接收数据通道3有效数据宽度(1~32字节),设置为0则非法
#define RX_PW_P4        0x15  //接收数据通道4有效数据宽度(1~32字节),设置为0则非法
#define RX_PW_P5        0x16  //接收数据通道5有效数据宽度(1~32字节),设置为0则非法
#define NRF_FIFO_STATUS 0x17  //FIFO状态寄存器;bit0,RX FIFO寄存器空标志;bit1,RX FIFO满标志;bit2,3,保留
//bit4,TX FIFO空标志;bit5,TX FIFO满标志;bit6,1,循环发送上一数据包.0,不循环;
#define MAX_TX  		0x10  //达到最大发送次数中断
#define TX_OK   		0x20  //TX发送完成中断
#define RX_OK   		0x40  //接收到数据中断

//-----24L01操作线-----//
#define NRF24L01_CE_H		GPIO_SetBits(GPIOC, GPIO_Pin_6) 					//24L01片选信号
#define NRF24L01_CE_L		GPIO_ResetBits(GPIOC, GPIO_Pin_6)
#define NRF24L01_CSN_H   	GPIO_SetBits(GPIOC, GPIO_Pin_7) 					//SPI片选信号
#define NRF24L01_CSN_L	        GPIO_ResetBits(GPIOC, GPIO_Pin_7)
#define NRF24L01_IRQ 		GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12)	//IRQ主机数据输入

//-----24L01发送接收数据宽度定义-----//
#define TX_ADR_WIDTH    5   	//5字节的地址宽度
#define RX_ADR_WIDTH    5   	//5字节的地址宽度
#define TX_PLOAD_WIDTH  32  	//32字节的用户数据宽度
#define RX_PLOAD_WIDTH  32  	//32字节的用户数据宽度

//-----变量声明-----//
extern u8 g_NRFRevData[RX_PLOAD_WIDTH];														//NRF24L01接收数据
extern u8 g_NRFSendData[TX_PLOAD_WIDTH];													//NRF24L01发送数据
extern __IO u8 g_NRFRevCnt;																				//NRF24L01接收计数器
extern u8 Data_buf[32];
extern uint8 RC_Control[32];
extern uint16 QuadData[2];
extern uint16 Throttle_Control,Last_Throttle_Control;
extern int16 Pitch_Control,Roll_Control,Yaw_Control;
extern int16 Target_Angle[2];
extern uint8 QuadRemoteFlag[4];
extern int16 RC_NewData[4];
extern uint16_t PPM_LPF_Databuf[4];
//-----函数声明-----//
extern void NRF24L01_Init(void);																	//初始化
extern void NRF24L01_RX_Mode(void);																//配置为接收模式
extern void NRF24L01_TX_Mode(void);																//配置为发送模式
extern void NRF24L01_Write_Buf(u8 reg, u8 *pBuf, u8 len);					//写数据区
extern void NRF24L01_Read_Buf(u8 reg, u8 *pBuf, u8 len);					//读数据区
extern u8 NRF24L01_Read_Reg(u8 reg);															//读寄存器
extern void NRF24L01_Write_Reg(u8 reg, u8 value);									//写寄存器
extern u8 NRF24L01_Check(void);																		//检查24L01是否存在
extern u8 NRF24L01_TxPacket(u8 *txbuf);														//发送一个包的数据
extern u8 NRF24L01_RxPacket(u8 *rxbuf);														//接收一个包的数据
void NRF24L01_RC(void );


#define Lock_Controler  0
#define Unlock_Controler  1
extern uint16 Controler_State;
extern int16_t Throttle_Rate;
extern uint16_t Auto_ReLock_Cnt;//自动上锁计数器
extern uint16_t Unlock_Makesure_Cnt,Lock_Makesure_Cnt,Forced_Lock_Makesure_Cnt;
extern uint16_t Unwanted_Lock_Flag;
#endif
