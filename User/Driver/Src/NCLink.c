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
#include "Headfile.h"//�û��Լ��⺯��ͷ�ļ�
#include "NCLink.h"


static uint8_t NCLink_Head[2]={0xFF,0xFC};//����֡ͷ
static uint8_t NCLink_End[2] ={0xA1,0xA2};//����֡β
uint8_t NCLink_Send_Ask_Flag[10]={0};//�ɿؽ��ջ�ȡ�����������󣬸�����վ���ͱ�־λ
uint8_t NCLink_Send_Check_Flag[20]={0};//���ݽ����ɹ����ɿظ�����վ���ͱ�־λ
uint8_t nclink_databuf[100];//���������ݻ�����
uint8_t rc_update_flag=0;//ң�������ݸ��±�־λ
uint8_t unlock_flag=0x02,takeoff_flag=0;//��������ɱ�־λ
uint8_t move_flag=0,mode_order=0;//SDK�ƶ���־λ���ƶ�˳��
uint16_t move_distance=0;//SDK�ƶ�����
uint8_t cal_flag=0,cal_step=0,cal_cmd=0,shutdown_now_cal_flag=0;//������У׼��־λ
uint32_t Guide_Flight_Lng=0,Guide_Flight_Lat=0,Guide_Flight_Cnt=0;
uint8_t Guide_Flight_Flag=0;
ngs_sdk_control ngs_sdk;
/***************************************************************************************
@��������Serial_Data_Send(uint8_t *buf, uint32_t cnt)
@��ڲ�����buf:����������
			     cnt:�������ֳ�
@���ڲ�������
�������������ڷ��ͺ���
@���ߣ�����С��
@���ڣ�2020��01��17��
****************************************************************************************/
void Serial_Data_Send(uint8_t *buf, uint32_t cnt)  
{
	//USART1_Send(buf,cnt);//�û���ֲʱ����д�˴��ڷ��ͺ���
  USART1_Send_Dma(buf,cnt);
	USB_TxWrite(buf,cnt);
}

/***************************************************************************************
@��������Pilot_Status_Tick(void) 
@��ڲ�������
@���ڲ�������
�����������ɿؽ���״̬��ʾ
@���ߣ�����С��
@���ڣ�2020��01��17��
****************************************************************************************/
void Pilot_Status_Tick(void)  
{
	Bling_Set(&Light_1,500,50,0.2,0,GPIOC,GPIO_Pin_6,0);//�û���ֲʱ����д�˺���
}


union
{
unsigned char floatByte[4];
float floatValue;
}FloatUnion;
/***************************************************************************************
@��������void Float2Byte(float *FloatValue, unsigned char *Byte, unsigned char Subscript)
@��ڲ�����FloatValue:floatֵ
			     Byte:����
		       Subscript:ָ��������ڼ���Ԫ�ؿ�ʼд��
@���ڲ�������
������������float����ת��4�ֽ����ݲ�����ָ����ַ
@���ߣ�����С��
@���ڣ�2020��01��17��
****************************************************************************************/
void Float2Byte(float *FloatValue, unsigned char *Byte, unsigned char Subscript)
{
	FloatUnion.floatValue = (float)2;
	if(FloatUnion.floatByte[0] == 0)//С��ģʽ
	{
		FloatUnion.floatValue = *FloatValue;
		Byte[Subscript]     = FloatUnion.floatByte[0];
		Byte[Subscript + 1] = FloatUnion.floatByte[1];
		Byte[Subscript + 2] = FloatUnion.floatByte[2];
		Byte[Subscript + 3] = FloatUnion.floatByte[3];
	}
	else//���ģʽ
	{
		FloatUnion.floatValue = *FloatValue;
		Byte[Subscript]     = FloatUnion.floatByte[3];
		Byte[Subscript + 1] = FloatUnion.floatByte[2];
		Byte[Subscript + 2] = FloatUnion.floatByte[1];
		Byte[Subscript + 3] = FloatUnion.floatByte[0];
	}
}


/***************************************************************************************
@��������void Byte2Float(unsigned char *Byte, unsigned char Subscript, float *FloatValue)
@��ڲ�����Byte:����
			     Subscript:ָ��������ڼ���Ԫ�ؿ�ʼд��
		       FloatValue:floatֵ
@���ڲ�������
������������ָ����ַ��4�ֽ�����ת��float����
@���ߣ�����С��
@���ڣ�2020��01��17��
****************************************************************************************/
void Byte2Float(unsigned char *Byte, unsigned char Subscript, float *FloatValue)
{
	FloatUnion.floatByte[0]=Byte[Subscript];
	FloatUnion.floatByte[1]=Byte[Subscript + 1];
	FloatUnion.floatByte[2]=Byte[Subscript + 2];
	FloatUnion.floatByte[3]=Byte[Subscript + 3];
	*FloatValue=FloatUnion.floatValue;
}


/***************************************************************************************
@��������void NCLink_Send_Status(float roll,float pitch,float yaw,
											           float roll_gyro,float pitch_gyro,float yaw_gyro,
												         float imu_temp,float vbat,uint8_t fly_model,uint8_t armed)
@��ڲ�����roll:�����
			     pitch:������
           yaw:ƫ����
					 roll_gyro:ƫ�����ٶ�
					 pitch_gyro:ƫ�����ٶ�
					 yaw_gyro:ƫ�����ٶ�
					 imu_temp:IMU�¶�
					 vbat:ƫ�����ٶ�
					 fly_model:����ģʽ
					 armed:����״̬
@���ڲ�������
����������������̬���¶ȡ��ɿ�״̬������վ
@���ߣ�����С��
@���ڣ�2020��01��17��
****************************************************************************************/
void NCLink_Send_Status(float roll,float pitch,float yaw,
											  float roll_gyro,float pitch_gyro,float yaw_gyro,
												float imu_temp,float vbat,uint8_t fly_model,uint8_t armed)
{
  uint8_t _cnt=0;
  int16_t _temp;
	int32_t _temp1;
  uint8_t sum = 0;
  uint8_t i;
  nclink_databuf[_cnt++]=NCLink_Head[0];
  nclink_databuf[_cnt++]=NCLink_Head[1];
  nclink_databuf[_cnt++]=NCLINK_STATUS;
  nclink_databuf[_cnt++]=0;
  
  _temp = (int)(roll*100);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp = (int)(pitch*100);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp = (int)(yaw*100);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);  
  _temp1=100*roll_gyro;
	nclink_databuf[_cnt++]=BYTE3(_temp1);
  nclink_databuf[_cnt++]=BYTE2(_temp1);
  nclink_databuf[_cnt++]=BYTE1(_temp1);
  nclink_databuf[_cnt++]=BYTE0(_temp1);
	_temp1=100*pitch_gyro;
	nclink_databuf[_cnt++]=BYTE3(_temp1);
  nclink_databuf[_cnt++]=BYTE2(_temp1);
  nclink_databuf[_cnt++]=BYTE1(_temp1);
  nclink_databuf[_cnt++]=BYTE0(_temp1);
	
	_temp1=100*yaw_gyro;
	nclink_databuf[_cnt++]=BYTE3(_temp1);
  nclink_databuf[_cnt++]=BYTE2(_temp1);
  nclink_databuf[_cnt++]=BYTE1(_temp1);
  nclink_databuf[_cnt++]=BYTE0(_temp1);
	
  _temp = (int16_t)(100*imu_temp);//��λ��
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);	

  _temp = (int16_t)(100*vbat);//��λV
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
	
	
  nclink_databuf[_cnt++]=fly_model;//����ģʽ
  nclink_databuf[_cnt++]=armed;//����0������1
  nclink_databuf[3] = _cnt-4;
  for(i=0;i<_cnt;i++) sum ^= nclink_databuf[i];
  nclink_databuf[_cnt++]=sum;
	nclink_databuf[_cnt++]=NCLink_End[0];
	nclink_databuf[_cnt++]=NCLink_End[1];
  Serial_Data_Send(nclink_databuf, _cnt);
}

/***************************************************************************************
@��������void NCLink_Send_Senser(int16_t a_x,int16_t a_y,int16_t a_z,
																 int16_t g_x,int16_t g_y,int16_t g_z,
															   int16_t m_x,int16_t m_y,int16_t m_z)
@��ڲ�����a_x:���ٶȼ�X��ԭʼ������
			     a_y:���ٶȼ�Y��ԭʼ������
           a_z:���ٶȼ�Z��ԭʼ������
					 g_x:������X��ԭʼ������
					 g_y:������Y��ԭʼ������
					 g_z:������Z��ԭʼ������
					 m_x:������X��ԭʼ������
					 m_y:������Y��ԭʼ������
					 m_z:������Z��ԭʼ������
@���ڲ�������
�������������ʹ�����ԭʼ���ݸ�����վ
@���ߣ�����С��
@���ڣ�2020��01��17��
****************************************************************************************/
void NCLink_Send_Senser(int16_t a_x,int16_t a_y,int16_t a_z,
												int16_t g_x,int16_t g_y,int16_t g_z,
												int16_t m_x,int16_t m_y,int16_t m_z)
{
  uint8_t _cnt=0;
  int16_t _temp;
  uint8_t sum = 0;
  uint8_t i=0;
  nclink_databuf[_cnt++]=NCLink_Head[0];
  nclink_databuf[_cnt++]=NCLink_Head[1];
  nclink_databuf[_cnt++]=NCLINK_SENSER;
  nclink_databuf[_cnt++]=0;
  
  _temp = a_x;
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp = a_y;
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp = a_z;
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
	
  _temp = g_x;
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp = g_y;
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp = g_z;
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  
  _temp = m_x;
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp = m_y;
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp = m_z;
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  
  nclink_databuf[3] = _cnt-4;
  
  for(i=0;i<_cnt;i++)sum ^= nclink_databuf[i];
  nclink_databuf[_cnt++] = sum;
	nclink_databuf[_cnt++]=NCLink_End[0];
	nclink_databuf[_cnt++]=NCLink_End[1];
  Serial_Data_Send(nclink_databuf, _cnt);
}


/***************************************************************************************
@��������void NCLink_Send_RCData(uint16_t ch1,uint16_t ch2,uint16_t ch3,uint16_t ch4,
	                               uint16_t ch5,uint16_t ch6,uint16_t ch7,uint16_t ch8)
@��ڲ�����ch1:ң������1ͨ������
			     ch2:ң������2ͨ������
           ch3:ң������3ͨ������
					 ch4:ң������4ͨ������
					 ch5:ң������5ͨ������
					 ch6:ң������6ͨ������
					 ch7:ң������7ͨ������
					 ch8:ң������8ͨ������
@���ڲ�������
��������������ң������ͨ�����ݸ�����վ
@���ߣ�����С��
@���ڣ�2020��01��17��
****************************************************************************************/
void NCLink_Send_RCData(uint16_t ch1,uint16_t ch2,uint16_t ch3,uint16_t ch4,
	                      uint16_t ch5,uint16_t ch6,uint16_t ch7,uint16_t ch8)
{
  uint8_t _cnt=0,i=0,sum = 0;
  nclink_databuf[_cnt++]=NCLink_Head[0];
  nclink_databuf[_cnt++]=NCLink_Head[1];
  nclink_databuf[_cnt++]=NCLINK_RCDATA;
  nclink_databuf[_cnt++]=0;
  nclink_databuf[_cnt++]=BYTE1(ch1);
  nclink_databuf[_cnt++]=BYTE0(ch1);
  nclink_databuf[_cnt++]=BYTE1(ch2);
  nclink_databuf[_cnt++]=BYTE0(ch2);
  nclink_databuf[_cnt++]=BYTE1(ch3);
  nclink_databuf[_cnt++]=BYTE0(ch3);
  nclink_databuf[_cnt++]=BYTE1(ch4);
  nclink_databuf[_cnt++]=BYTE0(ch4);
  nclink_databuf[_cnt++]=BYTE1(ch5);
  nclink_databuf[_cnt++]=BYTE0(ch5);
  nclink_databuf[_cnt++]=BYTE1(ch6);
  nclink_databuf[_cnt++]=BYTE0(ch6);
  nclink_databuf[_cnt++]=BYTE1(ch7);
  nclink_databuf[_cnt++]=BYTE0(ch7);
  nclink_databuf[_cnt++]=BYTE1(ch8);
  nclink_databuf[_cnt++]=BYTE0(ch8);
  nclink_databuf[3] = _cnt-4;
  for(i=0;i<_cnt;i++) sum ^= nclink_databuf[i];
  nclink_databuf[_cnt++]=sum;
  nclink_databuf[_cnt++]=NCLink_End[0];
	nclink_databuf[_cnt++]=NCLink_End[1];
  Serial_Data_Send(nclink_databuf, _cnt);
}

/***************************************************************************************
@��������NCLink_Send_GPSData(int32_t lng,int32_t lat,int32_t alt,int16_t pdop,uint8_t fixstate,uint8_t numsv)
@��ڲ�����lng:GPS����
			     lat:GPSγ��
           alt:GPS����
					 pdop:GPS��λ����
					 fixstate:GPS��λ״̬
					 numsv:GPS��Ч��λ����
@���ڲ�������
��������������GPS��λ���ݸ�����վ
@���ߣ�����С��
@���ڣ�2020��01��17��
****************************************************************************************/
void NCLink_Send_GPSData(int32_t lng,int32_t lat,int32_t alt,int16_t pdop,uint8_t fixstate,uint8_t numsv)
{
	uint16_t sum = 0,_cnt=0,i=0;
  nclink_databuf[_cnt++]=NCLink_Head[0];
  nclink_databuf[_cnt++]=NCLink_Head[1];
  nclink_databuf[_cnt++]=NCLINK_GPS;
  nclink_databuf[_cnt++]=0;
  
	nclink_databuf[_cnt++]=BYTE3(lng);
  nclink_databuf[_cnt++]=BYTE2(lng);
  nclink_databuf[_cnt++]=BYTE1(lng);
  nclink_databuf[_cnt++]=BYTE0(lng);
  
  nclink_databuf[_cnt++]=BYTE3(lat);
  nclink_databuf[_cnt++]=BYTE2(lat);
  nclink_databuf[_cnt++]=BYTE1(lat);
  nclink_databuf[_cnt++]=BYTE0(lat);  

  nclink_databuf[_cnt++]=BYTE3(alt);
  nclink_databuf[_cnt++]=BYTE2(alt);
  nclink_databuf[_cnt++]=BYTE1(alt);
  nclink_databuf[_cnt++]=BYTE0(alt);

  nclink_databuf[_cnt++]=BYTE1(pdop);
  nclink_databuf[_cnt++]=BYTE0(pdop);	

  nclink_databuf[_cnt++]=fixstate;
  nclink_databuf[_cnt++]=numsv;
  nclink_databuf[3] = _cnt-4; 
  for(i=0;i<_cnt;i++) sum ^= nclink_databuf[i];
  nclink_databuf[_cnt++]=sum;
	nclink_databuf[_cnt++]=NCLink_End[0];
	nclink_databuf[_cnt++]=NCLink_End[1];
  Serial_Data_Send(nclink_databuf, _cnt);
}


/***************************************************************************************
@��������NCLink_Send_Obs_NE(float lat_pos_obs,float lng_pos_obs,float lat_vel_obs,float lng_vel_obs)
@��ڲ�����lat_pos_obs:GPS����۲�λ��
			     lng_pos_obs:GPS����۲�λ��
           lat_vel_obs:GPS����۲��ٶ�
					 lng_vel_obs:GPS����۲��ٶ�
@���ڲ�������
��������������GPSλ�á��ٶ����ݸ�����վ
@���ߣ�����С��
@���ڣ�2020��01��17��
****************************************************************************************/
void NCLink_Send_Obs_NE(float lat_pos_obs,float lng_pos_obs,
												float lat_vel_obs,float lng_vel_obs)
{
  uint16_t sum = 0,_cnt=0,i=0;	
	int32_t _temp;
  nclink_databuf[_cnt++]=NCLink_Head[0];
  nclink_databuf[_cnt++]=NCLink_Head[1];
  nclink_databuf[_cnt++]=NCLINK_OBS_NE;
  nclink_databuf[_cnt++]=0;
  
	_temp=100*lat_pos_obs;
	nclink_databuf[_cnt++]=BYTE3(_temp);
  nclink_databuf[_cnt++]=BYTE2(_temp);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);

	_temp=100*lng_pos_obs;
  nclink_databuf[_cnt++]=BYTE3(_temp);
  nclink_databuf[_cnt++]=BYTE2(_temp);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);  
	
  _temp=100*lat_vel_obs;
  nclink_databuf[_cnt++]=BYTE3(_temp);
  nclink_databuf[_cnt++]=BYTE2(_temp);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);

  _temp=100*lng_vel_obs;
  nclink_databuf[_cnt++]=BYTE3(_temp);
  nclink_databuf[_cnt++]=BYTE2(_temp);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  nclink_databuf[3] = _cnt-4;
  for(i=0;i<_cnt;i++) sum ^= nclink_databuf[i];
  nclink_databuf[_cnt++]=sum;
  nclink_databuf[_cnt++]=NCLink_End[0];
	nclink_databuf[_cnt++]=NCLink_End[1];
  Serial_Data_Send(nclink_databuf, _cnt);
}

/***************************************************************************************
@��������NCLink_Send_Obs_UOP(float alt_obs_baro,float alt_obs_ult,float opt_vel_p,float opt_vel_r)
@��ڲ�����alt_obs_baro:��ѹ�ƹ۲�߶�
			     alt_obs_ult:�������۲�߶�
           opt_vel_p:�����۲��ٶ�-����
					 opt_vel_r:�����۲��ٶ�-���
@���ڲ�������
�������������͸߶ȹ۲����ݡ������ٶ����ݸ�����վ
@���ߣ�����С��
@���ڣ�2020��01��17��
****************************************************************************************/
void NCLink_Send_Obs_UOP(float alt_obs_baro,float alt_obs_ult,float opt_vel_p,float opt_vel_r)
{
  uint16_t sum = 0,_cnt=0,i=0;
	int32_t _temp;
  nclink_databuf[_cnt++]=NCLink_Head[0];
  nclink_databuf[_cnt++]=NCLink_Head[1];
  nclink_databuf[_cnt++]=NCLINK_OBS_UOP;
  nclink_databuf[_cnt++]=0;
  
	_temp=100*alt_obs_baro;
	nclink_databuf[_cnt++]=BYTE3(_temp);
  nclink_databuf[_cnt++]=BYTE2(_temp);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);

	_temp=100*alt_obs_ult;
  nclink_databuf[_cnt++]=BYTE3(_temp);
  nclink_databuf[_cnt++]=BYTE2(_temp);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);

	_temp=100*opt_vel_p;
	nclink_databuf[_cnt++]=BYTE3(_temp);
  nclink_databuf[_cnt++]=BYTE2(_temp);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);

	_temp=100*opt_vel_r;
  nclink_databuf[_cnt++]=BYTE3(_temp);
  nclink_databuf[_cnt++]=BYTE2(_temp);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp); 
  nclink_databuf[3] = _cnt-4;
  for(i=0;i<_cnt;i++) sum ^= nclink_databuf[i];
  nclink_databuf[_cnt++]=sum;
	nclink_databuf[_cnt++]=NCLink_End[0];
	nclink_databuf[_cnt++]=NCLink_End[1];
  Serial_Data_Send(nclink_databuf, _cnt);
}


/***************************************************************************************
@��������NCLink_Send_Fusion_U(float alt_pos_fus,float alt_vel_fus,float alt_accel_fus)
@��ڲ�����alt_pos_fus:��ֱ����߶ȹ���
			     alt_vel_fus:��ֱ�����ٶȹ���
           alt_accel_fus:��ֱ������ٶȹ���
@���ڲ�������
����������������ֱ����״̬�������ݸ�����վ
@���ߣ�����С��
@���ڣ�2020��01��17��
****************************************************************************************/
void NCLink_Send_Fusion_U(float alt_pos_fus,float alt_vel_fus,float alt_accel_fus)
{
  uint16_t sum = 0,_cnt=0,i=0;
	int32_t _temp;
  nclink_databuf[_cnt++]=NCLink_Head[0];
  nclink_databuf[_cnt++]=NCLink_Head[1];
  nclink_databuf[_cnt++]=NCLINK_FUS_U;
  nclink_databuf[_cnt++]=0;
	_temp=100*alt_pos_fus;
	nclink_databuf[_cnt++]=BYTE3(_temp);
  nclink_databuf[_cnt++]=BYTE2(_temp);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp=100*alt_vel_fus;
  nclink_databuf[_cnt++]=BYTE3(_temp);
  nclink_databuf[_cnt++]=BYTE2(_temp);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp=100*alt_accel_fus;
  nclink_databuf[_cnt++]=BYTE3(_temp);
  nclink_databuf[_cnt++]=BYTE2(_temp);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);	
  nclink_databuf[3] = _cnt-4;  
  for(i=0;i<_cnt;i++) sum ^= nclink_databuf[i]; 
  nclink_databuf[_cnt++]=sum;
	nclink_databuf[_cnt++]=NCLink_End[0];
	nclink_databuf[_cnt++]=NCLink_End[1];
  Serial_Data_Send(nclink_databuf, _cnt);
}


/***************************************************************************************
@��������NCLink_Send_Fusion_NE(float lat_pos_fus	,float lng_pos_fus,float lat_vel_fus,
															 float lng_vel_fus,float lat_accel_fus,float lng_accel_fus)
@��ڲ�����lat_pos_fus:��������λ�ù���
			     lng_pos_fus:��������λ�ù���
           lat_vel_fus:���������ٶȹ���
					 lng_vel_fus:���������ٶȹ���
			     lat_accel_fus:����������ٶȹ���
           lng_accel_fus:����������ٶȹ���
@���ڲ�������
��������������ˮƽ����״̬�������ݸ�����վ
@���ߣ�����С��
@���ڣ�2020��01��17��
****************************************************************************************/
void NCLink_Send_Fusion_NE(float lat_pos_fus	,float lng_pos_fus,
											     float lat_vel_fus  ,float lng_vel_fus,
											     float lat_accel_fus,float lng_accel_fus)
{
  u8 sum = 0,_cnt=0,i=0;
	int32_t _temp;
  nclink_databuf[_cnt++]=NCLink_Head[0];
  nclink_databuf[_cnt++]=NCLink_Head[1];
  nclink_databuf[_cnt++]=NCLINK_FUS_NE;
  nclink_databuf[_cnt++]=0;
	_temp=100*lat_pos_fus;
	nclink_databuf[_cnt++]=BYTE3(_temp);
  nclink_databuf[_cnt++]=BYTE2(_temp);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp=100*lng_pos_fus;
  nclink_databuf[_cnt++]=BYTE3(_temp);
  nclink_databuf[_cnt++]=BYTE2(_temp);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp=100*lat_vel_fus;
  nclink_databuf[_cnt++]=BYTE3(_temp);
  nclink_databuf[_cnt++]=BYTE2(_temp);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp=100*lng_vel_fus;
  nclink_databuf[_cnt++]=BYTE3(_temp);
  nclink_databuf[_cnt++]=BYTE2(_temp);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);	
	_temp=100*lat_accel_fus;
  nclink_databuf[_cnt++]=BYTE3(_temp);
  nclink_databuf[_cnt++]=BYTE2(_temp);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);	
	_temp=100*lng_accel_fus;
  nclink_databuf[_cnt++]=BYTE3(_temp);
  nclink_databuf[_cnt++]=BYTE2(_temp);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);	
  nclink_databuf[3] = _cnt-4;
  for(i=0;i<_cnt;i++) sum ^= nclink_databuf[i];
  nclink_databuf[_cnt++]=sum;
	nclink_databuf[_cnt++]=NCLink_End[0];
	nclink_databuf[_cnt++]=NCLink_End[1];
  Serial_Data_Send(nclink_databuf, _cnt);
}

/***************************************************************************************
@��������NCLink_Send_PID(uint8_t group,float pid1_kp,float pid1_ki,float pid1_kd,
																	     float pid2_kp,float pid2_ki,float pid2_kd,
																	     float pid3_kp,float pid3_ki,float pid3_kd
@��ڲ�����group:PID���
			     pid1_kp:��1��PID������������
           pid1_ki:��1��PID�������ֲ���
					 pid1_kd:��1��PID����΢�ֲ���
			     pid2_kp:��2��PID������������
           pid2_ki:��2��PID�������ֲ���
					 pid2_kd:��2��PID����΢�ֲ���
			     pid3_kp:��3��PID������������
           pid3_ki:��3��PID�������ֲ���
					 pid3_kd:��3��PID����΢�ֲ���
@���ڲ�������
��������������PID�������ݸ�����վ
@���ߣ�����С��
@���ڣ�2020��01��17��
****************************************************************************************/
void NCLink_Send_PID(uint8_t group,float pid1_kp,float pid1_ki,float pid1_kd,
																	 float pid2_kp,float pid2_ki,float pid2_kd,
																	 float pid3_kp,float pid3_ki,float pid3_kd)
{
  uint8_t _cnt=0,sum = 0,i=0;
  int16_t _temp;
  nclink_databuf[_cnt++]=NCLink_Head[0];
  nclink_databuf[_cnt++]=NCLink_Head[1];
  nclink_databuf[_cnt++]=group;
  nclink_databuf[_cnt++]=0;
  _temp = (int16_t)(pid1_kp * 1000);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp = (int16_t)(pid1_ki  * 1000);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp = (int16_t)(pid1_kd  * 100);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp = (int16_t)(pid2_kp  * 1000);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp = (int16_t)(pid2_ki  * 1000);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp = (int16_t)(pid2_kd * 100);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp = (int16_t)(pid3_kp  * 1000);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp = (int16_t)(pid3_ki  * 1000);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp = (int16_t)(pid3_kd * 100);
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  nclink_databuf[3] = _cnt-4;
  for(i=0;i<_cnt;i++) sum ^= nclink_databuf[i];
  nclink_databuf[_cnt++]=sum;
	nclink_databuf[_cnt++]=NCLink_End[0];
	nclink_databuf[_cnt++]=NCLink_End[1];
  Serial_Data_Send(nclink_databuf, _cnt);
}


/***************************************************************************************
@��������NCLink_Send_Parameter(uint16_t targeheight,uint16_t safeheight,uint16_t safevbat,uint16_t maxheight,
													     uint16_t maxradius,uint16_t maxupvel,uint16_t maxdownvel,uint16_t maxhorvel)
@��ڲ�����targeheight:һ�����Ŀ��߶�CM
					 safeheight:������ȫ�߶�
					 safevbat:��ȫ��ѹ��ֵ
					 maxheight:�����и߶�
					 maxradius:�����а뾶
					 maxupvel:��������ٶ�
					 maxdownvel:����½��ٶ�
					 maxhorvel:���ˮƽ�ٶ�
@���ڲ�������
�������������������������ݸ�����վ
@���ߣ�����С��
@���ڣ�2020��01��17��
****************************************************************************************/
void NCLink_Send_Parameter(uint16_t targeheight,uint16_t safeheight,uint16_t safevbat,uint16_t maxheight,
													 uint16_t maxradius,uint16_t maxupvel,uint16_t maxdownvel,uint16_t maxhorvel)
{
  uint8_t _cnt=0,sum = 0,i=0;
  uint16_t _temp;
  nclink_databuf[_cnt++]=NCLink_Head[0];
  nclink_databuf[_cnt++]=NCLink_Head[1];
  nclink_databuf[_cnt++]=NCLINK_SEND_PARA;
  nclink_databuf[_cnt++]=0; 
  _temp = targeheight;
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp = safeheight;
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp = safevbat;
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp = maxheight;
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp = maxradius;
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp = maxupvel;
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp = maxdownvel;
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp);
  _temp = maxhorvel;
  nclink_databuf[_cnt++]=BYTE1(_temp);
  nclink_databuf[_cnt++]=BYTE0(_temp); 
  nclink_databuf[3] = _cnt-4;
  for(i=0;i<_cnt;i++) sum ^= nclink_databuf[i];
  nclink_databuf[_cnt++]=sum;
	nclink_databuf[_cnt++]=NCLink_End[0];
	nclink_databuf[_cnt++]=NCLink_End[1];
  Serial_Data_Send(nclink_databuf, _cnt);
}



/***************************************************************************************
@��������NCLink_Send_Userdata(float userdata1	 ,float userdata2,
											        float userdata3  ,float userdata4,
											        float userdata5  ,float userdata6)
@��ڲ�����userdata1:�û�����1
					 userdata2:�û�����2
					 userdata3:�û�����3
					 userdata4:�û�����4
					 userdata5:�û�����5
					 userdata6:�û�����6
@���ڲ�������
���������������û����ݸ�����վ
@���ߣ�����С��
@���ڣ�2020��01��17��
****************************************************************************************/
void NCLink_Send_Userdata(float userdata1	 ,float userdata2,
											    float userdata3  ,float userdata4,
											    float userdata5  ,float userdata6)
{
  uint8_t sum=0,_cnt=0,i=0;
  nclink_databuf[_cnt++]=NCLink_Head[0];
  nclink_databuf[_cnt++]=NCLink_Head[1];
  nclink_databuf[_cnt++]=NCLINK_USER;
  nclink_databuf[_cnt++]=0;
		
	Float2Byte(&userdata1,nclink_databuf,_cnt);//4
	_cnt+=4;
	Float2Byte(&userdata2,nclink_databuf,_cnt);//8
	_cnt+=4;
	Float2Byte(&userdata3,nclink_databuf,_cnt);//12
	_cnt+=4;
	Float2Byte(&userdata4,nclink_databuf,_cnt);//16
	_cnt+=4;
	Float2Byte(&userdata5,nclink_databuf,_cnt);//20
	_cnt+=4;
	Float2Byte(&userdata6,nclink_databuf,_cnt);//24
	_cnt+=4;//28

  nclink_databuf[3] = _cnt-4;
	
  for(i=0;i<_cnt;i++) sum ^= nclink_databuf[i]; 
  nclink_databuf[_cnt++]=sum;
	
	nclink_databuf[_cnt++]=NCLink_End[0];
	nclink_databuf[_cnt++]=NCLink_End[1];
  Serial_Data_Send(nclink_databuf,_cnt);
}


/***************************************************************************************
@��������NCLink_Send_CalRawdata(float gyro_x_raw,float gyro_y_raw,float gyro_z_raw,
											          float acce_x_raw,float acce_y_raw,float acce_z_raw)
@��ڲ�����gyro_x_raw:���ٶ�У׼X��ԭʼ����
					 gyro_y_raw:���ٶ�У׼Y��ԭʼ����
					 gyro_z_raw:���ٶ�У׼Z��ԭʼ����
					 acce_x_raw:���ٶ�У׼X��ԭʼ����
					 acce_y_raw:���ٶ�У׼Y��ԭʼ����
					 acce_z_raw:���ٶ�У׼Z��ԭʼ����
					 mag_x_raw: ������У׼X��ԭʼ����
					 mag_y_raw: ������У׼Y��ԭʼ����
					 mag_z_raw: ������У׼Z��ԭʼ����
@���ڲ�������
�������������ʹ�����У׼ԭʼ���ݸ�����վ
@���ߣ�����С��
@���ڣ�2020��01��17��
****************************************************************************************/
void NCLink_Send_CalRawdata1(uint8_t gyro_auto_cal_flag,
													  float gyro_x_raw,float gyro_y_raw,float gyro_z_raw,
											      float acce_x_raw,float acce_y_raw,float acce_z_raw)
{
  uint8_t sum=0,_cnt=0,i=0;
  nclink_databuf[_cnt++]=NCLink_Head[0];
  nclink_databuf[_cnt++]=NCLink_Head[1];
  nclink_databuf[_cnt++]=NCLINK_SEND_CAL_RAW1;
  nclink_databuf[_cnt++]=0;
	nclink_databuf[_cnt++]=gyro_auto_cal_flag;
	
	Float2Byte(&gyro_x_raw,nclink_databuf,_cnt);
	_cnt+=4;
	Float2Byte(&gyro_y_raw,nclink_databuf,_cnt);
	_cnt+=4;
	Float2Byte(&gyro_z_raw,nclink_databuf,_cnt);
	_cnt+=4;
	Float2Byte(&acce_x_raw,nclink_databuf,_cnt);
	_cnt+=4;
	Float2Byte(&acce_y_raw,nclink_databuf,_cnt);
	_cnt+=4;
	Float2Byte(&acce_z_raw,nclink_databuf,_cnt);
	_cnt+=4;
	
  nclink_databuf[3] = _cnt-4;	
  for(i=0;i<_cnt;i++) sum ^= nclink_databuf[i]; 
  nclink_databuf[_cnt++]=sum;
	
	nclink_databuf[_cnt++]=NCLink_End[0];
	nclink_databuf[_cnt++]=NCLink_End[1];
	Serial_Data_Send(nclink_databuf,_cnt);
	//Serial_Data_Send((unsigned char *)databuf,sizeof(databuf));
}

/***************************************************************************************
@��������NCLink_Send_CalRawdata2(float mag_x_raw ,float mag_y_raw ,float mag_z_raw)
@��ڲ�����mag_x_raw: ������У׼X��ԭʼ����
					 mag_y_raw: ������У׼Y��ԭʼ����
					 mag_z_raw: ������У׼Z��ԭʼ����
@���ڲ�������
�������������ʹ�����У׼ԭʼ���ݸ�����վ
@���ߣ�����С��
@���ڣ�2020��01��17��
****************************************************************************************/
void NCLink_Send_CalRawdata2(float mag_x_raw ,float mag_y_raw ,float mag_z_raw)
{
  uint8_t sum=0,_cnt=0,i=0;
  nclink_databuf[_cnt++]=NCLink_Head[0];
  nclink_databuf[_cnt++]=NCLink_Head[1];
  nclink_databuf[_cnt++]=NCLINK_SEND_CAL_RAW2;
  nclink_databuf[_cnt++]=0;
	
	Float2Byte(&mag_x_raw,nclink_databuf,_cnt);
	_cnt+=4;
	Float2Byte(&mag_y_raw,nclink_databuf,_cnt);
	_cnt+=4;
	Float2Byte(&mag_z_raw,nclink_databuf,_cnt);
	_cnt+=4;	
	
  nclink_databuf[3] = _cnt-4;	
  for(i=0;i<_cnt;i++) sum ^= nclink_databuf[i]; 
  nclink_databuf[_cnt++]=sum;
	
	nclink_databuf[_cnt++]=NCLink_End[0];
	nclink_databuf[_cnt++]=NCLink_End[1];
	Serial_Data_Send(nclink_databuf,_cnt);
	//Serial_Data_Send((unsigned char *)databuf,sizeof(databuf));
}



/***************************************************************************************
@��������NCLink_Send_CalParadata1(float gyro_x_offset,float gyro_y_offset,float gyro_z_offset,
										             float mag_x_offset,float mag_y_offset,float mag_z_offset)
@��ڲ�����gyro_x_offset:���ٶ�У׼��X����ƫ����
					 gyro_y_offset:���ٶ�У׼��Y����ƫ����
					 gyro_z_offset:���ٶ�У׼��Z����ƫ����
					 mag_x_offset: ������У׼��X����ƫ����
					 mag_y_offset: ������У׼��Y����ƫ����
					 mag_z_offset: ������У׼��Z����ƫ����
@���ڲ�������
�������������ʹ�����У׼ԭʼ���ݸ�����վ
@���ߣ�����С��
@���ڣ�2020��01��17��
****************************************************************************************/
void NCLink_Send_CalParadata1(float gyro_x_offset,float gyro_y_offset,float gyro_z_offset,
										          float mag_x_offset ,float mag_y_offset ,float mag_z_offset)
{
  uint8_t sum=0,_cnt=0,i=0;
  nclink_databuf[_cnt++]=NCLink_Head[0];
  nclink_databuf[_cnt++]=NCLink_Head[1];
  nclink_databuf[_cnt++]=NCLINK_SEND_CAL_PARA1;
  nclink_databuf[_cnt++]=0;
	
	Float2Byte(&gyro_x_offset,nclink_databuf,_cnt);
	_cnt+=4;
	Float2Byte(&gyro_y_offset,nclink_databuf,_cnt);
	_cnt+=4;
	Float2Byte(&gyro_z_offset,nclink_databuf,_cnt);
	_cnt+=4;
	
	
	Float2Byte(&mag_x_offset,nclink_databuf,_cnt);
	_cnt+=4;
	Float2Byte(&mag_y_offset,nclink_databuf,_cnt);
	_cnt+=4;
	Float2Byte(&mag_z_offset,nclink_databuf,_cnt);
	_cnt+=4;	

  nclink_databuf[3] = _cnt-4;	
  for(i=0;i<_cnt;i++) sum ^= nclink_databuf[i]; 
  nclink_databuf[_cnt++]=sum;
  
  nclink_databuf[_cnt++]=NCLink_End[0];
	nclink_databuf[_cnt++]=NCLink_End[1];
	
	Serial_Data_Send(nclink_databuf,_cnt);	
}


/***************************************************************************************
@��������NCLink_Send_CalParadata1(float acce_x_offset,float acce_y_offset,float acce_z_offset,
														     float acce_x_scale,float acce_y_scale,float acce_z_scale)
@��ڲ�����acce_x_offset:���ٶ�У׼��X����ƫ����
					 acce_y_offset:���ٶ�У׼��Y����ƫ����
					 acce_z_offset:���ٶ�У׼��Z����ƫ����
					 acce_x_scale: ���ٶ�У׼��X����������
					 acce_y_scale: ���ٶ�У׼��Y����������
					 acce_z_scale: ���ٶ�У׼��Z����������
@���ڲ�������
�������������ʹ�����У׼ԭʼ���ݸ�����վ
@���ߣ�����С��
@���ڣ�2020��01��17��
****************************************************************************************/
void NCLink_Send_CalParadata2(float acce_x_offset,float acce_y_offset,float acce_z_offset,
														 float acce_x_scale ,float acce_y_scale ,float acce_z_scale)
{
  uint8_t sum=0,_cnt=0,i=0;
  nclink_databuf[_cnt++]=NCLink_Head[0];
  nclink_databuf[_cnt++]=NCLink_Head[1];
  nclink_databuf[_cnt++]=NCLINK_SEND_CAL_PARA2;
  nclink_databuf[_cnt++]=0;
	
	
	Float2Byte(&acce_x_offset,nclink_databuf,_cnt);
	_cnt+=4;
	Float2Byte(&acce_y_offset,nclink_databuf,_cnt);
	_cnt+=4;
	Float2Byte(&acce_z_offset,nclink_databuf,_cnt);
	_cnt+=4;
	
	Float2Byte(&acce_x_scale,nclink_databuf,_cnt);
	_cnt+=4;
	Float2Byte(&acce_y_scale,nclink_databuf,_cnt);
	_cnt+=4;
	Float2Byte(&acce_z_scale,nclink_databuf,_cnt);
	_cnt+=4;	
		
  nclink_databuf[3] = _cnt-4;	
  for(i=0;i<_cnt;i++) sum ^= nclink_databuf[i]; 
  nclink_databuf[_cnt++]=sum;
  
  nclink_databuf[_cnt++]=NCLink_End[0];
	nclink_databuf[_cnt++]=NCLink_End[1];
	
	Serial_Data_Send(nclink_databuf,_cnt);	
}

/***************************************************************************************
@��������NCLink_Send_CalParadata1(float pitch_offset,float roll_offset)
@��ڲ�����pitch_offset: ����ˮƽУ׼������ƫ����
					 roll_offset:  ����ˮƽУ׼������ƫ����
@���ڲ�������
�������������ʹ�����У׼ԭʼ���ݸ�����վ
@���ߣ�����С��
@���ڣ�2020��01��17��
****************************************************************************************/
void NCLink_Send_CalParadata3(float pitch_offset ,float roll_offset)
{
  uint8_t sum=0,_cnt=0,i=0;
  nclink_databuf[_cnt++]=NCLink_Head[0];
  nclink_databuf[_cnt++]=NCLink_Head[1];
  nclink_databuf[_cnt++]=NCLINK_SEND_CAL_PARA3;
  nclink_databuf[_cnt++]=0;
	
	Float2Byte(&pitch_offset,nclink_databuf,_cnt);
	_cnt+=4;
	Float2Byte(&roll_offset,nclink_databuf,_cnt);
	_cnt+=4;	
	
	
  nclink_databuf[3] = _cnt-4;	
  for(i=0;i<_cnt;i++) sum ^= nclink_databuf[i]; 
  nclink_databuf[_cnt++]=sum;
  
  nclink_databuf[_cnt++]=NCLink_End[0];
	nclink_databuf[_cnt++]=NCLink_End[1];
	
	Serial_Data_Send(nclink_databuf,_cnt);	
}
/***************************************************************************************
@��������void NCLink_Send_Check(uint8_t response)
@��ڲ�����response:Ӧ��
@���ڲ�������
��������������Ӧ�����ݸ�����վ
@���ߣ�����С��
@���ڣ�2020��01��17��
****************************************************************************************/
static void NCLink_Send_Check(uint8_t response)//����վӦ��У��
{
  uint8_t sum = 0,i=0;
  nclink_databuf[0]=NCLink_Head[0];
  nclink_databuf[1]=NCLink_Head[1];
  nclink_databuf[2]=NCLINK_SEND_CHECK;
  nclink_databuf[3]=1;
  nclink_databuf[4]=response;
  for(i=0;i<5;i++) sum ^= nclink_databuf[i];
  nclink_databuf[5]=sum;
	nclink_databuf[6]=NCLink_End[0];
	nclink_databuf[7]=NCLink_End[1];
  Serial_Data_Send(nclink_databuf,8);
}



/***************************************************************************************
@��������NCLink_Data_Prase_Prepare(uint8_t data)
@��ڲ�����data:����������
@���ڲ�������
�����������ɿؽ�������վ����׼�������������봮���жϺ�����
@���ߣ�����С��
@���ڣ�2020��01��17��
****************************************************************************************/
void NCLink_Data_Prase_Prepare(uint8_t data)//����վ���ݽ���
{
  static uint8_t buf[100];
  static uint8_t data_len = 0,data_cnt = 0;
  static uint8_t state = 0;
  if(state==0&&data==NCLink_Head[1])//�ж�֡ͷ1
  {
    state=1;
    buf[0]=data;
  }
  else if(state==1&&data==NCLink_Head[0])//�ж�֡ͷ2
  {
    state=2;
    buf[1]=data;
  }
  else if(state==2&&data<0XF1)//�����ֽ�
  {
    state=3;
    buf[2]=data;
  }
  else if(state==3&&data<100)//��Ч���ݳ���
  {
    state = 4;
    buf[3]=data;
    data_len = data;
    data_cnt = 0;
  }
  else if(state==4&&data_len>0)//���ݽ���
  {
    data_len--;
    buf[4+data_cnt++]=data;
    if(data_len==0)  state = 5;
  }
  else if(state==5)//���У��
  {
    state = 6;
    buf[4+data_cnt++]=data;
  }
	else if(state==6&&data==NCLink_End[0])//֡β0
	{
			state = 7;
			buf[4+data_cnt++]=data;
	}
	else if(state==7&&data==NCLink_End[1])//֡β1
	{
			state = 0;
			buf[4+data_cnt]=data;
		  NCLink_Data_Prase_Process(buf,data_cnt+5);//���ݽ���
	}
  else state = 0;
}




/***************************************************************************************
���Ϲ��ܴ�������Ķ����û���ֲ�Էɿ�ƽ̨ʱ����Ҫ������ȫ�ֱ����滻��
***************************************************************************************/



/***************************************************************************************
@��������NCLink_Send_Check_Status_Parameter(void)
@��ڲ�������
@���ڲ�������
��������������Ӧ�����ݡ��������ݸ�����վ
@���ߣ�����С��
@���ڣ�2020��01��17��
****************************************************************************************/
uint8_t NCLink_Send_Check_Status_Parameter(void)
{
	if(NCLink_Send_Check_Flag[0]==1)//�ɿؽ�����1��PID�����ɹ�������״̬������վ
	{
	   NCLink_Send_Check(NCLINK_SEND_PID1_3);
		 NCLink_Send_Check_Flag[0]=0;
		 return 1;
	}
	else if(NCLink_Send_Check_Flag[1]==1)//�ɿؽ�����2��PID�����ɹ�������״̬������վ
	{
	   NCLink_Send_Check(NCLINK_SEND_PID4_6);
		 NCLink_Send_Check_Flag[1]=0;
		 return 1;
	}
	else if(NCLink_Send_Check_Flag[2]==1)//�ɿؽ�����3��PID�����ɹ�������״̬������վ
	{
	   NCLink_Send_Check(NCLINK_SEND_PID7_9);
		 NCLink_Send_Check_Flag[2]=0;
		 return 1;
	}
	else if(NCLink_Send_Check_Flag[3]==1)//�ɿؽ�����4��PID�����ɹ�������״̬������վ
	{
	   NCLink_Send_Check(NCLINK_SEND_PID10_12);
		 NCLink_Send_Check_Flag[3]=0;
		 return 1;
	}
	else if(NCLink_Send_Check_Flag[4]==1)//�ɿؽ�����5��PID�����ɹ�������״̬������վ
	{
	   NCLink_Send_Check(NCLINK_SEND_PID13_15);
		 NCLink_Send_Check_Flag[4]=0;
		 return 1;
	}
	else if(NCLink_Send_Check_Flag[5]==1)//�ɿؽ�����6��PID�����ɹ�������״̬������վ
	{
	   NCLink_Send_Check(NCLINK_SEND_PID16_18);
		 NCLink_Send_Check_Flag[5]=0;
		 return 1;
	}
  else if(NCLink_Send_Check_Flag[6]==1)//�ɿؽ������������ɹ�������״̬������վ
	{
	   NCLink_Send_Check(NCLINK_SEND_PARA);
		 NCLink_Send_Check_Flag[6]=0;
		 return 1;
	}
	else if(NCLink_Send_Check_Flag[7]==1)//�ɿؽ���ң�������ݳɹ�������״̬������վ
	{
		 NCLink_Send_Check(NCLINK_SEND_RC);	
		 NCLink_Send_Check_Flag[7]=0;
		 return 1;
	}
  else if(NCLink_Send_Check_Flag[8]==1)//�ɿؽ���λ�����ݳɹ�������״̬������վ
	{
		 NCLink_Send_Check(NCLINK_SEND_DIS);
		 NCLink_Send_Check_Flag[8]=0;
		 return 1;
	}
	else if(NCLink_Send_Check_Flag[9]==1)//�ɿش�����У׼��ϣ�����״̬������վ
	{
		 NCLink_Send_Check(NCLINK_SEND_CAL);
		 NCLink_Send_Check_Flag[9]=0;
		
		 NCLink_Send_Check_Flag[10]=1;//ÿ��У׼����Զ�ˢ�µ���վУ׼����
		 return 1;
	}
  else if(NCLink_Send_Check_Flag[10]==1)//�ɿش�����У׼�ɹ�������״̬������վ
	{
		 static uint8_t cnt=0;
		 if(cnt==0)
		 {
		   NCLink_Send_Check(NCLINK_SEND_CAL_READ);	
			 cnt=1;
		 }
		 else if(cnt==1)
		 {
			 NCLink_Send_CalParadata1(gyro_offset.x,gyro_offset.y,gyro_offset.z,Mag_Offset[0],Mag_Offset[1],Mag_Offset[2]);		 
		   cnt=2;
		 }
		 else if(cnt==2)
		 {
				NCLink_Send_CalParadata2(B[0]*GRAVITY_MSS,B[1]*GRAVITY_MSS,B[2]*GRAVITY_MSS,K[0],K[1],K[2]);	 
		    cnt=3;
		 }      
		 else if(cnt==3)
		 {
			  NCLink_Send_CalParadata3(Pitch_Offset,Roll_Offset);
		    cnt=0;
			  NCLink_Send_Check_Flag[10]=0;
		 } 
		 return 1;
	}	
	else if(NCLink_Send_Ask_Flag[0]==1)//���յ�����վ��ȡPID�������󣬷ɿط��͵�1��PID����������վ
	{
		NCLink_Send_PID(NCLINK_SEND_PID1_3,Total_Controller.Roll_Gyro_Control.Kp,
										Total_Controller.Roll_Gyro_Control.Ki,
										Total_Controller.Roll_Gyro_Control.Kd,
										Total_Controller.Pitch_Gyro_Control.Kp,
										Total_Controller.Pitch_Gyro_Control.Ki,
										Total_Controller.Pitch_Gyro_Control.Kd,
										Total_Controller.Yaw_Gyro_Control.Kp,
										Total_Controller.Yaw_Gyro_Control.Ki,
										Total_Controller.Yaw_Gyro_Control.Kd);
		NCLink_Send_Ask_Flag[0]=0;
		return 1;
	}
	else if(NCLink_Send_Ask_Flag[1]==1)//���յ�����վ��ȡPID�������󣬷ɿط��͵�2��PID����������վ
	{
			NCLink_Send_PID(NCLINK_SEND_PID4_6,Total_Controller.Roll_Angle_Control.Kp,
											Total_Controller.Roll_Angle_Control.Ki,
											Total_Controller.Roll_Angle_Control.Kd,
											Total_Controller.Pitch_Angle_Control.Kp,
											Total_Controller.Pitch_Angle_Control.Ki,
											Total_Controller.Pitch_Angle_Control.Kd,
											Total_Controller.Yaw_Angle_Control.Kp,
											Total_Controller.Yaw_Angle_Control.Ki,
											Total_Controller.Yaw_Angle_Control.Kd);
			NCLink_Send_Ask_Flag[1]=0;
			return 1;
	}
  else if(NCLink_Send_Ask_Flag[2]==1)//���յ�����վ��ȡPID�������󣬷ɿط��͵�3��PID����������վ
  {
			NCLink_Send_PID(NCLINK_SEND_PID7_9,Total_Controller.High_Position_Control.Kp,
											Total_Controller.High_Position_Control.Ki,
											Total_Controller.High_Position_Control.Kd,
											Total_Controller.High_Speed_Control.Kp,
											Total_Controller.High_Speed_Control.Ki,
											Total_Controller.High_Speed_Control.Kd,
										  Total_Controller.High_Acce_Control.Kp,
											Total_Controller.High_Acce_Control.Ki,
											Total_Controller.High_Acce_Control.Kd);
			NCLink_Send_Ask_Flag[2]=0;
			return 1;
  }
  else if(NCLink_Send_Ask_Flag[3]==1)//���յ�����վ��ȡPID�������󣬷ɿط��͵�4��PID����������վ
  {
			NCLink_Send_PID(NCLINK_SEND_PID10_12,Total_Controller.Latitude_Position_Control.Kp,
											Total_Controller.Latitude_Position_Control.Ki,
											Total_Controller.Latitude_Position_Control.Kd,
											Total_Controller.Latitude_Speed_Control.Kp,
											Total_Controller.Latitude_Speed_Control.Ki,
											Total_Controller.Latitude_Speed_Control.Kd,
			                Total_Controller.SDK_Roll_Position_Control.Kp,
											Total_Controller.SDK_Roll_Position_Control.Ki,
										  Total_Controller.SDK_Roll_Position_Control.Kd); 
			NCLink_Send_Ask_Flag[3]=0;
			return 1;
	}
	else if(NCLink_Send_Ask_Flag[4]==1)//���յ�����վ��ȡPID�������󣬷ɿط��͵�5һ��PID����������վ
	{
		NCLink_Send_PID(NCLINK_SEND_PID13_15,Total_Controller.Optical_Position_Control.Kp
										 ,Total_Controller.Optical_Position_Control.Ki
										 ,Total_Controller.Optical_Position_Control.Kd
										 ,Total_Controller.Optical_Speed_Control.Kp
										 ,Total_Controller.Optical_Speed_Control.Ki
										 ,Total_Controller.Optical_Speed_Control.Kd
										 ,Pitch_Roll_Feedforward_Kp,0,Pitch_Roll_Feedforward_Kd);
		NCLink_Send_Ask_Flag[4]=0;
		return 1;
	}
	else if(NCLink_Send_Ask_Flag[5]==1)//���յ�����վ��ȡPID�������󣬷ɿط��͵�6��PID����������վ
	{
		NCLink_Send_PID(NCLINK_SEND_PID16_18,
									  0,0,0,
										0,0,0,
										0,0,0);
		NCLink_Send_Ask_Flag[5]=0;
		return 1;
	}
	else if(NCLink_Send_Ask_Flag[6]==1)//���յ�����վ��ȡ�����������󣬷ɿط�����������������վ
	{
		 NCLink_Send_Parameter(Target_Height,Safe_Height,Safe_Vbat,Max_Height,Max_Radius,Max_Upvel,Max_Downvel,Max_Horvel);
		 NCLink_Send_Ask_Flag[6]=0;
		 return 1;	
	}
	else return 0;
}

/***************************************************************************************
@��������NCLink_Data_Prase_Process(uint8_t *data_buf,uint8_t num)
@��ڲ�����data_buf:����������֡
					 num:����֡��
@���ڲ�������
����������������ȡ��������֡������ÿһ֡��������
@���ߣ�����С��
@���ڣ�2020��01��17��
****************************************************************************************/
void NCLink_Data_Prase_Process(uint8_t *data_buf,uint8_t num)//�ɿ����ݽ�������
{
  uint8_t sum = 0;
  for(uint8_t i=0;i<(num-3);i++)  sum ^= *(data_buf+i);
  if(!(sum==*(data_buf+num-3)))    																					return;//�ж�sum	
	if(!(*(data_buf)==NCLink_Head[1]&&*(data_buf+1)==NCLink_Head[0]))         return;//�ж�֡ͷ
	if(!(*(data_buf+num-2)==NCLink_End[0]&&*(data_buf+num-1)==NCLink_End[1])) return;//֡βУ��  
  if(*(data_buf+2)==0X01)//����վ����״̬����
  {
    if(*(data_buf+4)==0X01)		//����վ���Ͷ�ȡ��ǰPID��������
    {
      NCLink_Send_Ask_Flag[0]=1;//�ɿط��͵�1��PID����������λ��1
      NCLink_Send_Ask_Flag[1]=1;//�ɿط��͵�2��PID����������λ��1
      NCLink_Send_Ask_Flag[2]=1;//�ɿط��͵�3��PID����������λ��1
      NCLink_Send_Ask_Flag[3]=1;//�ɿط��͵�4��PID����������λ��1
      NCLink_Send_Ask_Flag[4]=1;//�ɿط��͵�5��PID����������λ��1
      NCLink_Send_Ask_Flag[5]=1;//�ɿط��͵�6��PID����������λ��1
      Pilot_Status_Tick();
    }	
    else if(*(data_buf+4)==0X02)   //����վ���ͻָ�Ĭ��PID��������
    {
      Sort_PID_Flag=3;
      Pilot_Status_Tick();
    }
		else if(*(data_buf+4)==0X03)//����վ���Ͷ�ȡ��ǰ������������    
    {
      NCLink_Send_Ask_Flag[6]=1;//�ɿط���������������λ��1
      Pilot_Status_Tick();
    }
		else if(*(data_buf+4)==0X04)//����վ���ͻָ�Ĭ��������������  
    {
      NCLink_Send_Ask_Flag[6]=1;//�ָ�Ĭ�ϲ���������Ĭ�ϲ������͵�����վ
			Sort_Other_Para_Cnt=0x01;
      Pilot_Status_Tick();
    }
  }
  else if(*(data_buf+2)==0X02)                             //����PID1-3
  {
    Total_Controller.Roll_Gyro_Control.Kp  = 0.001*( (int16_t)(*(data_buf+4)<<8)|*(data_buf+5));
    Total_Controller.Roll_Gyro_Control.Ki  = 0.001*( (int16_t)(*(data_buf+6)<<8)|*(data_buf+7));
    Total_Controller.Roll_Gyro_Control.Kd  = 0.01*( (int16_t)(*(data_buf+8)<<8)|*(data_buf+9));
    Total_Controller.Pitch_Gyro_Control.Kp = 0.001*( (int16_t)(*(data_buf+10)<<8)|*(data_buf+11));
    Total_Controller.Pitch_Gyro_Control.Ki = 0.001*( (int16_t)(*(data_buf+12)<<8)|*(data_buf+13));
    Total_Controller.Pitch_Gyro_Control.Kd = 0.01*( (int16_t)(*(data_buf+14)<<8)|*(data_buf+15));
    Total_Controller.Yaw_Gyro_Control.Kp   = 0.001*( (int16_t)(*(data_buf+16)<<8)|*(data_buf+17));
    Total_Controller.Yaw_Gyro_Control.Ki   = 0.001*( (int16_t)(*(data_buf+18)<<8)|*(data_buf+19));
    Total_Controller.Yaw_Gyro_Control.Kd   = 0.01*( (int16_t)(*(data_buf+20)<<8)|*(data_buf+21));
		NCLink_Send_Check_Flag[0]=1;
  }
  else if(*(data_buf+2)==0X03)                             //����PID4-6
  {
    Total_Controller.Roll_Angle_Control.Kp  = 0.001*( (int16_t)(*(data_buf+4)<<8)|*(data_buf+5) );
    Total_Controller.Roll_Angle_Control.Ki  = 0.001*( (int16_t)(*(data_buf+6)<<8)|*(data_buf+7) );
    Total_Controller.Roll_Angle_Control.Kd  = 0.01*( (int16_t)(*(data_buf+8)<<8)|*(data_buf+9) );
    Total_Controller.Pitch_Angle_Control.Kp   = 0.001*( (int16_t)(*(data_buf+10)<<8)|*(data_buf+11) );
    Total_Controller.Pitch_Angle_Control.Ki   = 0.001*( (int16_t)(*(data_buf+12)<<8)|*(data_buf+13) );
    Total_Controller.Pitch_Angle_Control.Kd   = 0.01*( (int16_t)(*(data_buf+14)<<8)|*(data_buf+15) );
    Total_Controller.Yaw_Angle_Control.Kp    = 0.001*( (int16_t)(*(data_buf+16)<<8)|*(data_buf+17) );
    Total_Controller.Yaw_Angle_Control.Ki    = 0.001*( (int16_t)(*(data_buf+18)<<8)|*(data_buf+19) );
    Total_Controller.Yaw_Angle_Control.Kd    = 0.01*( (int16_t)(*(data_buf+20)<<8)|*(data_buf+21) );
		NCLink_Send_Check_Flag[1]=1;
  }
  else if(*(data_buf+2)==0X04)                             //����PID7-9
  {
    Total_Controller.High_Position_Control.Kp= 0.001*( (int16_t)(*(data_buf+4)<<8)|*(data_buf+5) );
    Total_Controller.High_Position_Control.Ki= 0.001*( (int16_t)(*(data_buf+6)<<8)|*(data_buf+7) );
    Total_Controller.High_Position_Control.Kd= 0.01*( (int16_t)(*(data_buf+8)<<8)|*(data_buf+9) );
    Total_Controller.High_Speed_Control.Kp   = 0.001*( (int16_t)(*(data_buf+10)<<8)|*(data_buf+11) );
    Total_Controller.High_Speed_Control.Ki   = 0.001*( (int16_t)(*(data_buf+12)<<8)|*(data_buf+13) );
    Total_Controller.High_Speed_Control.Kd   = 0.01*( (int16_t)(*(data_buf+14)<<8)|*(data_buf+15) );
    Total_Controller.High_Acce_Control.Kp		 = 0.001*( (int16_t)(*(data_buf+16)<<8)|*(data_buf+17) );
    Total_Controller.High_Acce_Control.Ki		 = 0.001*( (int16_t)(*(data_buf+18)<<8)|*(data_buf+19) );
    Total_Controller.High_Acce_Control.Kd		 = 0.01*( (int16_t)(*(data_buf+20)<<8)|*(data_buf+21) );
    /***********************λ�ÿ��ƣ�λ�á��ٶȲ�������һ��PID����**********************************************************/
    Total_Controller.Longitude_Speed_Control.Kp=Total_Controller.Latitude_Speed_Control.Kp;
    Total_Controller.Longitude_Speed_Control.Ki=Total_Controller.Latitude_Speed_Control.Ki;
    Total_Controller.Longitude_Speed_Control.Kd=Total_Controller.Latitude_Speed_Control.Kd;
		NCLink_Send_Check_Flag[2]=1;
  }
  else if(*(data_buf+2)==0X05)                             //����PID9-11
  {
    Total_Controller.Latitude_Position_Control.Kp= 0.001*( (int16_t)(*(data_buf+4)<<8)|*(data_buf+5) );
    Total_Controller.Latitude_Position_Control.Ki= 0.001*( (int16_t)(*(data_buf+6)<<8)|*(data_buf+7) );
    Total_Controller.Latitude_Position_Control.Kd= 0.01*( (int16_t)(*(data_buf+8)<<8)|*(data_buf+9) );
    Total_Controller.Latitude_Speed_Control.Kp   = 0.001*( (int16_t)(*(data_buf+10)<<8)|*(data_buf+11) );
    Total_Controller.Latitude_Speed_Control.Ki   = 0.001*( (int16_t)(*(data_buf+12)<<8)|*(data_buf+13) );
    Total_Controller.Latitude_Speed_Control.Kd   = 0.01*( (int16_t)(*(data_buf+14)<<8)|*(data_buf+15) );
		Total_Controller.SDK_Roll_Position_Control.Kp= 0.001*( (int16_t)(*(data_buf+16)<<8)|*(data_buf+17) );
		Total_Controller.SDK_Roll_Position_Control.Ki= 0.001*( (int16_t)(*(data_buf+18)<<8)|*(data_buf+19) );
		Total_Controller.SDK_Roll_Position_Control.Kd= 0.01*( (int16_t)(*(data_buf+20)<<8)|*(data_buf+21) );
    /***********************λ�ÿ��ƣ�λ�á��ٶȲ�������һ��PID����**********************************************************/
    Total_Controller.Longitude_Position_Control.Kp=Total_Controller.Latitude_Position_Control.Kp;
    Total_Controller.Longitude_Position_Control.Ki=Total_Controller.Latitude_Position_Control.Ki;
    Total_Controller.Longitude_Position_Control.Kd=Total_Controller.Latitude_Position_Control.Kd;
		Total_Controller.Longitude_Speed_Control.Kp=Total_Controller.Latitude_Speed_Control.Kp;
		Total_Controller.Longitude_Speed_Control.Ki=Total_Controller.Latitude_Speed_Control.Ki;
		Total_Controller.Longitude_Speed_Control.Kd=Total_Controller.Latitude_Speed_Control.Kd;
		
		Total_Controller.SDK_Pitch_Position_Control.Kp = Total_Controller.SDK_Roll_Position_Control.Kp;
		Total_Controller.SDK_Pitch_Position_Control.Ki = Total_Controller.SDK_Roll_Position_Control.Ki;
		Total_Controller.SDK_Pitch_Position_Control.Kd = Total_Controller.SDK_Roll_Position_Control.Kd;
		
		NCLink_Send_Check_Flag[3]=1;
  }
  else if(*(data_buf+2)==0X06)                             //����PID12-15
  {
    Total_Controller.Optical_Position_Control.Kp = 0.001*( (int16_t)(*(data_buf+4)<<8)|*(data_buf+5) );
    Total_Controller.Optical_Position_Control.Ki = 0.001*( (int16_t)(*(data_buf+6)<<8)|*(data_buf+7) );
    Total_Controller.Optical_Position_Control.Kd = 0.01*( (int16_t)(*(data_buf+8)<<8)|*(data_buf+9) );
    Total_Controller.Optical_Speed_Control.Kp = 0.001*( (int16_t)(*(data_buf+10)<<8)|*(data_buf+11) );
    Total_Controller.Optical_Speed_Control.Ki = 0.001*( (int16_t)(*(data_buf+12)<<8)|*(data_buf+13) );
    Total_Controller.Optical_Speed_Control.Kd = 0.01*( (int16_t)(*(data_buf+14)<<8)|*(data_buf+15) );
    
		Pitch_Roll_Feedforward_Kp= 0.001*( (int16_t)(*(data_buf+16)<<8)|*(data_buf+17) ); 
		Pitch_Roll_Feedforward_Kd= 0.01*( (int16_t)(*(data_buf+20)<<8)|*(data_buf+21) );
		NCLink_Send_Check_Flag[4]=1;		
  }
  else if(*(data_buf+2)==0X07)                             //����PID16-18
  {
		NCLink_Send_Check_Flag[5]=1;
    Sort_PID_Flag=1;	
    Pilot_Status_Tick();
  }
	else if(*(data_buf+2)==0X08)                             //��������
  {
    Target_Height =(int16_t)(*(data_buf+4)<<8)|*(data_buf+5);
    Safe_Height =(int16_t)(*(data_buf+6)<<8)|*(data_buf+7);
    Safe_Vbat =(int16_t)(*(data_buf+8)<<8)|*(data_buf+9);
    Max_Height =(int16_t)(*(data_buf+10)<<8)|*(data_buf+11);
    Max_Radius =(int16_t)(*(data_buf+12)<<8)|*(data_buf+13);
    Max_Upvel =(int16_t)(*(data_buf+14)<<8)|*(data_buf+15);
    Max_Downvel =(int16_t)(*(data_buf+16)<<8)|*(data_buf+17);
    Max_Horvel =(int16_t)(*(data_buf+18)<<8)|*(data_buf+19);
		NCLink_Send_Check_Flag[6]=1;
		Pilot_Status_Tick();
		
		Sort_Other_Para_Cnt=0x02;
  }
  else if(*(data_buf+2)==0X09)                             //ң��������
  {
    PPM_Databuf[0]=(int16_t)(*(data_buf+4)<<8)|*(data_buf+5);
    PPM_Databuf[1]=(int16_t)(*(data_buf+6)<<8)|*(data_buf+7);
    PPM_Databuf[2]=(int16_t)(*(data_buf+8)<<8)|*(data_buf+9);
    PPM_Databuf[3]=(int16_t)(*(data_buf+10)<<8)|*(data_buf+11);
    PPM_Databuf[4]=(int16_t)(*(data_buf+12)<<8)|*(data_buf+13);
    PPM_Databuf[5]=(int16_t)(*(data_buf+14)<<8)|*(data_buf+15);
    PPM_Databuf[6]=(int16_t)(*(data_buf+16)<<8)|*(data_buf+17);
    PPM_Databuf[7]=(int16_t)(*(data_buf+18)<<8)|*(data_buf+19);
		rc_update_flag=1;
		
		unlock_flag=*(data_buf+20);
		takeoff_flag=*(data_buf+21);		
		NCLink_Send_Check_Flag[7]=1;
		Pilot_Status_Tick();	
  }
	else if(*(data_buf+2)==0X0A)                             //����վ�����ƶ�����
  {		
    ngs_sdk.move_mode=*(data_buf+4),
		ngs_sdk.mode_order=*(data_buf+5);
    ngs_sdk.move_distance=(uint16_t)(*(data_buf+6)<<8)|*(data_buf+7);;
    ngs_sdk.update_flag=true;
		
		ngs_sdk.move_flag.sdk_front_flag=false;
		ngs_sdk.move_flag.sdk_behind_flag=false;
		ngs_sdk.move_flag.sdk_left_flag=false;
		ngs_sdk.move_flag.sdk_right_flag=false;
		ngs_sdk.move_flag.sdk_up_flag=false;
		ngs_sdk.move_flag.sdk_down_flag=false;
		
		if(*(data_buf+4)==SDK_FRONT)
		{					
			ngs_sdk.move_flag.sdk_front_flag=true;
			ngs_sdk.f_distance=ngs_sdk.move_distance;
		}
		else if(*(data_buf+4)==SDK_BEHIND) 
		{					
			ngs_sdk.move_flag.sdk_behind_flag=true;
			ngs_sdk.f_distance=-ngs_sdk.move_distance;
		}
		else if(*(data_buf+4)==SDK_LEFT)  
		{			
			ngs_sdk.move_flag.sdk_left_flag=true;
			ngs_sdk.f_distance=-ngs_sdk.move_distance;
		}
		else if(*(data_buf+4)==SDK_RIGHT)
		{					
			ngs_sdk.move_flag.sdk_right_flag=true;
			ngs_sdk.f_distance=ngs_sdk.move_distance;
		}
		else if(*(data_buf+4)==SDK_UP)
		{  				
			ngs_sdk.move_flag.sdk_up_flag=true;
			ngs_sdk.f_distance=ngs_sdk.move_distance;
		}
		else if(*(data_buf+4)==SDK_DOWN) 
		{					
			ngs_sdk.move_flag.sdk_down_flag=true;
			ngs_sdk.f_distance=-ngs_sdk.move_distance;
		}				
		NCLink_Send_Check_Flag[8]=1;
		Pilot_Status_Tick();	
  }
	else if(*(data_buf+2)==0X0B)                             //����վ����У׼����
  {		
    cal_flag=*(data_buf+4),
		cal_step=*(data_buf+5);
		cal_cmd=*(data_buf+6);
		
		if(cal_flag==0x00&&cal_step==0x00&&cal_cmd==0x00)//��ǰ��ֹ��ǰУ׼
		{
		  shutdown_now_cal_flag=1;
		}	
		else
		{
			if(cal_cmd==0x01)
			{
				NCLink_Send_Check_Flag[10]=1;
				cal_cmd=0x00;
			}
	  }
		Pilot_Status_Tick();			
  }
	else if(*(data_buf+2)==0X0C)
  {
		Guide_Flight_Lng =((int32_t)(*(data_buf+4)<<24)|(*(data_buf+5)<<16)|(*(data_buf+6)<<8)|*(data_buf+7));
		Guide_Flight_Lat =((int32_t)(*(data_buf+8)<<24)|(*(data_buf+9)<<16)|(*(data_buf+10)<<8)|*(data_buf+11));
		Guide_Flight_Cnt++;;
		Guide_Flight_Flag=1;
		Pilot_Status_Tick();
	}		
}


/***************************************************************************************
@��������NCLink_SEND_StateMachine(void)
@��ڲ�������
@���ڲ�������
����������״̬�������ɿط������ݸ�����վ
@���ߣ�����С��
@���ڣ�2020��01��17��
****************************************************************************************/
void NCLink_SEND_StateMachine(void)
{
	static uint16_t NCLink_Cnt=0;
	if(!NCLink_Send_Check_Status_Parameter())//�жϵ���վ�����������ݡ��Ƿ���Ҫ����Ӧ��
	{
		if(NCLink_Cnt==0)//�ɿ���̬�Ȼ�����Ϣ
		{
			NCLink_Cnt=1;
			NCLink_Send_Status(Roll,Pitch,Yaw,
												 Roll_Gyro,Pitch_Gyro,Yaw_Gyro,
												 WP_Sensor.temperature,Battery_Valtage,Controler_High_Mode,Controler_State);
		}
		else if(NCLink_Cnt==1)//�ɿش�����ԭʼ����
		{
			NCLink_Cnt=2;
			NCLink_Send_Senser((int16_t)WP_Sensor.accel_raw.x,(int16_t)WP_Sensor.accel_raw.y,(int16_t)WP_Sensor.accel_raw.z,
												 (int16_t)WP_Sensor.gyro_raw.x,(int16_t)WP_Sensor.gyro_raw.y,(int16_t)WP_Sensor.gyro_raw.z,
												 (int16_t)WP_Sensor.mag_raw.x,(int16_t)WP_Sensor.mag_raw.y,(int16_t)WP_Sensor.mag_raw.z);
		}
		else if(NCLink_Cnt==2)//�ɿؽ���ң��������
		{
			NCLink_Cnt=3;
			NCLink_Send_RCData(PPM_Databuf[0],PPM_Databuf[1],
												 PPM_Databuf[2],PPM_Databuf[3],
												 PPM_Databuf[4],PPM_Databuf[5],
												 PPM_Databuf[6],PPM_Databuf[7]);
		}
		else if(NCLink_Cnt==3)//�ɿؽ���GPS��Ϣ
		{
			NCLink_Cnt=4;
			NCLink_Send_GPSData(Longitude_Origion,Latitude_Origion,Altitude_Origion,GPS_Pos_DOP,GPS_FixType,GPS_Sate_Num);
		}
		else if(NCLink_Cnt==4)//�ɿ�ˮƽ�۲�λ�á��ٶ�
		{
			NCLink_Cnt=5;
			NCLink_Send_Obs_NE(Earth_Frame_To_XYZ.N,Earth_Frame_To_XYZ.E,GPS_Speed_Resolve[1],GPS_Speed_Resolve[0]);
		}
		else if(NCLink_Cnt==5)//�ɿ���ֱ�۲�λ�á������ٶ�
		{
			NCLink_Cnt=6;
			NCLink_Send_Obs_UOP(WP_Sensor.baro_altitude,HC_SR04_Distance,opt_gyro_data.y,opt_gyro_data.x);
		}
		else if(NCLink_Cnt==6)//�ɿ���ֱ״̬����
		{
			NCLink_Cnt=7;
			NCLink_Send_Fusion_U(NamelessQuad.Position[_YAW],
													 NamelessQuad.Speed[_YAW],
													 NamelessQuad.Acceleration[_YAW]);
		}
		else if(NCLink_Cnt==7)//�ɿ�ˮƽ״̬����
		{
			NCLink_Cnt=8;
			NCLink_Send_Fusion_NE(NamelessQuad.Position[_ROLL],
														NamelessQuad.Position[_PITCH],
														NamelessQuad.Acceleration[_ROLL],
														NamelessQuad.Acceleration[_PITCH],
														NamelessQuad.Speed[_ROLL],
														NamelessQuad.Speed[_PITCH]);	
		}
		else if(NCLink_Cnt==8)//�û����ݲ�����ʾ
		{
		//NCLink_Cnt=9;
			NCLink_Send_Userdata(NamelessQuad.Position[_YAW],
													 NamelessQuad.Speed[_YAW],
													 NamelessQuad.Acceleration[_YAW],
													 WP_Sensor.baro_altitude,
													 HC_SR04_Distance,
													 0);								
		}
		else if(NCLink_Cnt==9)//������У׼ԭʼ����
		{
			NCLink_Cnt=10;
		  NCLink_Send_CalRawdata1(Gyro_Safety_Calibration_Flag,
			                       WP_Sensor.gyro_raw.x*Gyro_Range_Scale,WP_Sensor.gyro_raw.y*Gyro_Range_Scale,WP_Sensor.gyro_raw.z*Gyro_Range_Scale,
			                       WP_Sensor.accel_raw.x*ACCEL_TO_1G,WP_Sensor.accel_raw.y*ACCEL_TO_1G,WP_Sensor.accel_raw.z*ACCEL_TO_1G);
		}
		else if(NCLink_Cnt==10)//������У׼ԭʼ����
		{
			NCLink_Cnt=0;
		  NCLink_Send_CalRawdata2(Compass.x,Compass.y,Compass.z);
		}		
		else NCLink_Cnt=0;
 }
}

