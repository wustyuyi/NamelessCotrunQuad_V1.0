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
#ifndef __SINS_H
#define __SINS_H

#define Axis_Num  3
#define Num  50
typedef struct
{
 float Position[Axis_Num];//λ�ù�����
 float Speed[Axis_Num];//�ٶȹ�����
 float Acceleration[Axis_Num];//���ٶȹ�����
 float Pos_History[Axis_Num][Num];//��ʷ�ߵ�λ��
 float Vel_History[Axis_Num][Num];//��ʷ�ߵ��ٶ�
 float Acce_Bias[Axis_Num];//�ߵ����ٶ�Ư����������
 float Last_Acceleration[Axis_Num];
 float Last_Speed[Axis_Num];
}SINS;


#define AcceMax     4096  //   4096
#define AcceGravity 9.80f
/*************WGS84��������ο�ϵ��**************/
#define WGS84_RADIUS_EQUATOR        6378137.0f//�볤�ᣬ��λm
#define WGS84_INVERSE_FLATTENING    298.257223563f//����
#define WGS84_FLATTENING            (1/WGS84_INVERSE_FLATTENING)//���ʵ���
#define WGS84_RADIUS_POLAR          (WGS84_RADIUS_EQUATOR*(1-WGS84_FLATTENING))//����
#define WGS84_ECCENTRICITY_SQUARED  (2*WGS84_FLATTENING-WGS84_FLATTENING*WGS84_FLATTENING)
/*********************************************
���ȷ�����룺LON_TO_CM*���ȲLON_TO_CM��Ӧ�人��������γ��ƽ��Բ�ܳ�
γ�ȷ�����룺LAT_TO_CM*γ�Ȳ
*********************************************/

#define LON_COSINE_LOCAL 0.860460f//Լ���ڵ���γ�ȵ�����ֵ��cos(Lat*DEG_TO_RAD)
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

// radius of earth in meters
#define RADIUS_OF_EARTH 6378100
// scaling factor from 1e-7 degrees to meters at equater
// == 1.0e-7 * DEG_TO_RAD * RADIUS_OF_EARTH
#define LOCATION_SCALING_FACTOR 0.011131884502145034f
// inverse of LOCATION_SCALING_FACTOR
#define LOCATION_SCALING_FACTOR_INV 89.83204953368922f



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
extern Vector2i GPSData_To_XY_Home;//����γ��

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
extern uint8_t Filter_Defeated_Flag;
extern Location GPS_Home;//��ʼ��λ�ɹ�����Ϣ
extern Location GPS_Present;//��ǰλ�õ���Ϣ
extern float Acce_History[3][100];
extern float Declination;//�����ƫ��

float pythagorous2(float a, float b);
float longitude_scale(Location loc);
float constrain_float(float amt, float low, float high);
int16_t constrain_int16_t(int16_t amt, int16_t low, int16_t high);
void Observation_Tradeoff(uint8_t HC_SR04_Enable);
void  GPSData_Sort(void);
void  Set_GPS_Home(void);
void  SINS_Prepare(void);
void  Strapdown_INS_High(void);
void  Strapdown_INS_Horizontal(void);
void Strapdown_INS_High_Kalman(void);
void Strapdown_INS_Reset(SINS *Ins,uint8_t Axis,float Pos_Target,float Vel_Target);
void  KalmanFilter(float Observation,//λ�ù۲���
                    uint16 Pos_Delay_Cnt,//�۲⴫������ʱ��
                    SINS *Ins_Kf,//�ߵ��ṹ��
                    float System_drive,//ϵͳԭʼ���������ߵ����ٶ�
                    float *R,
                    float Q,
                    float dt,
                    uint16 N,
                    uint8_t update_flag);
void Filter_Horizontal(void);
float get_distance(Location loc1,Location loc2);
#endif
