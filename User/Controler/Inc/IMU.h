/*----------------------------------------------------------------------------------------------------------------------/
*               本程序只供购买者学习使用，版权著作权属于无名科创团队，无名科创团队将飞控程序源码提供给购买者，
*               购买者要为无名科创团队提供保护，未经作者许可，不得将源代码提供给他人，不得将源代码放到网上供他人免费下载， 
*               更不能以此销售牟利，如发现上述行为，无名科创团队将诉之以法律解决！！！
-----------------------------------------------------------------------------------------------------------------------/
*               生命不息、奋斗不止；前人栽树，后人乘凉！！！
*               开源不易，且学且珍惜，祝早日逆袭、进阶成功！！！
*               学习优秀者，简历可推荐到DJI、ZEROTECH、XAG、AEE、GDU、AUTEL、EWATT、HIGH GREAT等公司就业
*               求职简历请发送：15671678205@163.com，需备注求职意向单位、岗位、待遇等
*               无名科创开源飞控QQ群：540707961
*               CSDN博客：http://blog.csdn.net/u011992534
*               优酷ID：NamelessCotrun无名小哥
*               B站教学视频：https://space.bilibili.com/67803559/#/video
*               客户使用心得、改进意见征集贴：http://www.openedv.com/forum.php?mod=viewthread&tid=234214&extra=page=1
*               淘宝店铺：https://shop348646912.taobao.com/?spm=2013.1.1000126.2.5ce78a88ht1sO2
*               百度贴吧:无名科创开源飞控
*               修改日期:2018/8/30
*               版本：慧飞者——V1.0.1
*               版权所有，盗版必究。
*               Copyright(C) 武汉科技大学无名科创团队 2017-2025
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

#define  YAW_FUSION_MODE_QUAD  0	//1：偏航角来源于四元数更新，时间长容易偏移，
																	//   针对电赛室内环境磁场干扰大的情况，推荐此方式
																	//0：偏航角来源于偏航角速度与磁力计一阶互补，GPS定点时选择此方式
																	//   推荐采用外置磁力计数据



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
