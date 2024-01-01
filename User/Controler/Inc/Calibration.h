#ifndef _CALIBRATION_H
#define _CALIBRATION_H
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


#define AcceMax_1G      4096
#define GRAVITY_MSS     9.80665f
#define ACCEL_TO_1G     (GRAVITY_MSS/AcceMax_1G)
#define One_G_TO_Accel  (AcceMax_1G/GRAVITY_MSS)


typedef struct
{
 float x;
 float y;
 float z;
}Acce_Unit;

typedef struct
{
 float x;
 float y;
 float z;
}Mag_Unit;


typedef struct {
    int16_t x_max;
    int16_t y_max;
    int16_t z_max;
    int16_t x_min;
    int16_t y_min;
    int16_t z_min;
    float x_offset;
    float y_offset;
    float z_offset;
}Calibration;

void Calibrationer(void);
void Accel_Calibration_Check(void);
uint8_t Accel_Calibartion(void);
bool Parameter_Init(void);
void Mag_Calibration_Check(void);
uint8_t Mag_Calibartion(Mag_Unit MagData,Vector3f_Body Circle_Angle_Calibartion);
void Reset_Mag_Calibartion(uint8_t Type);
void Reset_Accel_Calibartion(uint8_t Type);

void Mag_LS_Init(void);
uint8_t Mag_Calibartion_LS(Mag_Unit MagData,Vector3f_Body Circle_Angle_Calibartion);

uint8_t Gyro_Calibration_Check(Vector3f *gyro);
void RC_Calibration_Trigger(void);
bool RC_Calibration_Check(uint16 *rc_date);
void ESC_HardWave_Init(void);//ֻ��ʼ��У׼����ı�Ҫ��Դ
void ESC_Calibration_Check(void);
uint8_t Check_Calibration_Flag(void);
void Reset_RC_Calibartion(uint8_t Type);
void Horizontal_Calibration_Check(void);
void Horizontal_Calibration_Init(void);
void Headless_Mode_Calibration_Check(void);


void Other_Parameter_Init(void);
void Other_Parameter_Default(void);


extern Acce_Unit acce_sample[6];
extern uint8_t  Mag_Calibration_Mode;
extern uint8_t flight_direction;
extern Acce_Unit Accel_Offset_Read,Accel_Scale_Read;
extern Mag_Unit DataMag;
extern Mag_Unit Mag_Offset_Read;
extern Calibration Mag;
extern uint8_t Mag_360_Flag[3][36];
extern uint16_t Mag_Is_Okay_Flag[3];
extern float Yaw_Correct;
extern Vector2f MagN;
extern float Mag_Offset[3];
extern float Mag_Data[3];
extern float HMC5883L_Yaw;
extern Vector_RC  RC_Calibration[8];
extern float Hor_Accel_Offset[3];
extern float mag_a,mag_b,mag_c,mag_r;
extern float ESC_Calibration_Flag;
extern float Pitch_Offset,Roll_Offset;
extern float Headless_Mode_Yaw;

extern uint8_t Gyro_Safety_Calibration_Flag;
extern uint16_t Target_Height,Safe_Height,Safe_Vbat,Max_Height,Max_Radius,Max_Upvel,Max_Downvel,Max_Horvel;
#endif

