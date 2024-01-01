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
#ifndef __IMU_H
#define __IMU_H
#define RtA         57.324841
#define AtR    	    0.0174533
#define Acc_G 	    0.0000610351
#define Gyro_G 	    0.0610351
#define Gyro_Gr	    0.0010653
#define DEG2RAD (PI / 180.0f)
#define RAD2DEG (180.0f / PI)
//#define GYRO_CALIBRATION_COFF 0.060976f  //2000
//#define GYRO_CALIBRATION_COFF 0.030488f  //1000
#define GYRO_CALIBRATION_COFF 0.0152672f    //500

#define  YAW_FUSION_MODE_QUAD  0	//1��ƫ������Դ����Ԫ�����£�ʱ�䳤����ƫ�ƣ�
																	//   ��Ե������ڻ����ų����Ŵ��������Ƽ��˷�ʽ
																	//0��ƫ������Դ��ƫ�����ٶ��������һ�׻�����GPS����ʱѡ��˷�ʽ
																	//   �Ƽ��������ô���������



typedef struct
{
  float q[4];
  float angle[3];
}_Attitude_Tag;
extern _Attitude_Tag att;

extern float Yaw;
extern float Pitch;
extern float Roll;
extern float Yaw_Gyro,Pitch_Gyro,Roll_Gyro,Yaw_Gyro_Earth_Frame;
float constrain(float value, const float min_val, const float max_val);

void AHRSUpdate_GraDes_TimeSync(float gx, float gy, float gz, float ax, float ay, float az);
void Vector_From_BodyFrame2EarthFrame(Vector3f *bf,Vector3f *ef);
void Vector_From_EarthFrame2BodyFrame(Vector3f *ef,Vector3f *bf);
uint8_t Effective_Gravity_Acceleration(uint16_t num,float quality);

void Euler_Angle_Init(void);
void NCQ_Quad_Init(void);
void DirectionConsineMatrix(Vector3f gyro,Vector3f acc,Vector2f magn);

extern float BETADEF;
extern  float rMat[3][3];
extern Vector3f DCM_Euler_Angle;
extern float Gyro_Length,Gyro_Length_Filter;
extern float Mag_Yaw;
extern float Gyro_Delta_Length;
extern float Test_DCM[2];
extern Vector3f Body_Motion_Acceleration;
extern Vector3f_Body Circle_Angle;
extern float gyro[3];
extern float Adjust_Beta;
#endif
