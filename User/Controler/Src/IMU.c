/* Copyright (c)  2019-2025 Wuhan Nameless Innovation Technology Co.,Ltd. All rights reserved.*/
/*----------------------------------------------------------------------------------------------------------------------/
                开源并不等于免费，先驱者的历史已经证明，在国内这个环境下，毫无收益的开源，单靠坊间个人爱好者，自发地参与项
								目完善的方式行不通，好的开源项目需要请专职人员做好售后服务、手把手教学、统计用户反馈需求、在实践中完成对产
								品的一次次完善与迭代升级。经过综合考虑，无名飞控开源代码中，程序仅保留公司正版激活功能代码，版本激活无实际
								功能，属于公司产品常规出厂操作，不影响客户学习，其余代码全部开放给客户学习，客户移植和二次开发代码请保留代
								码版权。
-----------------------------------------------------------------------------------------------------------------------/
*               本程序只供购买者学习使用，版权著作权属于无名科创团队，无名科创团队将飞控程序源码提供给购买者，
*               购买者要为无名科创团队提供保护，未经作者许可，不得将源代码提供给他人，不得将源代码放到网上供他人免费下载， 
*               更不能以此销售牟利，如发现上述行为，无名科创团队将诉之以法律解决！！！
-----------------------------------------------------------------------------------------------------------------------
*                                                 为什么选择无名创新？
*                                         感动人心价格厚道，最靠谱的开源飞控；
*                                         国内业界良心之作，最精致的售后服务；
*                                         追求极致用户体验，高效进阶学习之路；
*                                         萌新不再孤单求索，合理把握开源尺度；
*                                         响应国家扶贫号召，促进教育体制公平；
*                                         新时代奋斗最出彩，建人类命运共同体。 
-----------------------------------------------------------------------------------------------------------------------
*               生命不息、奋斗不止；前人栽树，后人乘凉！！！
*               开源不易，且学且珍惜，祝早日逆袭、进阶成功！！！
*               学习优秀者，简历可推荐到DJI、ZEROTECH、XAG、AEE、GDU、AUTEL、EWATT、HIGH GREAT等公司就业
*               求职简历请发送：15671678205@163.com，需备注求职意向单位、岗位、待遇等
*               无名科创开源飞控QQ群：2号群465082224、1号群540707961（人员已满）
*               CSDN博客：http://blog.csdn.net/u011992534
*               优酷ID：NamelessCotrun无名小哥
*               B站教学视频：https://space.bilibili.com/67803559/#/video
*               客户使用心得、改进意见征集贴：http://www.openedv.com/forum.php?mod=viewthread&tid=234214&extra=page=1
*               淘宝店铺：https://shop348646912.taobao.com/?spm=2013.1.1000126.2.5ce78a88ht1sO2
*               百度贴吧:无名科创开源飞控
*               公司官网:www.nameless.tech
*               无名创新国内首款TI开源飞控设计初衷、知乎专栏:https://zhuanlan.zhihu.com/p/54471146
*               修改日期:2019/11/27                    
*               版本：慧飞者PRO——WisdomPilot_Pro_V1.0.0
*               版权所有，盗版必究。
*               Copyright(C) 2019-2025 武汉无名创新科技有限公司 
*               All rights reserved
-----------------------------------------------------------------------------------------------------------------------
*               重要提示：
*               正常淘宝咸鱼转手的飞控、赠送朋友、传给学弟的都可以进售后群学习交流，
*               不得直接在网上销售无名创新资料，无名创新代码有声明版权，他人不得将
*               资料代码传网上供他人下载，不得以谋利为目的销售资料代码，发现有此操
*               作者，公司会提前告知，请1天内及时处理，否则你的学校、单位、姓名、电
*               话、地址信息会被贴出在公司官网、官方微信公众平台、官方技术博客、知乎
*               专栏以及淘宝店铺首页予以公示公告，此种所作所为，会成为个人污点，影响
*               升学、找工作、社会声誉、很快就很在无人机界出名，后果很严重。
*               因此行为给公司造成重大损失者，会以法律途径解决，感谢您的合作，谢谢！！！
----------------------------------------------------------------------------------------------------------------------*/
#include "Headfile.h"
#include "IMU.h"
#include "math.h"
void imuComputeRotationMatrix(void);
Vector3f_Body Circle_Angle;
float Yaw=0,Pitch=0,Roll=0;//四元数计算出的角度
float Yaw_Gyro=0,Pitch_Gyro=0,Roll_Gyro=0;
float Yaw_Gyro_Radian=0,Pitch_Gyro_Radian=0,Roll_Gyro_Radian=0;
float Yaw_Gyro_Earth_Frame=0;
float Mag_Yaw=0;
void Insert_Yaw(void)
{
#ifdef IMU_BOARD_NC686
  if(Extern_Mag_Work_Flag==1) Mag_Yaw=HMC5883L_Yaw;
  else Mag_Yaw=Mag_IST8310.Angle_Mag;
#endif
  
#ifdef IMU_BOARD_GY86
  Mag_Yaw=HMC5883L_Yaw;
#endif
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


_Attitude_Tag att =
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
  Sin_Pitch=sin(Pitch* DEG2RAD);
  Cos_Pitch=cos(Pitch* DEG2RAD);
  Sin_Roll=sin(Roll* DEG2RAD);
  Cos_Roll=cos(Roll* DEG2RAD);
  Sin_Yaw=sin(Yaw* DEG2RAD);
  Cos_Yaw=cos(Yaw* DEG2RAD); 
  rMat[0][0]=Cos_Yaw* Cos_Roll;
  rMat[0][1]=Sin_Pitch*Sin_Roll*Cos_Yaw-Cos_Pitch * Sin_Yaw;
  rMat[0][2]=Sin_Pitch * Sin_Yaw+Cos_Pitch * Sin_Roll * Cos_Yaw;  
  rMat[1][0]=Sin_Yaw * Cos_Roll;
  rMat[1][1]=Sin_Pitch * Sin_Roll * Sin_Yaw +Cos_Pitch * Cos_Yaw;
  rMat[1][2]=Cos_Pitch * Sin_Roll * Sin_Yaw - Sin_Pitch * Cos_Yaw;
  rMat[2][0]=-Sin_Roll;
  rMat[2][1]= Sin_Pitch * Cos_Roll;
  rMat[2][2]= Cos_Pitch * Cos_Roll;
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
#define Beta_Base 0.0075f
float BETADEF=0.01;
float Gyro_Length=0,Gyro_Length_Filter=0;//陀螺仪模长
#define Quad_Num  20
float Quad_Buf[Quad_Num][4]={0};
uint16 Quad_Delay=5;//3  10  5
float Gyro_History[3]={0};//角速度
float Gyro_Delta[3]={0};//角速度增量
float Gyro_Delta_Length=0;//角加速度模长
float Acce_Length=0;//角加速度模长
Testime IMU_Delta;
float IMU_Dt=0;
float Gyro_Record[3][10]={0};
uint16_t TimeSync_Cnt=9;//
float Adjust_Beta=0;
float exInt=0,eyInt=0,ezInt=0; 
float Kp=0,Ki=0;//0.0001f;
float Yaw_Fusion_Beta=0.025f;
Vector4q quad_buffer[Quad_Num];
Butter_BufferData Butter_Buffer_Gyro_Length;
void AHRSUpdate_GraDes_TimeSync(float gx, float gy, float gz, float ax, float ay, float az)
{
  float recipNorm;											// 平方根
  float s0, s1, s2, s3;									// 梯度下降算子求出来的姿态
  float qDot1, qDot2, qDot3, qDot4;			// 四元数微分方程求得的姿态
  float _2q0, _2q1, _2q2, _2q3, _4q0, _4q1, _4q2 ,_8q1, _8q2, q0q0, q1q1, q2q2, q3q3;
  float delta;
  static float vx=0,vy=0,vz=0;
  static float ex=0,ey=0,ez=0; 
  uint16 i=0;
  static Vector3f accel[Quad_Num];
  static uint16_t sync_cnt=0;
  Test_Period(&IMU_Delta);
  IMU_Dt=IMU_Delta.Time_Delta/1000.0;
  Insert_Yaw();//更具不同传感器模块，选择对应磁力计
  sync_cnt++;
  if(sync_cnt>=4)//4*5=20ms滑动一次
  {
    for(i=Quad_Num-1;i>0;i--)//将四元数历史值保存起来,20*20=400ms
    {
      quad_buffer[i].q0=quad_buffer[i-1].q0;
      quad_buffer[i].q1=quad_buffer[i-1].q1;
      quad_buffer[i].q2=quad_buffer[i-1].q2;
      quad_buffer[i].q3=quad_buffer[i-1].q3;
      accel[i].x=accel[i-1].x;
      accel[i].y=accel[i-1].y;
      accel[i].z=accel[i-1].z;
    }
    quad_buffer[0].q0=att.q[0];
    quad_buffer[0].q1=att.q[1];
    quad_buffer[0].q2=att.q[2];
    quad_buffer[0].q3=att.q[3];
    sync_cnt=0;
  }
  
  
  accel[0].x=ax;
  accel[0].y=ay;
  accel[0].z=az;
  
  for(i=9;i>0;i--)//将四元数历史值保存起来,20*20=400ms
  {
    Gyro_Record[0][i]=Gyro_Record[0][i-1];
    Gyro_Record[1][i]=Gyro_Record[1][i-1];
    Gyro_Record[2][i]=Gyro_Record[2][i-1];
  }
  Gyro_Record[0][0]=Pitch_Gyro;
  Gyro_Record[1][0]=Roll_Gyro;
  Gyro_Record[2][0]=Yaw_Gyro;
  
  /**************角速度数字量转化成角度制，单位:度/秒(deg/s)*************/
  gx*=Gyro_Range_Scale;
  gy*=Gyro_Range_Scale;
  gz*=Gyro_Range_Scale;
  /************角速度赋值，用于姿态控制内环,角速度反馈*************/
  
  Pitch_Gyro=X_w_av*Gyro_Range_Scale;
  Roll_Gyro=Y_w_av*Gyro_Range_Scale;
  Yaw_Gyro=Z_w_av*Gyro_Range_Scale;
  
  Pitch_Gyro_Radian=Pitch_Gyro*DEG2RAD;
  Roll_Gyro_Radian=Roll_Gyro*DEG2RAD;
  Yaw_Gyro_Radian=Yaw_Gyro*DEG2RAD; 
  
  //{-sinθ          cosθsin Φ                          cosθcosΦ                   }
  Yaw_Gyro_Earth_Frame=-Sin_Roll*gx+ Cos_Roll*Sin_Pitch *gy+ Cos_Pitch * Cos_Roll *gz;
  Gyro_Delta[0]=(Gyro_Record[0][0]-Gyro_Record[0][1]);
  Gyro_Delta[1]=(Gyro_Record[1][0]-Gyro_Record[1][1]);
  Gyro_Delta[2]=(Gyro_Record[2][0]-Gyro_Record[2][1]);
  //角加速度模长
  Gyro_Delta_Length=sqrt(Gyro_Delta[0]*Gyro_Delta[0]
                         +Gyro_Delta[1]*Gyro_Delta[1]
                           +Gyro_Delta[2]*Gyro_Delta[2]);
  //角速度模长
  Gyro_Length=sqrt(Yaw_Gyro*Yaw_Gyro
                   +Pitch_Gyro*Pitch_Gyro
                     +Roll_Gyro*Roll_Gyro);//单位deg/s
  Gyro_Length_Filter=LPButterworth(Gyro_Length,
                     &Butter_Buffer_Gyro_Length,&Butter_5HZ_Parameter_Acce);
  /* 加速度计输出有效时,利用加速度计补偿陀螺仪 */
  if(!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f)))
  {
    if(Effective_Gravity_Acceleration(GPS_Sate_Num,GPS_Quality))//GPS提取运动加速度
    {
      ax=accel[9].x-Body_Motion_Acceleration.x;//剔除运动加速度
      ay=accel[9].y-Body_Motion_Acceleration.y;
      az=accel[9].z-Body_Motion_Acceleration.z;
    }
    else
    {
      ax=accel[9].x;
      ay=accel[9].y;
      az=accel[9].z;
    }
    recipNorm=invSqrt(ax * ax + ay * ay + az * az);
    ax *= recipNorm;
    ay *= recipNorm;
    az *= recipNorm;
    /* 避免重复运算 */
    _2q0 = 2.0f * quad_buffer[TimeSync_Cnt].q0;
    _2q1 = 2.0f * quad_buffer[TimeSync_Cnt].q1;
    _2q2 = 2.0f * quad_buffer[TimeSync_Cnt].q2;
    _2q3 = 2.0f * quad_buffer[TimeSync_Cnt].q3;
    _4q0 = 4.0f * quad_buffer[TimeSync_Cnt].q0;
    _4q1 = 4.0f * quad_buffer[TimeSync_Cnt].q1;
    _4q2 = 4.0f * quad_buffer[TimeSync_Cnt].q2;
    _8q1 = 8.0f * quad_buffer[TimeSync_Cnt].q1;
    _8q2 = 8.0f * quad_buffer[TimeSync_Cnt].q2;
    q0q0 = quad_buffer[TimeSync_Cnt].q0 * quad_buffer[TimeSync_Cnt].q0;
    q1q1 = quad_buffer[TimeSync_Cnt].q1 * quad_buffer[TimeSync_Cnt].q1;
    q2q2 = quad_buffer[TimeSync_Cnt].q2 * quad_buffer[TimeSync_Cnt].q2;
    q3q3 = quad_buffer[TimeSync_Cnt].q3 * quad_buffer[TimeSync_Cnt].q3;
    
    /* 梯度下降算法,计算误差函数的梯度 */
    s0 = _4q0 * q2q2 + _2q2 * ax + _4q0 * q1q1 - _2q1 * ay;
    s1 = _4q1 * q3q3 - _2q3 * ax + 4.0f * q0q0 * quad_buffer[TimeSync_Cnt].q1 - _2q0 * ay - _4q1 + _8q1 * q1q1 + _8q1 * q2q2 + _4q1 * az;
    s2 = 4.0f * q0q0 * quad_buffer[TimeSync_Cnt].q2 + _2q0 * ax + _4q2 * q3q3 - _2q3 * ay - _4q2 + _8q2 * q1q1 + _8q2 * q2q2 + _4q2 * az;
    s3 = 4.0f * q1q1 * quad_buffer[TimeSync_Cnt].q3 - _2q1 * ax + 4.0f * q2q2 * quad_buffer[TimeSync_Cnt].q2 - _2q2 * ay;
    
    /* 梯度归一化 */
    recipNorm=invSqrt(s0 * s0 + s1 * s1 + s2 * s2 + s3 * s3);
    s0 *= recipNorm;
    s1 *= recipNorm;
    s2 *= recipNorm;
    s3 *= recipNorm;
    BETADEF=Beta_Base+0.025*IMU_Dt*constrain(Gyro_Length_Filter,0,400);
    BETADEF-=0.01*(constrain(Acceleration_Length,0,1000)/1000);//动态步长,正常悬停在500以内
    BETADEF=constrain(BETADEF,0.0075,0.06);
    
    
    vx=2*(quad_buffer[TimeSync_Cnt].q1*quad_buffer[TimeSync_Cnt].q3-quad_buffer[TimeSync_Cnt].q0*quad_buffer[TimeSync_Cnt].q2);
    vy=2*(quad_buffer[TimeSync_Cnt].q2*quad_buffer[TimeSync_Cnt].q3+quad_buffer[TimeSync_Cnt].q0*quad_buffer[TimeSync_Cnt].q1);
    vz=1-2*(quad_buffer[TimeSync_Cnt].q1*quad_buffer[TimeSync_Cnt].q1+quad_buffer[TimeSync_Cnt].q2*quad_buffer[TimeSync_Cnt].q2);
    
    ex =(ay*vz-az*vy);
    ey =(az*vx-ax*vz);
    ez =(ax*vy-ay*vx);
    // integral error scaled integral gain 
    exInt +=ex*Ki* IMU_Dt;
    eyInt +=ey*Ki* IMU_Dt;
    ezInt +=ez*Ki* IMU_Dt;
  }
  
  /* 转换为弧度制，用于姿态更新*/
  gx = gx * PI / 180+exInt+Kp*ex;
  gy = gy * PI / 180+eyInt+Kp*ey;
  gz = gz * PI / 180+ezInt+Kp*ez;
  
  /* 四元数微分方程计算本次待矫正四元数 */
  qDot1 = 0.5f * (-att.q[1] * gx - att.q[2] * gy - att.q[3] * gz);
  qDot2 = 0.5f * ( att.q[0] * gx + att.q[2] * gz - att.q[3] * gy);
  qDot3 = 0.5f * ( att.q[0] * gy - att.q[1] * gz + att.q[3] * gx);
  qDot4 = 0.5f * ( att.q[0] * gz + att.q[1] * gy - att.q[2] * gx);
  
  qDot1 -= BETADEF * s0;
  qDot2 -= BETADEF * s1;
  qDot3 -= BETADEF * s2;
  qDot4 -= BETADEF * s3;
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
  
	#if (YAW_FUSION_MODE_QUAD)
		  att.angle[_YAW] = atan2(2.0f * att.q[1] * att.q[2] + 2.0f * att.q[0] * att.q[3], -2.0f * att.q[3] * att.q[3] - 2.0f * att.q[2] * att.q[2] + 1.0f) * RAD2DEG;// Yaw
	    Yaw=att.angle[_YAW];
	#else
	/*偏航角一阶互补*/
	if(State_Breakdown.Compass_Fault_Flag==false)
	{	  
		att.angle[_YAW]+=Yaw_Gyro_Earth_Frame*IMU_Dt;
		if((Mag_Yaw>90 && att.angle[_YAW]<-90)
			 || (Mag_Yaw<-90 && att.angle[_YAW]>90))
			att.angle[_YAW] = -att.angle[_YAW]  *(1-Yaw_Fusion_Beta) + Mag_Yaw*Yaw_Fusion_Beta;
		else att.angle[_YAW] = att.angle[_YAW]*(1-Yaw_Fusion_Beta) + Mag_Yaw*Yaw_Fusion_Beta;
		
		if(att.angle[_YAW]<0)   Yaw=att.angle[_YAW]+360;
		else Yaw=att.angle[_YAW];
		
		if(GPS_Home_Set==1)  Yaw=Yaw-Declination;//如果GPS home点已设置，获取当地磁偏角，得到地理真北
  }
	else
	{
	  att.angle[_YAW] = atan2(2.0f * att.q[1] * att.q[2] + 2.0f * att.q[0] * att.q[3], -2.0f * att.q[3] * att.q[3] - 2.0f * att.q[2] * att.q[2] + 1.0f) * RAD2DEG;// Yaw
	  Yaw=att.angle[_YAW];
  }		
	#endif
  imuComputeRotationMatrix();
  
  Circle_Angle.Pit+=Pitch_Gyro*IMU_Dt;
  Circle_Angle.Rol+=Roll_Gyro*IMU_Dt;
  Circle_Angle.Yaw+=Yaw_Gyro*IMU_Dt;
  if(Circle_Angle.Pit<0)   Circle_Angle.Pit+=360;
  if(Circle_Angle.Pit>360) Circle_Angle.Pit-=360;
  if(Circle_Angle.Rol<0)   Circle_Angle.Rol+=360;
  if(Circle_Angle.Rol>360) Circle_Angle.Rol-=360;
  if(Circle_Angle.Yaw<0)   Circle_Angle.Yaw+=360;
  if(Circle_Angle.Yaw>360) Circle_Angle.Yaw-=360;
}





Vector3f Body_Motion_Acceleration;
uint8_t Effective_Gravity_Acceleration(uint16_t num,float quality)//有效重力加速度处理函数
{
  Vector3f Earth_Motion_Acceleration;
  if(num<=7||quality>3.0) return 0;
  Earth_Motion_Acceleration.x=GPS_Vel_Div.E/100;//单位m/s^2
  Earth_Motion_Acceleration.y=GPS_Vel_Div.N/100;//单位m/s^2
  Earth_Motion_Acceleration.z=GPS_Vel_Div.U/100;//单位m/s^2
  Vector_From_EarthFrame2BodyFrame(&Earth_Motion_Acceleration,&Body_Motion_Acceleration);
  Body_Motion_Acceleration.x*=(AcceMax/AcceGravity);//将GPS观测的运动加速度，量化为数字量
  Body_Motion_Acceleration.y*=(AcceMax/AcceGravity);
  Body_Motion_Acceleration.z*=(AcceMax/AcceGravity);
  return 1;
}

float euler_roll_init,euler_pitch_init,euler_yaw_init;
float q0_init, q1_init, q2_init, q3_init;

void Euler_Angle_Init()
{
  uint16_t i=0;
  //GET_MPU_DATA();
  Angle_Calculate();
  if(Extern_Mag_Work_Flag==1)//当检测存在HMC5883时，使用外部磁力计
  {
    for(i=0;i<5;i++)
    {
      delay_ms(5);
      HMC5883L_StateMachine();
    }
  }
  else  //使用外部磁力计IST8310
  {
    for(i=0;i<5;i++)
    {
      delay_ms(5);
      Get_Mag_IST8310();
    }
  }    
  Insert_Yaw();
  euler_roll_init =ACCE_X*DEG2RAD; //初始化欧拉翻滚角
  euler_pitch_init=ACCE_Y*DEG2RAD; //初始化欧拉俯仰角
  euler_yaw_init  =Mag_Yaw*DEG2RAD ;
}

/****************** 根据初始化欧拉角初始化四元数 *****************************/
void Quaternion_Init()
{
  Euler_Angle_Init();
  q0_init = cos(euler_yaw_init/2)*cos(euler_pitch_init/2)*cos(euler_roll_init/2)+sin(euler_yaw_init/2)*sin(euler_pitch_init/2)*sin(euler_roll_init/2);
  q1_init = cos(euler_yaw_init/2)*cos(euler_pitch_init/2)*sin(euler_roll_init/2)-sin(euler_yaw_init/2)*sin(euler_pitch_init/2)*cos(euler_roll_init/2);
  q2_init = cos(euler_yaw_init/2)*sin(euler_pitch_init/2)*cos(euler_roll_init/2)+sin(euler_yaw_init/2)*cos(euler_pitch_init/2)*sin(euler_roll_init/2);
  q3_init = sin(euler_yaw_init/2)*cos(euler_pitch_init/2)*cos(euler_roll_init/2)-cos(euler_yaw_init/2)*sin(euler_pitch_init/2)*sin(euler_roll_init/2);
}



float NCQ_Euler_To_Quaternion[4]={1,0,0,0};
void From_Euler_to_Quaternion(Vector3f euler)
{
  float _pitch,_roll,_yaw;
  _pitch=euler.x*DEG2RAD;
  _roll= euler.y*DEG2RAD;
  _yaw=  euler.z*DEG2RAD;
  NCQ_Euler_To_Quaternion[0] = cos(_yaw/2)*cos(_pitch/2)*cos(_roll/2)
    +sin(_yaw/2)*sin(_pitch/2)*sin(_roll/2);
  NCQ_Euler_To_Quaternion[1] = cos(_yaw/2)*cos(_pitch/2)*sin(_roll/2)
    -sin(_yaw/2)*sin(_pitch/2)*cos(_roll/2);
  NCQ_Euler_To_Quaternion[2] = cos(_yaw/2)*sin(_pitch/2)*cos(_roll/2)
    +sin(_yaw/2)*cos(_pitch/2)*sin(_roll/2);
  NCQ_Euler_To_Quaternion[3] = sin(_yaw/2)*cos(_pitch/2)*cos(_roll/2)
    -cos(_yaw/2)*sin(_pitch/2)*sin(_roll/2);
}


void NCQ_Quad_Init(void)//初始四元数初始化
{
  uint16_t i=0;
  Quaternion_Init();
  att.q[0]=q0_init;
  att.q[1]=q1_init;
  att.q[2]=q2_init;
  att.q[3]=q3_init;
  
  for(i=Quad_Num-1;i>0;i--)//将四元数历史值保存起来,20*20=400ms
  {
    quad_buffer[i].q0=att.q[0];
    quad_buffer[i].q1=att.q[1];
    quad_buffer[i].q2=att.q[2];
    quad_buffer[i].q3=att.q[3];
  }
  quad_buffer[0].q0=att.q[0];
  quad_buffer[0].q1=att.q[1];
  quad_buffer[0].q2=att.q[2];
  quad_buffer[0].q3=att.q[3];
  
}

void Vector_From_BodyFrame2EarthFrame(Vector3f *bf,Vector3f *ef)
{
  ef->x=rMat[0][0]*bf->x+rMat[0][1]*bf->y+rMat[0][2]*bf->z;
  ef->y=rMat[1][0]*bf->x+rMat[1][1]*bf->y+rMat[1][2]*bf->z;
  ef->z=rMat[2][0]*bf->x+rMat[2][1]*bf->y+rMat[2][2]*bf->z;
}

void Vector_From_EarthFrame2BodyFrame(Vector3f *ef,Vector3f *bf)
{
  bf->x=rMat[0][0]*ef->x+rMat[1][0]*ef->y+rMat[2][0]*ef->z;
  bf->y=rMat[0][1]*ef->x+rMat[1][1]*ef->y+rMat[2][1]*ef->z;
  bf->z=rMat[0][2]*ef->x+rMat[1][2]*ef->y+rMat[2][2]*ef->z;
}

#define INS_MAX_INSTANCES 3
Vector3f _omega_P;                          // accel Omega proportional correction
Vector3f _omega_yaw_P;                      // proportional yaw correction
Vector3f _omega_I;                          // Omega Integrator correction
Vector3f _omega_I_sum;
float _omega_I_sum_time;
Vector3f _omega;                            // Corrected Gyro_Vector data

void Zero_Matrix(Matrix3f *Matrix)
{
  Matrix->a.x = Matrix->a.y = Matrix->a.z = 0;
  Matrix->b.x = Matrix->b.y = Matrix->b.z = 0;
  Matrix->c.x = Matrix->c.y = Matrix->c.z = 0;
}


Vector3f Vector3f_Add_Const(Vector3f a,float constant)
{
  Vector3f Location_Delta;
  Location_Delta.x=a.x+constant;
  Location_Delta.y=a.y+constant;
  Location_Delta.z=a.z+constant;
  return Location_Delta;
}

Vector3f Vector3f_Mul_Const(Vector3f a,float constant)
{
  Vector3f Location_Delta;
  Location_Delta.x=a.x*constant;
  Location_Delta.y=a.y*constant;
  Location_Delta.z=a.z*constant;
  return Location_Delta;
}

void Vector3f_Mul_Const_Add(Vector3f *a,Vector3f b,float constant)
{
  a->x+=b.x*(constant);
  a->y+=b.y*(constant);
  a->z+=b.z*(constant);
}

Vector3f Vector3f_Point_Mul(Vector3f a,Vector3f b)
{
  Vector3f Location_Delta;
  Location_Delta.x=a.x*b.x;
  Location_Delta.y=a.y*b.y;
  Location_Delta.z=a.z*b.z;
  return Location_Delta;
}


void Matrix_Copy_B2A(Matrix3f *Matrix_B,Matrix3f *Matrix_A)
{
  Matrix_A->a.x=Matrix_B->a.x;
  Matrix_A->a.y=Matrix_B->a.y;
  Matrix_A->b.z=Matrix_B->a.z;
  Matrix_A->b.x=Matrix_B->b.x;
  Matrix_A->b.y=Matrix_B->b.y;
  Matrix_A->b.z=Matrix_B->b.z;
  Matrix_A->c.x=Matrix_B->c.x;
  Matrix_A->c.y=Matrix_B->c.y;
  Matrix_A->c.z=Matrix_B->c.z;
}

Matrix3f Rotate_Matrix_Delta(Matrix3f *_Matrix,Vector3f _Angle_Delta)
{
  Matrix3f tmp_mat={0,0,0,0,0,0,0,0,0};
  Matrix_Copy_B2A(_Matrix,&tmp_mat);
  tmp_mat.a.x += _Matrix->a.y * _Angle_Delta.z - _Matrix->a.z * _Angle_Delta.y;
  tmp_mat.a.y += _Matrix->a.z * _Angle_Delta.x - _Matrix->a.x * _Angle_Delta.z;
  tmp_mat.a.z += _Matrix->a.x * _Angle_Delta.y - _Matrix->a.y * _Angle_Delta.x;
  tmp_mat.b.x += _Matrix->b.y * _Angle_Delta.z - _Matrix->b.z * _Angle_Delta.y;
  tmp_mat.b.y += _Matrix->b.z * _Angle_Delta.x - _Matrix->b.x * _Angle_Delta.z;
  tmp_mat.b.z += _Matrix->b.x * _Angle_Delta.y - _Matrix->b.y * _Angle_Delta.x;
  tmp_mat.c.x += _Matrix->c.y * _Angle_Delta.z - _Matrix->c.z * _Angle_Delta.y;
  tmp_mat.c.y += _Matrix->c.z * _Angle_Delta.x - _Matrix->c.x * _Angle_Delta.z;
  tmp_mat.c.z += _Matrix->c.x * _Angle_Delta.y - _Matrix->c.y * _Angle_Delta.x;
  return tmp_mat;
}


float AP_AHRS_RP_P_MIN=5.0f;
float AP_AHRS_RP_I_MIN=0.05f;
float AP_AHRS_YAW_P_MIN=5.0f;
float AP_AHRS_YAW_I_MIN=0.01f;
float Test_DCM[2]={0};
float Test_DCM1[6]={0};
Matrix3f DCM_BF_To_NF={1.0f ,0    ,0,
0    ,1.0f ,0,
0    ,0    ,1.0f};//Body Frame To Earth Frame DCM
Vector3f Angle_Delta,Acc_Angle_Err;
Vector3f Vector_G_BF={0, 0, 1};
Vector3f DCM_Euler_Angle={0,0,0};
Vector3f t0, t1, t2;
Vector3f Acc_Correct_I,Acc_Correct_Output;
float Mag_Angle_Err=0;
Vector2f Vector_Mag_BF={0,1};
float error,Mag_Correct_I,Mag_Correct_Output;
Vector3f t0_err,t1_err;
Testime DCM_Delta;
void DirectionConsineMatrix(Vector3f gyro,Vector3f acc,Vector2f magn)
{
  float Acce_Length_Inv=0;
  float dcm_dt=0;
  Test_Period(&DCM_Delta);
  dcm_dt=DCM_Delta.Time_Delta/1000.0;
 
  Pitch_Gyro=gyro.x*RAD2DEG;
  Roll_Gyro=gyro.y*RAD2DEG;
  Yaw_Gyro=gyro.z*RAD2DEG;
  //{-sinθ          cosθsin Φ                          cosθcosΦ                   }
  Yaw_Gyro_Earth_Frame=-Sin_Roll*Pitch_Gyro+ Cos_Roll*Sin_Pitch *Roll_Gyro+ Cos_Pitch * Cos_Roll *Yaw_Gyro;
  //角速度模长
  Gyro_Length=sqrt(Yaw_Gyro*Yaw_Gyro
                 +Pitch_Gyro*Pitch_Gyro
                   +Roll_Gyro*Roll_Gyro);//单位deg/s
  
  //将导航系重力加速度向量（0,0,1g）^T旋转到载体系上
  Vector_G_BF.x=DCM_BF_To_NF.c.x;
  Vector_G_BF.y=DCM_BF_To_NF.c.y;
  Vector_G_BF.z=DCM_BF_To_NF.c.z;
  //将导航系旋转到载体系的重力向量叉乘，得到角度误差项，
  //两个单位化后(模长为1)的向量叉乘表示两个向量夹角的正弦值,Sin_A在小角度下约等于A
  //叉乘运算A(x1,y1,z1)叉乘B(x2,y2,z2)等于(y1z2-z1y2,z1x2-x1z2,x1y2-y1x2)
  Acce_Length_Inv=invSqrt(acc.x*acc.x+acc.y*acc.y+acc.z*acc.z);//载体系加速度模长
  acc=Vector3f_Mul_Const(acc,Acce_Length_Inv);//单位化处理
  Acc_Angle_Err.x=Vector_G_BF.y*acc.z-Vector_G_BF.z*acc.y;//向量叉乘得到角度误差
  Acc_Angle_Err.y=Vector_G_BF.z*acc.x-Vector_G_BF.x*acc.z;
  Acc_Angle_Err.z=Vector_G_BF.x*acc.y-Vector_G_BF.y*acc.x;
  
  Vector3f_Mul_Const_Add(&Acc_Correct_I,Acc_Angle_Err,AP_AHRS_RP_I_MIN*dcm_dt);
  Acc_Correct_Output.x=AP_AHRS_RP_P_MIN*Acc_Angle_Err.x+Acc_Correct_I.x;
  Acc_Correct_Output.y=AP_AHRS_RP_P_MIN*Acc_Angle_Err.y+Acc_Correct_I.y;
  Acc_Correct_Output.z=AP_AHRS_RP_P_MIN*Acc_Angle_Err.z+Acc_Correct_I.z;
  //将导航系磁力计向量（0,1）T旋转到载体系上
  Vector_Mag_BF.x=DCM_BF_To_NF.b.x;
  Vector_Mag_BF.y=DCM_BF_To_NF.b.y;
  Mag_Angle_Err=(Vector_Mag_BF.x*magn.y-Vector_Mag_BF.y*magn.x)*invSqrt(magn.x*magn.x+magn.y*magn.y);//向量叉乘得到角度误差
  Mag_Correct_I+=Mag_Angle_Err*AP_AHRS_YAW_I_MIN*dcm_dt;
  Mag_Correct_Output=AP_AHRS_YAW_P_MIN*Mag_Angle_Err+Mag_Correct_I;
  //Angle_Delta_Correct
  gyro.x-=Acc_Correct_Output.x;
  gyro.y-=Acc_Correct_Output.y;
  //gyro.z-=Acc_Correct_Output.z+Mag_Correct_Output;
  gyro.z-=Mag_Correct_Output;
  //Integrate the DCM matrix using gyro and correct inputs
  Angle_Delta =Vector3f_Mul_Const(gyro,dcm_dt);//计算角度增量
  DCM_BF_To_NF=Rotate_Matrix_Delta(&DCM_BF_To_NF,Angle_Delta);//更新方向余弦矩阵
  //方向余弦矩阵正交化、单位化处理
  //DCM.a点乘DCM.b=ax*bx+ay*by+az*bz
  error = DCM_BF_To_NF.a.x*DCM_BF_To_NF.b.x
    +DCM_BF_To_NF.a.y*DCM_BF_To_NF.b.y
      +DCM_BF_To_NF.a.z*DCM_BF_To_NF.b.z;
  t0_err=Vector3f_Mul_Const(DCM_BF_To_NF.b,(0.5f*error));
  t1_err=Vector3f_Mul_Const(DCM_BF_To_NF.a,(0.5f*error));
  t0.x=DCM_BF_To_NF.a.x-t0_err.x;//第一行修正
  t0.y=DCM_BF_To_NF.a.y-t0_err.y;
  t0.z=DCM_BF_To_NF.a.z-t0_err.z;
  t1.x=DCM_BF_To_NF.b.x-t1_err.x;//第二行修正
  t1.y=DCM_BF_To_NF.b.y-t1_err.y;
  t1.z=DCM_BF_To_NF.b.z-t1_err.z;
  t2.x=t0.y*t1.z-t0.z*t1.y;//第三行修正
  t2.y=t0.z*t1.x-t0.x*t1.z;
  t2.z=t0.x*t1.y-t0.y*t1.x;
  DCM_BF_To_NF.a=Vector3f_Mul_Const(t0,invSqrt(t0.x*t0.x+t0.y*t0.y+t0.z*t0.z));//第一行正交标准化处理
  DCM_BF_To_NF.b=Vector3f_Mul_Const(t1,invSqrt(t1.x*t1.x+t1.y*t1.y+t1.z*t1.z));//第二行正交标准化处理
  //DCM_BF_To_NF.c=Vector3f_Mul_Const(t2,invSqrt(t2.x*t2.x+t2.y*t2.y+t2.z*t2.z));//第三行正交标准化处理
  DCM_BF_To_NF.c=Vector3f_Mul_Const(DCM_BF_To_NF.c,
                                    invSqrt(DCM_BF_To_NF.c.x*DCM_BF_To_NF.c.x
                                            +DCM_BF_To_NF.c.y*DCM_BF_To_NF.c.y
                                              +DCM_BF_To_NF.c.z*DCM_BF_To_NF.c.z));//第三行单位化处理
  DCM_Euler_Angle.x=-asin(DCM_BF_To_NF.c.x)* RAD2DEG;//Roll
  DCM_Euler_Angle.y=atan2(DCM_BF_To_NF.c.y,DCM_BF_To_NF.c.z)* RAD2DEG;//Pitch
  DCM_Euler_Angle.z=atan2(DCM_BF_To_NF.b.x,DCM_BF_To_NF.a.x)* RAD2DEG;//Yaw
  
 
  Pitch=DCM_Euler_Angle.y;
  Roll=DCM_Euler_Angle.x;
  if(DCM_Euler_Angle.z<0)   Yaw=DCM_Euler_Angle.z+360;
  else Yaw=DCM_Euler_Angle.z;
  
  imuComputeRotationMatrix();
  
  Circle_Angle.Pit+=Pitch_Gyro*dcm_dt;
  Circle_Angle.Rol+=Roll_Gyro*dcm_dt;
  Circle_Angle.Yaw+=Yaw_Gyro*dcm_dt;
  if(Circle_Angle.Pit<0)   Circle_Angle.Pit+=360;
  if(Circle_Angle.Pit>360) Circle_Angle.Pit-=360;
  if(Circle_Angle.Rol<0)   Circle_Angle.Rol+=360;
  if(Circle_Angle.Rol>360) Circle_Angle.Rol-=360;
  if(Circle_Angle.Yaw<0)   Circle_Angle.Yaw+=360;
  if(Circle_Angle.Yaw>360) Circle_Angle.Yaw-=360;  
}

