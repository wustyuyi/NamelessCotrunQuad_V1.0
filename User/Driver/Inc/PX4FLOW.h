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
#ifndef _PX4FLOW_H
#define _PX4FLOW_H

#define PX4FLOW_ADDR        0x42         //������ַ
//�Ĵ����궨�壬�����2�ֽ�һ�����ݵ�ַָ�ĵ��ֽ�λ�����ֽ��ǵ��ֽڵ�ַ��һλ�����������������������  ����ժ�Թ���
//�����ֵ�����
//��¼�ܵĴ�����iic֡��
#define FRAME_COUNT_SUM     0x00
//uint16_t counts created I2C frames [frames]//X������һ֡���������ƶ���*10
#define PIXEL_FLOW_X_SUM    0x02                    //int16_t latest x flow measurement in pixels*10 [pixels]//Y������һ֡���������ƶ���*10
#define PIXEL_FLOW_Y_SUM    0x04                    //int16_t latest y flow measurement in pixels*10 [pixels]//X���ٶ�
#define FLOW_COMP_M_X       0x06                    //int16_t x velocity*1000 [meters/sec]//Y���ٶ�
#define FLOW_COMP_M_Y       0x08                    //int16_t y velocity*1000 [meters/sec]//����ͼ������
#define QUAL                0x0a                    //int16_t Optical flow quality / confidence [0: bad, 255: maximum quality]//X���������ٶ�
#define GYRO_X_RATE         0x0c                    //int16_t latest gyro x rate [rad/sec]//Y���������ٶ�
#define GYRO_Y_RATE         0x0e                   //int16_t latest gyro y rate [rad/sec]//Z���������ٶ�
#define GYRO_Z_RATE         0x10                    //int16_t latest gyro z rate [rad/sec]//���������ݷ�Χ
#define GYRO_RANGE          0x12                    //uint8_t gyro range [0 .. 7] equals [50 deg/sec .. 2000 deg/sec]
//�����������ϴθ���ʱ�䵽���ڵ�ʱ����
#define SONAR_TIMESTAMP1    0x13                    //uint8_t time since last sonar update [milliseconds] //�������  ��ֵ����֪���룬  ��ֵ��δ֪����
#define GROUND_DISTANCE1    0x14                   //int16_t Ground distance in meters*1000 [meters]. Positive value: distance known. //Negative value: Unknown distance
//���ֺ�����ݵ�ַ
//�ϴζ�ȡ���ݺ����ݸ����˶��ٴ�
#define FRAME_COUNT_SINCE_LAST_READOUT  0x16        //uint16_t number of flow measurements since last I2C readout [frames]//���ϴζ�ȡiic���ݺ� X���ٶȻ��ֺ�����ֵ
#define PIXEL_FLOW_X_INTEGRAL           0x18       //int16_t  accumulated flow in radians*10000 around x axis since last I2C readout [rad*10000]//���ϴζ�ȡiic���ݺ� Y���ٶȻ��ֺ�����ֵ
#define PIXEL_FLOW_Y_INTEGRAL           0x1a        //int16_t  accumulated flow in radians*10000 around y axis since last I2C readout [rad*10000]//���ϴζ�ȡiic���ݺ�X����ٶȻ���ֵ
#define GYRO_X_RATE_INTEGRAL            0x1c        //int16_t  accumulated gyro x rates in radians*10000 since last I2C readout [rad*10000]  //���ϴζ�ȡiic���ݺ�Y����ٶȻ���ֵ
#define GYRO_Y_RATE_INTEGRAL            0x1e        //int16_t  accumulated gyro y rates in radians*10000 since last I2C readout [rad*10000] //���ϴζ�ȡiic���ݺ�Z����ٶȻ���ֵ
#define GYRO_Z_RATE_INTEGRAL            0x20        //int16_t  accumulated gyro z rates in radians*10000 since last I2C readout [rad*10000]//�ϴκ���ζ�ȡiic���ݵ�ʱ����
#define INTEGRATION_TIMESPAN            0x22        //uint32_t accumulation timespan in microseconds since last I2C readout [microseconds]//�����������ϴθ���ʱ�䵽���ڵ�ʱ����
#define SONAR_TIMESTAMP2                0x26        //uint32_t time since last sonar update [microseconds]//�������
#define GROUND_DISTANCE2                0x2a        //int16_t  Ground distance in meters*1000 [meters*1000]//�������¶�
#define GYRO_TEMPERATURE                0x2c        //int16_t  Temperature * 100 in centi-degrees Celsius [degcelsius*100] //����������������
#define QUALITY                         0x2e        //uint8_t averaged quality of accumulated flow values [0:bad quality;255: max quality]//��ָ���Ĵ���ָ���ֽ�������
typedef struct
{
  uint16_t frame_count;// counts created I2C frames [#frames]
  int16_t pixel_flow_x_sum;// latest x flow measurement in pixels*10 [pixels]
  int16_t pixel_flow_y_sum;// latest y flow measurement in pixels*10 [pixels]
  int16_t flow_comp_m_x;// x velocity*1000 [meters/sec]
  int16_t flow_comp_m_y;// y velocity*1000 [meters/sec]
  int16_t qual;// Optical flow quality / confidence [0: bad, 255: maximum quality]
  int16_t gyro_x_rate; // latest gyro x rate [rad/sec]
  int16_t gyro_y_rate; // latest gyro y rate [rad/sec]
  int16_t gyro_z_rate; // latest gyro z rate [rad/sec]
  uint8_t gyro_range; // gyro range [0 .. 7] equals [50 deg/sec .. 2000 deg/sec]
  uint8_t sonar_timestamp;// time since last sonar update [milliseconds]
  int16_t ground_distance;// Ground distance in meters*1000 [meters]. Positive value: distance known. Negative value: Unknown distance
} i2c_frame;
typedef struct
{
  uint16_t frame_count_since_last_readout;//number of flow measurements since last I2C readout [#frames]
  int16_t pixel_flow_x_integral;//accumulated flow in radians*10000 around x axis since last I2C readout [rad*10000]
  int16_t pixel_flow_y_integral;//accumulated flow in radians*10000 around y axis since last I2C readout [rad*10000]
  int16_t gyro_x_rate_integral;//accumulated gyro x rates in radians*10000 since last I2C readout [rad*10000]
  int16_t gyro_y_rate_integral;//accumulated gyro y rates in radians*10000 since last I2C readout [rad*10000]
  int16_t gyro_z_rate_integral;//accumulated gyro z rates in radians*10000 since last I2C readout [rad*10000]
  uint32_t integration_timespan;//accumulation timespan in microseconds since last I2C readout [microseconds]
  uint32_t sonar_timestamp;// time since last sonar update [microseconds]
  int16_t ground_distance;// Ground distance in meters*1000 [meters*1000]
  int16_t gyro_temperature;// Temperature * 100 in centi-degrees Celsius [degcelsius*100]
  uint8_t quality;// averaged quality of accumulated flow values [0:bad quality;255: max quality]
} i2c_integral_frame;

u8 IIC_Read_nByte(u8 SlaveAddress, u8 REG_Address, u8 len, u8 *buf);
void PX4_State_Machine_Capture(void);
void PX4_Capture(void);


void OPTICAL_FLOW(void);
void Read_CalibrationData(void);
void BMP180_StateMachine(void);

extern float true_Press;      //ʵ����ѹ,��λ:Pa
extern float true_Temp,true_Altitude;   //ʵ�ʸ߶�,��λ:m


extern uint16 PX4FLOW_Update_Flag;
extern float  PX4FLOW_Data_LPF[3];
extern i2c_frame PX4FLOW_Origion;
extern float PX4FLOW_Vel_North,PX4FLOW_Vel_East,PX4FLOW_Pos_North,PX4FLOW_Pos_East;
#endif

