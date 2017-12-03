#include "Headfile.h"
#include "NRF24L01.H"
/*----------------------------------------------------------------------------------------------------------------------/
        *               本程序只供购买者学习使用，版权著作权属于无名科创团队，
        *               无名科创团队将飞控程序源码提供给购买者，
        *               购买者要为无名科创团队提供保护，
        *               未经作者许可，不得将源代码提供给他人
        *               不得将源代码放到网上供他人免费下载，
        *               更不能以此销售牟利，如发现上述行为，
        *               无名科创团队将诉之以法律解决！！！
-----------------------------------------------------------------------------------------------------------------------/
        *               生命不息、奋斗不止；前人栽树，后人乘凉！！！
        *               开源不易，且学且珍惜，祝早日逆袭、进阶成功！！！
-----------------------------------------------------------------------------------------------------------------------/
	*		无名科创开源飞控 V1.1	武汉科技大学  By.YuYi
	*		CSDN博客: http://blog.csdn.net/u011992534
	*               优酷ID：NamelessCotrun无名小哥
	*               无名科创开源飞控QQ群：540707961
        *               https://shop348646912.taobao.com/?spm=2013.1.1000126.2.5ce78a88ht1sO2
        *               百度贴吧:无名科创开源飞控
        *               修改日期:2017/10/30
        *               版本：V1.1
        *               版权所有，盗版必究。
        *               Copyright(C) 武汉科技大学无名科创团队 2017-2019
        *               All rights reserved
----------------------------------------------------------------------------------------------------------------------*/
#define RC_Middle 1500
#define RC_Deadband 80
/***************************觉得不错，欢迎打赏，请小哥吃热干面：支付宝账号：1094744141@qq.com*********************************/
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


uint16 Throttle_Control=0;
int16 Pitch_Control=0,Roll_Control=0,Yaw_Control=0;
int16 Target_Angle[2]={0};
uint8 RC_Control[32];
uint16 Last_Throttle_Control,Pre_Last_Throttle_Control;
uint16 Throttle_Base=1000,TempThrottle_Control;
uint16 QuadData[2];
uint8 QuadRemoteFlag[4]={0};
int16 RC_NewData[4]={0};
uint16 RC_Init_Cnt=0;
uint16_t Controler_State=0;
uint16_t Auto_ReLock_Cnt=0;//自动上锁计数器
uint8_t Auto_Relock_Flag=0;
uint8_t Auto_Relock_Flag_Set=0;
int16 Y_T=0,T_temp=0;
int16 Temp_RC=0;
uint16_t Unlock_Makesure_Cnt=0,Lock_Makesure_Cnt=0;

uint16_t NRF24L01_Channel[10]={0};
void NRF24L01_RC(void )
{
  if(RC_Init_Cnt<=5)
  {
    Throttle_Control=1000;
    Pitch_Control=0;
    Roll_Control=0;
    Yaw_Control=0;
    RC_Init_Cnt++;
  }
/****************PPM接收*****************/
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

/****************PPM接收*****************/
#ifdef RC_PPM
 if(PPM_Databuf[0]<=1480)  Roll_Control=(1450-PPM_Databuf[0])*50/400;
 else if(PPM_Databuf[0]>=1520)  Roll_Control=(1550-PPM_Databuf[0])*50/400;
 else Roll_Control=0;

 if(PPM_Databuf[1]<=1450)  Pitch_Control=(1450-PPM_Databuf[1])*50/400;
 else if(PPM_Databuf[1]>=1550)  Pitch_Control=(1550-PPM_Databuf[1])*50/400;
 else Pitch_Control=0;

 Target_Angle[0]=-Pitch_Control;
 Target_Angle[1]=-Roll_Control;

 Temp_RC=(PPM_Databuf[2]-1100);
 if(Temp_RC<=5)     Throttle_Control=0;
 else if(Temp_RC>=1000)  Throttle_Control=1000;
 else Throttle_Control=Temp_RC;

 if(PPM_Databuf[3]<=1450)  Yaw_Control=-(PPM_Databuf[3]-1450)*200/400;
 else if(PPM_Databuf[3]>=1550)  Yaw_Control=-(PPM_Databuf[3]-1550)*200/400;
 else Yaw_Control=0;
 if(Yaw_Control>=200) Yaw_Control=200;
 else if(Yaw_Control<=-200) Yaw_Control=-200;

 RC_NewData[0]=Throttle_Control;//遥感油门原始行程量
 Throttle_Rate=Get_Thr_Rate(Throttle_Control);
 Throttle_Control=Throttle_Base+Throttle_Control;
#endif


  if(Throttle_Control==1000
       &&Yaw_Control>=80
         &&Roll_Control<=-40
           &&Pitch_Control<=-40)
    Unlock_Makesure_Cnt++;

  if(Throttle_Control==1000
       &&Yaw_Control>=70
         &&Roll_Control<=-40
           &&Pitch_Control<=-40
             &&Unlock_Makesure_Cnt>250*1)//持续2S
  {
      Controler_State=Lock_Controler;
      Unlock_Makesure_Cnt=0;
      Bling_Set(&Light_1,3000,50,0.5,0,GPIOC,GPIO_Pin_4,0);
      Bling_Set(&Light_2,3000,50,0.5,0,GPIOC,GPIO_Pin_5,0);
      Bling_Set(&Light_3,3000,50,0.5,0,GPIOC,GPIO_Pin_10,0);
      Bling_Mode=0;
      Page_Number=0;//OLED恢复首页
      Reset_Mag_Calibartion(1);
      Reset_Accel_Calibartion(1);
  }

  if(Throttle_Control==1000
      &&Yaw_Control<=-70
        &&Roll_Control>=40
          &&Pitch_Control<=-40)
       Lock_Makesure_Cnt++;

   if(Throttle_Control==1000
      &&Yaw_Control<=-70
        &&Roll_Control>=40
          &&Pitch_Control<=-40
            &&Lock_Makesure_Cnt>250*1)//持续2S
  {
      Controler_State=Unlock_Controler;
      Lock_Makesure_Cnt=0;
      Bling_Set(&Light_1,5000,500,0.8,0,GPIOC,GPIO_Pin_4,0);
      Bling_Set(&Light_2,5000,500,0.5,0,GPIOC,GPIO_Pin_5,0);
      Bling_Set(&Light_3,5000,500,0.3,0,GPIOC,GPIO_Pin_10,0);
      Bling_Mode=0;
      Page_Number=0;//OLED恢复首页
      Reset_Mag_Calibartion(1);
      Reset_Accel_Calibartion(1);
      Auto_ReLock_Cnt=250*6;//持续10S
      Auto_Relock_Flag_Set=0;
  }

  if(Controler_State==Unlock_Controler
     &&Auto_Relock_Flag_Set==0//自动上锁位未设置
      &&Throttle_Control==1000
       &&Pitch_Control==0
        &&Roll_Control==0
         &&Yaw_Control==0)//解锁后遥感回中
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
          &&Controler_State==Unlock_Controler)//自动上锁计数器
    {
     Auto_ReLock_Cnt--;
     if(Auto_ReLock_Cnt<=0)  Auto_ReLock_Cnt=0;
     if(Auto_ReLock_Cnt==0)
     {
        Controler_State=Lock_Controler;//再次上锁
        Bling_Set(&Light_1,3000,50,0.5,0,GPIOC,GPIO_Pin_4,0);
        Bling_Set(&Light_2,3000,50,0.5,0,GPIOC,GPIO_Pin_5,0);
        Bling_Set(&Light_3,3000,50,0.5,0,GPIOC,GPIO_Pin_10,0);
        Bling_Mode=0;
     }
    }

    if((Throttle_Control!=1000
        ||Pitch_Control!=0
         ||Roll_Control!=0
          ||Yaw_Control!=0)
            &&Auto_ReLock_Cnt>0)//自动上锁计数器
   {
      Auto_Relock_Flag=0;//只要遥感有动作，本次解锁后，自动上锁就不开启
      Bling_Set(&Light_1,3000,200,0.2,0,GPIOC,GPIO_Pin_4,0);
      Bling_Set(&Light_2,3000,200,0.4,0,GPIOC,GPIO_Pin_5,0);
      Bling_Set(&Light_3,3000,200,0.7,0,GPIOC,GPIO_Pin_10,0);
      Bling_Mode=0;
   }
  }
}
