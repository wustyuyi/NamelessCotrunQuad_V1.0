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
#ifndef _PX4FLOW_H
#define _PX4FLOW_H

#define PX4FLOW_ADDR        0x42         //器件地址
//寄存器宏定义，如果是2字节一个数据地址指的低字节位，高字节是低字节地址后一位，组合起来就是完整的数据  解释摘自官网
//不积分的数据
//记录总的创建的iic帧数
#define FRAME_COUNT_SUM     0x00
//uint16_t counts created I2C frames [frames]//X轴最新一帧所有像素移动和*10
#define PIXEL_FLOW_X_SUM    0x02                    //int16_t latest x flow measurement in pixels*10 [pixels]//Y轴最新一帧所有像素移动和*10
#define PIXEL_FLOW_Y_SUM    0x04                    //int16_t latest y flow measurement in pixels*10 [pixels]//X轴速度
#define FLOW_COMP_M_X       0x06                    //int16_t x velocity*1000 [meters/sec]//Y轴速度
#define FLOW_COMP_M_Y       0x08                    //int16_t y velocity*1000 [meters/sec]//光流图像质量
#define QUAL                0x0a                    //int16_t Optical flow quality / confidence [0: bad, 255: maximum quality]//X轴陀螺仪速度
#define GYRO_X_RATE         0x0c                    //int16_t latest gyro x rate [rad/sec]//Y轴陀螺仪速度
#define GYRO_Y_RATE         0x0e                   //int16_t latest gyro y rate [rad/sec]//Z轴陀螺仪速度
#define GYRO_Z_RATE         0x10                    //int16_t latest gyro z rate [rad/sec]//陀螺仪数据范围
#define GYRO_RANGE          0x12                    //uint8_t gyro range [0 .. 7] equals [50 deg/sec .. 2000 deg/sec]
//超声波数据上次更新时间到现在的时间间隔
#define SONAR_TIMESTAMP1    0x13                    //uint8_t time since last sonar update [milliseconds] //地面距离  正值：已知距离，  负值：未知距离
#define GROUND_DISTANCE1    0x14                   //int16_t Ground distance in meters*1000 [meters]. Positive value: distance known. //Negative value: Unknown distance
//积分后的数据地址
//上次读取数据后数据更新了多少次
#define FRAME_COUNT_SINCE_LAST_READOUT  0x16        //uint16_t number of flow measurements since last I2C readout [frames]//自上次读取iic数据后 X轴速度积分后所得值
#define PIXEL_FLOW_X_INTEGRAL           0x18       //int16_t  accumulated flow in radians*10000 around x axis since last I2C readout [rad*10000]//自上次读取iic数据后 Y轴速度积分后所得值
#define PIXEL_FLOW_Y_INTEGRAL           0x1a        //int16_t  accumulated flow in radians*10000 around y axis since last I2C readout [rad*10000]//自上次读取iic数据后，X轴角速度积分值
#define GYRO_X_RATE_INTEGRAL            0x1c        //int16_t  accumulated gyro x rates in radians*10000 since last I2C readout [rad*10000]  //自上次读取iic数据后，Y轴角速度积分值
#define GYRO_Y_RATE_INTEGRAL            0x1e        //int16_t  accumulated gyro y rates in radians*10000 since last I2C readout [rad*10000] //自上次读取iic数据后，Z轴角速度积分值
#define GYRO_Z_RATE_INTEGRAL            0x20        //int16_t  accumulated gyro z rates in radians*10000 since last I2C readout [rad*10000]//上次和这次读取iic数据的时间间隔
#define INTEGRATION_TIMESPAN            0x22        //uint32_t accumulation timespan in microseconds since last I2C readout [microseconds]//超声波数据上次更新时间到现在的时间间隔
#define SONAR_TIMESTAMP2                0x26        //uint32_t time since last sonar update [microseconds]//地面距离
#define GROUND_DISTANCE2                0x2a        //int16_t  Ground distance in meters*1000 [meters*1000]//陀螺仪温度
#define GYRO_TEMPERATURE                0x2c        //int16_t  Temperature * 100 in centi-degrees Celsius [degcelsius*100] //光流积分数据质量
#define QUALITY                         0x2e        //uint8_t averaged quality of accumulated flow values [0:bad quality;255: max quality]//读指定寄存器指定字节数数据
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

extern float true_Press;      //实际气压,单位:Pa
extern float true_Temp,true_Altitude;   //实际高度,单位:m


extern uint16 PX4FLOW_Update_Flag;
extern float  PX4FLOW_Data_LPF[3];
extern i2c_frame PX4FLOW_Origion;
extern float PX4FLOW_Vel_North,PX4FLOW_Vel_East,PX4FLOW_Pos_North,PX4FLOW_Pos_East;
#endif

