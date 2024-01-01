/*----------------------------------------------------------------------------------------------------------------------/
*               ������ֻ��������ѧϰʹ�ã���Ȩ����Ȩ���������ƴ��Ŷӣ������ƴ��Ŷӽ��ɿس���Դ���ṩ�������ߣ�
*               ������ҪΪ�����ƴ��Ŷ��ṩ������δ��������ɣ����ý�Դ�����ṩ�����ˣ����ý�Դ����ŵ����Ϲ�����������أ� 
*               �������Դ�����Ĳ�����緢��������Ϊ�������ƴ��Ŷӽ���֮�Է��ɽ��������
-----------------------------------------------------------------------------------------------------------------------/
*               ������Ϣ���ܶ���ֹ��ǰ�����������˳���������
*               ��Դ���ף���ѧ����ϧ��ף������Ϯ�����׳ɹ�������
*               ѧϰ�����ߣ��������Ƽ���DJI��ZEROTECH��XAG��AEE��GDU��AUTEL��EWATT��HIGH GREAT�ȹ�˾��ҵ
*               ��ְ�����뷢�ͣ�15671678205@163.com���豸ע��ְ����λ����λ��������
*               �����ƴ���Դ�ɿ�QQȺ��540707961
*               CSDN���ͣ�http://blog.csdn.net/u011992534
*               �ſ�ID��NamelessCotrun����С��
*               Bվ��ѧ��Ƶ��https://space.bilibili.com/67803559/#/video
*               �ͻ�ʹ���ĵá��Ľ������������http://www.openedv.com/forum.php?mod=viewthread&tid=234214&extra=page=1
*               �Ա����̣�https://shop348646912.taobao.com/?spm=2013.1.1000126.2.5ce78a88ht1sO2
*               �ٶ�����:�����ƴ���Դ�ɿ�
*               �޸�����:2018/8/30
*               �汾���۷��ߡ���V1.0.1
*               ��Ȩ���У�����ؾ���
*               Copyright(C) �人�Ƽ���ѧ�����ƴ��Ŷ� 2017-2025
*               All rights reserved
----------------------------------------------------------------------------------------------------------------------*/
#ifndef _MPU6050_H_
#define _MPU6050_H_

//****************************************
// MPU6050
//****************************************
// acceleration due to gravity in m/s/s
#define GRAVITY_MSS 9.80665f
// Gyroscope scale (uncertain where the 0.01745 value comes from)
#define GYRO_SCALE_2000  (0.0174532f / 16.4f)
#define GYRO_SCALE_1000  (0.0174532f / 32.8f)
#define GYRO_SCALE_500  (0.0174532f / 65.5f)
#define SCALE_250  (0.0174532f / 131f)
// Accelerometer scale adjustment
#define ACCEL_SCALE_16G   (GRAVITY_MSS / 2048.0f)
#define ACCEL_SCALE_8G    (GRAVITY_MSS / 4096.0f)
#define ACCEL_SCALE_4G    (GRAVITY_MSS / 8192.0f)
#define ACCEL_SCALE_2G    (GRAVITY_MSS / 16384.0f)


#define	SMPLRT_DIV		0x19
#define	MPU_CONFIG		0x1A
#define	GYRO_CONFIG		0x1B
#define	ACCEL_CONFIG	        0x1C
#define	ACCEL_XOUT_H	        0x3B
#define	ACCEL_XOUT_L	        0x3C
#define	ACCEL_YOUT_H	        0x3D
#define	ACCEL_YOUT_L	        0x3E
#define	ACCEL_ZOUT_H	        0x3F
#define	ACCEL_ZOUT_L	        0x40
#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42
#define	GYRO_XOUT_H		0x43
#define	GYRO_XOUT_L		0x44
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48
#define	PWR_MGMT_1		0x6B
#define	WHO_AM_I		0x75
#define USER_CTRL		0x6A
#define INT_PIN_CFG		0x37




float invSqrt(float x);
void GET_MPU_DATA(void);
int16_t GetData(uint8_t REG_Address);
void IMU_Calibration(void);
void Angle_Calculate(void);//�Ƕȼ���
void Accel_Filter(void);



void Init_MPU6050(void);
//-----IMU-----//
typedef struct
{
  float accelRaw[3];	// ���ٶȼ�ԭʼ����
  float gyroRaw[3];     // ������ԭʼ����
  float accelFilter[3];	// ���ٶȼ��˲�������
  float gyroFilter[3];	// �������˲�������
}_IMU_Tag;


extern float ACCE_X,ACCE_Y,ACCE_Z;
extern float  X_g,Y_g,Z_g;
extern float  X_g_av,Y_g_av,Z_g_av;
extern float  X_w,Y_w,Z_w;
extern float  X_w_av,Y_w_av,Z_w_av;
extern float X_Origion,Y_Origion,Z_Origion;
extern float  X_g_av_bpf,Y_g_av_bpf,Z_g_av_bpf;//�����˲�����õļ��ٶȼ�ֵ
extern int16_t Acce_Correct[3];
extern float K[3];//������
extern float B[3];//��λ���
extern _IMU_Tag imu;
extern uint8_t Acce_Correct_Update_Flag;
extern Vector3f DCM_Gyro,DCM_Acc;
extern uint8_t Gyro_Range_Mode;
extern float Gyro_Range_Scale,Gyro_Range_Offset_Gain;
extern Vector3f gyro_offset;

#endif
