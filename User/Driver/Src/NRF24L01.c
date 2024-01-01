/* Copyright (c)  2019-2025 Wuhan Nameless Innovation Technology Co.,Ltd. All rights reserved.*/
/*----------------------------------------------------------------------------------------------------------------------/
                ��Դ����������ѣ������ߵ���ʷ�Ѿ�֤�����ڹ�����������£���������Ŀ�Դ������������˰����ߣ��Է��ز�����
								Ŀ���Ƶķ�ʽ�в�ͨ���õĿ�Դ��Ŀ��Ҫ��רְ��Ա�����ۺ�����ְ��ֽ�ѧ��ͳ���û�����������ʵ������ɶԲ�
								Ʒ��һ�δ���������������������ۺϿ��ǣ������ɿؿ�Դ�����У������������˾���漤��ܴ��룬�汾������ʵ��
								���ܣ����ڹ�˾��Ʒ���������������Ӱ��ͻ�ѧϰ���������ȫ�����Ÿ��ͻ�ѧϰ���ͻ���ֲ�Ͷ��ο��������뱣����
								���Ȩ��
-----------------------------------------------------------------------------------------------------------------------/
*               ������ֻ��������ѧϰʹ�ã���Ȩ����Ȩ���������ƴ��Ŷӣ������ƴ��Ŷӽ��ɿس���Դ���ṩ�������ߣ�
*               ������ҪΪ�����ƴ��Ŷ��ṩ������δ��������ɣ����ý�Դ�����ṩ�����ˣ����ý�Դ����ŵ����Ϲ�����������أ� 
*               �������Դ�����Ĳ�����緢��������Ϊ�������ƴ��Ŷӽ���֮�Է��ɽ��������
-----------------------------------------------------------------------------------------------------------------------
*                                                 Ϊʲôѡ���������£�
*                                         �ж����ļ۸�������׵Ŀ�Դ�ɿأ�
*                                         ����ҵ������֮������µ��ۺ����
*                                         ׷�����û����飬��Ч����ѧϰ֮·��
*                                         ���²��ٹµ�������������տ�Դ�߶ȣ�
*                                         ��Ӧ���ҷ�ƶ���٣��ٽ��������ƹ�ƽ��
*                                         ��ʱ���ܶ�����ʣ����������˹�ͬ�塣 
-----------------------------------------------------------------------------------------------------------------------
*               ������Ϣ���ܶ���ֹ��ǰ�����������˳���������
*               ��Դ���ף���ѧ����ϧ��ף������Ϯ�����׳ɹ�������
*               ѧϰ�����ߣ��������Ƽ���DJI��ZEROTECH��XAG��AEE��GDU��AUTEL��EWATT��HIGH GREAT�ȹ�˾��ҵ
*               ��ְ�����뷢�ͣ�15671678205@163.com���豸ע��ְ����λ����λ��������
*               �����ƴ���Դ�ɿ�QQȺ��2��Ⱥ465082224��1��Ⱥ540707961����Ա������
*               CSDN���ͣ�http://blog.csdn.net/u011992534
*               �ſ�ID��NamelessCotrun����С��
*               Bվ��ѧ��Ƶ��https://space.bilibili.com/67803559/#/video
*               �ͻ�ʹ���ĵá��Ľ������������http://www.openedv.com/forum.php?mod=viewthread&tid=234214&extra=page=1
*               �Ա����̣�https://shop348646912.taobao.com/?spm=2013.1.1000126.2.5ce78a88ht1sO2
*               �ٶ�����:�����ƴ���Դ�ɿ�
*               ��˾����:www.nameless.tech
*               �������¹����׿�TI��Դ�ɿ���Ƴ��ԡ�֪��ר��:https://zhuanlan.zhihu.com/p/54471146
*               �޸�����:2019/11/27                    
*               �汾���۷���PRO����WisdomPilot_Pro_V1.0.0
*               ��Ȩ���У�����ؾ���
*               Copyright(C) 2019-2025 �人�������¿Ƽ����޹�˾ 
*               All rights reserved
-----------------------------------------------------------------------------------------------------------------------
*               ��Ҫ��ʾ��
*               �����Ա�����ת�ֵķɿء��������ѡ�����ѧ�ܵĶ����Խ��ۺ�Ⱥѧϰ������
*               ����ֱ�����������������������ϣ��������´�����������Ȩ�����˲��ý�
*               ���ϴ��봫���Ϲ��������أ�������ı��ΪĿ���������ϴ��룬�����д˲�
*               ���ߣ���˾����ǰ��֪����1���ڼ�ʱ�����������ѧУ����λ����������
*               ������ַ��Ϣ�ᱻ�����ڹ�˾�������ٷ�΢�Ź���ƽ̨���ٷ��������͡�֪��
*               ר���Լ��Ա�������ҳ���Թ�ʾ���棬����������Ϊ�����Ϊ�����۵㣬Ӱ��
*               ��ѧ���ҹ���������������ܿ�ͺ������˻����������������ء�
*               �����Ϊ����˾����ش���ʧ�ߣ����Է���;���������л���ĺ�����лл������
----------------------------------------------------------------------------------------------------------------------*/
#include "Headfile.h"
#include "NRF24L01.H"


uint16_t RC_Buttom=1000,RC_Top=2000,RC_Middle=1500,RC_Deadband=100;
uint16_t RC_Deadzone_Buttom=0,RC_Deadzone_Top=0;


//-----NRF24L01���ͽ��յ�ַ-----//
const u8 TX_ADDRESS[TX_ADR_WIDTH] = {0x12,0x37,0x96,0x75,0xA1}; //���͵�ַ
const u8 RX_ADDRESS[RX_ADR_WIDTH] = {0x12,0x37,0x96,0x75,0xA1}; //���յ�ַ
u8 Data_buf[32]={0,0};


//-----NRF24L01��������-----//
u8 g_NRFRevData[RX_PLOAD_WIDTH]={0,0};
//-----NRF24L01��������-----//
u8 g_NRFSendData[TX_PLOAD_WIDTH]={0};

//-----NRF24L01���ռ�����-----//
__IO u8 g_NRFRevCnt = 0;

/********************************
��������void NRF24L01_Init(void)
˵������ʼ��24L01
��ڣ���
���ڣ���
��ע����
*********************************/
void NRF24L01_Init(void)
{
  NRF24L01_CE_L; 			//ʹ��24L01
  NRF24L01_CSN_H;			//SPIƬѡȡ��
}

/******************************
��������u8 NRF24L01_Check(void)
˵�������24L01�Ƿ����
��ڣ���
���ڣ�u8
0���ɹ�;
1��ʧ��
��ע����
*******************************/
u8 NRF24L01_Check(void)
{
  u8 buf[5] = {0XA5,0XA5,0XA5,0XA5,0XA5}, i;
  NRF24L01_Write_Buf(WRITE_REG_NRF+TX_ADDR,buf,5);//д��5���ֽڵĵ�ַ��TX_ADDRΪ��ַ��WRITE_REG_NRFΪ����
  NRF24L01_Read_Buf(TX_ADDR,buf,5);//����д��ĵ�ַ
  for (i = 0; i < 5; i++)
    if (buf[i] != 0XA5)
      break;
  if (i != 5)
    return 1;//���24L01����
  return 0;//��⵽24L01
}

/************************************************
��������void NRF24L01_Write_Reg(u8 reg, u8 value)
˵����SPIд�Ĵ���
��ڣ�u8 reg		�Ĵ�����ַ
u8 value	��Ҫд���ֵ
���ڣ���
��ע����
************************************************/
void NRF24L01_Write_Reg(u8 reg, u8 value)
{
  NRF24L01_CSN_L;                 	//ʹ��SPI����
  SPI2_ReadWriteByte(reg);			    //���ͼĴ����ţ�������Զ�ȡ���Ĵ�����״̬
  SPI2_ReadWriteByte(value);      		//д��Ĵ�����ֵ
  NRF24L01_CSN_H;                 	//��ֹSPI����
}

/************************************
��������u8 NRF24L01_Read_Reg(u8 reg)
˵������ȡSPI�Ĵ���ֵ
��ڣ�u8 reg		�Ĵ�����ַ
���ڣ�u8	״̬
��ע����
*************************************/
//
//reg:Ҫ���ļĴ���
u8 NRF24L01_Read_Reg(u8 reg)
{
  u8 reg_val;
  
  NRF24L01_CSN_L;          				//ʹ��SPI����
  SPI2_ReadWriteByte(reg);   				//���ͼĴ�����
  reg_val = SPI2_ReadWriteByte(0XFF);	    //��ȡ�Ĵ������ݣ�ֻ��Ҫ��ȡ�������������⴫�����ݹ�ȥ
  NRF24L01_CSN_H;          			    //��ֹSPI����
  return(reg_val);           				//����״ֵ̬
}

/*******************************************************
��������void NRF24L01_Read_Buf(u8 reg, u8 *pBuf, u8 len)
˵������ָ��λ�ö���ָ�����ȵ�����
��ڣ�u8 reg		�Ĵ���(λ��)
u8 *pBuf	����ָ��
u8 len		���ݳ���
���ڣ���
��ע����
*******************************************************/
void NRF24L01_Read_Buf(u8 reg, u8 *pBuf, u8 len)
{
  u8 i;
  
  NRF24L01_CSN_L;           							//ʹ��SPI����
  SPI2_ReadWriteByte(reg);									//���ͼĴ���ֵ(λ��)
  for (i = 0; i < len; i++)
    pBuf[i] = SPI2_ReadWriteByte(0XFF);		//��������
  NRF24L01_CSN_H;       									//�ر�SPI����
}

/********************************************************
��������void NRF24L01_Write_Buf(u8 reg, u8 *pBuf, u8 len)
˵������ָ��λ��дָ�����ȵ�����
��ڣ�u8 reg		�Ĵ���(λ��)
u8 *pBuf	����ָ��
u8 len		���ݳ���
���ڣ���
��ע����
********************************************************/
void NRF24L01_Write_Buf(u8 reg, u8 *pBuf, u8 len)
{
  u8 i;
  
  NRF24L01_CSN_L;          						//ʹ��SPI����
  SPI2_ReadWriteByte(reg);							//���ͼĴ���ֵ(λ��)
  for	(i = 0; i < len; i++)
    SPI2_ReadWriteByte(*pBuf++); 			//д������
  NRF24L01_CSN_H;       							//�ر�SPI����
}

/***************************************
��������u8 NRF24L01_TxPacket(u8 *txbuf)
˵��������NRF24L01����һ������
��ڣ�u8 *txbuf	�����������׵�ַ
���ڣ�U8	�������״��
��ע����
****************************************/
u8 NRF24L01_TxPacket(u8 *txbuf)
{
  u8 sta;
  NRF24L01_CE_L;																						//Ƭѡ
  NRF24L01_Write_Buf(WR_TX_PLOAD, txbuf, TX_PLOAD_WIDTH);		//д���ݵ�TX BUF  32���ֽ�
  NRF24L01_CE_H;
  while (NRF24L01_IRQ != 0);																//�ȴ��������
  sta = NRF24L01_Read_Reg(STATUS);  												//��ȡ״̬�Ĵ�����ֵ
  NRF24L01_Write_Reg(WRITE_REG_NRF + STATUS, sta); 					//���TX_DS��MAX_RT�жϱ�־
  if (sta & MAX_TX)																					//�ﵽ����ط�����
  {
    NRF24L01_Write_Reg(FLUSH_TX, 0xFF);											//���TX FIFO�Ĵ���
    return MAX_TX;
  }
  if (sta & TX_OK)																					//�������
  {
    return TX_OK;
  }
  return 0xFF;																							//����ԭ����ʧ��
}

/***************************************
��������u8 NRF24L01_RxPacket(u8 *rxbuf)
˵��������NRF24L01����һ������
��ڣ�u8 *txbuf	�����������׵�ַ
���ڣ�u8	0���������
1�����ղ��ɹ�
��ע����
****************************************/
u8 NRF24L01_RxPacket(u8 *rxbuf)
{
  u8 sta;
  sta = NRF24L01_Read_Reg(STATUS);  							//��ȡ״̬�Ĵ�����ֵ
  NRF24L01_Write_Reg(WRITE_REG_NRF + STATUS,sta); 			//���TX_DS��MAX_RT�жϱ�־
  if (sta & RX_OK)											//���յ�����
  {
    NRF24L01_Read_Buf(RD_RX_PLOAD, rxbuf, RX_PLOAD_WIDTH);	//��ȡ����
    NRF24L01_Write_Reg(FLUSH_RX, 0xFF);						//���RX FIFO�Ĵ���
    return 0;
  }
  return 1;													//û�յ��κ�����
}

/*****************************************************
��������void NRF24L01_RX_Mode(void)
˵������ʼ��NRF24L01��RXģʽ
��ڣ���
���ڣ���
��ע��
����RX��ַ,дRX���ݿ��,ѡ��RFƵ��,�����ʺ�LNA HCURR
��CE��ߺ�,������RXģʽ,�����Խ���������
******************************************************/
void NRF24L01_RX_Mode(void)
{
  EXTI_InitTypeDef EXTI_InitStructure;
  EXTI_ClearITPendingBit(EXTI_Line12);//����жϱ�־
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource12); //ѡ���жϹܽ�PB12
  //����EXTI�ṹ��
  //���ڷ���ģʽ���Ѿ����ж����жϣ����Ե��л��ɽ���ģʽʱ����Ҫ������������
  EXTI_InitStructure.EXTI_Line = EXTI_Line12;							//EXTI���жϿ�ͨ
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;				    //����Ϊ�жϻ����¼�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;				//�½��ش���
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;							//ʹ��EXTI���ж�
  EXTI_Init(&EXTI_InitStructure);
  
  NRF24L01_CE_L;
  NRF24L01_Write_Buf(WRITE_REG_NRF+TX_ADDR,(u8*)TX_ADDRESS,TX_ADR_WIDTH);	//дTX�ڵ��ַ
  NRF24L01_Write_Buf(WRITE_REG_NRF+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH);//дRX�ڵ��ַ
  NRF24L01_Write_Reg(WRITE_REG_NRF+EN_AA,0x01);    						//ʹ��ͨ��0���Զ�Ӧ��
  NRF24L01_Write_Reg(WRITE_REG_NRF+EN_RXADDR,0x01);						//ʹ��ͨ��0�Ľ��յ�ַ
  NRF24L01_Write_Reg(WRITE_REG_NRF+RF_CH,40);	    						//����RFͨ��Ƶ��
  NRF24L01_Write_Reg(WRITE_REG_NRF+RX_PW_P0,RX_PLOAD_WIDTH);				//ѡ��ͨ��0����Ч���ݿ��
  NRF24L01_Write_Reg(WRITE_REG_NRF+RF_SETUP,0x0f);						//����TX�������,0db����,2Mbps,���������濪��
  NRF24L01_Write_Reg(WRITE_REG_NRF+NRF24L01_CONFIG,0x0f);				//���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ
  NRF24L01_CE_H; 																																	//CEΪ��,�������ģʽ
}

/*****************************************************************************************
��������void NRF24L01_TX_Mode(void)
˵������ʼ��NRF24L01��TXģʽ
��ڣ���
���ڣ���
��ע��
����TX��ַ,дTX���ݿ��,����RX�Զ�Ӧ��ĵ�ַ,���TX��������,ѡ��RFƵ��,�����ʺ�LNA HCURR
PWR_UP,CRCʹ��
CEΪ�ߴ���10us,����������
******************************************************************************************/
void NRF24L01_TX_Mode(void)
{
  EXTI_InitTypeDef EXTI_InitStructure;//����EXTI�ṹ��
  //���ڽ���ģʽ�µ�IRQ��������Ϊ�ж��������ţ����Ե��л��ɷ���ģʽʱ����Ҫ���ж��������ŵĹ���ȡ��
  EXTI_InitStructure.EXTI_Line = EXTI_Line12;//EXTI���жϿ�ͨ
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//����Ϊ�жϻ����¼�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//�½��ش���
  EXTI_InitStructure.EXTI_LineCmd =ENABLE;//ʧ��EXTI���ж�
  EXTI_Init(&EXTI_InitStructure);
  
  NRF24L01_CE_L;
  NRF24L01_Write_Buf(WRITE_REG_NRF+TX_ADDR,(u8*)TX_ADDRESS,TX_ADR_WIDTH);	//дTX�ڵ��ַ
  NRF24L01_Write_Buf(WRITE_REG_NRF+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH); //����TX�ڵ��ַ,��ҪΪ��ʹ��ACK
  NRF24L01_Write_Reg(WRITE_REG_NRF+EN_AA,0x01); //ʹ��ͨ��0�Զ�Ӧ��
  NRF24L01_Write_Reg(WRITE_REG_NRF+EN_RXADDR,0x01); //ʹ��ͨ��0�Ľ��յ�ַ
  NRF24L01_Write_Reg(WRITE_REG_NRF+SETUP_RETR,0x1a);//�����Զ��ط����ʱ��:500us + 86us;����Զ��ط�����:15��
  NRF24L01_Write_Reg(WRITE_REG_NRF+RF_CH,40);//����RFͨ��Ϊ40
  NRF24L01_Write_Reg(WRITE_REG_NRF+RF_SETUP,0x0f);//����TX�������,0db����,2Mbps,���������濪��
  NRF24L01_Write_Reg(WRITE_REG_NRF+NRF24L01_CONFIG,0x0e);//���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ,���������ж�
  NRF24L01_CE_H;																															//CEΪ��,10us����������
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
  for(i=0;i<4;i++)//��ң����ǰ�ĸ�ͨ���˲�����
  {
    PPM_LPF_Databuf[i]=(uint16_t)(LPButterworth(PPM_Databuf[i],&RC_LPF_Buffer[i],&Butter_5HZ_Parameter_RC));
  }
}


int16_t Throttle_Rate=0;
int16_t Get_Thr_Rate(float Thr)//���ű仯��
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
uint16_t Auto_ReLock_Cnt=0;//�Զ�����������
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

  /****************NRF24L01����*****************/
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
  NRF24L01_Channel[0]=((uint16_t)(RC_Control[6]<<8)|RC_Control[7])*3000/4095;     //�����ch1
  NRF24L01_Channel[1]=((uint16_t)(RC_Control[4]<<8)|RC_Control[5])*3000/4095;     //������ch2
  NRF24L01_Channel[2]=((uint16_t)(RC_Control[0]<<8)|RC_Control[1])*1000/4095+1000;//����ͨ��ch3
  NRF24L01_Channel[3]=((uint16_t)(RC_Control[2]<<8)|RC_Control[3])*3000/4095;     //ƫ��ͨ��ch4
  
  NRF24L01_Channel[4]=((uint16_t)((RC_Control[12]&0x0008)>>3)*2000);              //��������ch5
  NRF24L01_Channel[5]=((uint16_t)((RC_Control[12]&0x0004)>>2)*2000);              //��������ch6
  NRF24L01_Channel[6]=((uint16_t)((RC_Control[12]&0x0002)>>1)*2000);              //��������ch7
  NRF24L01_Channel[7]=((uint16_t)((RC_Control[12]&0x0001)>>0)*2000);              //��������ch8
  
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
  
  RC_NewData[0]=Throttle_Control;//ң������ԭʼ�г���
  Throttle_Rate=Get_Thr_Rate(Throttle_Control);
  Throttle_Control=Throttle_Base+Throttle_Control;
#endif


if(sbus_update_flag==1||rc_update_flag==1||ppm_update_flag==1)
{
	  sbus_update_flag=0;
	  rc_update_flag=0;
	  ppm_update_flag=0;
		/****************PPM����*****************/
	#ifdef RC_PPM
		RC_Data_LPF_Filter();
		RC_Scale_Set(&RC_Calibration[0]);
		if(PPM_Databuf[0]<=RC_Deadzone_Buttom)  Roll_Control=(RC_Deadzone_Buttom-PPM_LPF_Databuf[0])*Pit_Rol_Max/(RC_Deadzone_Buttom-RC_Buttom);//����г̿�����+-45
		else if(PPM_Databuf[0]>=RC_Deadzone_Top)  Roll_Control=(RC_Deadzone_Top-PPM_LPF_Databuf[0])*Pit_Rol_Max/(RC_Top-RC_Deadzone_Top);
		else Roll_Control=0;
		Roll_Control=constrain_int16_t(Roll_Control,-Pit_Rol_Max,Pit_Rol_Max);
		
		RC_Scale_Set(&RC_Calibration[1]);
		if(PPM_Databuf[1]<=RC_Deadzone_Buttom)  Pitch_Control=(RC_Deadzone_Buttom-PPM_LPF_Databuf[1])*Pit_Rol_Max/(RC_Deadzone_Buttom-RC_Buttom);//����г̿�����+-45
		else if(PPM_Databuf[1]>=RC_Deadzone_Top)  Pitch_Control=(RC_Deadzone_Top-PPM_LPF_Databuf[1])*Pit_Rol_Max/(RC_Top-RC_Deadzone_Top);
		else Pitch_Control=0;
		Pitch_Control=constrain_int16_t(Pitch_Control,-Pit_Rol_Max,Pit_Rol_Max);
		
		Target_Angle[0]=-Pitch_Control;//����ʱ������������
		Target_Angle[1]=-Roll_Control;//����ʱ�����������
		
		RC_Scale_Set(&RC_Calibration[2]);
		Temp_RC=(PPM_LPF_Databuf[2]-(RC_Buttom+Buttom_Safe_Deadband));//Ϊ�˰�ȫ�����Ÿ˵�λ����ΪButtom_Safe_Deadband
		Throttle_Control=constrain_int16_t(Temp_RC,0,1000);
		
		RC_Scale_Set(&RC_Calibration[3]);
		if(PPM_Databuf[3]<=RC_Deadzone_Buttom)  Yaw_Control=-(PPM_LPF_Databuf[3]-RC_Deadzone_Buttom)*Yaw_Max/(RC_Deadzone_Buttom-RC_Buttom);//ƫ������г̿�����+-150
		else if(PPM_Databuf[3]>=RC_Deadzone_Top)  Yaw_Control=-(PPM_LPF_Databuf[3]-RC_Deadzone_Top)*Yaw_Max/(RC_Top-RC_Deadzone_Top);
		else Yaw_Control=0;
		Yaw_Control=constrain_int16_t(Yaw_Control,-Yaw_Max,Yaw_Max);
		RC_NewData[0]=Throttle_Control;//ң������ԭʼ�г���
		Throttle_Rate=Get_Thr_Rate(Throttle_Control);
		Throttle_Control=Throttle_Base+Throttle_Control;
	#endif
		/***************************************************************
		��������ʱ��ң�����������������ҡ�˴��ڵ�λ�����ڲ���
		��������ʱ��ң�����������������ҡ�˴��ڵ�λ���������
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
						 &&(Unlock_Makesure_Cnt>50*1.0))//����1.0S
								||Forced_Lock_Makesure_Cnt>=50*5
								||unlock_flag==0)//����
		{
			Controler_State=Lock_Controler;
			Unlock_Makesure_Cnt=0;
			Lock_Makesure_Cnt=0;
			Forced_Lock_Makesure_Cnt=0;
			Bling_Set(&Light_3,3000,200,0.5,0,GPIOC,GPIO_Pin_8,0);
			Bling_Mode=0;
			Page_Number=0;//OLED�ָ���ҳ
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
						 &&Lock_Makesure_Cnt>50*1.0//����1.0S
		          &&Gyro_Safety_Calibration_Flag==1
							 &&Check_Calibration_Flag()==0x00)
							 ||unlock_flag==1)//����
		{
			Controler_State=Unlock_Controler;
			if(Controler_High_Mode==2)//������ڶ���ģʽ�½��� 
			{
				Unwanted_Lock_Flag=1;   //����Ҫ�Զ���������ģʽ
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
			Page_Number=0;//OLED�ָ���ҳ
			Reset_Mag_Calibartion(1);
			Reset_Accel_Calibartion(1);
			Reset_RC_Calibartion(1);
			Auto_ReLock_Cnt=50*6;//����6S
			Auto_Relock_Flag_Set=0;
		}
		
		if(Controler_State==Unlock_Controler
			 &&Auto_Relock_Flag_Set==0//�Զ�����λδ����
				 &&Throttle_Control==1000
					 &&Pitch_Control==0
						 &&Roll_Control==0
							 &&Yaw_Control==0//������ң�л���
								 &&Unwanted_Lock_Flag==0)
		{
			Auto_Relock_Flag=1;//������ʼʱ�����Զ�������־λ
			Auto_Relock_Flag_Set=1;//���ν�����ֻ��λһ��
		}
		
		
		if(Auto_Relock_Flag==1)
		{
			if(Throttle_Control==1000
				 &&Pitch_Control==0
					 &&Roll_Control==0
						 &&Yaw_Control==0
							 &&Controler_State==Unlock_Controler//�Զ�����������
								 &&Unwanted_Lock_Flag==0)
			{
				Auto_ReLock_Cnt--;
				if(Auto_ReLock_Cnt<=0)  Auto_ReLock_Cnt=0;
				if(Auto_ReLock_Cnt==0)
				{
					Controler_State=Lock_Controler;//�ٴ�����
					Bling_Set(&Light_3,3000,200,0.5,0,GPIOC,GPIO_Pin_8,0);
					Bling_Mode=0;
				}
			}
			
			if((Throttle_Control!=1000
					||Pitch_Control!=0
						||Roll_Control!=0
							||Yaw_Control!=0)
							 &&Auto_ReLock_Cnt>0//�Զ�����������
								&&Unwanted_Lock_Flag==0)
			{
				Auto_Relock_Flag=0;//ֻҪң���ж��������ν������Զ������Ͳ�����
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
		Page_Number=0;//OLED�ָ���ҳ
	}

}
