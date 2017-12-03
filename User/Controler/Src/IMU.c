#include "Headfile.h"
#include "IMU.h"
#include "math.h"
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
/***************************觉得不错，欢迎打赏，请小哥吃热干面：支付宝账号：1094744141@qq.com*********************************/
void imuComputeRotationMatrix(void);
float Yaw=0,Pitch=0,Roll=0;//四元数计算出的角度
float Yaw_Gyro=0,Pitch_Gyro=0,Roll_Gyro=0;
float Mag_Yaw=0;
float Yaw_Correct=0;
void Insert_Yaw(void)
{
  Mag_Yaw=Mag_IST8310.Angle_Mag;
}

#define FAST_ATAN2_PIBY2_FLOAT  1.5707963f
// fast_atan2 - faster version of atan2
//      126 us on AVR cpu vs 199 for regular atan2
//      absolute error is < 0.005 radians or 0.28 degrees
//      origin source: https://gist.github.com/volkansalma/2972237/raw/
float fast_atan2(float y, float x)
{
        float atan;
        float z;
	if (x == 0.0f) {
       if (y > 0.0f) {
           return FAST_ATAN2_PIBY2_FLOAT;
       }
       if (y == 0.0f) {
           return 0.0f;
       }
       return -FAST_ATAN2_PIBY2_FLOAT;
   }

   z = y/x;
   if (fabs( z ) < 1.0f) {
       atan = z / (1.0f + 0.28f * z * z);
       if (x < 0.0f) {
           if (y < 0.0f) {
               return atan - PI;
           }
           return atan + PI;
       }
   } else {
       atan = FAST_ATAN2_PIBY2_FLOAT - (z / (z * z + 0.28f));
       if (y < 0.0f) {
           return atan - PI;
       }
   }
   return atan;
}

float constrain(float value, const float min_val, const float max_val)
{
  if(value>=max_val)  value=max_val;
  if(value<=min_val)  value=min_val;
  return value;
}


extern float  X_w;
extern float  Y_w;
extern float  Z_w;
//-----姿态更新相关定义-----//

#define dt 0.005f																								//2倍Ki
float g_q0 = 1.0f, g_q1 = 0.0f, g_q2 = 0.0f, g_q3 = 0.0f;					//四元数


struct _Attitude_Tag
{
	float q[4];
	float angle[3];
};

struct _Attitude_Tag att =
{
	{1.0f, 0.0f, 0.0f, 0.0f},
	{0.0f, 0.0f, 0.0f}
};

float Get_Gyro_Length(float gx,float gy,float gz)
{
   return sqrt(gx*gx+gy*gy+gz*gz);
}


float q0_DCM  = 1.0f, q1_DCM  = 0.0f, q2_DCM  = 0.0f, q3_DCM  = 0.0f;
float rMat[3][3];
float sqf(float x) {return ((x)*(x));}
void imuComputeRotationMatrix(void)
{
     float q1q1,q2q2,q3q3;
     float q0q1,q0q2,q0q3,q1q2,q1q3,q2q3;

    q0_DCM=att.q[0];
    q1_DCM=att.q[1];
    q2_DCM=att.q[2];
    q3_DCM=att.q[3];

    q1q1 = sqf(q1_DCM );
    q2q2 = sqf(q2_DCM );
    q3q3 = sqf(q3_DCM );

    q0q1 = q0_DCM  * q1_DCM ;
    q0q2 = q0_DCM  * q2_DCM ;
    q0q3 = q0_DCM  * q3_DCM ;
    q1q2 = q1_DCM  * q2_DCM ;
    q1q3 = q1_DCM  * q3_DCM ;
    q2q3 = q2_DCM  * q3_DCM ;

    rMat[0][0] = 1.0f - 2.0f * q2q2 - 2.0f * q3q3;
    rMat[0][1] = 2.0f * (q1q2 -q0q3);
    rMat[0][2] = 2.0f * (q1q3 +q0q2);

    rMat[1][0] = 2.0f * (q1q2 +q0q3);
    rMat[1][1] = 1.0f - 2.0f * q1q1 - 2.0f * q3q3;
    rMat[1][2] = 2.0f * (q2q3 -q0q1);

    rMat[2][0] = 2.0f * (q1q3 -q0q2);
    rMat[2][1] = 2.0f * (q2q3 +q0q1);
    rMat[2][2] = 1.0f - 2.0f * q1q1 - 2.0f * q2q2;
}

/******************************************************************************************
函数名:	void AHRSUpdate_GraDes(float gx, float gy, float gz, float ax, float ay, float az)
说明:	陀螺仪+加速度计梯度下降姿态融合算法
入口:	float gx	陀螺仪x分量
		float gy	陀螺仪y分量
		float gz	陀螺仪z分量
		float ax	加速度计x分量
		float ay	加速度计y分量
		float az	加速度计z分量
出口:	无
备注:	http://blog.csdn.net/nemol1990
******************************************************************************************/
float Beta_Adjust[5]={0.06,0.03,0.025,0.02,0.01};//{0.04,0.03,0.025,0.02,0.01};
float BETADEF=0.4;
float Gyro_Length=0;//陀螺仪模长
#define Quad_Num  50
float Quad_Buf[Quad_Num][4]={0};
uint16 Quad_Delay=3;//5
float Gyro_History[3]={0};//角速度
float Gyro_Delta[3]={0};//角速度增量
float Gyro_Delta_Length=0;//角加速度模长
float Acce_Length=0;//角加速度模长
Testime IMU_Delta;
float IMU_Dt=0;
void AHRSUpdate_GraDes_Delay_Corretion(float gx, float gy, float gz, float ax, float ay, float az)
{
	float recipNorm;					// 平方根
	float s0, s1, s2, s3;					// 梯度下降算子求出来的姿态
	float qDot1, qDot2, qDot3, qDot4;			// 四元数微分方程求得的姿态
	float _2q0, _2q1, _2q2, _2q3, _4q0, _4q1, _4q2 ,_8q1, _8q2, q0q0, q1q1, q2q2, q3q3;
	float delta;
        uint16 i=0;
        float Tmep_Acce_Length=0;
        Test_Period(&IMU_Delta);
        IMU_Dt=IMU_Delta.Time_Delta/1000.0;
        Insert_Yaw();//更具不同传感器模块，选择对应磁力计
        for(i=Quad_Num-1;i>0;i--)//将四元数历史值保存起来
        {
          Quad_Buf[i][0]=Quad_Buf[i-1][0];
          Quad_Buf[i][1]=Quad_Buf[i-1][1];
          Quad_Buf[i][2]=Quad_Buf[i-1][2];
          Quad_Buf[i][3]=Quad_Buf[i-1][3];
        }
          Quad_Buf[0][0]=att.q[0];
          Quad_Buf[0][1]=att.q[1];
          Quad_Buf[0][2]=att.q[2];
          Quad_Buf[0][3]=att.q[3];
          Gyro_History[0]=Pitch_Gyro;
          Gyro_History[1]=Roll_Gyro;
          Gyro_History[2]=Yaw_Gyro;
          /**************角速度数字量转化成角度制，单位:度/秒(deg/s)*************/
          gx*=GYRO_CALIBRATION_COFF;
          gy*=GYRO_CALIBRATION_COFF;
          gz*=GYRO_CALIBRATION_COFF;
          /************角速度赋值，用于姿态控制内环,角速度反馈*************/
          Yaw_Gyro=gz;
          Pitch_Gyro=gx;
          Roll_Gyro=gy;

          Gyro_Delta[0]=Pitch_Gyro-Gyro_History[0];
          Gyro_Delta[1]=Roll_Gyro-Gyro_History[1];
          Gyro_Delta[2]=Yaw_Gyro-Gyro_History[2];
          //角加速度模长
          Gyro_Delta_Length=sqrt(Gyro_Delta[0]*Gyro_Delta[0]
                                 +Gyro_Delta[1]*Gyro_Delta[1]
                                         +Gyro_Delta[2]*Gyro_Delta[2]);
          //角速度模长
          Gyro_Length=sqrt(Yaw_Gyro*Yaw_Gyro
                                 +Pitch_Gyro*Pitch_Gyro
                                         +Roll_Gyro*Roll_Gyro);


          /* 转换为弧度制，用于姿态更新*/
          gx = gx * PI / 180;
          gy = gy * PI / 180;
          gz = gz * PI / 180;
          /* 四元数微分方程计算本次待矫正四元数 */
          qDot1 = 0.5f * (-Quad_Buf[Quad_Delay][1] * gx - Quad_Buf[Quad_Delay][2] * gy - Quad_Buf[Quad_Delay][3] * gz);
          qDot2 = 0.5f * (Quad_Buf[Quad_Delay][0] * gx + Quad_Buf[Quad_Delay][2] * gz - Quad_Buf[Quad_Delay][3] * gy);
          qDot3 = 0.5f * (Quad_Buf[Quad_Delay][0] * gy - Quad_Buf[Quad_Delay][1] * gz + Quad_Buf[Quad_Delay][3] * gx);
          qDot4 = 0.5f * (Quad_Buf[Quad_Delay][0] * gz + Quad_Buf[Quad_Delay][1] * gy - Quad_Buf[Quad_Delay][2] * gx);
	/* 加速度计输出有效时,利用加速度计补偿陀螺仪 */
	if(!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f)))
	{
                recipNorm=invSqrt(ax * ax + ay * ay + az * az);
		ax *= recipNorm;
		ay *= recipNorm;
		az *= recipNorm;
		/* 避免重复运算 */
		_2q0 = 2.0f * att.q[0];
		_2q1 = 2.0f * att.q[1];
		_2q2 = 2.0f * att.q[2];
		_2q3 = 2.0f * att.q[3];
		_4q0 = 4.0f * att.q[0];
		_4q1 = 4.0f * att.q[1];
		_4q2 = 4.0f * att.q[2];
		_8q1 = 8.0f * att.q[1];
		_8q2 = 8.0f * att.q[2];
		q0q0 = att.q[0] * att.q[0];
		q1q1 = att.q[1] * att.q[1];
		q2q2 = att.q[2] * att.q[2];
		q3q3 = att.q[3] * att.q[3];

		/* 梯度下降算法,计算误差函数的梯度 */
		s0 = _4q0 * q2q2 + _2q2 * ax + _4q0 * q1q1 - _2q1 * ay;
		s1 = _4q1 * q3q3 - _2q3 * ax + 4.0f * q0q0 * att.q[1] - _2q0 * ay - _4q1 + _8q1 * q1q1 + _8q1 * q2q2 + _4q1 * az;
		s2 = 4.0f * q0q0 * att.q[2] + _2q0 * ax + _4q2 * q3q3 - _2q3 * ay - _4q2 + _8q2 * q1q1 + _8q2 * q2q2 + _4q2 * az;
		s3 = 4.0f * q1q1 * att.q[3] - _2q1 * ax + 4.0f * q2q2 * att.q[3] - _2q2 * ay;

		/* 梯度归一化 */
		recipNorm=invSqrt(s0 * s0 + s1 * s1 + s2 * s2 + s3 * s3);
		s0 *= recipNorm;
		s1 *= recipNorm;
		s2 *= recipNorm;
		s3 *= recipNorm;
                Tmep_Acce_Length=constrain(Acceleration_Length,0,1000);//正常悬停在500以内
                BETADEF=Beta_Adjust[0]-0.02*Tmep_Acce_Length/1000;//动态步长
                qDot1 -= BETADEF * s0;
                qDot2 -= BETADEF * s1;
                qDot3 -= BETADEF * s2;
                qDot4 -= BETADEF * s3;
	}
		/* 补偿由四元数微分方程引入的姿态误差 */
		/* 将四元数姿态导数积分,得到当前四元数姿态 */
		/* 二阶毕卡求解微分方程 */
		delta = (IMU_Dt * gx) * (IMU_Dt * gx) + (IMU_Dt * gy) * (IMU_Dt * gy) + (IMU_Dt * gz) * (IMU_Dt * gz);
		att.q[0] = (1.0f - delta / 8.0f) * att.q[0] + qDot1 * IMU_Dt;
		att.q[1] = (1.0f - delta / 8.0f) * att.q[1] + qDot2 * IMU_Dt;
		att.q[2] = (1.0f - delta / 8.0f) * att.q[2] + qDot3 * IMU_Dt;
		att.q[3] = (1.0f - delta / 8.0f) * att.q[3] + qDot4 * IMU_Dt;
		/* 单位化四元数 */
		recipNorm=invSqrt(att.q[0] * att.q[0] + att.q[1] * att.q[1] + att.q[2] * att.q[2] + att.q[3] * att.q[3]);
		att.q[0] *= recipNorm;
		att.q[1] *= recipNorm;
		att.q[2] *= recipNorm;
		att.q[3] *= recipNorm;
		/* 四元数到欧拉角转换,转换顺序为Z-Y-X,参见<Representing Attitude: Euler Angles, Unit Quaternions, and Rotation Vectors>.pdf一文,P24 */
		Pitch= atan2(2.0f * att.q[2] * att.q[3] + 2.0f * att.q[0] * att.q[1], -2.0f * att.q[1] * att.q[1] - 2.0f * att.q[2]* att.q[2] + 1.0f) * RAD2DEG;// Pitch
		Roll= asin(2.0f * att.q[0]* att.q[2]-2.0f * att.q[1] * att.q[3]) * RAD2DEG;									// Roll
		//att.angle[YAW] = atan2(2.0f * att.q[1] * att.q[2] + 2.0f * att.q[0] * att.q[3], -2.0f * att.q[3] * att.q[3] - 2.0f * att.q[2] * att.q[2] + 1.0f) * RAD2DEG;// Yaw
						/*偏航角一阶互补*/
		att.angle[_YAW]+=Yaw_Gyro*dt;
		if((Mag_Yaw>90 && att.angle[_YAW]<-90)
				 || (Mag_Yaw<-90 && att.angle[_YAW]>90))
                att.angle[_YAW] = -att.angle[_YAW] * 0.98f + Mag_Yaw * 0.02f;
                else att.angle[_YAW] = att.angle[_YAW] * 0.98f + Mag_Yaw * 0.02f;
		if(att.angle[_YAW]<0)   Yaw=att.angle[_YAW]+360;
		else Yaw=att.angle[_YAW];
		Yaw_Correct=Yaw;//0~360
	        imuComputeRotationMatrix();
}
/***************************觉得不错，欢迎打赏，请小哥吃热干面：支付宝账号：1094744141@qq.com*********************************/