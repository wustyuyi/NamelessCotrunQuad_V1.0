#ifndef _FLIGHT_CONTROL_FAULT_H_
#define _FLIGHT_CONTROL_FAULT_H_

typedef struct
{
  uint8_t Low_Voltage_Fault_Flag;//�͵�ѹ����
  uint8_t Compass_Fault_Flag;    //�����ƴ���������
  uint8_t Accel_Fault_Flag;      //���ٶȼƴ���������
  uint8_t Gyro_Fault_Flag;       //�����Ǵ���������
  uint8_t Baro_Fault_Flag;       //��ѹ�ƴ���������
  uint8_t Ultrasonic_Fault_Flag; //����������������
  uint8_t Opticalflow_Fault_Flag;//��������������
}Flight_Control_Fault_State;


void Flight_Control_Fault_ALL(void);
extern Flight_Control_Fault_State  State_Breakdown;
extern  float Battery_Valtage;
extern Vector3f Accel,Gyro,Compass;
#endif

