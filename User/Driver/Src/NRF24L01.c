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
#include "NRF24L01.H"


uint16_t RC_Buttom=1000,RC_Top=2000,RC_Middle=1500,RC_Deadband=100;
uint16_t RC_Deadzone_Buttom=0,RC_Deadzone_Top=0;


//-----NRF24L01发送接收地址-----//
const u8 TX_ADDRESS[TX_ADR_WIDTH] = {0x12,0x37,0x96,0x75,0xA1}; //发送地址
const u8 RX_ADDRESS[RX_ADR_WIDTH] = {0x12,0x37,0x96,0x75,0xA1}; //接收地址
u8 Data_buf[32]={0,0};


//-----NRF24L01接收数据-----//
u8 g_NRFRevData[RX_PLOAD_WIDTH]={0,0};
//-----NRF24L01发送数据-----//
u8 g_NRFSendData[TX_PLOAD_WIDTH]={0};

//-----NRF24L01接收计数器-----//
__IO u8 g_NRFRevCnt = 0;

/********************************
函数名：void NRF24L01_Init(void)
说明：初始化24L01
入口：无
出口：无
备注：无
*********************************/
void NRF24L01_Init(void)
{
  NRF24L01_CE_L; 			//使能24L01
  NRF24L01_CSN_H;			//SPI片选取消
}

/******************************
函数名：u8 NRF24L01_Check(void)
说明：检测24L01是否存在
入口：无
出口：u8
0，成功;
1，失败
备注：无
*******************************/
u8 NRF24L01_Check(void)
{
  u8 buf[5] = {0XA5,0XA5,0XA5,0XA5,0XA5}, i;
  NRF24L01_Write_Buf(WRITE_REG_NRF+TX_ADDR,buf,5);//写入5个字节的地址，TX_ADDR为地址，WRITE_REG_NRF为命令
  NRF24L01_Read_Buf(TX_ADDR,buf,5);//读出写入的地址
  for (i = 0; i < 5; i++)
    if (buf[i] != 0XA5)
      break;
  if (i != 5)
    return 1;//检测24L01错误
  return 0;//检测到24L01
}

/************************************************
函数名：void NRF24L01_Write_Reg(u8 reg, u8 value)
说明：SPI写寄存器
入口：u8 reg		寄存器地址
u8 value	需要写入的值
出口：无
备注：无
************************************************/
void NRF24L01_Write_Reg(u8 reg, u8 value)
{
  NRF24L01_CSN_L;                 	//使能SPI传输
  SPI2_ReadWriteByte(reg);			    //发送寄存器号，这里可以读取到寄存器的状态
  SPI2_ReadWriteByte(value);      		//写入寄存器的值
  NRF24L01_CSN_H;                 	//禁止SPI传输
}

/************************************
函数名：u8 NRF24L01_Read_Reg(u8 reg)
说明：读取SPI寄存器值
入口：u8 reg		寄存器地址
出口：u8	状态
备注：无
*************************************/
//
//reg:要读的寄存器
u8 NRF24L01_Read_Reg(u8 reg)
{
  u8 reg_val;
  
  NRF24L01_CSN_L;          				//使能SPI传输
  SPI2_ReadWriteByte(reg);   				//发送寄存器号
  reg_val = SPI2_ReadWriteByte(0XFF);	    //读取寄存器内容，只需要读取，主机可以随意传送数据过去
  NRF24L01_CSN_H;          			    //禁止SPI传输
  return(reg_val);           				//返回状态值
}

/*******************************************************
函数名：void NRF24L01_Read_Buf(u8 reg, u8 *pBuf, u8 len)
说明：在指定位置读出指定长度的数据
入口：u8 reg		寄存器(位置)
u8 *pBuf	数据指针
u8 len		数据长度
出口：无
备注：无
*******************************************************/
void NRF24L01_Read_Buf(u8 reg, u8 *pBuf, u8 len)
{
  u8 i;
  
  NRF24L01_CSN_L;           							//使能SPI传输
  SPI2_ReadWriteByte(reg);									//发送寄存器值(位置)
  for (i = 0; i < len; i++)
    pBuf[i] = SPI2_ReadWriteByte(0XFF);		//读出数据
  NRF24L01_CSN_H;       									//关闭SPI传输
}

/********************************************************
函数名：void NRF24L01_Write_Buf(u8 reg, u8 *pBuf, u8 len)
说明：在指定位置写指定长度的数据
入口：u8 reg		寄存器(位置)
u8 *pBuf	数据指针
u8 len		数据长度
出口：无
备注：无
********************************************************/
void NRF24L01_Write_Buf(u8 reg, u8 *pBuf, u8 len)
{
  u8 i;
  
  NRF24L01_CSN_L;          						//使能SPI传输
  SPI2_ReadWriteByte(reg);							//发送寄存器值(位置)
  for	(i = 0; i < len; i++)
    SPI2_ReadWriteByte(*pBuf++); 			//写入数据
  NRF24L01_CSN_H;       							//关闭SPI传输
}

/***************************************
函数名：u8 NRF24L01_TxPacket(u8 *txbuf)
说明：启动NRF24L01发送一次数据
入口：u8 *txbuf	待发送数据首地址
出口：U8	发送完成状况
备注：无
****************************************/
u8 NRF24L01_TxPacket(u8 *txbuf)
{
  u8 sta;
  NRF24L01_CE_L;																						//片选
  NRF24L01_Write_Buf(WR_TX_PLOAD, txbuf, TX_PLOAD_WIDTH);		//写数据到TX BUF  32个字节
  NRF24L01_CE_H;
  while (NRF24L01_IRQ != 0);																//等待发送完成
  sta = NRF24L01_Read_Reg(STATUS);  												//读取状态寄存器的值
  NRF24L01_Write_Reg(WRITE_REG_NRF + STATUS, sta); 					//清除TX_DS或MAX_RT中断标志
  if (sta & MAX_TX)																					//达到最大重发次数
  {
    NRF24L01_Write_Reg(FLUSH_TX, 0xFF);											//清除TX FIFO寄存器
    return MAX_TX;
  }
  if (sta & TX_OK)																					//发送完成
  {
    return TX_OK;
  }
  return 0xFF;																							//其他原因发送失败
}

/***************************************
函数名：u8 NRF24L01_RxPacket(u8 *rxbuf)
说明：启动NRF24L01接收一次数据
入口：u8 *txbuf	待接收数据首地址
出口：u8	0：接收完成
1：接收不成功
备注：无
****************************************/
u8 NRF24L01_RxPacket(u8 *rxbuf)
{
  u8 sta;
  sta = NRF24L01_Read_Reg(STATUS);  							//读取状态寄存器的值
  NRF24L01_Write_Reg(WRITE_REG_NRF + STATUS,sta); 			//清除TX_DS或MAX_RT中断标志
  if (sta & RX_OK)											//接收到数据
  {
    NRF24L01_Read_Buf(RD_RX_PLOAD, rxbuf, RX_PLOAD_WIDTH);	//读取数据
    NRF24L01_Write_Reg(FLUSH_RX, 0xFF);						//清除RX FIFO寄存器
    return 0;
  }
  return 1;													//没收到任何数据
}

/*****************************************************
函数名：void NRF24L01_RX_Mode(void)
说明：初始化NRF24L01到RX模式
入口：无
出口：无
备注：
设置RX地址,写RX数据宽度,选择RF频道,波特率和LNA HCURR
当CE变高后,即进入RX模式,并可以接收数据了
******************************************************/
void NRF24L01_RX_Mode(void)
{
  EXTI_InitTypeDef EXTI_InitStructure;
  EXTI_ClearITPendingBit(EXTI_Line12);//清空中断标志
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource12); //选择中断管脚PB12
  //定义EXTI结构体
  //由于发送模式下已经将中断线切断，所以当切换成接收模式时，需要重新连接起来
  EXTI_InitStructure.EXTI_Line = EXTI_Line12;							//EXTI线中断开通
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;				    //定义为中断还是事件
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;				//下降沿触发
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;							//使能EXTI线中断
  EXTI_Init(&EXTI_InitStructure);
  
  NRF24L01_CE_L;
  NRF24L01_Write_Buf(WRITE_REG_NRF+TX_ADDR,(u8*)TX_ADDRESS,TX_ADR_WIDTH);	//写TX节点地址
  NRF24L01_Write_Buf(WRITE_REG_NRF+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH);//写RX节点地址
  NRF24L01_Write_Reg(WRITE_REG_NRF+EN_AA,0x01);    						//使能通道0的自动应答
  NRF24L01_Write_Reg(WRITE_REG_NRF+EN_RXADDR,0x01);						//使能通道0的接收地址
  NRF24L01_Write_Reg(WRITE_REG_NRF+RF_CH,40);	    						//设置RF通信频率
  NRF24L01_Write_Reg(WRITE_REG_NRF+RX_PW_P0,RX_PLOAD_WIDTH);				//选择通道0的有效数据宽度
  NRF24L01_Write_Reg(WRITE_REG_NRF+RF_SETUP,0x0f);						//设置TX发射参数,0db增益,2Mbps,低噪声增益开启
  NRF24L01_Write_Reg(WRITE_REG_NRF+NRF24L01_CONFIG,0x0f);				//配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式
  NRF24L01_CE_H; 																																	//CE为高,进入接收模式
}

/*****************************************************************************************
函数名：void NRF24L01_TX_Mode(void)
说明：初始化NRF24L01到TX模式
入口：无
出口：无
备注：
设置TX地址,写TX数据宽度,设置RX自动应答的地址,填充TX发送数据,选择RF频道,波特率和LNA HCURR
PWR_UP,CRC使能
CE为高大于10us,则启动发送
******************************************************************************************/
void NRF24L01_TX_Mode(void)
{
  EXTI_InitTypeDef EXTI_InitStructure;//定义EXTI结构体
  //由于接收模式下的IRQ引脚设置为中断输入引脚，所以当切换成发送模式时，需要将中断输入引脚的功能取消
  EXTI_InitStructure.EXTI_Line = EXTI_Line12;//EXTI线中断开通
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//定义为中断还是事件
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
  EXTI_InitStructure.EXTI_LineCmd =ENABLE;//失能EXTI线中断
  EXTI_Init(&EXTI_InitStructure);
  
  NRF24L01_CE_L;
  NRF24L01_Write_Buf(WRITE_REG_NRF+TX_ADDR,(u8*)TX_ADDRESS,TX_ADR_WIDTH);	//写TX节点地址
  NRF24L01_Write_Buf(WRITE_REG_NRF+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH); //设置TX节点地址,主要为了使能ACK
  NRF24L01_Write_Reg(WRITE_REG_NRF+EN_AA,0x01); //使能通道0自动应答
  NRF24L01_Write_Reg(WRITE_REG_NRF+EN_RXADDR,0x01); //使能通道0的接收地址
  NRF24L01_Write_Reg(WRITE_REG_NRF+SETUP_RETR,0x1a);//设置自动重发间隔时间:500us + 86us;最大自动重发次数:15次
  NRF24L01_Write_Reg(WRITE_REG_NRF+RF_CH,40);//设置RF通道为40
  NRF24L01_Write_Reg(WRITE_REG_NRF+RF_SETUP,0x0f);//设置TX发射参数,0db增益,2Mbps,低噪声增益开启
  NRF24L01_Write_Reg(WRITE_REG_NRF+NRF24L01_CONFIG,0x0e);//配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,发送模式,开启所有中断
  NRF24L01_CE_H;																															//CE为高,10us后启动发送
}


uint16_t NRF24L01_CNT=0;
Testime NRF_Time;
void EXTI15_10_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line12) != RESET)
  {
    Test_Period(&NRF_Time);
    NRF24L01_CNT++;
  }
  EXTI_ClearITPendingBit(EXTI_Line12);
}

Butter_BufferData RC_LPF_Buffer[4];
uint16_t PPM_LPF_Databuf[4];
void RC_Data_LPF_Filter()
{
  uint16_t i=0;
  for(i=0;i<4;i++)//对遥控器前四个通道滤波处理
  {
    PPM_LPF_Databuf[i]=(uint16_t)(LPButterworth(PPM_Databuf[i],&RC_LPF_Buffer[i],&Butter_5HZ_Parameter_RC));
  }
}


int16_t Throttle_Rate=0;
int16_t Get_Thr_Rate(float Thr)//油门变化量
{
  static float Thr_Rec[20];
  uint16_t i=0;
  for(i=19;i>0;i--)
  {
    Thr_Rec[i]=Thr_Rec[i-1];
  }
  Thr_Rec[0]=Thr;
  return (int16_t)((Thr_Rec[0]-Thr_Rec[9])/1.0f);
}


void RC_Scale_Set(Vector_RC *rc_date)
{
  RC_Buttom=(uint16_t)(rc_date->min);
  RC_Top=(uint16_t)(rc_date->max);
  RC_Middle=(uint16_t)(rc_date->middle);
  RC_Deadband=(uint16_t)(rc_date->deadband);
  RC_Deadzone_Buttom=RC_Middle-RC_Deadband/2;
  RC_Deadzone_Top=RC_Middle+RC_Deadband/2;
}


uint16 Throttle_Control=1000;
int16 Pitch_Control=0,Roll_Control=0,Yaw_Control=0;
int16 Target_Angle[2]={0};
uint8 RC_Control[32];
uint16 Last_Throttle_Control,Pre_Last_Throttle_Control;
uint16 Throttle_Base=1000,TempThrottle_Control;
uint16 QuadData[2];
uint8 QuadRemoteFlag[4]={0};
int16 RC_NewData[4]={0};
uint16_t Controler_State=0;
uint16_t Auto_ReLock_Cnt=0;//自动上锁计数器
uint8_t Auto_Relock_Flag=0;
uint8_t Auto_Relock_Flag_Set=0;
int16 Y_T=0,T_temp=0;
int16 Temp_RC=0;
uint16_t Unlock_Makesure_Cnt=0,Lock_Makesure_Cnt=0;
uint16_t Unwanted_Lock_Flag=0;
uint16_t Forced_Lock_Makesure_Cnt=0;
uint16_t NRF24L01_Channel[10]={0};
void NRF24L01_RC(void )
{

  /****************NRF24L01接收*****************/
#ifdef RC_NRF24L01
  if(NRF24L01_RxPacket(Data_buf)==0)
  {
    RC_Control[0]=Data_buf[0];
    RC_Control[1]=Data_buf[1];
    
    RC_Control[2]=Data_buf[2];
    RC_Control[3]=Data_buf[3];
    
    RC_Control[4]=Data_buf[4];
    RC_Control[5]=Data_buf[5];
    
    RC_Control[6]=Data_buf[6];
    RC_Control[7]=Data_buf[7];
    
    RC_Control[8]=Data_buf[8];
    RC_Control[9]=Data_buf[9];
    
    RC_Control[10]=Data_buf[10];
    RC_Control[11]=Data_buf[11];
    
    RC_Control[12]=Data_buf[12];
    RC_Control[13]=Data_buf[13];
  }
  NRF24L01_Channel[0]=((uint16_t)(RC_Control[6]<<8)|RC_Control[7])*3000/4095;     //横滚角ch1
  NRF24L01_Channel[1]=((uint16_t)(RC_Control[4]<<8)|RC_Control[5])*3000/4095;     //俯仰角ch2
  NRF24L01_Channel[2]=((uint16_t)(RC_Control[0]<<8)|RC_Control[1])*1000/4095+1000;//油门通道ch3
  NRF24L01_Channel[3]=((uint16_t)(RC_Control[2]<<8)|RC_Control[3])*3000/4095;     //偏航通道ch4
  
  NRF24L01_Channel[4]=((uint16_t)((RC_Control[12]&0x0008)>>3)*2000);              //波动开关ch5
  NRF24L01_Channel[5]=((uint16_t)((RC_Control[12]&0x0004)>>2)*2000);              //波动开关ch6
  NRF24L01_Channel[6]=((uint16_t)((RC_Control[12]&0x0002)>>1)*2000);              //波动开关ch7
  NRF24L01_Channel[7]=((uint16_t)((RC_Control[12]&0x0001)>>0)*2000);              //波动开关ch8
  
  NRF24L01_Channel[8]=((uint16_t)(RC_Control[8]<<8)|RC_Control[9])*3000/4095;
  NRF24L01_Channel[9]=((uint16_t)(RC_Control[10]<<8)|RC_Control[11])*3000/4095;
  
  if(NRF24L01_Channel[0]<=RC_Middle-RC_Deadband/2)  Roll_Control=-(RC_Middle-RC_Deadband/2-NRF24L01_Channel[0])*50/1500;
  else if(NRF24L01_Channel[0]>=RC_Middle+RC_Deadband/2)  Roll_Control=-(RC_Middle+RC_Deadband/2-NRF24L01_Channel[0])*50/1500;
  else Roll_Control=0;
  
  if(NRF24L01_Channel[1]<=RC_Middle-RC_Deadband/2)  Pitch_Control=-(RC_Middle-RC_Deadband/2-NRF24L01_Channel[1])*50/1500;
  else if(NRF24L01_Channel[1]>=RC_Middle+RC_Deadband/2)  Pitch_Control=-(RC_Middle+RC_Deadband/2-NRF24L01_Channel[1])*50/1500;
  else Pitch_Control=0;
  
  Target_Angle[0]=-Pitch_Control;
  Target_Angle[1]=-Roll_Control;
  
  Temp_RC=(NRF24L01_Channel[2]-1100);
  if(Temp_RC<=5)     Throttle_Control=0;
  else if(Temp_RC>=1000)  Throttle_Control=1000;
  else Throttle_Control=Temp_RC;
  
  if(NRF24L01_Channel[3]<=RC_Middle-RC_Deadband/2)
    Yaw_Control=(NRF24L01_Channel[3]-(RC_Middle-RC_Deadband/2))*150/1500;
  else if(NRF24L01_Channel[3]>=RC_Middle+RC_Deadband/2)
    Yaw_Control=(NRF24L01_Channel[3]-(RC_Middle+RC_Deadband/2))*150/1500;
  else Yaw_Control=0;
  if(Yaw_Control>=150) Yaw_Control=150;
  else if(Yaw_Control<=-150) Yaw_Control=-150;
  
  RC_NewData[0]=Throttle_Control;//遥感油门原始行程量
  Throttle_Rate=Get_Thr_Rate(Throttle_Control);
  Throttle_Control=Throttle_Base+Throttle_Control;
#endif


if(sbus_update_flag==1||rc_update_flag==1||ppm_update_flag==1)
{
	  sbus_update_flag=0;
	  rc_update_flag=0;
	  ppm_update_flag=0;
		/****************PPM接收*****************/
	#ifdef RC_PPM
		RC_Data_LPF_Filter();
		RC_Scale_Set(&RC_Calibration[0]);
		if(PPM_Databuf[0]<=RC_Deadzone_Buttom)  Roll_Control=(RC_Deadzone_Buttom-PPM_LPF_Databuf[0])*Pit_Rol_Max/(RC_Deadzone_Buttom-RC_Buttom);//最大行程控制量+-45
		else if(PPM_Databuf[0]>=RC_Deadzone_Top)  Roll_Control=(RC_Deadzone_Top-PPM_LPF_Databuf[0])*Pit_Rol_Max/(RC_Top-RC_Deadzone_Top);
		else Roll_Control=0;
		Roll_Control=constrain_int16_t(Roll_Control,-Pit_Rol_Max,Pit_Rol_Max);
		
		RC_Scale_Set(&RC_Calibration[1]);
		if(PPM_Databuf[1]<=RC_Deadzone_Buttom)  Pitch_Control=(RC_Deadzone_Buttom-PPM_LPF_Databuf[1])*Pit_Rol_Max/(RC_Deadzone_Buttom-RC_Buttom);//最大行程控制量+-45
		else if(PPM_Databuf[1]>=RC_Deadzone_Top)  Pitch_Control=(RC_Deadzone_Top-PPM_LPF_Databuf[1])*Pit_Rol_Max/(RC_Top-RC_Deadzone_Top);
		else Pitch_Control=0;
		Pitch_Control=constrain_int16_t(Pitch_Control,-Pit_Rol_Max,Pit_Rol_Max);
		
		Target_Angle[0]=-Pitch_Control;//自稳时，期望俯仰角
		Target_Angle[1]=-Roll_Control;//自稳时，期望横滚角
		
		RC_Scale_Set(&RC_Calibration[2]);
		Temp_RC=(PPM_LPF_Databuf[2]-(RC_Buttom+Buttom_Safe_Deadband));//为了安全，油门杆低位死区为Buttom_Safe_Deadband
		Throttle_Control=constrain_int16_t(Temp_RC,0,1000);
		
		RC_Scale_Set(&RC_Calibration[3]);
		if(PPM_Databuf[3]<=RC_Deadzone_Buttom)  Yaw_Control=-(PPM_LPF_Databuf[3]-RC_Deadzone_Buttom)*Yaw_Max/(RC_Deadzone_Buttom-RC_Buttom);//偏航最大行程控制量+-150
		else if(PPM_Databuf[3]>=RC_Deadzone_Top)  Yaw_Control=-(PPM_LPF_Databuf[3]-RC_Deadzone_Top)*Yaw_Max/(RC_Top-RC_Deadzone_Top);
		else Yaw_Control=0;
		Yaw_Control=constrain_int16_t(Yaw_Control,-Yaw_Max,Yaw_Max);
		RC_NewData[0]=Throttle_Control;//遥感油门原始行程量
		Throttle_Rate=Get_Thr_Rate(Throttle_Control);
		Throttle_Control=Throttle_Base+Throttle_Control;
	#endif
		/***************************************************************
		左手油门时，遥控器解锁动作：左边摇杆处于低位并向内侧打杆
		左手油门时，遥控器上锁动作：左边摇杆处于低位并向外侧打杆
		***************************************************************/
		if(Throttle_Control==1000
			 &&Yaw_Control>=Yaw_Max*Scale_Pecent_Max
				 &&Roll_Control==0
					 &&Pitch_Control==0)
		{
			Unlock_Makesure_Cnt++;
			if(Forced_Lock_Makesure_Cnt<1000) Forced_Lock_Makesure_Cnt++;
		}
		
		if((Throttle_Control==1000
			 &&Yaw_Control>=Yaw_Max*Scale_Pecent_Max
				 &&Roll_Control==0
					 &&Pitch_Control==0
						 &&(Unlock_Makesure_Cnt>50*1.0))//持续1.0S
								||Forced_Lock_Makesure_Cnt>=50*5
								||unlock_flag==0)//上锁
		{
			Controler_State=Lock_Controler;
			Unlock_Makesure_Cnt=0;
			Lock_Makesure_Cnt=0;
			Forced_Lock_Makesure_Cnt=0;
			Bling_Set(&Light_3,3000,200,0.5,0,GPIOC,GPIO_Pin_8,0);
			Bling_Mode=0;
			Page_Number=0;//OLED恢复首页
			Reset_Mag_Calibartion(1);
			Reset_Accel_Calibartion(1);
			Reset_RC_Calibartion(1);
		}
		
		if(Throttle_Control==1000
			 &&Yaw_Control<=-Yaw_Max*Scale_Pecent_Max
				 &&Roll_Control==0
					 &&Pitch_Control==0)
			Lock_Makesure_Cnt++;
		
		if((Throttle_Control==1000
			 &&Yaw_Control<=-Yaw_Max*Scale_Pecent_Max
				 &&Roll_Control==0
					 &&Pitch_Control==0
						 &&Lock_Makesure_Cnt>50*1.0//持续1.0S
		          &&Gyro_Safety_Calibration_Flag==1
							 &&Check_Calibration_Flag()==0x00)
							 ||unlock_flag==1)//解锁
		{
			Controler_State=Unlock_Controler;
			if(Controler_High_Mode==2)//如果是在定高模式下解锁 
			{
				Unwanted_Lock_Flag=1;   //不需要自动进入上锁模式
	#if    (YAW_Pos_Control_Accel_Disable==1)
				Total_Controller.High_Speed_Control.Integrate=-Total_Controller.High_Speed_Control.Integrate_Max;
	#else
				Total_Controller.High_Acce_Control.Integrate=-Total_Controller.High_Acce_Control.Integrate_Max;
	#endif
			}
			else Unwanted_Lock_Flag=0;
			Lock_Makesure_Cnt=0;
			Unlock_Makesure_Cnt=0;
			Forced_Lock_Makesure_Cnt=0;
			Bling_Set(&Light_3,3000,1000,0.5,0,GPIOC,GPIO_Pin_8,0);
			Bling_Mode=0;
			Page_Number=0;//OLED恢复首页
			Reset_Mag_Calibartion(1);
			Reset_Accel_Calibartion(1);
			Reset_RC_Calibartion(1);
			Auto_ReLock_Cnt=50*6;//持续6S
			Auto_Relock_Flag_Set=0;
		}
		
		if(Controler_State==Unlock_Controler
			 &&Auto_Relock_Flag_Set==0//自动上锁位未设置
				 &&Throttle_Control==1000
					 &&Pitch_Control==0
						 &&Roll_Control==0
							 &&Yaw_Control==0//解锁后遥感回中
								 &&Unwanted_Lock_Flag==0)
		{
			Auto_Relock_Flag=1;//解锁初始时开启自动上锁标志位
			Auto_Relock_Flag_Set=1;//单次解锁后，只置位一次
		}
		
		
		if(Auto_Relock_Flag==1)
		{
			if(Throttle_Control==1000
				 &&Pitch_Control==0
					 &&Roll_Control==0
						 &&Yaw_Control==0
							 &&Controler_State==Unlock_Controler//自动上锁计数器
								 &&Unwanted_Lock_Flag==0)
			{
				Auto_ReLock_Cnt--;
				if(Auto_ReLock_Cnt<=0)  Auto_ReLock_Cnt=0;
				if(Auto_ReLock_Cnt==0)
				{
					Controler_State=Lock_Controler;//再次上锁
					Bling_Set(&Light_3,3000,200,0.5,0,GPIOC,GPIO_Pin_8,0);
					Bling_Mode=0;
				}
			}
			
			if((Throttle_Control!=1000
					||Pitch_Control!=0
						||Roll_Control!=0
							||Yaw_Control!=0)
							 &&Auto_ReLock_Cnt>0//自动上锁计数器
								&&Unwanted_Lock_Flag==0)
			{
				Auto_Relock_Flag=0;//只要遥感有动作，本次解锁后，自动上锁就不开启
				Auto_ReLock_Cnt=0;
				Bling_Set(&Light_3,3000,500,0.5,0,GPIOC,GPIO_Pin_8,0);
				Bling_Mode=0;
			}
		}
}

  if(shutdown_now_cal_flag==1)
	{
		Reset_Mag_Calibartion(1);
		Reset_Accel_Calibartion(1);
		Reset_RC_Calibartion(1);
		shutdown_now_cal_flag=0;
		Bling_Set(&Light_2,0,1000,0.5,0,GPIOC,GPIO_Pin_7,0);
		Page_Number=0;//OLED恢复首页
	}

}
