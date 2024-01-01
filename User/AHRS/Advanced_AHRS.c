#include "Headfile.h"
#include "arm_math.h"
#include "Advanced_AHRS.h"
#include "EKF.h"

EKF_Filter EKF_NamelessCotrun;
float EKF_Q_NamelessCotrun[4]={1,0,0,0};
float EKF_Gyro_NamelessCotrun[3]={0,0,0};
float EKF_Accel_NamelessCotrun[3]={0,0,0};
float EKF_Mag_NamelessCotrun[3]={0,0,0};

/***********EKF״̬��Ϊ��X=[q0 q1 q2 q3 wx wy wz]^T*******************/
void EKF_Init_NamelessCotrun(void)//����Ԫ����ֵ�뵱ǰ���ٶȳ�ʼ��EKF״̬��
{
  EKF_Init(&EKF_NamelessCotrun,
           EKF_Q_NamelessCotrun,
           EKF_Gyro_NamelessCotrun);
}


/*******************ʵ��STM32F103RCT6�����ʱ96ms�������������Ҫ�󣬴���*************************/
void EKF_Update_NamelessCotrun(void)
{
  EKF_Gyro_NamelessCotrun[0]=X_w_av*GYRO_CALIBRATION_COFF;
  EKF_Gyro_NamelessCotrun[1]=Y_w_av*GYRO_CALIBRATION_COFF;
  EKF_Gyro_NamelessCotrun[2]=Z_w_av*GYRO_CALIBRATION_COFF;
  EKF_Accel_NamelessCotrun[0]=X_g_av;
  EKF_Accel_NamelessCotrun[1]=Y_g_av;
  EKF_Accel_NamelessCotrun[2]=Z_g_av;
  ///EKF_Mag_NamelessCotrun[0]=MAGData[0];
  //EKF_Mag_NamelessCotrun[1]=MAGData[1];
  //EKF_Mag_NamelessCotrun[2]=MAGData[2];
  
  EFK_Update(&EKF_NamelessCotrun,
             EKF_Q_NamelessCotrun,
             EKF_Gyro_NamelessCotrun,
             EKF_Accel_NamelessCotrun,
             EKF_Mag_NamelessCotrun,
             AHRS_DT);
}