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
#include "MPU6050.h"

float K[3]={1.0,1.0,1.0};//Ĭ�ϱ��(����)���
float B[3]={0,0,0};//Ĭ����λ���
//********************************************************
float  X_g,Y_g,Z_g;
float  X_w,Y_w,Z_w;
float  X_g_av,Y_g_av,Z_g_av;//���õļ��ٶȼ�ֵ
float  X_w_av,Y_w_av,Z_w_av;//���õ�������ֵ
float  X_w_av_bpf,Y_w_av_bpf,Z_w_av_bpf;//�����˲�����õ�������ֵ
float  X_g_av_bpf,Y_g_av_bpf,Z_g_av_bpf;//�����˲�����õļ��ٶȼ�ֵ
_IMU_Tag imu;
//200_30z
Butter_Parameter Accel_Parameter={
  1,  -0.7477891782585,    0.272214937925,
  0.1311064399166,   0.2622128798333,   0.1311064399166
};
Butter_Parameter Gyro_Parameter={
  //200hz---51hz
  1,  0.03680751639284,   0.1718123812701,
  0.3021549744157,   0.6043099488315,   0.3021549744157
};
Butter_Parameter Butter_1HZ_Parameter_Acce={
  //200hz---1hz
  1,   -1.955578240315,   0.9565436765112,
  0.000241359049042, 0.000482718098084, 0.000241359049042
};

float invSqrt(float x)
{
  float halfx = 0.5f * x;
  float y = x;
  long i = *(long*)&y;
  
  i = 0x5f3759df - (i>>1);
  y = *(float*)&i;
  y = y * (1.5f - (halfx * y * y));
  
  return y;
}


//**************************************
//MPU6050
//**************************************
void Init_MPU6050(void)
{
  Single_WriteI2C(0xD0,PWR_MGMT_1  , 0x00);//�ر������ж�,�������
  Single_WriteI2C(0xD0,SMPLRT_DIV  , 0x00); // sample rate.  Fsample= 1Khz/(<this value>+1) = 1000Hz
  Single_WriteI2C(0xD0,MPU_CONFIG  , 0x02); //�ڲ���ͨ�˲�Ƶ�ʣ����ٶȼ�94hz,������98hz
  //Single_WriteI2C(0xD0,MPU_CONFIG  , 0x03); //�ڲ���ͨ�˲�Ƶ�ʣ����ٶȼ�44hz��������42hz
  Single_WriteI2C(0xD0,GYRO_CONFIG , 0x08);//500deg/s
  Single_WriteI2C(0xD0,ACCEL_CONFIG, 0x10);// Accel scale 8g (4096 LSB/g)
#ifdef IMU_BOARD_GY86
  Single_WriteI2C(0xD0,USER_CTRL, 0x00);//����MPU6050����ģʽ�����GY86ģ��
  Single_WriteI2C(0xD0,INT_PIN_CFG, 0x02);
#endif
  Set_Cutoff_Frequency(Sampling_Freq, 30,&Gyro_Parameter);//��̬���ٶȷ����˲�����  30
  Set_Cutoff_Frequency(Sampling_Freq, 60,&Accel_Parameter);//��̬����Ӽ������˲�ֵ  25
  Set_Cutoff_Frequency(Sampling_Freq, 1,&Butter_1HZ_Parameter_Acce);//������У׼�Ӽ��˲�ֵ
}


uint8_t Gyro_Range_Mode=0x00;
float Gyro_Range_Scale=0,Gyro_Range_Offset_Gain=2000;
//**************************************
int16_t GetData(uint8_t REG_Address)
{
  uint8_t Hd,Ld;
  Hd=Single_ReadI2C(0xD0,REG_Address);
  Ld=Single_ReadI2C(0xD0,REG_Address+1);
  return (Hd<<8)+Ld;
}
//**************************************
//���ƾ�ֵ�˲�
//**************************************
#define N 5
float Data_X_g[N];
float Data_Y_g[N];
float Data_Z_g[N];
float GildeAverageValueFilter(float NewValue,float *Data)
{
  float max,min;
  float sum;
  unsigned char i;
  Data[0]=NewValue;
  max=Data[0];
  min=Data[0];
  sum=Data[0];
  for(i=N-1;i!=0;i--)
  {
    if(Data[i]>max) max=Data[i];
    else if(Data[i]<min) min=Data[i];
    sum+=Data[i];
    Data[i]=Data[i-1];
  }
  i=N-2;
  sum=sum-max-min;
  sum=sum/i;
  return(sum);
}

/**********************************
��������void IMU_Calibration(void)
˵����MPU6050�궨
��ڣ���
���ڣ���
��ע����������ʱ�趨�����ǵ���ֵ
**********************************/
void GET_GYRO(void)
{
  Y_w  = -GetData(GYRO_XOUT_H);
  X_w  = -GetData(GYRO_YOUT_H);
  Z_w  = -GetData(GYRO_ZOUT_H);
}


Vector3f gyro_offset;
void IMU_Calibration(void)
{
  u8 i;
	Vector3f gyro_offset_temp;
	ReadFlashParameterOne(GYRO_X_OFFSET,&gyro_offset_temp.x);
	ReadFlashParameterOne(GYRO_Y_OFFSET,&gyro_offset_temp.y);
	ReadFlashParameterOne(GYRO_Z_OFFSET,&gyro_offset_temp.z);	
	
	if(isnan(gyro_offset_temp.x)==0
			&&isnan(gyro_offset_temp.y)==0
				&&isnan(gyro_offset_temp.z)==0)//���֮ǰ�Ѿ��¶�У׼��������ʱֱ����֮ǰУ׼������ 
	{
		 gyro_offset.x=gyro_offset_temp.x;
		 gyro_offset.y=gyro_offset_temp.y;
		 gyro_offset.z=gyro_offset_temp.z;
	}
	else
	{
		s32 g_Gyro_xoffset = 0, g_Gyro_yoffset = 0, g_Gyro_zoffset = 0;
		for (i = 0; i < 100; i++)			//��������30�Σ�һ����ʱ30*3=90ms
		{
			GET_GYRO();						//��ȡMPU6050��ֵ
			g_Gyro_xoffset +=X_w;
			g_Gyro_yoffset +=Y_w;
			g_Gyro_zoffset +=Z_w;
			delay_ms(5);
		}
		gyro_offset.x=(g_Gyro_xoffset/100);
		gyro_offset.y=(g_Gyro_yoffset/100);
		gyro_offset.z=(g_Gyro_zoffset/100);
	}
}





Butter_BufferData Gyro_BufferData[3];
Butter_BufferData Gyro_BufferData_BPF[3];
Butter_BufferData Accel_BufferData[3];
Butter_BufferData Accel_BufferData_BPF[3];
float Butterworth_Filter(float curr_inputer,
                         Butter_BufferData *Buffer,
                         Butter_Parameter *Parameter)
{
  /* ���ٶȼ�Butterworth�˲� */
  /* ��ȡ����x(n) */
  Buffer->Input_Butter[2]=curr_inputer;
  /* Butterworth�˲� */
  Buffer->Output_Butter[2]=
    Parameter->b[0] * Buffer->Input_Butter[2]
      +Parameter->b[1] * Buffer->Input_Butter[1]
	+Parameter->b[2] * Buffer->Input_Butter[0]
          -Parameter->a[1] * Buffer->Output_Butter[1]
            -Parameter->a[2] * Buffer->Output_Butter[0];
  /* x(n) ���б��� */
  Buffer->Input_Butter[0]=Buffer->Input_Butter[1];
  Buffer->Input_Butter[1]=Buffer->Input_Butter[2];
  /* y(n) ���б��� */
  Buffer->Output_Butter[0]=Buffer->Output_Butter[1];
  Buffer->Output_Butter[1]=Buffer->Output_Butter[2];
  return (Buffer->Output_Butter[2]);
}


void GET_GYRO_DATA(void)//���ٶȵ�ͨ�˲���������̬����
{
  X_w=Gyro.x=WP_Sensor.gyro_raw.x-gyro_offset.x;
  Y_w=Gyro.y=WP_Sensor.gyro_raw.y-gyro_offset.y;
  Z_w=Gyro.z=WP_Sensor.gyro_raw.z-gyro_offset.z;
  
  X_w_av_bpf=Butterworth_Filter(X_w,&Gyro_BufferData_BPF[0],&Bandstop_Filter_Parameter_30_98);
  Y_w_av_bpf=Butterworth_Filter(Y_w,&Gyro_BufferData_BPF[1],&Bandstop_Filter_Parameter_30_98);
  Z_w_av_bpf=Butterworth_Filter(Z_w,&Gyro_BufferData_BPF[2],&Bandstop_Filter_Parameter_30_98);
  
//  X_w_av=Butterworth_Filter(X_w_av_bpf,&Gyro_BufferData[0],&Gyro_Parameter);
//  Y_w_av=Butterworth_Filter(Y_w_av_bpf,&Gyro_BufferData[1],&Gyro_Parameter);
//  Z_w_av=Butterworth_Filter(Z_w_av_bpf,&Gyro_BufferData[2],&Gyro_Parameter);  
  
	X_w_av=X_w_av_bpf;//Butterworth_Filter(X_w,&Gyro_BufferData[0],&Gyro_Parameter);
	Y_w_av=Y_w_av_bpf;//Butterworth_Filter(Y_w,&Gyro_BufferData[1],&Gyro_Parameter);
	Z_w_av=Z_w_av_bpf;//Butterworth_Filter(Z_w,&Gyro_BufferData[2],&Gyro_Parameter);
}

Vector3f DCM_Gyro,DCM_Acc;
void GET_MPU_DATA(void)
{
  Gyro_Range_Scale=GYRO_CALIBRATION_COFF;
  Gyro_Range_Offset_Gain=500;
  WP_Sensor.accel_raw.y=-GetData(ACCEL_XOUT_H);
	WP_Sensor.accel_raw.x=-GetData(ACCEL_YOUT_H);
	WP_Sensor.accel_raw.z=-GetData(ACCEL_ZOUT_H);
	
	WP_Sensor.temperature=36.53f+(double)(GetData(TEMP_OUT_H)/340.0f);	
	
	WP_Sensor.gyro_raw.y=-GetData(GYRO_XOUT_H);
	WP_Sensor.gyro_raw.x=-GetData(GYRO_YOUT_H);
	WP_Sensor.gyro_raw.z=-GetData(GYRO_ZOUT_H);
	
	
	if(Gyro_Safety_Calibration_Flag==0)  Gyro_Safety_Calibration_Flag=Gyro_Calibration_Check(&WP_Sensor.gyro_raw);
   
  if(cal_flag==0x01) 
	{
		Gyro_Safety_Calibration_Flag=0;
		cal_flag=0x00;
	}		
	
  Accel_Filter();
  GET_GYRO_DATA();
  DCM_Acc.x=X_Origion;
  DCM_Acc.y=Y_Origion;
  DCM_Acc.z=Z_Origion;
  DCM_Gyro.x=X_w_av*GYRO_CALIBRATION_COFF*DEG2RAD;
  DCM_Gyro.y=Y_w_av*GYRO_CALIBRATION_COFF*DEG2RAD;
  DCM_Gyro.z=Z_w_av*GYRO_CALIBRATION_COFF*DEG2RAD;
}

float Gyro_X,Gyro_Y,Gyro_Z;
float Angle_X,Angle_Y,Angle_Z;
float ACCE_X,ACCE_Y,ACCE_Z;
void Angle_Calculate(void)//�Ƕȼ���
{
  float ACCE_X_TEMP,ACCE_Y_TEMP,ACCE_Z_TEMP;
  ACCE_X_TEMP=ACCE_X=X_g_av;
  ACCE_Y_TEMP=ACCE_Y=Y_g_av;
  ACCE_Z_TEMP=ACCE_Z=Z_g_av;
  ACCE_Y=-57.3*atan(ACCE_X_TEMP*invSqrt(ACCE_Y_TEMP*ACCE_Y_TEMP+ACCE_Z_TEMP*ACCE_Z_TEMP));//�����
  ACCE_X=57.3*atan(ACCE_Y_TEMP*invSqrt(ACCE_X_TEMP*ACCE_X_TEMP+ACCE_Z_TEMP*ACCE_Z_TEMP));//������
}


int16_t Acce_Correct[3]={0};//���ڽ������ٶ���������Ƶ�ʺܵ�
uint8_t Acce_Correct_Update_Flag=0;
Butter_BufferData Butter_Buffer_Correct[3];
void Acce_Correct_Filter()
{
  Acce_Correct[0]=Int_Sort(LPButterworth(imu.accelRaw[0],
                                         &Butter_Buffer_Correct[0],&Butter_1HZ_Parameter_Acce));
  Acce_Correct[1]=Int_Sort(LPButterworth(imu.accelRaw[1]
                                         ,&Butter_Buffer_Correct[1],&Butter_1HZ_Parameter_Acce));
  Acce_Correct[2]=Int_Sort(LPButterworth(imu.accelRaw[2]
                                         ,&Butter_Buffer_Correct[2],&Butter_1HZ_Parameter_Acce));
  Acce_Correct_Update_Flag=1;
}


float X_Origion,Y_Origion,Z_Origion;
void Accel_Filter(void)
{
  imu.accelRaw[0] =Accel.x =  WP_Sensor.accel_raw.x;
  imu.accelRaw[1] =Accel.y =  WP_Sensor.accel_raw.y;
  imu.accelRaw[2] =Accel.z =  WP_Sensor.accel_raw.z;
  Acce_Correct_Filter();
  X_Origion=K[0]*imu.accelRaw[0]-B[0]*One_G_TO_Accel;//��������У�����������ٶ���
  Y_Origion=K[1]*imu.accelRaw[1]-B[1]*One_G_TO_Accel;
  Z_Origion=K[2]*imu.accelRaw[2]-B[2]*One_G_TO_Accel;
  FilterBefore_NamelessQuad.Acceleration[_YAW]=
    -Sin_Roll* X_Origion
      + Sin_Pitch *Cos_Roll *Y_Origion
        + Cos_Pitch * Cos_Roll *Z_Origion;
  FilterBefore_NamelessQuad.Acceleration[_PITCH]=
    Cos_Yaw* Cos_Roll * X_Origion
      +(Sin_Pitch*Sin_Roll*Cos_Yaw-Cos_Pitch * Sin_Yaw) * Y_Origion
        +(Sin_Pitch * Sin_Yaw+Cos_Pitch * Sin_Roll * Cos_Yaw) * Z_Origion;
  FilterBefore_NamelessQuad.Acceleration[_ROLL]=
    Sin_Yaw* Cos_Roll * X_Origion
      +(Sin_Pitch * Sin_Roll * Sin_Yaw +Cos_Pitch * Cos_Yaw) * Y_Origion
        + (Cos_Pitch * Sin_Roll * Sin_Yaw - Sin_Pitch * Cos_Yaw) * Z_Origion;
  FilterBefore_NamelessQuad.Acceleration[_YAW]*=AcceGravity/AcceMax;
  FilterBefore_NamelessQuad.Acceleration[_YAW]-=AcceGravity;
  FilterBefore_NamelessQuad.Acceleration[_YAW]*=100;//���ٶ�cm/s^2
  FilterBefore_NamelessQuad.Acceleration[_PITCH]*=AcceGravity/AcceMax;
  FilterBefore_NamelessQuad.Acceleration[_PITCH]*=100;//���ٶ�cm/s^2
  FilterBefore_NamelessQuad.Acceleration[_ROLL]*=AcceGravity/AcceMax;
  FilterBefore_NamelessQuad.Acceleration[_ROLL]*=100;//���ٶ�cm/s^2
  Acce_Control_Filter();//���ٶ��˲������ڹߵ������ٶȿ��Ʒ�����
  /* ���ٶȼ�Butterworth�˲� */
  X_g_av_bpf=Butterworth_Filter(X_Origion,&Accel_BufferData_BPF[0],&Bandstop_Filter_Parameter_30_94);
  Y_g_av_bpf=Butterworth_Filter(Y_Origion,&Accel_BufferData_BPF[1],&Bandstop_Filter_Parameter_30_94);
  Z_g_av_bpf=Butterworth_Filter(Z_Origion,&Accel_BufferData_BPF[2],&Bandstop_Filter_Parameter_30_94);
  X_g_av=Butterworth_Filter(X_g_av_bpf,&Accel_BufferData[0],&Accel_Parameter);
  Y_g_av=Butterworth_Filter(Y_g_av_bpf,&Accel_BufferData[1],&Accel_Parameter);
  Z_g_av=Butterworth_Filter(Z_g_av_bpf,&Accel_BufferData[2],&Accel_Parameter);
}



