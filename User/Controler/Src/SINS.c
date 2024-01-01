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
#include "SINS.h"
#include "Earth_Declination.h"
#include "math.h"
SINS NamelessQuad;
SINS Origion_NamelessQuad;
SINS FilterBefore_NamelessQuad;
SINS FilterAfter_NamelessQuad;
SINS Filter_Feedback_NamelessQuad;
float SpeedDealt[3]={0};
float Sin_Pitch=0,Sin_Roll=0,Sin_Yaw=0;
float Cos_Pitch=0,Cos_Roll=0,Cos_Yaw=0;
float Baro_Climbrate=0;
float Acceleration_Length=0;
Vector2f SINS_Accel_Body={0,0};
float Acce_History[3][100]={0};
float Declination=0;//地球磁偏角
void  SINS_Prepare(void)
{
  
  //static uint16_t Acce_Save_Cnt=0;
  //uint16_t i=0;
  Vector2f SINS_Accel_Earth={0,0};
  Vector3f Body_Frame,Earth_Frame;
  /*Z-Y-X欧拉角转方向余弦矩阵
  //Pitch Roll  Yaw 分别对应Φ θ Ψ
  
  X轴旋转矩阵
  R（Φ）
  {1      0        0    }
  {0      cosΦ    sinΦ}
  {0    -sinΦ    cosΦ }
  
  Y轴旋转矩阵
  R（θ）
  {cosθ     0        -sinθ}
  {0         1        0     }
  {sinθ     0        cosθ}
  
  Z轴旋转矩阵
  R（θ）
  {cosΨ      sinΨ       0}
  {-sinΨ     cosΨ       0}
  {0          0           1 }
  
  由Z-Y-X顺规有:
  载体坐标系到导航坐标系下旋转矩阵R(b2n)
  R(b2n) =R(Ψ)^T*R(θ)^T*R(Φ)^T
  
  R=
  {cosΨ*cosθ     -cosΦ*sinΨ+sinΦ*sinθ*cosΨ        sinΨ*sinΦ+cosΦ*sinθ*cosΨ}
  {cosθ*sinΨ     cosΦ*cosΨ +sinΦ*sinθ*sinΨ       -cosΨ*sinΦ+cosΦ*sinθ*sinΨ}
  {-sinθ          cosθsin Φ                          cosθcosΦ                   }
  */
  /*
  Origion_NamelessQuad.Acceleration[_YAW] =
  -Sin_Roll* Acce_Control[0]
  + Sin_Pitch *Cos_Roll * Acce_Control[1]
  + Cos_Pitch * Cos_Roll *Acce_Control[2];
  
  Origion_NamelessQuad.Acceleration[_PITCH]=
  Cos_Yaw* Cos_Roll * Acce_Control[0]
  +(Sin_Pitch*Sin_Roll*Cos_Yaw-Cos_Pitch * Sin_Yaw) * Acce_Control[1]
  +(Sin_Pitch * Sin_Yaw+Cos_Pitch * Sin_Roll * Cos_Yaw)*Acce_Control[2];
  
  Origion_NamelessQuad.Acceleration[_ROLL]=
  Sin_Yaw* Cos_Roll * Acce_Control[0]
  +(Sin_Pitch * Sin_Roll * Sin_Yaw +Cos_Pitch * Cos_Yaw) * Acce_Control[1]
  + (Cos_Pitch * Sin_Roll * Sin_Yaw - Sin_Pitch * Cos_Yaw)*Acce_Control[2];
  */
  Body_Frame.x=Acce_SINS[0];//X_Origion;//Acce_Control[0];
  Body_Frame.y=Acce_SINS[1];//Y_Origion;//Acce_Control[1];
  Body_Frame.z=Acce_SINS[2];//Z_Origion;//Acce_Control[2];
  Vector_From_BodyFrame2EarthFrame(&Body_Frame,&Earth_Frame);
  Origion_NamelessQuad.Acceleration[_YAW]=Earth_Frame.z;
  Origion_NamelessQuad.Acceleration[_PITCH]=Earth_Frame.x;
  Origion_NamelessQuad.Acceleration[_ROLL]=Earth_Frame.y;
  
  
  Origion_NamelessQuad.Acceleration[_YAW]*=AcceGravity/AcceMax;
  Origion_NamelessQuad.Acceleration[_YAW]-=AcceGravity;//减去重力加速度
  Origion_NamelessQuad.Acceleration[_YAW]*=100;//加速度cm/s^2
  
  Origion_NamelessQuad.Acceleration[_PITCH]*=AcceGravity/AcceMax;
  Origion_NamelessQuad.Acceleration[_PITCH]*=100;//加速度cm/s^2
  
  Origion_NamelessQuad.Acceleration[_ROLL]*=AcceGravity/AcceMax;
  Origion_NamelessQuad.Acceleration[_ROLL]*=100;//加速度cm/s^2
  
  
  Acceleration_Length=sqrt(Origion_NamelessQuad.Acceleration[_YAW]*Origion_NamelessQuad.Acceleration[_YAW]
                           +Origion_NamelessQuad.Acceleration[_PITCH]*Origion_NamelessQuad.Acceleration[_PITCH]
                             +Origion_NamelessQuad.Acceleration[_ROLL]*Origion_NamelessQuad.Acceleration[_ROLL]);
  
  /******************************************************************************/
  //将无人机在导航坐标系下的沿着正东、正北方向的运动加速度旋转到当前航向的运动加速度:机头(俯仰)+横滚
  
  SINS_Accel_Earth.x=Origion_NamelessQuad.Acceleration[_PITCH];//沿地理坐标系，正东方向运动加速度,单位为CM
  SINS_Accel_Earth.y=Origion_NamelessQuad.Acceleration[_ROLL];//沿地理坐标系，正北方向运动加速度,单位为CM
  
  
  SINS_Accel_Body.x=SINS_Accel_Earth.x*Cos_Yaw+SINS_Accel_Earth.y*Sin_Yaw;  //横滚正向运动加速度  X轴正向
  SINS_Accel_Body.y=-SINS_Accel_Earth.x*Sin_Yaw+SINS_Accel_Earth.y*Cos_Yaw; //机头正向运动加速度  Y轴正向
  
  /*
  Acce_Save_Cnt++;
  if(Acce_Save_Cnt>=2)//10ms
  {
  for(i=99;i>0;i--)
  {
  Acce_History[_PITCH][i]=Acce_History[_PITCH][i-1];
  Acce_History[_ROLL][i]=Acce_History[_ROLL][i-1];
  Acce_History[_YAW][i]=Acce_History[_YAW][i-1];
}
  Acce_History[_PITCH][0]=Origion_NamelessQuad.Acceleration[_PITCH];
  Acce_History[_ROLL][0]=Origion_NamelessQuad.Acceleration[_ROLL];
  Acce_History[_YAW][0]=Origion_NamelessQuad.Acceleration[_YAW];
  Acce_Save_Cnt=0;
}
  */
}


/******************************************
原始运动加速度方向为东北天方向
Origion_NamelessQuad.Acceleration[_ROLL]
为载体沿着正北方向的运动加速度
Origion_NamelessQuad.Acceleration[_PITCH]
为载体沿着正东方向的运动加速度
Origion_NamelessQuad.Acceleration[_YAW]
为载体沿着‘天’方向的运动加速度

载体沿着正东（E）、正北（N）、正天（U）运动时，加速度方向为正
U（正天、气压高度、_YAW）
*
*
*
*
*
*
* * * * * * * * * *N（正北、纬线方向、_ROLL）
*
*
*
*
*
*
E（正东、经线方向、_PITCH）
*/

/*****************算法技术博客讲解***************************************************
1、四旋翼定高篇之惯导加速度+速度+位置三阶互补融合方案:
http://blog.csdn.net/u011992534/article/details/61924200
2、四旋翼惯导融合之观测传感器滞后问题汇总与巴特沃斯低通滤波器设计
（气压计MS5611、GPS模块M8N、超声波、PX4FLOW等）:
http://blog.csdn.net/u011992534/article/details/73743955
3、从APM源码分析GPS、气压计惯导融合
http://blog.csdn.net/u011992534/article/details/78257684
**********************************************************************************/
float pos_correction[3]={0,0,0};
float acc_correction[3]={0,0,0};
float vel_correction[3]={0,0,0};
/****气压计三阶互补滤波方案——参考开源飞控APM****/
//#define TIME_CONTANST_ZER       1.5f
float TIME_CONTANST_ZER=3.5f;//3.0
#define K_ACC_ZER 	        (1.0f / (TIME_CONTANST_ZER * TIME_CONTANST_ZER * TIME_CONTANST_ZER))
#define K_VEL_ZER	        (3.0f / (TIME_CONTANST_ZER * TIME_CONTANST_ZER))
#define K_POS_ZER               (3.0f / TIME_CONTANST_ZER)
#define MS5611_Sync_Cnt 10
#define SPL06_Sync_Cnt 20
#define FBM320_Sync_Cnt 10
#define HCSR04_Sync_Cnt 10//20
uint16 High_Delay_Cnt=0;

float Altitude_Dealt=0;
float Altitude_Estimate=0;
Testime SINS_High_Delta;
float Delta_T;
void Strapdown_INS_High()
{
  uint16 Cnt=0;
  static uint16_t Save_Cnt=0;
  Save_Cnt++;//数据存储周期
  Test_Period(&SINS_High_Delta);
  Delta_T=SINS_High_Delta.Time_Delta/1000.0;
  
  Observation_Tradeoff(HC_SR04);  
  
  //由观测量（气压计）得到状态误差
  Altitude_Dealt=Altitude_Estimate-NamelessQuad.Pos_History[_YAW][High_Delay_Cnt];//气压计(超声波)与SINS估计量的差，单位cm
  //三路积分反馈量修正惯导
  acc_correction[_YAW] +=Altitude_Dealt* K_ACC_ZER*Delta_T ;//加速度矫正量
  vel_correction[_YAW] +=Altitude_Dealt* K_VEL_ZER*Delta_T ;//速度矫正量
  pos_correction[_YAW] +=Altitude_Dealt* K_POS_ZER*Delta_T ;//位置矫正量
  //加速度计矫正后更新
  NamelessQuad.Last_Acceleration[_YAW]=NamelessQuad.Acceleration[_YAW];//上一次加速度量
  NamelessQuad.Acceleration[_YAW]=Origion_NamelessQuad.Acceleration[_YAW]+acc_correction[_YAW];
  //速度增量矫正后更新，用于更新位置,由于步长h=0.005,相对较长，
  //这里采用二阶龙格库塔法更新微分方程，不建议用更高阶段，因为加速度信号非平滑
  SpeedDealt[_YAW]=(NamelessQuad.Last_Acceleration[_YAW]
                    +NamelessQuad.Acceleration[_YAW])*Delta_T/2.0;
  //原始位置更新
  Origion_NamelessQuad.Position[_YAW]+=(NamelessQuad.Speed[_YAW]+0.5*SpeedDealt[_YAW])*Delta_T;
  //位置矫正后更新
  NamelessQuad.Position[_YAW]=Origion_NamelessQuad.Position[_YAW]+pos_correction[_YAW];
  //原始速度更新
  Origion_NamelessQuad.Speed[_YAW]+=SpeedDealt[_YAW];
  //速度矫正后更新
  NamelessQuad.Speed[_YAW]=Origion_NamelessQuad.Speed[_YAW]+vel_correction[_YAW];
  
  if(Save_Cnt>=1)//20ms
  {
    for(Cnt=Num-1;Cnt>0;Cnt--)//20ms滑动一次
    {
      NamelessQuad.Pos_History[_YAW][Cnt]=NamelessQuad.Pos_History[_YAW][Cnt-1];
    }
    NamelessQuad.Pos_History[_YAW][0]=NamelessQuad.Position[_YAW];
    Save_Cnt=0;
  }
}




#define KALMAN_DT 0.005f
float R[2]={5.0e-4f,6.0e-4f};//float R[2]={5.0e-4f,3.0e-4f};//{5.0e-4f,3.0e-4f}
float Q=30;//100  150  30
float Q_Baro=150;
float Q_Tofsense=30;
float Acce_Bias_Gain[3]={
  0.0005,//0.001
  0.0005,//0.001
  0.0005,//0.001
};
float Pre_conv[4]=
{
  0.18,0.1,//0.001,0,
  0.1,0.18//0,0.001
};//上一次协方差
void  KalmanFilter(float Observation,//位置观测量
                   uint16 Pos_Delay_Cnt,//观测传感器延时量
                   SINS *Ins_Kf,//惯导结构体
                   float System_drive,//系统原始驱动量，惯导加速度
                   float *R,
                   float Q,
                   float dt,
                   uint16 N,
                   uint8_t update_flag)
{
  uint16 Cnt=0;
  static uint16 Speed_Sync_Cnt=0;
  float Temp_conv[4]={0};//先验协方差
  float Conv_Z=0,Z_Cor=0;
  float k[2]={0};//增益矩阵
  float Ctemp=0;
	//先验状态
	Ins_Kf->Acceleration[N]=System_drive;
	Ins_Kf->Acceleration[N]=Ins_Kf->Acce_Bias[N]+Ins_Kf->Acceleration[N];
	Ins_Kf->Position[N] +=Ins_Kf->Speed[N]*dt+(Ins_Kf->Acceleration[N]*dt*dt)/2.0;
	Ins_Kf->Speed[N]+=Ins_Kf->Acceleration[N]*dt;
	if(update_flag==1)
	{
		//先验协方差
		Ctemp=Pre_conv[1]+Pre_conv[3]*dt;
		Temp_conv[0]=Pre_conv[0]+Pre_conv[2]*dt+Ctemp*dt+R[0];
		Temp_conv[1]=Ctemp;
		Temp_conv[2]=Pre_conv[2]+Pre_conv[3]*dt;;
		Temp_conv[3]=Pre_conv[3]+R[1];
		//计算卡尔曼增益
		Conv_Z=Temp_conv[0]+Q;
		k[0]=Temp_conv[0]/Conv_Z;
		k[1]=Temp_conv[2]/Conv_Z;
		//融合数据输出
		Z_Cor=Observation-Ins_Kf->Pos_History[N][Pos_Delay_Cnt];
		//Z_Cor=Positional-*Position;
		Ins_Kf->Position[N] +=k[0]*Z_Cor;
		Ins_Kf->Speed[N] +=k[1]*Z_Cor;
		Ins_Kf->Acce_Bias[N]+=Acce_Bias_Gain[_YAW]*Z_Cor;
		Ins_Kf->Acce_Bias[N]=constrain_float(Ins_Kf->Acce_Bias[N],-200,200);
		//更新状态协方差矩阵
		Pre_conv[0]=(1-k[0])*Temp_conv[0];
		Pre_conv[1]=(1-k[0])*Temp_conv[1];
		Pre_conv[2]=Temp_conv[2]-k[1]*Temp_conv[0];
		Pre_conv[3]=Temp_conv[3]-k[1]*Temp_conv[1]; 
	}
  
  for(Cnt=Num-1;Cnt>0;Cnt--)//5ms滑动一次
  {
    Ins_Kf->Pos_History[N][Cnt]=Ins_Kf->Pos_History[N][Cnt-1];
  }
  Ins_Kf->Pos_History[N][0]=Ins_Kf->Position[N];
  
  Speed_Sync_Cnt++;
  if(Speed_Sync_Cnt>=20)//100ms滑动一次
  {
  for(Cnt=Num-1;Cnt>0;Cnt--)
  {
    Ins_Kf->Vel_History[N][Cnt]=Ins_Kf->Vel_History[N][Cnt-1];
  }
  Speed_Sync_Cnt=0;
  }
  Ins_Kf->Vel_History[N][0]=Ins_Kf->Speed[N];
}

void Alt_SINS_Init(void)
{
	uint16_t _cnt=0;
	if(Sensor_Flag.Hcsr04_Health==1)
	{
		NamelessQuad.Position[_YAW]=HC_SR04_Distance;
		for(_cnt=Num-1;_cnt>0;_cnt--){NamelessQuad.Pos_History[_YAW][_cnt]=HC_SR04_Distance;}
		NamelessQuad.Pos_History[_YAW][0]=HC_SR04_Distance;
		Total_Controller.High_Position_Control.Expect=HC_SR04_Distance;//将惯导高度设置为期望高度，有且仅设置一次
		Origion_NamelessQuad.Position[_YAW]=HC_SR04_Distance;
		Origion_NamelessQuad.Speed[_YAW]=0;
		Q=Q_Tofsense;	
	}
	else
	{
		NamelessQuad.Position[_YAW]=WP_Sensor.baro_altitude;
		for(_cnt=Num-1;_cnt>0;_cnt--){NamelessQuad.Pos_History[_YAW][_cnt]=WP_Sensor.baro_altitude;}
		NamelessQuad.Pos_History[_YAW][0]=WP_Sensor.baro_altitude;
		Total_Controller.High_Position_Control.Expect=WP_Sensor.baro_altitude;//将惯导高度设置为期望高度，有且仅设置一次
		Origion_NamelessQuad.Position[_YAW]=WP_Sensor.baro_altitude;
		Origion_NamelessQuad.Speed[_YAW]=0;
		Q=Q_Baro;
	}
}

uint8_t Observation_Update_Flag=0;
void Observation_Tradeoff(uint8_t HC_SR04_Enable)
{
  static uint8_t observation_flag=1,last_observation_flag=1;
  uint16 Cnt=0;
  last_observation_flag=observation_flag;
	
	if(Sensor_Flag.Hcsr04_Health==1)
	{
		Altitude_Estimate=HC_SR04_Distance*Cos_Roll*Cos_Pitch;
		High_Delay_Cnt=HCSR04_Sync_Cnt;
		observation_flag=2;
		//if(HCSR_04_Update_Flag==1)
		//{
		//	Observation_Update_Flag=HCSR_04_Update_Flag;
		//	HCSR_04_Update_Flag=0;
		//}
		Observation_Update_Flag=1;
		Q=Q_Tofsense;	
	}
	else
	{
		Altitude_Estimate=SPL06_001_Filter_high;//高度观测量
		High_Delay_Cnt=SPL06_Sync_Cnt;
		Observation_Update_Flag=1;
		observation_flag=1;
		Q=Q_Baro;	
	} 
	
	if(observation_flag==2&&last_observation_flag==1)//气压计切超声波
	{
		NamelessQuad.Position[_YAW]=HC_SR04_Distance*Cos_Roll*Cos_Pitch;
		for(Cnt=Num-1;Cnt>0;Cnt--){NamelessQuad.Pos_History[_YAW][Cnt]=HC_SR04_Distance*Cos_Roll*Cos_Pitch;}
		NamelessQuad.Pos_History[_YAW][0]=HC_SR04_Distance*Cos_Roll*Cos_Pitch;
		Total_Controller.High_Position_Control.Expect=HC_SR04_Distance*Cos_Roll*Cos_Pitch;//将惯导高度设置为期望高度，有且仅设置一次
		
		Origion_NamelessQuad.Position[_YAW]=HC_SR04_Distance*Cos_Roll*Cos_Pitch;
		Origion_NamelessQuad.Speed[_YAW]=0;
		acc_correction[_YAW]=0 ;//加速度矫正量
		vel_correction[_YAW]=0;//速度矫正量
		pos_correction[_YAW]=0;
	}
	else if(observation_flag==1&&last_observation_flag==2)//超声波切气压计
	{
		NamelessQuad.Position[_YAW]=Altitude_Estimate;
		for(Cnt=Num-1;Cnt>0;Cnt--){NamelessQuad.Pos_History[_YAW][Cnt]=Altitude_Estimate;}
		NamelessQuad.Pos_History[_YAW][0]=Altitude_Estimate;
		Total_Controller.High_Position_Control.Expect=Altitude_Estimate;//将惯导高度设置为期望高度，有且仅设置一次
		
		Origion_NamelessQuad.Position[_YAW]=Altitude_Estimate;
		Origion_NamelessQuad.Speed[_YAW]=0;
		acc_correction[_YAW]=0 ;//加速度矫正量
		vel_correction[_YAW]=0;//速度矫正量
		pos_correction[_YAW]=0;
	}
}

void Strapdown_INS_High_Kalman(void)
{
  Test_Period(&SINS_High_Delta);
  Delta_T=SINS_High_Delta.Time_Delta/1000.0;
  Observation_Tradeoff(HC_SR04);
  if(Gyro_Safety_Calibration_Flag==1)
	{
		KalmanFilter(Altitude_Estimate,//位置观测量
								 High_Delay_Cnt,//观测传感器延时量
								 &NamelessQuad,//惯导结构体
								 Origion_NamelessQuad.Acceleration[_YAW],//系统原始驱动量，惯导加速度
								 R,
								 Q,
								 Delta_T,//0.005f,
								 _YAW,
								 1);
	}
	else
	{
		Alt_SINS_Init();
		NamelessQuad.Acce_Bias[_YAW]=-Origion_NamelessQuad.Acceleration[_YAW];
	}
}


/*************************以下计算球面投影距离内容源于APM3.2 AP.Math.c文件******************************/
// constrain a value
float constrain_float(float amt, float low, float high){
  return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}

int16_t constrain_int16_t(int16_t amt, int16_t low, int16_t high){
  return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}

float longitude_scale(Location loc)
{
  static int32_t last_lat;
  static float scale = 1.0;
  //比较两次纬度相差值，避免重复运算余弦函数
  if (ABS(last_lat - loc.lat) < 100000) {
    // we are within 0.01 degrees (about 1km) of the
    // same latitude. We can avoid the cos() and return
    // the same scale factor.
    return scale;
  }
  scale = cosf(loc.lat * 1.0e-7f * DEG_TO_RAD);
  scale = constrain_float(scale, 0.01f, 1.0f);
  last_lat = loc.lat;
  return scale;
}
/*
return the distance in meters in North/East plane as a N/E vector
from loc1 to loc2
*/
Vector2f location_diff(Location loc1,Location loc2)
{
  Vector2f Location_Delta;
  Location_Delta.x=(loc2.lat - loc1.lat) * LOCATION_SCALING_FACTOR;//距离单位为m
  Location_Delta.y=(loc2.lng - loc1.lng) * LOCATION_SCALING_FACTOR * longitude_scale(loc2);//距离单位为m
  return Location_Delta;
}
// square
float sq(float v) {return v*v;}
// 2D vector length
float pythagorous2(float a, float b) {	return sqrtf(sq(a)+sq(b));}
// 3D vector length
float pythagorous3(float a, float b, float c) {return sqrtf(sq(a)+sq(b)+sq(c));}
// return distance in meters between two locations
float get_distance(Location loc1,Location loc2){
  float dlat              = (float)(loc2.lat - loc1.lat);
  float dlong             = ((float)(loc2.lng - loc1.lng)) * longitude_scale(loc2);
  return pythagorous2(dlat, dlong) * LOCATION_SCALING_FACTOR;
}
/*************************以上计算球面投影距离内容源于APM3.2 AP.Math.c文件******************************/

Vector2i GPSData_To_XY_Home={1143637460,306276000};//经、纬度
Location GPS_Home;//初始定位成功点信息
Location GPS_Present;//当前位置点信息
uint8 GPS_Home_Set=0;
void Set_GPS_Home(void)//设置Home点
{	
	static uint16_t gps_home_cnt=0;
  if(GPS_Home_Set==0
			&&GPS_Sate_Num>=9//星数大于等于9
				&&Horizontal_Acc_Est<=1.5f)//水平位置估计精度小于1.5m
	 {
		 if(gps_home_cnt<=100) gps_home_cnt++;//刷新10hz，连续10S满足
	 }

   if(GPS_Home_Set==0&&gps_home_cnt==100)//全程只设置一次
  {
    GPSData_To_XY_Home.x=Longitude_Origion;//Longitude;
    GPSData_To_XY_Home.y=Latitude_Origion;//Latitude;
    GPS_Home_Set=1;//设定返航点
    GPS_Home.lng=GPSData_To_XY_Home.x;
    GPS_Home.lat=GPSData_To_XY_Home.y; 
    Strapdown_INS_Reset(&NamelessQuad,_PITCH,Earth_Frame_To_XYZ.E,0);//复位惯导融合
    Strapdown_INS_Reset(&NamelessQuad,_ROLL,Earth_Frame_To_XYZ.N,0);//复位惯导融合
    Declination=get_declination(0.0000001f*GPS_Home.lat,0.0000001f*GPS_Home.lng);//获取当地磁偏角
  }
}

float Body_Frame_To_XYZ[3]={0,0,0};//导航（地理）坐标系，机体横滚(Y正)、俯仰(X正)方向位置偏移
Vector3_Nav Earth_Frame_To_XYZ={0,0,0};//导航（地理）坐标系，天 、正北、正东方向上位置偏移
void GPSData_Sort()
{
  Vector2f location_delta={0,0};
  GPS_Present.lng=Longitude_Origion;//更新当前经纬度
  GPS_Present.lat=Latitude_Origion;
  location_delta=location_diff(GPS_Home,GPS_Present);//根据当前GPS定位信息与Home点位置信息计算正北、正东方向位置偏移
  /***********************************************************************************
  明确下导航系方向，这里正北、正东为正方向:
  沿着正东，经度增加,当无人机相对home点，往正东向移动时，此时GPS_Present.lng>GPS_Home.lng，得到的location_delta.x大于0;
  沿着正北，纬度增加,当无人机相对home点，往正北向移动时，此时GPS_Present.lat>GPS_Home.lat，得到的location_delta.y大于0;
  ******************************************************************************/
  location_delta.x*=100;//沿地理坐标系，正北方向位置偏移,单位为CM
  location_delta.y*=100;//沿地理坐标系，正东方向位置偏移,单位为CM
  Earth_Frame_To_XYZ.E=location_delta.y;//地理系下相对Home点正东位置偏移，单位为CM
  Earth_Frame_To_XYZ.N=location_delta.x;//地理系下相对Home点正北位置偏移，单位为CM
  //将无人机在导航坐标系下的沿着正东、正北方向的位置偏移旋转到当前航向的位置偏移:机头(俯仰)+横滚
  Body_Frame_To_XYZ[_PITCH]=location_delta.x*Cos_Yaw+location_delta.y*Sin_Yaw;//机头正向位置偏移  Y轴正向
  Body_Frame_To_XYZ[_ROLL]=-location_delta.x*Sin_Yaw+location_delta.y*Cos_Yaw;  //横滚正向位置偏移  X轴正向
}

#define TIME_CONTANST_XY      2.5f
#define K_ACC_XY	           (1.0f / (TIME_CONTANST_XY * TIME_CONTANST_XY * TIME_CONTANST_XY))
#define K_VEL_XY             (3.0f / (TIME_CONTANST_XY * TIME_CONTANST_XY))
#define K_POS_XY             (3.0f / TIME_CONTANST_XY)
float X_Delta=0,Y_Delta=0;
uint16_t GPS_Save_Period_Cnt=0;
uint16_t GPS_SINS_Delay_Cnt=40;//100ms
Testime SINS_Horizontal_Delta;
Vector2_Body Pos_Err_On_Accel={0};
Vector2_Body  Accel_Correction_BF={0};
Vector2_Earth Accel_Correction_EF={0};
void Strapdown_INS_Horizontal()
{
  uint16 Cnt=0;
  GPSData_Sort();//获取相对home的水平偏移
  GPS_Save_Period_Cnt++;
  if(GPS_Save_Period_Cnt>=2)//10ms
  {
    for(Cnt=Num-1;Cnt>0;Cnt--)//10ms滑动一次
    {
      NamelessQuad.Pos_History[_PITCH][Cnt]=NamelessQuad.Pos_History[_PITCH][Cnt-1];
      NamelessQuad.Pos_History[_ROLL][Cnt]=NamelessQuad.Pos_History[_ROLL][Cnt-1];
    }
    NamelessQuad.Pos_History[_PITCH][0]=NamelessQuad.Position[_PITCH];
    NamelessQuad.Pos_History[_ROLL][0]=NamelessQuad.Position[_ROLL];
    GPS_Save_Period_Cnt=0;
  }
  //GPS导航坐标系下，正北、正东方向位置偏移与SINS估计量的差，单位cm
  X_Delta=Earth_Frame_To_XYZ.E-NamelessQuad.Pos_History[_PITCH][GPS_SINS_Delay_Cnt];
  Y_Delta=Earth_Frame_To_XYZ.N-NamelessQuad.Pos_History[_ROLL][GPS_SINS_Delay_Cnt];
  
  
  Pos_Err_On_Accel.Rol=X_Delta*Cos_Yaw+Y_Delta*Sin_Yaw;//载体系Roll方向    X轴
  Pos_Err_On_Accel.Pit=-X_Delta*Sin_Yaw+Y_Delta*Cos_Yaw;//载体系Pitch方向  Y轴
  
  Accel_Correction_BF.Pit+=Pos_Err_On_Accel.Pit* K_ACC_XY*CNTLCYCLE;//在载体机头方向，加速度矫正量
  Accel_Correction_BF.Rol+=Pos_Err_On_Accel.Rol* K_ACC_XY*CNTLCYCLE;//在载体横滚方向，加速度矫正量
  
  Accel_Correction_EF.North=Accel_Correction_BF.Rol*Cos_Yaw+Accel_Correction_BF.Pit*Sin_Yaw;//将载体方向上加速度修正量，旋转至导航系北向  Y Axis
  Accel_Correction_EF.East=Accel_Correction_BF.Rol*Sin_Yaw-Accel_Correction_BF.Pit*Cos_Yaw;//将载体方向上加速度修正量，旋转至导航系动向   X axis
  
  acc_correction[_PITCH] += X_Delta*K_ACC_XY*CNTLCYCLE;//加速度矫正量
  //acc_correction[_PITCH]  = Accel_Correction_EF.East;//加速度矫正量
  vel_correction[_PITCH] += X_Delta* K_VEL_XY*CNTLCYCLE;//速度矫正量
  pos_correction[_PITCH] += X_Delta* K_POS_XY*CNTLCYCLE;//位置矫正量
  
  //acc_correction[_ROLL]  = Accel_Correction_EF.North;//加速度矫正量
  acc_correction[_ROLL] += Y_Delta* K_ACC_XY*CNTLCYCLE;//加速度矫正量
  vel_correction[_ROLL] += Y_Delta* K_VEL_XY*CNTLCYCLE;//速度矫正量
  pos_correction[_ROLL] += Y_Delta* K_POS_XY*CNTLCYCLE;//位置矫正量
  
  /*************************************************************/
  //水平运动加速度计校正
  NamelessQuad.Acceleration[_PITCH]=Origion_NamelessQuad.Acceleration[_PITCH]+acc_correction[_PITCH];
  //速度增量矫正后更新，用于更新位置
  SpeedDealt[_PITCH]=NamelessQuad.Acceleration[_PITCH]*CNTLCYCLE;
  //原始位置更新
  Origion_NamelessQuad.Position[_PITCH]+=(NamelessQuad.Speed[_PITCH]+0.5*SpeedDealt[_PITCH])*CNTLCYCLE;
  //位置矫正后更新
  NamelessQuad.Position[_PITCH]=Origion_NamelessQuad.Position[_PITCH]+pos_correction[_PITCH];
  //原始速度更新
  Origion_NamelessQuad.Speed[_PITCH]+=SpeedDealt[_PITCH];
  //速度矫正后更新
  NamelessQuad.Speed[_PITCH]=Origion_NamelessQuad.Speed[_PITCH]+vel_correction[_PITCH];
  
  /*************************************************************/
  //水平运动加速度计校正
  NamelessQuad.Acceleration[_ROLL]=Origion_NamelessQuad.Acceleration[_ROLL]+acc_correction[_ROLL];
  //速度增量矫正后更新，用于更新位置
  SpeedDealt[_ROLL]=NamelessQuad.Acceleration[_ROLL]*CNTLCYCLE;
  //原始位置更新
  Origion_NamelessQuad.Position[_ROLL]+=(NamelessQuad.Speed[_ROLL]+0.5*SpeedDealt[_ROLL])*CNTLCYCLE;
  //位置矫正后更新
  NamelessQuad.Position[_ROLL]=Origion_NamelessQuad.Position[_ROLL]+pos_correction[_ROLL];
  //原始速度更新
  Origion_NamelessQuad.Speed[_ROLL]+=SpeedDealt[_ROLL];
  //速度矫正后更新
  NamelessQuad.Speed[_ROLL]=Origion_NamelessQuad.Speed[_ROLL]+vel_correction[_ROLL];
}



void Strapdown_INS_Reset(SINS *Ins,uint8_t Axis,float Pos_Target,float Vel_Target)
{
  uint16_t Cnt=0;
  Ins->Position[Axis]=Pos_Target;//位置重置
  Ins->Speed[Axis]=Vel_Target;//速度重置
  Ins->Acceleration[Axis]=0.0f;//加速度清零
  Ins->Acce_Bias[Axis]=0.0f;
  for(Cnt=Num-1;Cnt>0;Cnt--)//历史位置值，全部装载为当前观测值
  {
    Ins->Pos_History[Axis][Cnt]=Pos_Target;
  }
  Ins->Pos_History[Axis][0]=Pos_Target;
  for(Cnt=Num-1;Cnt>0;Cnt--)//历史速度值，全部装载为当前观测值
  {
    Ins->Vel_History[Axis][Cnt]=Vel_Target;
  }
  Ins->Vel_History[Axis][0]=Vel_Target;
  pos_correction[Axis]=0;//清空惯导融合量
  acc_correction[Axis]=0;
  vel_correction[Axis]=0;
}



#define Dealt_Update 0.1 //100ms更新一次
#define Process_Noise_Constant 1
#define Pos_Process_Noise  0.5*Process_Noise_Constant*Dealt_Update*Dealt_Update//0.005
#define Vel_Process_Noise  Process_Noise_Constant*Dealt_Update  //0.1
float R_GPS[2]={Pos_Process_Noise,Vel_Process_Noise};
//float Q_GPS[2]={0.075,3};//{0.075,5}  {0.03，3}
//float R_Acce_bias[2]={0.0001,0.000005};
//float Q_GPS[2]={0.075,1.2};//{0.075,5}  {0.03，3}
//float R_Acce_bias[2]={0.0001,0};
float   Q_GPS[2]={0.02,0.45};//{0.015,3.0}{0.075,3.0};
float   R_Acce_bias[2]={0.00025,0};//0.0001  0.001初始易发散
double Pre_conv_GPS[2][4]=
{
  0.018 ,    0.005,  0.005    , 0.5,//0.0001 ,    0.00001,  0.00001    , 0.003,
  0.018 ,    0.005,  0.005    , 0.5,
};//上一次协方差
double K_GPS[2][2]={0};//增益矩阵
float Acce_Bias[2]={0,0.001};
void   KalmanFilter_Horizontal_GPS(float Position_GPS,float Vel_GPS,float Position_Last,float Vel_Last,
                                   float *Position,float *Vel,
                                   float *Acce,float *R,
                                   float *Q,float dt,uint8_t Axis)
{
  float Conv_Z=0;
  float Z_Delta[2]={0};
  float Conv_Temp=0;
  double Temp_conv[4]={0};//先验协方差
  uint8 Label=0;
  if(Axis=='X') Label=0;
  else Label=1;
  //先验状态
  *Position +=*Vel*dt+((*Acce+Acce_Bias[Label])*dt*dt)/2.0;
  *Vel+=(*Acce+Acce_Bias[Label])*dt;
  //*Vel+=(*Acce)*dt;
  //先验协方差
  Conv_Temp=Pre_conv_GPS[Label][1]+Pre_conv_GPS[Label][3]*dt;
  Temp_conv[0]=Pre_conv_GPS[Label][0]+Pre_conv_GPS[Label][2]*dt+Conv_Temp*dt+R_GPS[0];
  Temp_conv[1]=Conv_Temp;
  Temp_conv[2]=Pre_conv_GPS[Label][2]+Pre_conv_GPS[Label][3]*dt;
  //Temp_conv[1]=Conv_Temp+R_GPS[0]*0.5*0.00001;
  //Temp_conv[2]=Temp_conv[1];
  Temp_conv[3]=Pre_conv_GPS[Label][3]+R_GPS[1];
  //计算卡尔曼增益
  Conv_Z=1.0/((Temp_conv[0]+Q_GPS[0]*GPS_Quality)*(Temp_conv[3]+Q_GPS[1]*GPS_Quality)-Temp_conv[1]*Temp_conv[2]);
  //K_GPS[0][0]=( Temp_conv[0]*(Temp_conv[3]+Q_GPS[1])-Temp_conv[1]*Temp_conv[2])*Conv_Z;
  //K_GPS[0][1]=(-Temp_conv[0]*Temp_conv[1]+Temp_conv[1]*(Temp_conv[0]+Q_GPS[0]))*Conv_Z;
  //K_GPS[1][0]=( Temp_conv[2]*(Temp_conv[3]+Q_GPS[1])-Temp_conv[2]*Temp_conv[3])*Conv_Z;
  //K_GPS[1][1]=(-Temp_conv[1]*Temp_conv[2]+Temp_conv[3]*(Temp_conv[0]+Q_GPS[0]))*Conv_Z;
  //化简如下
  K_GPS[0][0]=( Temp_conv[0]*(Temp_conv[3]+Q_GPS[1]*GPS_Quality)-Temp_conv[1]*Temp_conv[2])*Conv_Z;
  K_GPS[0][1]=(Temp_conv[1]*Q_GPS[0]*GPS_Quality)*Conv_Z;
  K_GPS[1][0]=(Temp_conv[2]*Q_GPS[1]*GPS_Quality)*Conv_Z;
  K_GPS[1][1]=(-Temp_conv[1]*Temp_conv[2]+Temp_conv[3]*(Temp_conv[0]+Q_GPS[0]*GPS_Quality))*Conv_Z;
  //融合数据输出
  Z_Delta[0]=Position_GPS-Position_Last;
  Z_Delta[1]=Vel_GPS-Vel_Last;
	
	Z_Delta[0]=constrain_float(Z_Delta[0],-10000,10000);//100m
	Z_Delta[1]=constrain_float(Z_Delta[1],-2000,2000);//20m/s
	
  *Position +=K_GPS[0][0]*Z_Delta[0]+K_GPS[0][1]*Z_Delta[1];
  *Vel +=K_GPS[1][0]*Z_Delta[0]+K_GPS[1][1]*Z_Delta[1];
  Acce_Bias[Label]+=R_Acce_bias[0]*Z_Delta[0]+R_Acce_bias[1]*Z_Delta[1];
	
	
	Acce_Bias[Label]=constrain_float(Acce_Bias[Label],-100,100);//100
	
	
  //更新状态协方差矩阵
  Pre_conv_GPS[Label][0]=(1-K_GPS[0][0])*Temp_conv[0]-K_GPS[0][1]*Temp_conv[2];
  Pre_conv_GPS[Label][1]=(1-K_GPS[0][0])*Temp_conv[1]-K_GPS[0][1]*Temp_conv[3];
  Pre_conv_GPS[Label][2]=(1-K_GPS[1][1])*Temp_conv[2]-K_GPS[1][0]*Temp_conv[0];
  Pre_conv_GPS[Label][3]=(1-K_GPS[1][1])*Temp_conv[3]-K_GPS[1][0]*Temp_conv[1];
}


#define X_Axis  0
#define Y_Axis  1
#define NUM_BUF 50
float Position_History[2][NUM_BUF]={0};
float Vel_History[2][NUM_BUF]={0};
uint16 GPS_Vel_Delay_Cnt=20;// 200ms 20-200ms
uint16 GPS_Pos_Delay_Cnt=10;// 100ms 10-100ms
int16 GPS_Position_Cnt=0;
float Acce_bias[2]={0};
Testime SINS_Horizontal_Delta;
float Horizontal_Delta_T=0;
uint8_t Filter_Defeated_Flag=0;
void Filter_Horizontal(void)
{
  int16 i=0;
  GPSData_Sort();
  Test_Period(&SINS_Horizontal_Delta);
  Horizontal_Delta_T=SINS_Horizontal_Delta.Time_Delta/1000.0;
  
  GPS_Position_Cnt++;
  if(GPS_Position_Cnt>=2)//每10ms保存一次
  {
    for(i=NUM_BUF-1;i>0;i--)
    {
      Position_History[X_Axis][i]=Position_History[X_Axis][i-1];
      Position_History[Y_Axis][i]=Position_History[Y_Axis][i-1];
      
      Vel_History[X_Axis][i]=Vel_History[X_Axis][i-1];
      Vel_History[Y_Axis][i]=Vel_History[Y_Axis][i-1];
    }
    Position_History[X_Axis][0]=NamelessQuad.Position[_PITCH];
    Position_History[Y_Axis][0]=NamelessQuad.Position[_ROLL];
    
    Vel_History[X_Axis][0]=NamelessQuad.Speed[_PITCH];
    Vel_History[Y_Axis][0]=NamelessQuad.Speed[_ROLL];
    
    GPS_Position_Cnt=0;
  }
  NamelessQuad.Acceleration[_PITCH]=Origion_NamelessQuad.Acceleration[_PITCH];
  NamelessQuad.Acceleration[_ROLL]=Origion_NamelessQuad.Acceleration[_ROLL];
  
  
  
  if(GPS_Update_finished_Correct_Flag==1)
  {
    KalmanFilter_Horizontal_GPS(Earth_Frame_To_XYZ.E,
                                GPS_Speed_Resolve[1],
                                Position_History[X_Axis][GPS_Pos_Delay_Cnt],
                                Vel_History[X_Axis][GPS_Vel_Delay_Cnt],
                                &NamelessQuad.Position[_PITCH],
                                &NamelessQuad.Speed[_PITCH],
                                &Origion_NamelessQuad.Acceleration[_PITCH],
                                R_GPS,Q_GPS,Horizontal_Delta_T,'X');
    
    
    KalmanFilter_Horizontal_GPS(Earth_Frame_To_XYZ.N,
                                GPS_Speed_Resolve[0],
                                Position_History[Y_Axis][GPS_Pos_Delay_Cnt],
                                Vel_History[Y_Axis][GPS_Vel_Delay_Cnt],
                                &NamelessQuad.Position[_ROLL],
                                &NamelessQuad.Speed[_ROLL],
                                &Origion_NamelessQuad.Acceleration[_ROLL],
                                R_GPS,Q_GPS,Horizontal_Delta_T,'Y');
    GPS_Update_finished_Correct_Flag=0;
  }
  else
  {
      NamelessQuad.Position[_PITCH] +=NamelessQuad.Speed[_PITCH]*Horizontal_Delta_T
        +((NamelessQuad.Acceleration[_PITCH]+Acce_Bias[0])*Horizontal_Delta_T*Horizontal_Delta_T)/2.0f;
      NamelessQuad.Speed[_PITCH]+=(NamelessQuad.Acceleration[_PITCH]+Acce_Bias[0])*Horizontal_Delta_T;
      
      NamelessQuad.Position[_ROLL] +=NamelessQuad.Speed[_ROLL]*Horizontal_Delta_T
        +((NamelessQuad.Acceleration[_ROLL]+Acce_Bias[1])*Horizontal_Delta_T*Horizontal_Delta_T)/2.0f;
      NamelessQuad.Speed[_ROLL]+=(NamelessQuad.Acceleration[_ROLL]+Acce_Bias[1])*Horizontal_Delta_T;
  }
  
  if(ABS(NamelessQuad.Position[_PITCH]-Earth_Frame_To_XYZ.E)>1000000
     ||ABS(NamelessQuad.Position[_ROLL]-Earth_Frame_To_XYZ.N)>1000000
       ||ABS(NamelessQuad.Speed[_PITCH]-GPS_Speed_Resolve[1])>1000000
         ||ABS(NamelessQuad.Speed[_ROLL]-GPS_Speed_Resolve[0])>1000000
           )
  {
    Filter_Defeated_Flag=1;//开始时，融合失败标志
  }
  
  
}


