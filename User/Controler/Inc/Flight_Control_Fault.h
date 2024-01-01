#ifndef _FLIGHT_CONTROL_FAULT_H_
#define _FLIGHT_CONTROL_FAULT_H_

typedef struct
{
  uint8_t Low_Voltage_Fault_Flag;//低电压故障
  uint8_t Compass_Fault_Flag;    //磁力计传感器故障
  uint8_t Accel_Fault_Flag;      //加速度计传感器故障
  uint8_t Gyro_Fault_Flag;       //陀螺仪传感器故障
  uint8_t Baro_Fault_Flag;       //气压计传感器故障
  uint8_t Ultrasonic_Fault_Flag; //超声波传感器故障
  uint8_t Opticalflow_Fault_Flag;//光流传感器故障
}Flight_Control_Fault_State;


void Flight_Control_Fault_ALL(void);
extern Flight_Control_Fault_State  State_Breakdown;
extern  float Battery_Valtage;
extern Vector3f Accel,Gyro,Compass;
#endif

