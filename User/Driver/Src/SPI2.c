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
#include "SPI2.h"

SPI_InitTypeDef   SPI_InitStructure;
/************************************
��������void SPI_Configuration(void)
˵����SPI����
��ڣ���
���ڣ���
��ע������SPI2
************************************/
void SPI2_Configuration(void)
{ 
  GPIO_InitTypeDef GPIO_InitStructure;//����GPIO�ṹ��
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);   
  //-----SPI2-----//
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;								//PB13-->SCK,PB14-->MISO,PB15-->MOSI
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;  																			//PB13/14/15�����������
  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOB,&GPIO_InitStructure);
  	
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; //����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;							//����SPI����ģʽ:����Ϊ��SPI
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;					//����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;								//����ͬ��ʱ�ӵĿ���״̬Ϊ�͵�ƽ
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;							//����ͬ��ʱ�ӵĵ�һ�������أ��������½������ݱ�����
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;									//NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ2��36MHz/2/4=4.5MHz
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;				//ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
  SPI_InitStructure.SPI_CRCPolynomial = 7;									//CRCֵ����Ķ���ʽ����ȫ˫��ģʽ��CRC��Ϊ���һ���ֽڷ��ͳ�ȥ
  SPI_Init(SPI2, &SPI_InitStructure);  											//����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ��� 
  SPI_Cmd(SPI2, ENABLE); 											   						//ʹ��SPI����
}

/***************************************
��������u8 SPI_ReadWriteByte(u8 txData)
˵����SPI��дһ���ֽں���
��ڣ�u8 txData MOSIд�����ֽ�
���ڣ�u8	MISOд����ֽ�
��ע������ֵΪ0ʱ������û�з���/���ճɹ�
****************************************/
u8 SPI2_ReadWriteByte(u8 txData)
{
  u8 retry = 0;
  
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET) //���ָ����SPI��־λ�������:���ͻ���ձ�־λ
  {
    retry++;
    if (retry > 200)			//��ʱ
      return 0;
  }
  SPI_I2S_SendData(SPI2, txData); 							//ͨ������SPIx����һ������
  retry = 0;
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) //���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ
  {
    retry++;
    if(retry > 200)				//��ʱ
      return 0;
  }
  return SPI_I2S_ReceiveData(SPI2); 						//����ͨ��SPIx������յ�����
}


void SPI2_SetSpeed(uint16 SPI_BaudRatePrescaler)
{	
  if(SPI_BaudRatePrescaler==2)  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;  //Ԥ��ƵֵΪ2
  else if(SPI_BaudRatePrescaler==4) SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;  //Ԥ��ƵֵΪ4
  else if(SPI_BaudRatePrescaler==8) SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8; //Ԥ��ƵֵΪ8
  else if(SPI_BaudRatePrescaler==16) SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;  //Ԥ��ƵֵΪ16
  else if(SPI_BaudRatePrescaler==32) SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;//Ԥ��ƵֵΪ32
  else if(SPI_BaudRatePrescaler==64) SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;  //Ԥ��ƵֵΪ64
  else if(SPI_BaudRatePrescaler==128) SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;  //Ԥ��ƵֵΪ128
  else if(SPI_BaudRatePrescaler==256) SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256; //Ԥ��ƵֵΪ256
  else  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;  //Ԥ��ƵֵΪ4  
}

