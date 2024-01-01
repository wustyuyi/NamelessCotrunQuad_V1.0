#ifndef _up_flow_H
#define _up_flow_H
//#include "stm32f4xx.h"
//#include "ms5611.h"
void Flow_Init(void);
void Flow_Duty(float dT);
//void Flow_Get(u8);
extern struct flow_float flow_dat;
extern float exp_rol_flow,exp_pit_flow;


struct flow_integral_frame {
  unsigned short frame_count_since_last_readout;
  signed short pixel_flow_x_integral;
  signed short pixel_flow_y_integral;
  signed short gyro_x_rate_integral;
  signed short gyro_y_rate_integral;
  signed short gyro_z_rate_integral;
  unsigned int integration_timespan;
  unsigned int sonar_timestamp;
  unsigned short ground_distance;
  signed short gyro_temperature;
  unsigned char qual;
};

struct flow_float{
  float x;
  float y;
  unsigned short dt;
  unsigned char qual;
  unsigned char update;
};

#endif