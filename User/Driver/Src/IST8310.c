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
#include "IST8310.h"
#include "HMC5883.h"


void IST8310_Init(void)
{
  Single_WriteI2C(IST8310_SLAVE_ADDRESS,0x41,0x24);//����16x�ڲ�ƽ��
  Single_WriteI2C(IST8310_SLAVE_ADDRESS,0x42,0xC0);//Set/Reset�ڲ�ƽ��
	extern_mag_id[2]=Single_ReadI2C(IST8310_SLAVE_ADDRESS,IST8310_REG_WIA);
}



IST8310 Mag_IST8310;
//����������Ǽ����벹����https://blog.csdn.net/u013636775/article/details/72675148
void Get_Mag_IST8310(void)
{
  static uint16_t IST8310_Sample_Cnt=0;
  float MagTemp[3]={0};
  IST8310_Sample_Cnt++;
  if(IST8310_Sample_Cnt==1)
  {
    Single_WriteI2C(IST8310_SLAVE_ADDRESS,IST8310_REG_CNTRL1,0x01);//Single Measurement Mode
  }
  else if(IST8310_Sample_Cnt==4)//���ټ��6ms,�˴�Ϊ8ms
  {
    Mag_IST8310.Buf[0]=Single_ReadI2C(IST8310_SLAVE_ADDRESS,0x03);//OUT_X_L_A
    Mag_IST8310.Buf[1]=Single_ReadI2C(IST8310_SLAVE_ADDRESS,0x04);//OUT_X_H_A
    Mag_IST8310.Buf[2]=Single_ReadI2C(IST8310_SLAVE_ADDRESS,0x05);//OUT_Y_L_A
    Mag_IST8310.Buf[3]=Single_ReadI2C(IST8310_SLAVE_ADDRESS,0x06);//OUT_Y_H_A
    Mag_IST8310.Buf[4]=Single_ReadI2C(IST8310_SLAVE_ADDRESS,0x07);//OUT_Z_L_A
    Mag_IST8310.Buf[5]=Single_ReadI2C(IST8310_SLAVE_ADDRESS,0x08);//OUT_Z_H_A
	
    /*****************�ϳ��������������******************/
    Mag_IST8310.Mag_Data[0]=(int16_t)((Mag_IST8310.Buf[1]<<8)|Mag_IST8310.Buf[0]);
    Mag_IST8310.Mag_Data[1]=(int16_t)((Mag_IST8310.Buf[3]<<8)|Mag_IST8310.Buf[2]);
    Mag_IST8310.Mag_Data[2]=(int16_t)((Mag_IST8310.Buf[5]<<8)|Mag_IST8310.Buf[4]);
		
		Mag_IST8310.Mag_Data[0]/=330.0f;
		Mag_IST8310.Mag_Data[1]/=330.0f;
		Mag_IST8310.Mag_Data[2]/=330.0f;
		
    IST8310_Sample_Cnt=0;
  }
	
  Mag_IST8310.x = Mag_IST8310.Mag_Data[0];
  Mag_IST8310.y = -Mag_IST8310.Mag_Data[1];
  Mag_IST8310.z = Mag_IST8310.Mag_Data[2];
		
  DataMag.x=Compass.x=Mag_IST8310.x;
  DataMag.y=Compass.y=Mag_IST8310.y;
  DataMag.z=Compass.z=Mag_IST8310.z;
	
  MagTemp[0]=GildeAverageValueFilter_MAG(Mag_IST8310.x-Mag_Offset[0],Data_X_MAG);//���������˲�
  MagTemp[1]=GildeAverageValueFilter_MAG(Mag_IST8310.y-Mag_Offset[1],Data_Y_MAG);
  MagTemp[2]=GildeAverageValueFilter_MAG(Mag_IST8310.z-Mag_Offset[2],Data_Z_MAG);
   
  Mag_Data[0]=Mag_IST8310.Mag_Data_Correct[0]=MagTemp[0];
  Mag_Data[1]=Mag_IST8310.Mag_Data_Correct[1]=MagTemp[1];
  Mag_Data[2]=Mag_IST8310.Mag_Data_Correct[2]=MagTemp[2];
  
  /************��������ǲ���*****************/
  MagN.x=Mag_IST8310.thx = MagTemp[0] * Cos_Roll+ MagTemp[2] * Sin_Roll;
  MagN.y=Mag_IST8310.thy = MagTemp[0] * Sin_Pitch*Sin_Roll
                          +MagTemp[1] * Cos_Pitch
                          -MagTemp[2] * Cos_Roll*Sin_Pitch;
  /***********�����еõ������ƹ۲�Ƕ�*********/
  Mag_IST8310.Angle_Mag=atan2(Mag_IST8310.thx,Mag_IST8310.thy)*57.296;
}


float Earth_Magnetic_Field_Intensity=0;
void Compass_Tradeoff(void)
{
	if(extern_mag_id[2]==0x10)
	{
		Get_Mag_IST8310();
		Earth_Magnetic_Field_Intensity=sqrt(Mag_Data[0]*Mag_Data[0]
																				+Mag_Data[1]*Mag_Data[1]
																					+Mag_Data[2]*Mag_Data[2]);	
	}
	else if(extern_mag_id[0]==0x48)
	{
    HMC5883L_StateMachine();
    Earth_Magnetic_Field_Intensity=sqrt(Mag_Data[0]*Mag_Data[0]
                                        +Mag_Data[1]*Mag_Data[1]
                                          +Mag_Data[2]*Mag_Data[2]);	
	}
  else if(extern_mag_id[1]==0xff)
  { 
    QMC5883L_StateMachine();
    Earth_Magnetic_Field_Intensity=sqrt(Mag_Data[0]*Mag_Data[0]
                                        +Mag_Data[1]*Mag_Data[1]
                                          +Mag_Data[2]*Mag_Data[2]);		
		
  }
  WP_Sensor.mag_raw.x=Compass.x;
	WP_Sensor.mag_raw.y=Compass.y;
	WP_Sensor.mag_raw.z=Compass.z;
}


