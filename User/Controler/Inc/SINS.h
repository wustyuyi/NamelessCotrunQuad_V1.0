#ifndef __SINS_H
#define __SINS_H
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
#define Axis_Num  3
#define Num  50
typedef struct
{
 float Position[Axis_Num];//位置估计量
 float Speed[Axis_Num];//速度估计量
 float Acceleration[Axis_Num];//加速度估计量
 float Pos_History[Axis_Num][Num];//历史惯导位置
 float Vel_History[Axis_Num][Num];//历史惯导速度
 float Acce_Bias[Axis_Num];//惯导加速度漂移量估计量
 float Last_Acceleration[Axis_Num];
 float Last_Speed[Axis_Num];
}SINS;


#define AcceMax     4096  //   4096
#define AcceGravity 9.80f
/*************WGS84地心坐标参考系数**************/
#define WGS84_RADIUS_EQUATOR        6378137.0f//半长轴，单位m
#define WGS84_INVERSE_FLATTENING    298.257223563f//扁率
#define WGS84_FLATTENING            (1/WGS84_INVERSE_FLATTENING)//扁率导数
#define WGS84_RADIUS_POLAR          (WGS84_RADIUS_EQUATOR*(1-WGS84_FLATTENING))//短轴
#define WGS84_ECCENTRICITY_SQUARED  (2*WGS84_FLATTENING-WGS84_FLATTENING*WGS84_FLATTENING)
/*********************************************
经度方向距离：LON_TO_CM*经度差，LON_TO_CM对应武汉地区所在纬度平面圆周长
纬度方向距离：LAT_TO_CM*纬度差，
*********************************************/

#define LON_COSINE_LOCAL 0.860460f//约等于当地纬度的余弦值，cos(Lat*DEG_TO_RAD)
//#define LAT_TO_CM  (2.0f * WGS84_RADIUS_EQUATOR * PI / (360.0f * 100000.0f))
//#define LON_TO_CM  (2.0f * WGS84_RADIUS_EQUATOR * PI / (360.0f * 100000.0f))*LON_COSINE_LOCAL
#define LAT_TO_CM  (2.0f * WGS84_RADIUS_EQUATOR * PI/360.0f)*100.0f
#define LON_TO_CM  (2.0f * WGS84_RADIUS_EQUATOR * PI*LON_COSINE_LOCAL/360.0f)*100.0f

#define LAT_TO_M  (2.0f * WGS84_RADIUS_EQUATOR * PI/360.0f)
#define LON_TO_M  (2.0f * WGS84_RADIUS_EQUATOR * PI*LON_COSINE_LOCAL/360.0f)

#ifndef M_PI_F
 #define M_PI_F 3.141592653589793f
#endif
#ifndef PI
 # define PI M_PI_F
#endif
#ifndef M_PI_2
 # define M_PI_2 1.570796326794897f
#endif
//Single precision conversions
#define DEG_TO_RAD 0.017453292519943295769236907684886f
#define RAD_TO_DEG 57.295779513082320876798154814105f



typedef struct{
   // by making alt 24 bit we can make p1 in a command 16 bit,
    // allowing an accurate angle in centi-degrees. This keeps the
    // storage cost per mission item at 15 bytes, and allows mission
    // altitudes of up to +/- 83km
    int32_t alt:24; ///< param 2 - Altitude in centimeters (meters * 100)
    int32_t lat;    ///< param 3 - Lattitude * 10**7
    int32_t lng;    ///< param 4 - Longitude * 10**7
}Location;

extern SINS NamelessQuad,Origion_NamelessQuad;
extern float Body_Frame_To_XYZ[3];
extern Vector2f SINS_Accel_Body;
extern Vector2i GPSData_To_XY_Home;//经、纬度

extern SINS FilterBefore_NamelessQuad,FilterAfter_NamelessQuad,Filter_Feedback_NamelessQuad;
extern float Sin_Pitch,Sin_Roll,Sin_Yaw;
extern float Cos_Pitch,Cos_Roll,Cos_Yaw;
extern uint8 GPS_Home_Set;
extern float pos_correction[3];
extern float acc_correction[3];
extern float vel_correction[3];
extern float Altitude_Estimate;
extern float Sin_Pitch,Sin_Roll,Sin_Yaw;
extern float Cos_Pitch,Cos_Roll,Cos_Yaw;
extern float Baro_Climbrate;
extern float Acceleration_Length;
extern Vector2f SINS_Accel_Body;
extern Vector3_Nav Earth_Frame_To_XYZ;

float constrain_float(float amt, float low, float high);
void  GPSData_Sort(void);
void  Set_GPS_Home(void);
void  SINS_Prepare(void);
void  Strapdown_INS_High(void);
void  Strapdown_INS_Horizontal(void);
void Strapdown_INS_High_Kalman(void);
void Strapdown_INS_Reset(SINS *Ins,uint8_t Axis,float Pos_Target,float Vel_Target);
void  KalmanFilter(float Observation,//位置观测量
                    uint16 Pos_Delay_Cnt,//观测传感器延时量
                    SINS *Ins_Kf,//惯导结构体
                    float System_drive,//系统原始驱动量，惯导加速度
                    float *R,
                    float Q,
                    float dt,
                    uint16 N);
void Filter_Horizontal(void);
#endif
